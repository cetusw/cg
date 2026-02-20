#include "BackgroundView.h"

namespace
{
sf::Texture GetChessboardTexture()
{
	sf::Image img;
	constexpr unsigned int boardSize = 64;
	img.create(boardSize, boardSize);

	for (unsigned int y = 0; y < boardSize; y++)
	{
		for (unsigned int x = 0; x < boardSize; x++)
		{
			const bool isColorWhite = (x / (boardSize / 2) + y / (boardSize / 2)) % 2 == 0;
			img.setPixel(x, y, isColorWhite ? sf::Color::White : sf::Color(200, 200, 200));
		}
	}

	sf::Texture texture;
	texture.loadFromImage(img);
	texture.setRepeated(true);
	return texture;
}
} // namespace

BackgroundView::BackgroundView()
	: m_texture(GetChessboardTexture())
{
}

void BackgroundView::Draw(sf::RenderWindow& window, const ViewerSettings& settings) const
{
	const sf::View fixedView({ 0.f, 0.f,
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y) });

	window.setView(fixedView);

	sf::RectangleShape rect(static_cast<sf::Vector2f>(window.getSize()));

	if (settings.bgType == BackgroundType::Chessboard)
	{
		rect.setTexture(&m_texture);

		rect.setTextureRect({ 0, 0,
			static_cast<int>(window.getSize().x),
			static_cast<int>(window.getSize().y) });

		rect.setFillColor(sf::Color::White);
	}
	else
	{
		rect.setTexture(nullptr);
		rect.setFillColor(sf::Color::White);
	}

	window.draw(rect);
}