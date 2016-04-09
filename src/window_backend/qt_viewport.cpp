#include "ge/window_backend/qt_viewport.hpp"

#include "ge/window_backend/qt_window.hpp"
#include "ge/window_backend/qt.hpp"

namespace ge  {
namespace window_backend {

qt_viewport::qt_viewport(qt& backend, qt_window& window)
	:QOpenGLWidget(&window)
{
	
}

void qt_viewport::initializeGL()
{
	initializeOpenGLFunctions();
}

} // namespace window_backend
} // namespace ge

