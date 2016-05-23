#pragma once

#include <entityx/entityx.h>

#include "ge/concept/viewport.hpp"

#include <glm/glm.hpp>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include <memory>

namespace ge
{
class qt_application;
class qt_window;
class camera_component;

class qt_viewport : public QOpenGLWidget
{
	qt_window* m_window;

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

public:
	qt_viewport(qt_application& backend, qt_window& window);

	void set_background_color(const glm::vec4 newColor);

	qt_window& get_window() const { return *m_window; }
};
BOOST_CONCEPT_ASSERT((concept::Viewport<qt_viewport>));

}  // namespace ge
