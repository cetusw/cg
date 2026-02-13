#include "Simulation.h"
#include "../View/LetterView.h"

Simulation::Simulation()
{
	m_window.create(sf::VideoMode(800, 600), "Letters Simulation");
	m_window.setFramerateLimit(60);
	SetupLetters();
}

void Simulation::Run()
{
	while (m_window.isOpen())
	{
		const float deltaTime = m_clock.restart().asSeconds();
		ProcessEvents();
		Update(deltaTime);
		Render();
	}
}

void Simulation::SetupLetters()
{
	float startY = 400.0f;

	std::vector<LetterPart> kParts;
	kParts.push_back({ { { 0, 0 }, { 30, 0 }, { 30, 150 }, { 0, 150 } },
		sf::Color::Red });
	kParts.push_back({ { { 30, 53.78 }, { 126.21, 150 }, { 83.79, 150 }, { 30, 96.21 } },
		sf::Color::Red });
	kParts.push_back({ { { 30, 53.78 }, { 83.79, 0 }, { 126.21, 0 }, { 30, 96.21 } },
		sf::Color::Red });

	std::vector<LetterPart> mParts;
	mParts.push_back({ { { 0, 0 }, { 30, 0 }, { 30, 150 }, { 0, 150 } },
		sf::Color::Green });
	mParts.push_back({ { { 0, 0 }, { 30, 0 }, { 90, 90 }, { 60, 90 } },
		sf::Color::Green });
	mParts.push_back({ { { 60, 90 }, { 90, 90 }, { 150, 0 }, { 120, 0 } },
		sf::Color::Green });
	mParts.push_back({ { { 120, 0 }, { 150, 0 }, { 150, 150 }, { 120, 150 } },
		sf::Color::Green });

	std::vector<LetterPart> gParts;
	gParts.push_back({ { { 0, 0 }, { 30, 0 }, { 30, 150 }, { 0, 150 } },
		sf::Color::Blue });
	gParts.push_back({ { { 30, 0 }, { 90, 0 }, { 90, 30 }, { 30, 30 } },
		sf::Color::Blue });

	m_letters.emplace_back(150.0f, startY, 0.0f, kParts);
	m_letters.emplace_back(300.0f, startY, 0.2f, mParts);
	m_letters.emplace_back(475.0f, startY, 0.4f, gParts);
}

void Simulation::ProcessEvents()
{
	sf::Event event{};
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void Simulation::Update(const float deltaTime)
{
	for (auto& letter : m_letters)
	{
		letter.Update(deltaTime);
	}
}

void Simulation::Render()
{
	m_window.clear(sf::Color::White);
	for (const auto& letter : m_letters)
	{
		LetterView::Render(m_window, letter);
	}
	m_window.display();
}