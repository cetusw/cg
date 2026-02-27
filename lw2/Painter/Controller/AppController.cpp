#include "AppController.h"
#include "imgui-SFML.h"
#include "imgui_internal.h"

AppController::AppController(sf::RenderWindow& window, Canvas& canvas, AppView& appView)
	: m_window(window)
	, m_canvas(canvas)
	, m_appView(appView)
{
}

void AppController::Run()
{
	m_deltaTime.restart();
	m_appView.Init();
	HandleEvents();
	ImGui::SFML::Shutdown();
}

void AppController::HandleEvents()
{
	while (m_window.isOpen())
	{
		PollEvent();
		m_appView.UpdateUI(m_deltaTime.restart());
		m_appView.Render();
	}
}

void AppController::PollEvent() const
{
	sf::Event event{};
	while (m_window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(m_window, event);
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0.f, 0.f,
				static_cast<float>(event.size.width),
				static_cast<float>(event.size.height));
			m_window.setView(sf::View(visibleArea));
		}
		if (ImGui::GetIO().WantCaptureMouse)
		{
			continue;
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			m_canvas.StartStroke(GetCanvasMousePosition());
		}
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			m_canvas.EndStroke();
		}
		else if (event.type == sf::Event::MouseMoved
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)
			&& !ImGui::GetIO().WantCaptureMouse)
		{
			m_canvas.ContinueStroke(GetCanvasMousePosition());
		}
	}
}

sf::Vector2f AppController::GetCanvasMousePosition() const
{
	const float canvasPadding = m_canvas.GetBrushSize();
	const sf::Vector2i pixel = sf::Mouse::getPosition(m_window);
	const sf::Vector2f coords = m_window.mapPixelToCoords(pixel);
	const sf::Vector2f relativeToCanvas = coords - m_canvas.GetSprite().getPosition();
	const sf::Vector2u size = m_canvas.GetSize();
	return {
		std::clamp(relativeToCanvas.x, -canvasPadding, static_cast<float>(size.x) + canvasPadding),
		std::clamp(relativeToCanvas.y, -canvasPadding, static_cast<float>(size.y) + canvasPadding)
	};
}
