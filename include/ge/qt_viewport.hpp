#pragma once

#include <glm/glm.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <memory>

namespace ge
{
class world;
class camera;

class qt_application;
class qt_window;

class qt_viewport : public QOpenGLWidget
{
	qt_window& m_window;

	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;

	camera* m_camera = nullptr;

	std::unique_ptr<world> m_world;

public:
	qt_viewport(qt_application& backend, qt_window& window);

	void set_background_color(const glm::vec4 newColor);

	void render();

	camera& get_camera() const { return *m_camera; }
	void set_camera(camera& new_camera) { m_camera = &new_camera; }
	world& get_world() const { return *m_world; }
	void set_world(std::unique_ptr<world>&& new_world) { m_world = std::move(new_world); }

};

}  // namespace ge
