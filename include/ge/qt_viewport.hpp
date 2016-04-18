#pragma once

#include <glm/glm.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <memory>

#include "ge/concept/viewport.hpp"

namespace ge
{
class world;
class camera_actor;

class qt_application;
class qt_window;

class qt_viewport : public QOpenGLWidget
{
	qt_window& m_window;

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

	camera_actor* m_camera = nullptr;

	std::unique_ptr<world> m_world;

public:
	qt_viewport(qt_application& backend, qt_window& window);

	void set_background_color(const glm::vec4 newColor);

	void render();

	camera_actor& get_camera() const { return *m_camera; }
	void set_camera(camera_actor& new_camera) { m_camera = &new_camera; }
	world& get_world() const { return *m_world; }
	void set_world(std::unique_ptr<world>&& new_world) { m_world = std::move(new_world); }
};
BOOST_CONCEPT_ASSERT((concept::Viewport<qt_viewport>));

}  // namespace ge
