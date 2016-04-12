#pragma once

#include <glm/glm.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

namespace ge {

class actor;
class camera;

namespace window_backend {

class qt;
class qt_window;

class qt_viewport : public QOpenGLWidget
{
	qt_window& m_window;
	
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	
	camera* current_camera = nullptr;
	
public:
	qt_viewport(qt& backend, qt_window& window);
	
	void set_background_color(const glm::vec4 newColor);
	
	void render_actor(actor* actor);
	
	void set_camera(camera* camera);
	camera* get_camera() const;
	
	
};

} // namespace window_backend
} // namespace ge
