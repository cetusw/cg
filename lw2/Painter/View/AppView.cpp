#include "AppView.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "portable-file-dialogs.h"
#include <iostream>

AppView::AppView(sf::RenderWindow& window, Canvas& canvas)
	: m_window(window)
	, m_canvas(canvas)
{
}

void AppView::Init() const
{
	if (!ImGui::SFML::Init(m_window))
	{
		std::cerr << "Failed to initialize window." << std::endl;
	}

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->Clear();
	io.FontGlobalScale = 3.f;

	if (!ImGui::SFML::UpdateFontTexture())
	{
		std::cerr << "Failed to update font." << std::endl;
	}
}

void AppView::UpdateUI(const sf::Time deltaTime)
{
	ImGui::SFML::Update(m_window, deltaTime);
	BuildMenuBar();
}

void AppView::Render() const
{
	m_window.clear(sf::Color(50, 50, 50));
	CenterPicture();
	m_window.draw(m_canvas.GetSprite());
	ImGui::SFML::Render(m_window);
	m_window.display();
}

void AppView::BuildMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		BuildFileMenu();
		BuildToolsMenu();
		ImGui::EndMainMenuBar();
	}
}

void AppView::BuildFileMenu() const
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New"))
		{
			m_canvas.CreateNewCanvas(m_canvas.GetDefaultSize());
		}

		if (ImGui::MenuItem("Open"))
		{
			OpenFileDialogue();
		}
		if (ImGui::MenuItem("Save As"))
		{
			SaveFileDialogue();
		}
		ImGui::EndMenu();
	}
}

void AppView::BuildToolsMenu()
{
	if (ImGui::BeginMenu("Tools"))
	{
		BuildBrushSizeSlider();
		BuildBrushColorPicker();
		ImGui::EndMenu();
	}
}

void AppView::OpenFileDialogue() const
{
	const auto selection = pfd::open_file("Select a file", ".",
		{ "Image Files (.png, .jpg, .bmp)", "*.png *.jpg *.jpeg *.bmp",
			"All Files", "*" })
							   .result();

	if (!selection.empty())
	{
		m_canvas.LoadFromFile(selection[0]);
	}
}

void AppView::SaveFileDialogue() const
{
	const auto destination = pfd::save_file("Save file as", "picture.png",
		{ "PNG Files", "*.png",
			"JPEG Files", "*.jpg *.jpeg",
			"BMP Files", "*.bmp" })
								 .result();

	if (!destination.empty())
	{
		if (!m_canvas.SaveToFile(destination))
		{
			std::cerr << "Failed to save file: " << destination << std::endl;
		}
	}
}

void AppView::BuildBrushSizeSlider() const
{
	float size = m_canvas.GetBrushSize();
	if (ImGui::SliderFloat("Size", &size, 1.0f, 50.0f))
	{
		m_canvas.SetBrushSize(size);
	}
}

void AppView::BuildBrushColorPicker()
{
	const sf::Color color = m_canvas.GetColor();
	m_colorArray[0] = static_cast<float>(color.r) / 255.f;
	m_colorArray[1] = static_cast<float>(color.g) / 255.f;
	m_colorArray[2] = static_cast<float>(color.b) / 255.f;

	if (ImGui::ColorEdit3("Color", m_colorArray))
	{
		m_canvas.SetColor(sf::Color(
			static_cast<sf::Uint8>(m_colorArray[0] * 255),
			static_cast<sf::Uint8>(m_colorArray[1] * 255),
			static_cast<sf::Uint8>(m_colorArray[2] * 255)));
	}
}

void AppView::CenterPicture() const
{
	const sf::Vector2u windowSize = m_window.getSize();
	const sf::FloatRect spriteBounds = m_canvas.GetSprite().getGlobalBounds();

	const float x = (static_cast<float>(windowSize.x) - spriteBounds.width) / 2.f;
	const float y = (static_cast<float>(windowSize.y) - spriteBounds.height) / 2.f;

	const_cast<sf::Sprite&>(m_canvas.GetSprite()).setPosition(x, y);
}