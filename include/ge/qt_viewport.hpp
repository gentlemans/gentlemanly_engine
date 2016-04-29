#pragma once

#include "ge/concept/viewport.hpp"

#include <glm/glm.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <memory>

#include <anax/World.hpp>


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

	void render(const model_system& models, const camera_component& camera);

};
BOOST_CONCEPT_ASSERT((concept::Viewport<qt_viewport>));

}  // namespace ge
