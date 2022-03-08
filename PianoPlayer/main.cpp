// Using SFML 2.5.1
#include "SFML/Graphics.hpp" 
#include "SFML/Audio.hpp"


class key
{
private:
	int y;
	bool pressable;
	bool is_sharp;
	sf::Color normal_color;
	sf::Color pressed_color;
	sf::Vector2f key_pos;
	sf::Vector2i mouse;
public:
	sf::RectangleShape rect;
	sf::SoundBuffer sound_buffer;
	sf::Sound sound;
	sf::Keyboard::Key keyboard_key;
	sf::Font font;
	sf::Text text;


	key(const float x, const sf::SoundBuffer buffer, const sf::Keyboard::Key keyboard, const bool sharp, const sf::String t)
	{
		font.loadFromFile("Resources/Fonts/arial.ttf");
		text = sf::Text(t, font, 32);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Bold);
		is_sharp = sharp;
		if (is_sharp)
		{
			y = 190;
			text.setPosition(x + 25, y + 70);
			rect = sf::RectangleShape(sf::Vector2f(70.0f, 120.0f));
			normal_color = sf::Color(60, 60, 60, 255);
			pressed_color = sf::Color(30, 30, 30, 255);
		}
		else
		{
			y = 200;
			text.setPosition(x + 30, y + 150);
			rect = sf::RectangleShape(sf::Vector2f(80.0f, 200.0f));
			normal_color = sf::Color::White;
			pressed_color = sf::Color(200, 200, 200, 255);
		}
		rect.setFillColor(normal_color);
		rect.setPosition(sf::Vector2f(x, y));

		sound_buffer = buffer;
		sound.setBuffer(sound_buffer);

		keyboard_key = keyboard;
		pressable = true;
	}

	void input(bool& hasClicked, sf::RenderWindow& window)
	{
		mouse = sf::Mouse::getPosition(window);
		key_pos = rect.getPosition();
		if (!hasClicked && sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse.x >= key_pos.x && mouse.x <= key_pos.x + rect.getSize().x && mouse.y >= key_pos.y && mouse.y <= key_pos.y + rect.getSize().y)
		{
			hasClicked = true;
			if (pressable)
			{
				sound.play();
				pressable = false;
			}
			rect.setFillColor(pressed_color);
		}
		else if (sf::Keyboard::isKeyPressed(keyboard_key))
		{
			if (pressable)
			{
				sound.play();
				pressable = false;
			}
			rect.setFillColor(pressed_color);
		}
		else
		{
			pressable = true;
			rect.setFillColor(normal_color);
		}
	}

	bool isSharp()
	{
		return is_sharp;
	}

	void draw_screen(sf::RenderWindow& window)
	{
		window.draw(rect);
		window.draw(text);
	}
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(775, 600), "Piano Player");
	window.setFramerateLimit(40);

	sf::Image* icon{ new sf::Image };
	(*icon).loadFromFile("Resources/Icon.png");
	window.setIcon((*icon).getSize().x, (*icon).getSize().y, (*icon).getPixelsPtr());
	delete icon;

	sf::RectangleShape background(sf::Vector2f(1000, 1000));
	background.setFillColor(sf::Color(155, 155, 155, 255));

	sf::Font title_font;
	title_font.loadFromFile("Resources/Fonts/RobotoMono-Thin.ttf");
	sf::Text title_text("Piano Player", title_font, 40);
	title_text.setPosition(240, 50);
	title_text.setStyle(sf::Text::Style::Bold);

	sf::SoundBuffer* buffer{ new sf::SoundBuffer[13] };
	buffer[0].loadFromFile("Resources/Sounds/C5.wav");
	buffer[1].loadFromFile("Resources/Sounds/C#5.wav");
	buffer[2].loadFromFile("Resources/Sounds/D5.wav");
	buffer[3].loadFromFile("Resources/Sounds/D#5.wav");
	buffer[4].loadFromFile("Resources/Sounds/E5.wav");
	buffer[5].loadFromFile("Resources/Sounds/F5.wav");
	buffer[6].loadFromFile("Resources/Sounds/F#5.wav");
	buffer[7].loadFromFile("Resources/Sounds/G5.wav");
	buffer[8].loadFromFile("Resources/Sounds/G#5.wav");
	buffer[9].loadFromFile("Resources/Sounds/A5.wav");
	buffer[10].loadFromFile("Resources/Sounds/A#5.wav");
	buffer[11].loadFromFile("Resources/Sounds/B5.wav");
	buffer[12].loadFromFile("Resources/Sounds/C6.wav");

	key keys[] = {
		key(50, buffer[0], sf::Keyboard::Q, false, "Q"),
/*SHARP*/ key(97.5, buffer[1], sf::Keyboard::Num2, true, "2"),
		key(135, buffer[2], sf::Keyboard::W, false, "W"),
/*SHARP*/ key(182.5, buffer[3], sf::Keyboard::Num3, true, "3"),
		key(220, buffer[4], sf::Keyboard::E, false, "E"),
		key(305, buffer[5], sf::Keyboard::R, false, "R"),
/*SHARP*/ key(352.5, buffer[6], sf::Keyboard::Num5, true, "5"),
		key(390, buffer[7], sf::Keyboard::T, false, "T"),
/*SHARP*/ key(437.5, buffer[8], sf::Keyboard::Num6, true, "6"),
		key(475, buffer[9], sf::Keyboard::Y, false, "Y"),
/*SHARP*/ key(522.5, buffer[10], sf::Keyboard::Num7, true, "7"),
		key(560, buffer[11], sf::Keyboard::U, false, "U"),
		key(645, buffer[12], sf::Keyboard::I, false, "I"),
	};
	
	delete[] buffer;

	bool hasClicked{ false };

	sf::Event event;
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
			window.close();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(background);
		window.draw(title_text);

		hasClicked = false;

		for (int i{ 0 }; i < 13; ++i)
		{
			if (keys[i].isSharp())
			{
				keys[i].input(hasClicked, window);
			}
		}
		for (int i{ 0 }; i < 13; ++i)
		{
			if (keys[i].isSharp() == false)
			{
				keys[i].input(hasClicked, window);
			}
		}

		for (int i{ 0 }; i < 13; ++i)
		{
			if (keys[i].isSharp() == false)
			{
				keys[i].draw_screen(window);
			}
		}
		for (int i{ 0 }; i < 13; ++i)
		{
			if (keys[i].isSharp())
			{
				keys[i].draw_screen(window);
			}
		}

		window.display();
	}
	return 0;
}