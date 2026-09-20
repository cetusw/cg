#include "view/SceneRenderer.h"

#include "view/Texture2D.h"

#include <GL/glew.h>

#include <array>
#include <cmath>
#include <filesystem>

namespace
{
struct TexturedVertex
{
	float x;
	float y;
	float z;
	float u;
	float v;
};

std::array<GLfloat, 4> ToGlColor(const RgbColor& color)
{
	return { color.red, color.green, color.blue, 1.0f };
}

void DrawVertex(const TexturedVertex& vertex)
{
	glTexCoord2f(vertex.u, vertex.v);
	glVertex3f(vertex.x, vertex.y, vertex.z);
}

void DrawQuad(const Vector3& normal, const std::array<TexturedVertex, 4>& vertices)
{
	glBegin(GL_QUADS);
	glNormal3f(normal.x, normal.y, normal.z);
	for (const TexturedVertex& vertex : vertices)
	{
		DrawVertex(vertex);
	}
	glEnd();
}
} // namespace

SceneRenderer::SceneRenderer() = default;

SceneRenderer::~SceneRenderer() = default;

void SceneRenderer::Initialize()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // TODO заменить
}

void SceneRenderer::Render(const Scene& scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	const Camera& camera = scene.GetCamera();
	gluLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	ConfigureLight(scene.GetMainLight());

	for (const SceneObject& object : scene.GetObjects())
	{
		DrawObject(object);
	}
}

void SceneRenderer::SetProjection(const int width, const int height)
{
	const int safeHeight = height == 0 ? 1 : height;

	const double aspect = static_cast<double>(width) / static_cast<double>(safeHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(
		60.0,
		aspect,
		0.1,
		100.0);

	glMatrixMode(GL_MODELVIEW);
}

void SceneRenderer::ConfigureLight(const PointLight& light) const
{
	const std::array<GLfloat, 4> ambient = ToGlColor(light.ambient);
	const std::array<GLfloat, 4> diffuse = ToGlColor(light.diffuse);
	const std::array<GLfloat, 4> specular = ToGlColor(light.specular);
	const std::array position{ light.position.x, light.position.y, light.position.z, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient.data());
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse.data());
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular.data());
	glLightfv(GL_LIGHT0, GL_POSITION, position.data());
}

void SceneRenderer::ApplyMaterial(const MaterialDescription& material) const
{
	const std::array<GLfloat, 4> ambient = ToGlColor(material.ambient);
	const std::array<GLfloat, 4> diffuse = ToGlColor(material.diffuse);
	const std::array<GLfloat, 4> specular = ToGlColor(material.specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient.data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse.data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular.data());
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);
}

void SceneRenderer::DrawObject(const SceneObject& object)
{
	ApplyMaterial(object.material);
	if (object.texturePath.empty())
	{
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glEnable(GL_TEXTURE_2D);
		GetTexture(object.texturePath).Bind();
	}

	glPushMatrix();

	const Transform& transform = object.transform;

	// TODO возможно имеет смысл разбить на функции
	glTranslatef(transform.position.x, transform.position.y, transform.position.z);
	glRotatef(transform.rotation.x, 1.0f, 0.0f, 0.0f);
	glRotatef(transform.rotation.y, 0.0f, 1.0f, 0.0f);
	glRotatef(transform.rotation.z, 0.0f, 0.0f, 1.0f);
	glScalef(transform.scale.x, transform.scale.y, transform.scale.z);
	glColor3f(1.0f, 1.0f, 1.0f);
	DrawGeometry(object.geometry);
	glPopMatrix();
}

void SceneRenderer::DrawGeometry(const GeometryDescription& geometry) const
{
	switch (geometry.type)
	{
	case GeometryType::Box:
		DrawBox(geometry);
		break;
	case GeometryType::Ground:
		DrawGround(geometry);
		break;
	case GeometryType::Roof:
		DrawRoof(geometry);
		break;
	}
}

