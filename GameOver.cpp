#include "GameOver.hpp"
#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context>& context)
	: m_context(context), m_isRetryButtonSelected(true),
	m_isRetryButtonPressed(false), m_isExitButtonSelected(false),
	m_isExitButtonPressed(false)
{
}


GameOver::~GameOver()
{
}


void GameOver::Init() {
	// Title
	m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameOverTitle.setString("Game Over");
	m_gameOverTitle.setOrigin(
		m_gameOverTitle.getLocalBounds().width / 2,
		m_gameOverTitle.getLocalBounds().height / 2);
	m_gameOverTitle.setPosition(
		m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 150.f);
	m_gameOverTitle.setFillColor(sf::Color(239, 68, 35));
	m_gameOverTitle.setOutlineThickness(2.5f);

	// Play
	m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_retryButton.setString("Retry");
	m_retryButton.setOrigin(
		m_retryButton.getLocalBounds().width / 2,
		m_retryButton.getLocalBounds().height / 2);
	m_retryButton.setPosition(
		m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 25.f);
	m_retryButton.setCharacterSize(20);
	m_retryButton.setOutlineThickness(1.f);

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

void GameOver::ProcessInput() {
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				if (!m_isRetryButtonSelected) {
					m_isRetryButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}

			case sf::Keyboard::Down:
			{
				if (!m_isExitButtonSelected) {
					m_isExitButtonSelected = true;
					m_isRetryButtonSelected = false;
				}
				break;
			}

			case sf::Keyboard::Return:
			{
				m_isRetryButtonPressed = false;
				m_isExitButtonPressed = false;
				if (m_isRetryButtonSelected)
					m_isRetryButtonPressed = true;
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

void GameOver::Update(sf::Time deltaTime) {
	if (m_isRetryButtonSelected) {
		m_retryButton.setFillColor(sf::Color(246, 235, 20));
		m_exitButton.setFillColor(sf::Color::White);
	}
	else {
		m_retryButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(sf::Color(246, 235, 20));
	}

	if (m_isRetryButtonPressed) {
		m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
	}
	else if (m_isExitButtonPressed) {
		m_context->m_window->close();
		exit(0);
	}
}

void GameOver::Draw() {

	m_context->m_window->clear(sf::Color(79, 175, 68));
	m_context->m_window->draw(m_gameOverTitle);
	m_context->m_window->draw(m_retryButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();
}