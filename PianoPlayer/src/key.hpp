#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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

	key(const float x, const sf::SoundBuffer buffer, const sf::Keyboard::Key keyboard, const bool sharp, const sf::String t);

	void input(bool& hasClicked, sf::RenderWindow& window);
	bool isSharp();
	void draw_screen(sf::RenderWindow& window);
};

#endif