void SceneRenderer::DrawBox(const GeometryDescription& geometry) const
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	const float repeatX = geometry.width / geometry.textureScale;
	const float repeatY = geometry.depth / geometry.textureScale;
	const float repeatZ = geometry.height / geometry.textureScale;
	const float top = geometry.height;

	DrawQuad({ 0.0f, 1.0f, 0.0f }, { { { halfWidth, halfDepth, 0.0f, 0.0f, 0.0f }, { -halfWidth, halfDepth, 0.0f, repeatX, 0.0f }, { -halfWidth, halfDepth, top, repeatX, repeatZ }, { halfWidth, halfDepth, top, 0.0f, repeatZ } } });
	DrawQuad({ 0.0f, -1.0f, 0.0f }, { { { -halfWidth, -halfDepth, 0.0f, 0.0f, 0.0f }, { halfWidth, -halfDepth, 0.0f, repeatX, 0.0f }, { halfWidth, -halfDepth, top, repeatX, repeatZ }, { -halfWidth, -halfDepth, top, 0.0f, repeatZ } } });
	DrawQuad({ 1.0f, 0.0f, 0.0f }, { { { halfWidth, -halfDepth, 0.0f, 0.0f, 0.0f }, { halfWidth, halfDepth, 0.0f, repeatY, 0.0f }, { halfWidth, halfDepth, top, repeatY, repeatZ }, { halfWidth, -halfDepth, top, 0.0f, repeatZ } } });
	DrawQuad({ -1.0f, 0.0f, 0.0f }, { { { -halfWidth, halfDepth, 0.0f, 0.0f, 0.0f }, { -halfWidth, -halfDepth, 0.0f, repeatY, 0.0f }, { -halfWidth, -halfDepth, top, repeatY, repeatZ }, { -halfWidth, halfDepth, top, 0.0f, repeatZ } } });
	DrawQuad({ 0.0f, 0.0f, 1.0f }, { { { -halfWidth, -halfDepth, top, 0.0f, 0.0f }, { halfWidth, -halfDepth, top, repeatX, 0.0f }, { halfWidth, halfDepth, top, repeatX, repeatY }, { -halfWidth, halfDepth, top, 0.0f, repeatY } } });
	DrawQuad({ 0.0f, 0.0f, -1.0f }, { { { -halfWidth, halfDepth, 0.0f, 0.0f, 0.0f }, { halfWidth, halfDepth, 0.0f, repeatX, 0.0f }, { halfWidth, -halfDepth, 0.0f, repeatX, repeatY }, { -halfWidth, -halfDepth, 0.0f, 0.0f, repeatY } } });
}

void SceneRenderer::DrawGround(const GeometryDescription& geometry) const
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	const float repeatX = geometry.width / geometry.textureScale;
	const float repeatY = geometry.depth / geometry.textureScale;
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(repeatX, 0.0f);
	glVertex3f(halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(repeatX, repeatY);
	glVertex3f(halfWidth, halfDepth, 0.0f);
	glTexCoord2f(0.0f, repeatY);
	glVertex3f(-halfWidth, halfDepth, 0.0f);
	glEnd();
}

void SceneRenderer::DrawRoof(const GeometryDescription& geometry) const
{
	const float halfWidth = geometry.width / 2.0f;
	const float halfDepth = geometry.depth / 2.0f;
	const float repeatY = geometry.depth / geometry.textureScale;
	const float repeatZ = geometry.height / geometry.textureScale;
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(halfWidth, halfDepth, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-halfWidth, halfDepth, 0.0f);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, halfDepth, geometry.height);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, -halfDepth, geometry.height);
	glEnd();
	glBegin(GL_QUADS);
	const float slopeLength = std::sqrt(halfWidth * halfWidth + geometry.height * geometry.height);
	const float normalX = geometry.height / slopeLength;
	const float normalZ = halfWidth / slopeLength;
	glNormal3f(-normalX, 0.0f, normalZ);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(0.0f, repeatZ);
	glVertex3f(0.0f, -halfDepth, geometry.height);
	glTexCoord2f(repeatY, repeatZ);
	glVertex3f(0.0f, halfDepth, geometry.height);
	glTexCoord2f(repeatY, 0.0f);
	glVertex3f(-halfWidth, halfDepth, 0.0f);
	glNormal3f(normalX, 0.0f, normalZ);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.0f, -halfDepth, geometry.height);
	glTexCoord2f(0.0f, repeatZ);
	glVertex3f(halfWidth, -halfDepth, 0.0f);
	glTexCoord2f(repeatY, repeatZ);
	glVertex3f(halfWidth, halfDepth, 0.0f);
	glTexCoord2f(repeatY, 0.0f);
	glVertex3f(0.0f, halfDepth, geometry.height);
	glEnd();
}

Texture2D& SceneRenderer::GetTexture(const std::string& path)
{
	auto [iterator, inserted] = m_textures.try_emplace(path);
	if (inserted)
	{
		const std::filesystem::path texturePath = std::filesystem::path(COTTAGE_SOURCE_DIR) / path;
		iterator->second = std::make_unique<Texture2D>(texturePath);
	}
	return *iterator->second;
}
