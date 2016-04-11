#include "ge/window_backend/qt_viewport.hpp"

#include "ge/window_backend/qt_window.hpp"
#include "ge/window_backend/qt.hpp"

#include <GL/gl.h>

#include <iostream>

#include <QSurfaceFormat>
#include <QSurface>

namespace ge  {
namespace window_backend {

qt_viewport::qt_viewport(qt& backend, qt_window& window)
	:QOpenGLWidget(&window),
	m_window(window)
{
	std::cout << "INit" << std::endl;
	
	window.setCentralWidget(this);
	
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	setFormat(format);
}

void qt_viewport::initializeGL()
{
	m_window.qt_inst.app.init();
	

}

void qt_viewport::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_window.qt_inst.app.update();
	
}

void qt_viewport::resizeGL(int w, int h)
{
	
}

void qt_viewport::set_background_color(const glm::vec4 newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}



} // namespace window_backend
} // namespace ge

