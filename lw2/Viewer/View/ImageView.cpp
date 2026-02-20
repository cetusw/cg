#include "ImageView.h"

void ImageView::UpdateLayout(const sf::Vector2u windowSize, const sf::Vector2f imageSize)
{
	if (windowSize.x == 0 || windowSize.y == 0)
	{
		return;
	}

	const float windowRatio = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
	const float imageRatio = imageSize.x / imageSize.y;

	float viewportWidth = VIEWPORT_FULL_SCALE;
	float viewportHeight = VIEWPORT_FULL_SCALE;
	float viewportX = VIEWPORT_START;
	float viewportY = VIEWPORT_START;

	if (windowRatio > imageRatio)
	{
		viewportWidth = imageRatio / windowRatio;
		viewportX = (VIEWPORT_FULL_SCALE - viewportWidth) / 2.0f;
	}
	else
	{
		viewportHeight = windowRatio / imageRatio;
		viewportY = (VIEWPORT_FULL_SCALE - viewportHeight) / 2.0f;
	}

	m_view.reset({ 0, 0, imageSize.x, imageSize.y });
	m_view.setViewport({ viewportX, viewportY, viewportWidth, viewportHeight });
}

void ImageView::Draw(sf::RenderWindow& window, const Image& image) const
{
	if (!image.IsLoaded())
	{
		return;
	}
	const sf::View oldView = window.getView();
	window.setView(m_view);
	const sf::Sprite s(image.GetTexture());
	window.draw(s);
	window.setView(oldView);
}