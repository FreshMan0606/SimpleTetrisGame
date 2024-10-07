#include <sfml\Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
#include <sfml\Audio.hpp>
#include <imgui.h>
#include <imgui-sfml.h>

int main() {
	srand(time(0));
	const int fieldWidth = 10;
	const int fieldHeight = 20;




	enum class Type {
		None = 0,
		O,
		I,
		L,
		J,
		S,
		T,
		Z,
	};

	sf::Texture backGroundTexture;
	if (!backGroundTexture.loadFromFile("background.png")) {
		return EXIT_FAILURE;
	}
	backGroundTexture.setRepeated(true);

	Type field[fieldWidth][fieldHeight] = {};

	sf::Texture yellowTexture;
	if (!yellowTexture.loadFromFile("yellow.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture lightBlueTexture;
	if (!lightBlueTexture.loadFromFile("light_blue.png")) {
		return EXIT_FAILURE;
	}

	sf::Texture orangeTexture;
	if (!orangeTexture.loadFromFile("orange.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture blueTexture;
	if (!blueTexture.loadFromFile("blue.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture greenTexture;
	if (!greenTexture.loadFromFile("green.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture purpleTexture;
	if (!purpleTexture.loadFromFile("purple.png")) {
		return EXIT_FAILURE;
	}
	sf::Texture redTexture;
	if (!redTexture.loadFromFile("red.png")) {
		return EXIT_FAILURE;
	}

	std::map<Type, std::vector<std::vector<sf::Vector2i>>> shapes = {
		{
			Type::O,
			{	{
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
					sf::Vector2i(0, -1),
					sf::Vector2i(1, -1)
				}
			},
		},
		{
			Type::I,
			{
				{
					sf::Vector2i(-1, 0),
					sf::Vector2i(0, 0),
					sf::Vector2i(1, 0),
					sf::Vector2i(2, 0)
				},

				{
					sf::Vector2i(0, 2),
					sf::Vector2i(0, -1),
					sf::Vector2i(0, 0),
					sf::Vector2i(0, 1)
				}
			}
		},
		{
			Type::L,
			{
				{
					sf::Vector2i(0,0),	//  o
					sf::Vector2i(-1,0),	//ooo
					sf::Vector2i(1,0),
					sf::Vector2i(1,-1)
				},
				{
					sf::Vector2i(1,1),
					sf::Vector2i(0,1),		//o
					sf::Vector2i(0,-1),		//o
					sf::Vector2i(0,0)		//oo

				},

				{
					sf::Vector2i(0,0),	//oo  
					sf::Vector2i(0,1),	// o  
					sf::Vector2i(0,-1),	// o 
					sf::Vector2i(-1,-1)
				},
				{
					sf::Vector2i(1,0),	//ooo
					sf::Vector2i(0,0),	//o
					sf::Vector2i(-1,0),
					sf::Vector2i(-1,1)
				}
			}
		},
		{
			Type::J,
			{
				{
					sf::Vector2i(0,0),	//o
					sf::Vector2i(1,0),	//ooo
					sf::Vector2i(-1,0),
					sf::Vector2i(-1,-1)
				},
				{
					sf::Vector2i(0,0),
					sf::Vector2i(0,-1),	    // o
					sf::Vector2i(0,1),		// o
					sf::Vector2i(-1,1)		//oo

				},
				{
					sf::Vector2i(0,0),	//ooo
					sf::Vector2i(-1,0),	//  o
					sf::Vector2i(1,0),
					sf::Vector2i(1,1)
				},
				{
					sf::Vector2i(0,0),	// oo
					sf::Vector2i(0,1),	// o
					sf::Vector2i(0,-1),	// o
					sf::Vector2i(1,-1)
				}

			}
		},
		{
			Type::S,
			{
				{
					sf::Vector2i(1,-1),
					sf::Vector2i(0,-1), 	    // 
					sf::Vector2i(-1,0),		// ss
					sf::Vector2i(0,0)		//ss

				},
				{
					sf::Vector2i(0,0),	//s
					sf::Vector2i(0,-1),	//ss
					sf::Vector2i(1,0),	// s
					sf::Vector2i(1,1)
				},

			}
		},
		{
			Type::T,
			{
				{
					sf::Vector2i(0,0),
					sf::Vector2i(0,-1), 	//	T
					sf::Vector2i(-1,0),		// TTT
					sf::Vector2i(1,0)		//

				},
				{
					sf::Vector2i(0,-1),	//T
					sf::Vector2i(0,0),	//TT
					sf::Vector2i(1,0),	//T
					sf::Vector2i(0,1)
				},
				{
					sf::Vector2i(0,0),	//
					sf::Vector2i(-1,0),	//TTT
					sf::Vector2i(1,0),	// T
					sf::Vector2i(0,1)
				},
				{
					sf::Vector2i(0,-1),	// T
					sf::Vector2i(0,0),	//TT
					sf::Vector2i(-1,0),	// T
					sf::Vector2i(0,1)
				},

			}
		},
		{
			Type::Z,
			{
				{
					sf::Vector2i(-1,-1),
					sf::Vector2i(0,-1), 	// 
					sf::Vector2i(1,0),		//zz
					sf::Vector2i(0,0)		// zz

				},
				{
					sf::Vector2i(0,0),	// z  s
					sf::Vector2i(0,1),	//zz  ss
					sf::Vector2i(-1,1),	//z	   s
					sf::Vector2i(-1,2)
				},

			}
		}
	};

	Type currentType = Type(rand() % 7 + 1);
	Type NextType = Type(rand() % 7 + 1);
	int currentIndex = 0;

	const int blockWidth = yellowTexture.getSize().x;
	const int blockHeight = yellowTexture.getSize().y;

	const int windowWidth = blockWidth * fieldWidth;
	const int windowHeight = blockHeight * fieldHeight;


	std::map<Type, sf::Sprite> sprites{
		{ Type::O, sf::Sprite(yellowTexture) },
		{ Type::I, sf::Sprite(lightBlueTexture) },
		{ Type::L, sf::Sprite(orangeTexture) },
		{ Type::J, sf::Sprite(blueTexture) },
		{ Type::S, sf::Sprite(greenTexture) },
		{ Type::T, sf::Sprite(purpleTexture) },
		{ Type::Z, sf::Sprite(redTexture) },
	};

	sf::Sprite backGroundSprite(backGroundTexture, sf::IntRect(0, 0, windowWidth, windowHeight));

	std::vector<sf::Vector2i> currentShape;
	sf::Sprite currentSprite;

	sf::Vector2i origin(fieldWidth / 2, 0);
	sf::Vector2i pos(origin);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "TetrisGame");
	if (!ImGui::SFML::Init(window)) {
		return EXIT_FAILURE;
	}


	sf::SoundBuffer bufferPutdown;
	if (!bufferPutdown.loadFromFile("putdownsound.mp3")) {
		return EXIT_FAILURE;
	}
	sf::Sound putDownSound(bufferPutdown);


	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("bombsound.wav")) {
		return EXIT_FAILURE;
	}
	sf::Sound Bombsound(buffer);
	
	sf::Music music;
	if (!music.openFromFile("spacetravel.wav")) {
		return EXIT_FAILURE;
	}
	music.play();
	music.setLoop(true);
	music.setVolume(30.f);

	sf::Clock clock;

	int change = 0;
	bool RightLeft_move = true;

	while (window.isOpen()) {

		currentShape = shapes[currentType][currentIndex];
		currentSprite = sprites[currentType];

		enum class Action {
			Hold = 0,
			MoveDown,
			MoveLeft,
			MoveRight,
			Rotate,
			SPACE,
			SWITCH,
			SPEED_UP
		};
		Action action = Action::Hold;
		
		sf::Event event;
		while (window.pollEvent(event)) {

			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			if (event.type == sf::Event::KeyPressed) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					action = Action::SPACE;
				}

				switch (event.key.code) {
				case sf::Keyboard::Left:
					if (RightLeft_move) {
						action = Action::MoveLeft;
					}
					break;
				case sf::Keyboard::Right:
					if (RightLeft_move) {
						action = Action::MoveRight;
					}
					break;
				case sf::Keyboard::Up:
					action = Action::Rotate;
					break;
				case sf::Keyboard::LShift:
					action = Action::SWITCH;
					break;
				case sf::Keyboard::Down:
					action = Action::SPEED_UP;
					break;
				}
				
			}
		}

		if (action == Action::SWITCH && change == 0) {
			currentType = Type(rand() % 7 + 1);
			pos = origin;
			RightLeft_move = true;
			change++;
		}

		if (clock.getElapsedTime().asSeconds() >= 0.3f) {
			action = Action::MoveDown;
			clock.restart();
		}
		
		sf::Vector2i nextPos(pos);
		int nextIndex = currentIndex;
		if (action == Action::Rotate && RightLeft_move) {
			nextIndex = (nextIndex + 1) % shapes[currentType].size();
		}

		std::vector<sf::Vector2i> nextShape = shapes[currentType][nextIndex];	
		switch (action) {
		case Action::Hold:
			break;
		case Action::MoveDown:
			nextPos.y++;
			break;
		case Action::MoveLeft:
			nextPos.x--;
			break;
		case Action::MoveRight:
			nextPos.x++;
			break;
		case Action::SPEED_UP:
			nextPos.y++;
			break;
		case Action::SPACE: {
			
			while (true) {
				sf::Vector2i tempPos = nextPos;
				tempPos.y++; // 將y座標增加1，嘗試往下移動

				int countEmpty = 0;
				for (const auto& d : currentShape) {
					sf::Vector2i np = tempPos + d;
					if (np.x >= 0 && np.x < fieldWidth &&
						np.y < fieldHeight &&
						(np.y < 0 || field[np.x][np.y] == Type::None)) {
						countEmpty++;
					}
				}

				if (countEmpty == currentShape.size()) {
					nextPos = tempPos; // 如果可以往下移，就更新位置
				}
				else {
					break; // 如果不能往下移，退出循環
				}
			}
			RightLeft_move = false;
			change = 0;
			break;
		}
			
			
		}

		int countEmpty = 0;
		for(const auto& d : nextShape) {
			sf::Vector2i np = nextPos + d;
			if (np.x >= 0 && np.x < fieldWidth && 
				np.y < fieldHeight && 
				(np.y < 0 || field[np.x][np.y] == Type::None)) {
				countEmpty++;
			}
		}
		
		if (countEmpty == 4) {
			pos = nextPos;
			currentIndex = nextIndex;
			currentShape = nextShape;
			
		}
		else {
			if (action == Action::MoveDown) {
				for (const auto& d : currentShape) {
					sf::Vector2i np = pos + d;
					if (np.y > 0) {
						field[np.x][np.y] = currentType;
						putDownSound.play();
					}
					else if (np.y < 0) {
						return EXIT_SUCCESS;
					}
				}
				for (int y = 0; y < fieldHeight; ++y) {
					bool isfull = true;
					for (int x = 0; x < fieldWidth; ++x) {
						if (field[x][y] == Type::None) {
							isfull = false;
						}
					}
					if (isfull) {
						Bombsound.play();
						for (int ty = y; ty > 0; --ty) {
							for (int x = 0; x < fieldWidth; ++x) {
								field[x][ty] = field[x][ty - 1];
							}
						}
						for (int x = 0; x < fieldWidth; ++x) {
							field[x][0] = Type::None;
						}
					}
				}
				
				pos = origin;
				currentType = Type(rand() % 7 + 1);
				currentIndex = 0;
				RightLeft_move = true;
			}
		}
		
		window.clear(sf::Color(190, 190, 190));

		window.draw(backGroundSprite);

		for (int y = 0; y < fieldHeight; ++y) {
			for (int x = 0; x < fieldWidth; ++x) {
				if (field[x][y] == Type::None) continue;
				sf::Sprite& s = sprites[field[x][y]];
				s.setPosition(float(x* blockWidth), float(y* blockHeight));
				window.draw(s);
			}
		}

		for (const auto& d : currentShape) {
			sf::Vector2i np = pos + d;
			currentSprite.setPosition(float(np.x* blockWidth), float(np.y* blockHeight));
			window.draw(currentSprite);
		}
		
		window.display();
	}


	return EXIT_SUCCESS;

}