#include "MainMenu.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>



MainMenu::MainMenu(std::shared_ptr<Context> &context) 
	: m_context(context), m_isPlayButtonSelected(true),
	m_isPlayButtonPressed(false), m_isExitButtonSelected(false), 
	m_isExitButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init() {
	m_context->m_assets->AddFont(MAIN_FONT, "Assets/Fonts/Pacifico-Regular.ttf");

	// Title
	m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameTitle.setString("Snake Game");
	m_gameTitle.setOrigin(
		m_gameTitle.getLocalBounds().width / 2,
		m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(
		m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 150.f);
	m_gameTitle.setFillColor(sf::Color(239, 68, 35));
	m_gameTitle.setOutlineThickness(2.5f);

	// Play
	m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_playButton.setString("Play");
	m_playButton.setOrigin(
		m_playButton.getLocalBounds().width / 2,
		m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(
		m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 25.f);
	m_playButton.setCharacterSize(20);
	m_playButton.setOutlineThickness(1.f);

	// Exit
	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setOrigin(
		m_exitButton.getLocalBounds().width / 2,
		m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(
		m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 + 25.f);
	m_exitButton.setCharacterSize(20);
	m_exitButton.setOutlineThickness(1.f);
}

void MainMenu::ProcessInput() {
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
		}
		else if(event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				if (!m_isPlayButtonSelected) {
					m_isPlayButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}

			case sf::Keyboard::Down:
			{
				if (!m_isExitButtonSelected) {
					m_isExitButtonSelected = true;
					m_isPlayButtonSelected = false;
				}
				break;
			}

			case sf::Keyboard::Return:
			{
				m_isPlayButtonPressed = false;
				m_isExitButtonPressed = false;
				if (m_isPlayButtonSelected)
					m_isPlayButtonPressed = true;
				else
					m_isExitButtonPressed = true;
				break;
			}

			default:
				break;
			}
		}
	}
}

void MainMenu::Update(sf::Time deltaTime) {
	if(m_isPlayButtonSelected) {
		m_playButton.setFillColor(sf::Color(246, 235, 20));
		m_exitButton.setFillColor(sf::Color::White);
	}
	else {
		m_playButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(sf::Color(246, 235, 20));
	}

	if (m_isPlayButtonPressed) {
		// Todo:
		m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
	}
	else if (m_isExitButtonPressed) {
		m_context->m_window->close();
		exit(0);
	}
}

void MainMenu::Draw() {

	m_context->m_window->clear(sf::Color(79, 175, 68));
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();
} 