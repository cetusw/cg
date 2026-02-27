#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Canvas
{
public:
	explicit Canvas(sf::Vector2u size);
	void CreateNewCanvas(sf::Vector2u size);

	void StartStroke(sf::Vector2f position);
	void EndStroke();
	void ContinueStroke(sf::Vector2f position);
	void DrawInterpolatedBrush(sf::Vector2f start, sf::Vector2f end);
	void DrawPoint(sf::Vector2f position);

	bool SaveToFile(const std::string& filename) const;
	bool LoadFromFile(const std::string& filename);

	bool Contains(const sf::Vector2f& position) const;

	sf::Vector2u GetDefaultSize() const;
	const sf::Sprite& GetSprite() const;
	sf::Color GetColor() const;
	float GetBrushSize() const;
	sf::Vector2u GetSize() const;
	void SetBrushSize(float size);
	void SetColor(sf::Color color);

private:
	sf::Vector2u m_defaultSize;
	sf::RenderTexture m_renderTexture;
	sf::Sprite m_sprite;
	sf::Color m_currentColor;
	float m_brushSize;
	sf::Vector2f m_lastMousePosition;
	bool m_isDrawing;
};
