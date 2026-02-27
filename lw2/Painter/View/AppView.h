#pragma once

#include "Model/Canvas.h"
#include <SFML/Graphics/RenderWindow.hpp>

class AppView
{
public:
	AppView(sf::RenderWindow& window, Canvas& canvas);

	void Init() const;
	void UpdateUI(sf::Time deltaTime);
	void Render() const;

private:
	sf::RenderWindow& m_window;
	Canvas& m_canvas;
	float m_colorArray[3] = { 0.0f, 0.0f, 0.0f };

	void BuildMenuBar();
	void BuildFileMenu() const;
	void BuildToolsMenu();
	void OpenFileDialogue() const;
	void SaveFileDialogue() const;
	void BuildBrushSizeSlider() const;
	void BuildBrushColorPicker();
	void CenterPicture() const;
};
