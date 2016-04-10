#pragma once

#include <glm/glm.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace ge {
namespace window_backend {

class qt;
class qt_window;

class qt_viewport : public QOpenGLWidget
{
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
public:
	qt_viewport(qt& backend, qt_window& window);
	
	void set_background_color(const glm::vec4 newColor);
	
	
};

} // namespace window_backend
} // namespace ge
