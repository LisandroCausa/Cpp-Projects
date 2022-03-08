#include "key.hpp"

key::key(const float x, const sf::SoundBuffer buffer, const sf::Keyboard::Key keyboard, const bool sharp, const sf::String t)
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

void key::input(bool& hasClicked, sf::RenderWindow& window)
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

bool key::isSharp()
{
	return is_sharp;
}

void key::draw_screen(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(text);
}