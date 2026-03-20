#include "PolyhedronApp.h"
#include "DirectLight.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/orthonormalize.hpp>
#include <vector>

PolyhedronApp::PolyhedronApp(const int width, const int height, const char* title)
	: GLFWApplication(width, height, title)
	, m_isDragging(false)
	, m_mousePos(0.0, 0.0)
{
	const std::vector<glm::vec3> vertices = {
		{ 1.0f, 0.0f, 0.0f },
		{ -1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, -1.0f }
	};

	const std::vector<std::vector<size_t>> faces = {
		{ 0, 2, 4 },
		{ 2, 1, 4 },
		{ 1, 3, 4 },
		{ 3, 0, 4 },
		{ 0, 5, 2 },
		{ 2, 5, 1 },
		{ 1, 5, 3 },
		{ 3, 5, 0 }
	};

	m_polyhedron.SetData(vertices, faces);
	m_polyhedron.SetRandomColors();
}

void PolyhedronApp::OnInit()
{
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	SetLight();

	glLineWidth(6);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	m_camera = glm::lookAt(
		glm::dvec3(1.5, 1.5, 1.5),
		glm::dvec3(0.0, 0.0, 0.0),
		glm::dvec3(0.0, 1.0, 0.0));
}

void PolyhedronApp::OnReshape(const int width, const int height)
{
	glViewport(0, 0, width, height);

	const double aspect = static_cast<double>(width) / height;

	double frustumHeight = FRUSTUM_SIZE;
	double frustumWidth = FRUSTUM_SIZE * aspect;

	if (frustumWidth < FRUSTUM_SIZE && aspect != 0)
	{
		frustumWidth = FRUSTUM_SIZE;
		frustumHeight = frustumWidth / aspect;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-frustumWidth / 2, frustumWidth / 2,
		-frustumHeight / 2, frustumHeight / 2,
		FRUSTUM_SIZE * Z_NEAR, FRUSTUM_SIZE * Z_FAR);
	glMatrixMode(GL_MODELVIEW);
}

void PolyhedronApp::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	SetLight();
	glLoadIdentity();
	glMultMatrixd(glm::value_ptr(m_camera));

	m_polyhedron.Draw();
}

void PolyhedronApp::OnMouseButton(const int button, const int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		m_isDragging = action & GLFW_PRESS;
	}
}

void PolyhedronApp::OnMouseMove(const double x, const double y)
{
	const glm::dvec2 mousePos(x, y);
	if (m_isDragging)
	{
		int w, h;
		glfwGetFramebufferSize(m_window, &w, &h);

		const auto delta = mousePos - m_mousePos;
		const double xAngle = delta.y * glm::pi<double>() / w;
		const double yAngle = delta.x * glm::pi<double>() / h;
		RotateCamera(xAngle, yAngle);
	}
	m_mousePos = mousePos;
}

void PolyhedronApp::RotateCamera(const double xAngle, const double yAngle)
{
	const glm::dvec3 xAxis{ m_camera[0][0], m_camera[1][0], m_camera[2][0] };
	const glm::dvec3 yAxis{ m_camera[0][1], m_camera[1][1], m_camera[2][1] };

	m_camera = glm::rotate(m_camera, xAngle, xAxis);
	m_camera = glm::rotate(m_camera, yAngle, yAxis);

	glm::dmat3 subMatrix = glm::orthonormalize(glm::dmat3(m_camera));
	m_camera[0] = glm::dvec4(subMatrix[0], 0.0);
	m_camera[1] = glm::dvec4(subMatrix[1], 0.0);
	m_camera[2] = glm::dvec4(subMatrix[2], 0.0);
}

void PolyhedronApp::SetLight()
{
	DirectLight light(glm::vec3(1, 1, 3));
	light.SetDiffuseIntensity(0.5f, 0.5f, 0.5f);
	light.SetAmbientIntensity(0.2f, 0.2f, 0.2f);
	light.SetSpecularIntensity(0.3f, 0.3f, 0.3f);
	light.SetLight(GL_LIGHT0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}