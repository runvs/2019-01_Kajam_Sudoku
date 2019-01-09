#include "GameBoard.hpp"
#include "StateGame.hpp"
#include "JamTemplate/Game.hpp"

//void GameBoard::moveCursorTo(int nextX, int nextY)
//{
//	m_selectorX = nextX;
//	m_selectorY = nextY;
//
//	auto start = m_selector->getPosition();
//	auto end = positionFromCoord(m_selectorX, m_selectorY);
//	auto tw = JamTemplate::TweenPosition<JamTemplate::SmartShape>::create(m_selector, 0.5, start, end);
//	m_stateGame.add(tw);
//}


void GameBoard::checkForNextBoard()
{
	if (m_board.getOpenFields() == 0)
	{
		m_board.clearBoard();
		m_boardFull.clearBoard();
		m_board.createPuzzle(5);
		m_board.getSolution(m_boardFull);
	}
}

void GameBoard::updateNumbers(float elapsed)
{
	auto c = m_board.getCellAt(Coord{ m_selectorX,m_selectorY });

	if (c->getValue() != 0)
		return;

	auto cc = m_boardFull.getCellAt(Coord{ m_selectorX,m_selectorY });

	int num = 0;
	if (m_firstPlayer)
	{
		if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num1))
			num = 1;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num2))
			num = 2;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num3))
			num = 3;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num4))
			num = 4;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num5))
			num = 5;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num6))
			num = 6;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num7))
			num = 7;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num8))
			num = 8;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Num9))
			num = 9;

	}
	else
	{
		if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad1))
			num = 1;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad2))
			num = 2;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad3))
			num = 3;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad4))
			num = 4;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad5))
			num = 5;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad6))
			num = 6;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad7))
			num = 7;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad8))
			num = 8;
		else if (JamTemplate::InputManager::justPressed(sf::Keyboard::Key::Numpad9))
			num = 9;
	}
	if (num == 0) return;
	if (cc->getValue() == num)
	{
		placeCorrectValue(c, num);
	}
	else
	{
		placeWrongValue();
	}
}

void GameBoard::placeCorrectValue(std::shared_ptr<Cell> c, int num)
{
	c->setValue(num);
}
void GameBoard::placeWrongValue()
{

}

void GameBoard::updateSelector(float elapsed)
{
	//std::cout << m_selectorX << " " << m_selectorY << "\n";
	int nextX = m_selectorX;
	int nextY = m_selectorY;
	bool moved = false;
	if (
		JamTemplate::InputManager::justReleased(sf::Keyboard::Key::A) && m_firstPlayer ||
		JamTemplate::InputManager::justReleased(sf::Keyboard::Key::Left) && !m_firstPlayer)
	{
		nextX--;
		moved = true;
	}
	if (
		JamTemplate::InputManager::justReleased(sf::Keyboard::Key::D) && m_firstPlayer ||
		JamTemplate::InputManager::justReleased(sf::Keyboard::Key::Right) && !m_firstPlayer)
	{
		nextX++;
		moved = true;
	}

	if (nextX < 0)
		nextX = 0;
	if (nextX >= 9)
		nextX = 8;

	if (
		JamTemplate::InputManager::justReleased(sf::Keyboard::Key::W) && m_firstPlayer ||
		JamTemplate::InputManager::justReleased(sf::Keyboard::Key::Up) && !m_firstPlayer)
	{
		nextY--;
		moved = true;
	}
	if (
		JamTemplate::InputManager::justReleased(sf::Keyboard::Key::S) && m_firstPlayer ||
		JamTemplate::InputManager::justReleased(sf::Keyboard::Key::Down) && !m_firstPlayer)
	{
		nextY++;
		moved = true;
	}

	if (nextY < 0)
		nextY = 0;
	if (nextY >= 9)
		nextY = 8;

	if (moved)
	{
		std::cout << "move to " << nextX << " " << nextY << " from " << m_selectorX << " " << m_selectorY << std::endl;
		moveCursorTo(nextX, nextY);
	}


	m_selector->update(elapsed);
}

void GameBoard::moveCursorTo(int nextX, int nextY)
{
	m_selectorX = nextX;
	m_selectorY = nextY;
	m_selector->setPosition(positionFromCoord(nextX, nextY));

}

void GameBoard::doDraw() const 
{
	m_selector->draw(getGame()->getRenderTarget());
	for (auto const& c : m_board)
	{
		if (c->getValue() != 0)
		{
			m_text.setPosition(positionFromCoord(c->getPosition().x, c->getPosition().y));
			m_text.setText(std::to_string(c->getValue()));
			m_text.update(0.0f);
			m_text.setCharacterSize(16U);
			m_text.draw(getGame()->getRenderTarget());
		}
	}
};

 void GameBoard::doCreate()
{
	m_board.createPuzzle(2);

	m_board.getSolution(m_boardFull);

	m_text.loadFont("assets/font.ttf");

	m_selector = std::make_shared<JamTemplate::SmartShape>();
	m_selector->makeRect(sf::Vector2f{ GP::CellPositionSpacing() , GP::CellPositionSpacing() });
	m_selector->setColor(sf::Color::Red);
	m_selector->setPosition(positionFromCoord(m_selectorX, m_selectorY));
}
