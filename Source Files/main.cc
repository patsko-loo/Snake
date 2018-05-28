#include "snake.h"
#include "info.h"
#include "board.h"
#include "cell.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>


void resetClock(sf::Clock &c, sf::Time &time1, float &test) {
	c.restart();
	time1 = c.getElapsedTime();
	test = time1.asSeconds();
}

template <class Type>
void getSettings(sf::RenderWindow &w, Type &toChange, std::string msg, Type restriction) {

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cerr << "Did not load font" << std::endl;
	}

	sf::Text playerInput;//Input the player will give	
	playerInput.setFont(font);
	playerInput.setPosition(0, 30);

	sf::Text input;//Messages to player
	input.setFont(font);
	input.setString(msg);

	std::string whatPlayerTypes; // What the player inputs 

	sf::Text error;
	error.setFont(font);
	error.setString("Input not valid");
	error.setPosition(0, 60);
	bool invalid = false; //Flag which checks if valid entry



	while (w.isOpen())
	{
		sf::Event event;
		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) w.close();
			else if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128) {
					if (event.text.unicode == 13) {
						//Convert to a float;
						if (toChange <= restriction) {

							//toChange = strtof(whatPlayerTypes.c_str(), 0);
							std::istringstream ss(whatPlayerTypes);
							if (!(ss >> toChange)) {
								toChange = 0;
							}
							invalid = true;
							if (toChange > 0) {
								invalid = false;
								return;
							}
						}
						whatPlayerTypes = "";
					}
					else if (event.text.unicode == 8) {
						whatPlayerTypes = whatPlayerTypes.substr(0, whatPlayerTypes.size() - 1);
						playerInput.setString(whatPlayerTypes);
					}
					else {
						char temp = static_cast<char>(event.text.unicode);
						whatPlayerTypes += temp;
						playerInput.setString(whatPlayerTypes);
					}
				}
			}
		}

		playerInput.setString(whatPlayerTypes);
		w.clear();
		if (invalid) w.draw(error);
		w.draw(input);
		w.draw(playerInput);
		w.display();
	}
}


void playGame() {
	int row = 0;
	int col = 0;
	int increaseBy = 0;
	float speed = 0;
	//getSettings(speed, row, col);

	sf::RenderWindow SettingsWindow(sf::VideoMode(1000, 500), "Settings");
	while (SettingsWindow.isOpen()) {
		getSettings <float>(SettingsWindow, speed, "Please input a speed: ", 0.0);
		getSettings <int>(SettingsWindow, row, "Please input the amount of Rows: ", 3);
		getSettings <int>(SettingsWindow, col, "Please input the amount of Cols: ", 3);
		getSettings <int>(SettingsWindow, increaseBy, "Please input how much the snake will increase by: ", 0);
		SettingsWindow.close();
	}

	if (speed <= 0) speed = 0.1;
	if (row <= 3) row = 20;
	if (col <= 3) col = 20;
	if (increaseBy <= 0) increaseBy = 4;

	int sizeOfCell = 20;

	Board *b = new Board{ row,col,increaseBy };
	b->makeFoodBlock();

	sf::RenderWindow window(sf::VideoMode(col * sizeOfCell, row * sizeOfCell), "Snake");

	sf::Clock clock;

	sf::Time time1;
	float test = 0;
	while (window.isOpen()) {

		Direction nextDir = Direction::None;
		sf::Event event;

		time1 = clock.getElapsedTime();
		test = time1.asSeconds();
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			else if (event.type == sf::Event::KeyPressed) {
				try {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !b->sameDirection(Direction::Left) && b->isDirValid(Direction::Left)) {
						nextDir = Direction::Left;
						b->nextMove(nextDir);
						resetClock(clock, time1, test);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !b->sameDirection(Direction::Up) && b->isDirValid(Direction::Up)) {
						nextDir = Direction::Up;
						b->nextMove(nextDir);
						resetClock(clock, time1, test);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !b->sameDirection(Direction::Right) && b->isDirValid(Direction::Right)) {
						nextDir = Direction::Right;
						b->nextMove(nextDir);
						resetClock(clock, time1, test);
					}
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !b->sameDirection(Direction::Down) && b->isDirValid(Direction::Down)) {
						nextDir = Direction::Down;
						b->nextMove(nextDir);
						resetClock(clock, time1, test);
					}
				}
				catch (GameOver &g) {
					window.close();
				}
				catch (Winner &win) {
					window.close();
				}
			}

		}
		if (b) {
			if (test > speed) {
				try {
					b->nextMove();
				}
				catch (GameOver &g) {
					window.close();
				}
				catch (Winner &win) {
					window.close();
				}
				clock.restart();
			}
			window.clear();

			for (int i = 0; i < row; ++i) {
				for (int j = 0; j < col; ++j) {
					sf::RectangleShape rectangle(sf::Vector2f(sizeOfCell, sizeOfCell));
					rectangle.setPosition(j * sizeOfCell, i * sizeOfCell);
					rectangle.setOutlineThickness(sizeOfCell / 10);
					rectangle.setOutlineColor(sf::Color::Black);

					Cell *temp = b->getCell(i, j);

					sf::Color tempColor(252, 32, 157);

					if (temp->getInfo().statetype == StateType::Snake && b->isFront(i, j)) rectangle.setFillColor(tempColor);
					else if (temp->getInfo().statetype == StateType::Empty) rectangle.setFillColor(sf::Color::White);
					else if (temp->getInfo().statetype == StateType::Food) rectangle.setFillColor(sf::Color::Blue);
					else if (temp->getInfo().statetype == StateType::Snake) rectangle.setFillColor(sf::Color::Red);

					window.draw(rectangle);
				}
			}
		}
		window.display();
	}

	delete b;
}

int WinMain() {

	sf::Text text;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cerr << "Did not load font" << std::endl;
		return 1;
	}
	text.setFont(font);
	text.setString("Would you like to play again? (y/n)");

	sf::Text playerInput;
	playerInput.setFont(font);
	playerInput.setPosition(0, 30);
	std::string playerInput_S;
	while (1) {		
		playerInput_S = "";
		playerInput.setString(playerInput_S);
		playGame();
		sf::RenderWindow MainWindow(sf::VideoMode(1000, 500), "Play Again?");
		bool playAgain = false;
		while (MainWindow.isOpen()) {
			sf::Event event;
			while (MainWindow.pollEvent(event)) {
				if (event.type == sf::Event::Closed) MainWindow.close();
				else if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode < 128) {
						if (event.text.unicode == 13) {
							if (playerInput_S == "y") {
								MainWindow.close();
								playAgain = true;
							}else MainWindow.close();
						}
						else if (event.text.unicode == 8) {
							playerInput_S = playerInput_S.substr(0, playerInput_S.size() - 1);
							playerInput.setString(playerInput_S);
						}
						else {
							char temp = static_cast<char>(event.text.unicode);
							playerInput_S += temp;
							playerInput.setString(playerInput_S);
						}
					}
				}
			}
			MainWindow.clear();
			MainWindow.draw(text);
			MainWindow.draw(playerInput);
			MainWindow.display();
		}
		if (!playAgain) break;
	}

	
	return 0;
}

