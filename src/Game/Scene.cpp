#include "Scene.h"
#include <AssetManager.h>

Scene::Scene(OpenGLWindow * window) :
	m_window(window)
{
	assert(window != nullptr);
}

Scene::~Scene()
{}

bool Scene::init()
{
	try
	{
		//Load shader
		m_assets.addShaderProgram("shader", AssetManager::createShaderProgram("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"));
		m_shader = m_assets.getShaderProgram("shader");
        m_shader->use();
        float vertices[] = {-0.5, -0.5,0.0, 0.0, 1.0,
                            0.5, -0.5,0.0, 0.0, 1.0,
                            0.5, 0.5, 0.0, 1.0, 0.0,
                            0.0, 1.0,1.0, 0.0, 0.0,
                            -0.5, 0.5, 0.0, 1.0, 0.0};

        float vertices2[] = {-1.0, 1.0,1.0,1.0,0.0,
                             -0.2,1.0,0.0,1.0,0.0,
                             -0.2,0.8,0.0,1.0,1.0,
                             -0.8,0.8,0.0,1.0,0.0,
                             -0.8,0.1,0.0,1.0,0.0,
                             -0.4,0.1,0.0,1.0,0.0,
                             -0.4,-0.1,0.0,1.0,1.0,
                             -0.8,-0.1,0.0,1.0, 0.0,
                             -0.8,-1.0,1.0,1.0,0.0,
                             -1.0,-1.0,0.0,1.0,1.0,
                             -1.0,0.8,0.0,1.0,0.0,
                             //S
                             0.2,1.0,0.0,1.0,0.0,
                             1.0,1.0,0.0,1.0,0.0,
                             0.2,0.8,0.0,1.0,0.0,
                             1.0,0.8,0.0,1.0,0.0,
                             0.4,0.8,0.0,1.0,0.0,
                             0.2,0.1,1.0,1.0,0.0,
                             0.4,0.1,0.0,1.0,0.0,
                             1.0,0.1,0.0,1.0,0.0,
                             1.0,-0.1,0.0,1.0,1.0,
                             0.2,-0.1,0.0,1.0,0.0,
                             0.8,-0.8,0.0,1.0,0.0,
                             0.8,-0.1,0.0,1.0,0.0,
                             1.0,-0.8,1.0,1.0,0.0,
                             0.2,-0.8,0.0,1.0,0.0,
                             1.0,-1.0,0.0,1.0,0.0,
                             0.2,-1.0,0.0,1.0,1.0,};

        float cubeVert[] = {0.5, -0.5, -0.5, 1, 0, 0,
                        0.5, -0.5, 0.5, 0, 1, 0,
                        -0.5, -0.5, 0.5, 0, 0, 1,
                        -0.5, -0.5, -0.5, 1, 1, 0,
                        0.5, 0.5, -0.5, 1, 0, 1,
                        0.5, 0.5, 0.5, 0, 1, 1,
                        -0.5, 0.5, 0.5, 1, 1, 1,
                        -0.5, 0.5, -0.5, 0.5, 1, 0.5};

        int indices[] = {0, 1, 2,
                         0, 2, 4,
                         4, 2, 3};

        int indices2[] = {0,2,1,
                          0,10,2,
                          8,10,9,
                          3,10,8,
                          4,6,5,
                          4,7,6,
                          //S
                          11,13,12,
                          14,12,13,
                          15,13,16,
                          16,17,15,
                          16,19,18,
                          16,20,19,
                          21,19,22,
                          19,21,23,
                          24,25,23,
                          24,26,25};

        static const int cubeInd[] = {1, 2, 3,
                                      7, 6, 5,
                                      4, 5, 1,
                                      5, 6, 2,
                                      2, 6, 7,
                                      0, 3, 7,
                                      0, 1, 3,
                                      4, 7, 5,
                                      0, 4, 1,
                                      1, 5, 2,
                                      3, 2, 7,
                                      4, 0, 7};



        //VBO
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVert), &cubeVert, GL_STATIC_DRAW);

        //VAO
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 24, 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 24, (void*)12);
        glEnableVertexAttribArray(1);
        //IBO
        glGenBuffers(1, &iboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeInd), cubeInd, GL_STATIC_DRAW);
        std::cout << "Scene initialization done\n";

        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_GREATER);
        glClearDepth(0.0);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        robot->rotate(glm::vec3(0.,0.4,0.));
        //m_shader->setUniform("robot", robot->getMatrix(), false);

        body->scale(glm::vec3(0.3, 0.7, 0.3));

        head->translate(glm::vec3(0.0,0.55,0));
        head->scale(glm::vec3(0.15,0.3,0.2));

        armRight->rotateAroundPoint(glm::vec3(0.2,0.3,0),glm::vec3(-0.4,0,0));

        armUpperRight->translate(glm::vec3(0.2,0.2,0.));
        armUpperRight->scale(glm::vec3(0.05,0.3,0.1));

        armLowerRight->translate(glm::vec3(0.2,-0.15,0));
        armLowerRight->scale(glm::vec3(0.05,0.3,0.1));
        armLowerRight->rotateAroundPoint(glm::vec3(0.2,0.,0), glm::vec3(-0.5,0,0));

        armLeft->rotateAroundPoint(glm::vec3(-0.2,0.3,0),glm::vec3(0.4,0,0));

        armUpperLeft->translate(glm::vec3(-0.2,0.2,0.));
        armUpperLeft->scale(glm::vec3(0.05,0.3,0.1));

        armLowerLeft->translate(glm::vec3(-0.2,-0.15,0));
        armLowerLeft->scale(glm::vec3(0.05,0.3,0.1));
        armLowerLeft->rotateAroundPoint(glm::vec3(-0.2,0.,0), glm::vec3(-0.5,0.,0));

        legRight->translate(glm::vec3(0.08,-0.5,0));
        legRight->scale(glm::vec3(0.08,0.4,0.1));
        legRight->rotateAroundPoint(glm::vec3(-0.0,-0.35,0), glm::vec3(-0.4,0.,0));

        legLeft->translate(glm::vec3(-0.08,-0.5,0));
        legLeft->scale(glm::vec3(0.08,0.4,0.1));
        legLeft->rotateAroundPoint(glm::vec3(-0.0,-0.35,0), glm::vec3(0.4,0.,0));

        return true;
	}
	catch (std::exception& ex)
	{
	    throw std::logic_error("Scene initialization failed:\n" + std::string(ex.what()) + "\n");
	}
}

