#include "ge/window_backend/qt_window.hpp"
#include "ge/window_backend/qt.hpp"

#include "ge/application.hpp"

namespace ge {
namespace window_backend {

qt_window::qt_window(qt& app, const char* title, boost::optional<glm::uvec2> loc, glm::uvec2 size, bool fullscreen, bool decorated)
	:qt_inst(app)
{
	setWindowTitle(QLatin1String(title));
	
	setFixedSize(size.x, size.y);
	
	if (fullscreen) showFullScreen();
	if (!decorated) setWindowFlags(Qt::CustomizeWindowHint);
	
	show();
	
	connect(&qt_inst.qt_app, &QApplication::aboutToQuit, [this] {
		sig_quit();
	});
	
}


qt_window::~qt_window()
{
	
}

} // namespace window_backend
} // namespace ge



