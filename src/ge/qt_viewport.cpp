#include "ge/qt_viewport.hpp"
#include "ge/qt_window.hpp"
#include "ge/qt_application.hpp"
#include "ge/camera_component.hpp"
#include "ge/model_system.hpp"

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
qt_viewport::qt_viewport(qt_application& backend, qt_window& window)
	: QOpenGLWidget(&window), m_window(&window)
{
	window.setCentralWidget(this);

	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	setFormat(format);
}

void qt_viewport::initializeGL() { m_window->qt_inst.signal_init(); }
void qt_viewport::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static auto last_tick = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();

	std::chrono::duration<float> diff = now - last_tick;

	last_tick = now;

	m_window->qt_inst.signal_update(diff.count());
	
	update();
}

void qt_viewport::resizeGL(int w, int h) {}
void qt_viewport::set_background_color(const glm::vec4 newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

void qt_viewport::render(const model_system& models, const camera_component& camera)
{
	float aspect = (float)m_window->get_size().x / (float)m_window->get_size().y;

	glm::mat3 projection = glm::ortho2d(-aspect * camera.vertical_units,
		aspect * camera.vertical_units, -camera.vertical_units, camera.vertical_units);
	glm::mat3 vp = projection; // TODO:  * camera.calculate_model_matrix();
	
	for(auto& ent : models.entities)
	{
		ent.getComponent<model_component>().render(vp);
	}
}

}  // namespace ge
