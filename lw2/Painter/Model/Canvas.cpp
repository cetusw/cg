#include "Canvas.h"

#include <cmath>
#include <iostream>

Canvas::Canvas(const sf::Vector2u size)
{
	m_defaultSize = size;
	CreateNewCanvas(size);
	m_currentColor = sf::Color::Black;
	m_brushSize = 5.0f;
	m_isDrawing = false;
}

void Canvas::CreateNewCanvas(const sf::Vector2u size)
{
	if (!m_renderTexture.create(size.x, size.y))
	{
		std::cerr << "Error creating render texture" << std::endl;
	}
	m_renderTexture.clear(sf::Color::White);
	m_renderTexture.display();

	m_sprite.setTexture(m_renderTexture.getTexture(), true);
	m_sprite.setPosition(0, 0);
}

void Canvas::StartStroke(const sf::Vector2f position)
{
	if (!Contains(position))
	{
		return;
	}
	m_isDrawing = true;
	m_lastMousePosition = position;
	DrawPoint(position);
}

void Canvas::EndStroke()
{
	m_isDrawing = false;
}

void Canvas::ContinueStroke(const sf::Vector2f position)
{
	if (!m_isDrawing)
	{
		return;
	}

	DrawInterpolatedBrush(m_lastMousePosition, position);

	m_lastMousePosition = position;
}

void Canvas::DrawInterpolatedBrush(const sf::Vector2f start, const sf::Vector2f end)
{
	const sf::Vector2f diff = end - start;
	const float distance = std::hypot(diff.x, diff.y);

	if (distance <= 0)
	{
		return;
	}

	const sf::Vector2f direction = diff / distance;

	const float step = std::max(1.0f, m_brushSize / 4.0f);
	for (float i = 0; i < distance; i += step)
	{
		DrawPoint(start + direction * i);
	}

	DrawPoint(end);
	m_renderTexture.display();
}

void Canvas::DrawPoint(const sf::Vector2f position)
{
	sf::CircleShape brush(m_brushSize);
	brush.setOrigin(m_brushSize, m_brushSize);
	brush.setPosition(position);
	brush.setFillColor(m_currentColor);
	m_renderTexture.draw(brush);
}

bool Canvas::SaveToFile(const std::string& filename) const
{
	return m_renderTexture.getTexture().copyToImage().saveToFile(filename);
}

bool Canvas::LoadFromFile(const std::string& filename)
{
	sf::Texture texture;
	if (!texture.loadFromFile(filename))
	{
		return false;
	}

	CreateNewCanvas(texture.getSize());

	const sf::Sprite sprite(texture);
	m_renderTexture.draw(sprite);
	m_renderTexture.display();
	return true;
}

bool Canvas::Contains(const sf::Vector2f& position) const
{
	const sf::Vector2u size = GetSize();
	return position.x > 0 && position.x < size.x && position.y > 0 && position.y < size.y;
}

sf::Vector2u Canvas::GetDefaultSize() const
{
	return m_defaultSize;
}

const sf::Sprite& Canvas::GetSprite()
{
	return m_sprite;
}

void Canvas::SetColor(const sf::Color color)
{
	m_currentColor = color;
}

void Canvas::SetSpritePosition(const float x, const float y)
{
	m_sprite.setPosition(x, y);
}

sf::Color Canvas::GetColor() const
{
	return m_currentColor;
}

void Canvas::SetBrushSize(const float size)
{
	m_brushSize = size;
}

float Canvas::GetBrushSize() const
{
	return m_brushSize;
}

sf::Vector2u Canvas::GetSize() const
{
	return m_renderTexture.getSize();
}