#include "ge/window_backend/qt_viewport.hpp"

#include "ge/window_backend/qt_window.hpp"
#include "ge/window_backend/qt.hpp"

#include "ge/actor.hpp"
#include "ge/camera.hpp"

#include "ge/ortho2d.hpp"

#include <GL/gl.h>

#include <iostream>
#include <stdexcept>

#include <QSurfaceFormat>
#include <QSurface>

#include <glm/gtx/matrix_transform_2d.hpp>

namespace ge
{
namespace window_backend
{
qt_viewport::qt_viewport(qt& backend, qt_window& window) : QOpenGLWidget(&window), m_window(window)
{
	window.setCentralWidget(this);

	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	setFormat(format);
	
	root = new actor(nullptr);
}

void qt_viewport::initializeGL() { m_window.qt_inst.app.init(); }
void qt_viewport::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_window.qt_inst.app.update();
}

void qt_viewport::resizeGL(int w, int h) {}
void qt_viewport::set_background_color(const glm::vec4 newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

void qt_viewport::render()
{
	if (!current_camera) throw std::runtime_error("Cannot call render_actor with a null camera");

	float aspect = (float)width() / (float)height();

	glm::mat3 projection = glm::ortho2d(
		-aspect * current_camera->vertical_units, aspect * current_camera->vertical_units,
		-current_camera->vertical_units, current_camera->vertical_units);
	glm::mat3 vp = projection * current_camera->calculate_model_matrix();

	root->render_tree(vp);
}

void qt_viewport::set_camera(ge::camera* camera) { current_camera = camera; }
ge::camera* qt_viewport::get_camera() const { return current_camera; }
}  // namespace window_backend
}  // namespace ge
