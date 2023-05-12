#pragma once

#include "OpenGLWindow.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>
#include <Transform.h>

class Scene
{
public:
	Scene(OpenGLWindow* window);
	~Scene();

	bool init();
	void shutdown();
	void render(float dt);
	void update(float dt);
    float x = 0.0;
    float t;
	OpenGLWindow* getWindow();
    Transform *robot = new Transform;
    Transform *body = new Transform;
    Transform *head = new Transform;
    Transform *armRight = new Transform;
    Transform *armUpperRight = new Transform;
    Transform *armLowerRight = new Transform;
    Transform *armLeft = new Transform;
    Transform *armUpperLeft = new Transform;
    Transform *armLowerLeft = new Transform;
    Transform *legRight = new Transform;
    Transform *legLeft = new Transform;

	void onKey(Key key, Action action, Modifier modifier);
	void onMouseMove(MousePosition mouseposition);
	void onMouseButton(MouseButton button, Action action, Modifier modifier);
	void onMouseScroll(double xscroll, double yscroll);
	void onFrameBufferResize(int width, int height);

private:
	OpenGLWindow* m_window;
	AssetManager m_assets;
    ShaderProgram* m_shader;
    GLuint vaoID, vboID, iboID;

};

