#pragma once

#include <glm/glm.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace ge {
namespace window_backend {

class qt;
class qt_window;

class qt_viewport : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	qt_viewport(qt& backend, qt_window& window);
	
	void initializeGL() override;
};

} // namespace window_backend
} // namespace ge
