
#include "ge/window_backend/qt.hpp"

#include <iostream>

namespace ge {
namespace window_backend {

qt::qt(application<qt>& _app, int& argc, char** argv)
	:qt_app(argc, argv),
	app(_app)
{
	app.update.connect([this]
		{
			qt_app.processEvents();
		}
	);
}


} // namespace ge
} // namespace window_backend
