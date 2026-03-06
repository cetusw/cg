#include "GLApplication.h"
#include <GL/glut.h>
#include <cassert>

GLApplication* GLApplication::m_pApplication = nullptr;

GLApplication::GLApplication(
	const char* title,
	const int width,
	const int height,
	const bool needDepth,
	const bool needStencil)
{
	if (m_pApplication)
	{
		assert(!"Only one instance of the application is permitted");
	}
	m_pApplication = this;

	int argc = 1;
	char** argv = {};
	glutInit(&argc, argv);

	glutInitDisplayMode(
		GLUT_RGBA | GLUT_DOUBLE | (needDepth ? GLUT_DEPTH : 0) | (needStencil ? GLUT_STENCIL : 0));

	if (width > 0 && height > 0)
	{
		glutInitWindowSize(width, height);
	}

	glutCreateWindow(title);
	InitEventHandlers();
}

GLApplication::~GLApplication()
{
	m_pApplication = nullptr;
}

void GLApplication::InitEventHandlers()
{
	glutDisplayFunc(&DisplayHandler);
	glutReshapeFunc(&ReshapeHandler);

	glutKeyboardFunc(&KeyboardHandler);
	glutKeyboardUpFunc(&KeyboardUpHandler);

	glutSpecialFunc(&SpecialHandler);
	glutSpecialUpFunc(&SpecialUpHandler);

	glutMouseFunc(&MouseHandler);
	glutMotionFunc(&MotionHandler);
	glutIdleFunc(&IdleHandler);
}

void GLApplication::MotionHandler(const int x, const int y)
{
	m_pApplication->OnMotion(x, y);
}

void GLApplication::MouseHandler(const int button, const int state, const int x, const int y)
{
	m_pApplication->OnMouse(button, state, x, y);
}

void GLApplication::DisplayHandler()
{
	m_pApplication->OnDisplay();
	glutSwapBuffers();
}

void GLApplication::IdleHandler()
{
	const int currentTime = glutGet(GLUT_ELAPSED_TIME);
	m_pApplication->m_deltaTime = static_cast<float>(currentTime - m_pApplication->m_lastTime) / 1000.0f;
	m_pApplication->m_lastTime = currentTime;

	if (m_pApplication->m_deltaTime > 0.1f)
	{
		m_pApplication->m_deltaTime = 0.1f;
	}

	m_pApplication->OnIdle();
}

void GLApplication::ReshapeHandler(const int width, const int height)
{
	m_pApplication->OnReshape(width, height);
}

void GLApplication::KeyboardHandler(const unsigned char key, const int x, const int y)
{
	m_pApplication->m_keys[key] = true;
}

void GLApplication::KeyboardUpHandler(const unsigned char key, int x, int y)
{
	m_pApplication->m_keys[key] = false;
}

void GLApplication::SpecialHandler(const int key, int x, int y)
{
	m_pApplication->m_specialKeys[key] = true;
}

void GLApplication::SpecialUpHandler(const int key, int x, int y)
{
	m_pApplication->m_specialKeys[key] = false;
}

void GLApplication::OnReshape(const int width, const int height)
{
	glViewport(0, 0, width, height);
}

void GLApplication::OnKeyboard(unsigned char /*key*/, int /*x*/, int /*y*/)
{
}

bool GLApplication::IsKeyPressed(const unsigned char key) const
{
	return m_keys[key];
}

bool GLApplication::IsSpecialKeyPressed(const int key) const
{
	return m_specialKeys[key];
}

void GLApplication::OnMouse(
	int /*button*/, int /*state*/, int /*x*/, int /*y*/)
{
}

void GLApplication::OnMotion(int /*x*/, int /*y*/)
{
}

void GLApplication::OnIdle()
{
}

void GLApplication::OnInit()
{
}

void GLApplication::PostRedisplay()
{
	glutPostRedisplay();
}

float GLApplication::GetDeltaTime() const
{
	return m_deltaTime;
}

void GLApplication::MainLoop()
{
	OnInit();
	glutMainLoop();
}