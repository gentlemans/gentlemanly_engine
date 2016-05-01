
#include "ge/qt_application.hpp"

#include <iostream>

namespace ge
{
qt_application::qt_application(int& argc, char** argv) : qt_app(argc, argv) {}
void qt_application::execute(window&) { qt_app.exec(); }
}  // namespace ge