void Scene::render(float dt) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vaoID);
    m_shader->setUniform("robot", robot->getMatrix(), false);

    m_shader->setUniform("model", head->getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", body->getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    armRight->rotateAroundPoint(glm::vec3(0.2, 0.3, 0), glm::vec3(-cos(x), 0., 0));

    m_shader->setUniform("model", armRight->getMatrix() * armUpperRight->getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", armRight->getMatrix() * armLowerRight->getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    armLeft->rotateAroundPoint(glm::vec3(-0.2, 0.3, 0), glm::vec3(cos(x), 0., 0));

    m_shader->setUniform("model", armLeft->getMatrix() * armUpperLeft->getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_shader->setUniform("model", armLeft->getMatrix() * armLowerLeft->getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    legRight->rotateAroundPoint(glm::vec3(-0.0, -0.35, 0), glm::vec3(cos(x), 0., 0));

    m_shader->setUniform("model", legRight->getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    if (t > 0.1) {
    t-=0.1;
    legLeft->rotateAroundPoint(glm::vec3(-0.0, -0.35, 0), glm::vec3(dt, 0., 0));
}
    m_shader->setUniform("model", legLeft->getMatrix(), false);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    t+=dt;
    //m_shader->setUniform("c", GLfloat(0.6));
}

void Scene::update(float dt)
{

}

OpenGLWindow * Scene::getWindow()
{
	return m_window;
}

void Scene::onKey(Key key, Action action, Modifier modifier)
{

}

void Scene::onMouseMove(MousePosition mouseposition)
{

}

void Scene::onMouseButton(MouseButton button, Action action, Modifier modifier)
{

}

void Scene::onMouseScroll(double xscroll, double yscroll)
{

}

void Scene::onFrameBufferResize(int width, int height)
{

}
void Scene::shutdown()
{

}
