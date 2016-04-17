#include "ge/qt_viewport.hpp"
#include "ge/qt_window.hpp"
#include "ge/qt_application.hpp"
#include "ge/world.hpp"
#include "ge/actor.hpp"
#include "ge/camera.hpp"

#include "ge/ortho2d.hpp"

#include <GL/gl.h>

#include <iostream>
#include <stdexcept>
#include <chrono>

#include <QSurfaceFormat>
#include <QSurface>

#include <glm/gtx/matrix_transform_2d.hpp>

namespace ge
{
qt_viewport::qt_viewport(qt_application& backend, qt_window& window) : QOpenGLWidget(&window), m_window(window)
{
	window.setCentralWidget(this);

	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	setFormat(format);
}

void qt_viewport::initializeGL() { m_window.qt_inst.signal_init(); }
void qt_viewport::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static auto last_tick = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();
	
	std::chrono::duration<float> diff =  now - last_tick;
	
	last_tick = now;
	
	m_window.qt_inst.signal_update(diff.count());
}

void qt_viewport::resizeGL(int w, int h) {}
void qt_viewport::set_background_color(const glm::vec4 newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

void qt_viewport::render()
{
	if (!m_camera) throw std::runtime_error("Cannot call render_actor with a null camera");
	if (!m_world) throw std::runtime_error("Cannot call render_actor with a null world");

	float aspect = (float)width() / (float)height();

	glm::mat3 projection = glm::ortho2d(-aspect * m_camera->vertical_units,
		aspect * m_camera->vertical_units, -m_camera->vertical_units,
		m_camera->vertical_units);
	glm::mat3 vp = projection * m_camera->calculate_model_matrix();

	
	m_world->for_each_actor([&vp](actor* actor_to_render) {
		actor_to_render->render(vp);
	});
}

}  // namespace ge
