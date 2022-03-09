// Using SFML 2.5.1
#include <SFML/Graphics.hpp>
#include <sstream>


sf::Vector2i searchCellInGrid(const sf::Vector2i mouse, const int cellSpace);


int main()
{
	constexpr int screenSizeX{ 800 };
	constexpr int screenSizeY{ 800 };

	sf::RenderWindow window(sf::VideoMode(screenSizeX, screenSizeY), "Conway's Game of Life - by Lisandro Causa");
	window.setFramerateLimit(45);
	int updateCount{ 1 };

	const sf::Vector2f pauseRectSize{ sf::Vector2f(50, 115) };

	sf::RectangleShape pauseRect1(pauseRectSize);
	pauseRect1.setFillColor(sf::Color::Red);
	pauseRect1.setPosition(645, 670);

	sf::RectangleShape pauseRect2(pauseRectSize);
	pauseRect2.setFillColor(sf::Color::Red);
	pauseRect2.setPosition(735, 670);

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text populationText;
	populationText.setFont(font);
	populationText.setString("Population");
	populationText.setCharacterSize(28);
	populationText.setPosition(5, 700);
	populationText.setFillColor(sf::Color::Blue);
	populationText.setStyle(sf::Text::Style::Bold);

	std::stringstream ss_pop;

	bool pause{ false };
	bool wasKeyPressed{ false };

	constexpr int size{ 72 }; // grid size

	bool grid[size][size]{};
	bool temp_grid[size][size]{};

	int neighbours{};

	int population{ 0 };

	constexpr int pixelsPerCell{ 10 };
	constexpr int pixelsBetweenCells{ 1 };

	for (int y{ 0 }; y < size; ++y) // Start all cells at false (dead)
	{
		for (int x{ 0 }; x < size; ++x)
		{
			grid[y][x] = false;
			temp_grid[y][x] = false;
		}
	}

	grid[4][4] = true;
	grid[4][5] = true;
	grid[4][6] = true;
	grid[3][6] = true;
	grid[2][5] = true;

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (wasKeyPressed == false)
			{
				pause = !pause;
				wasKeyPressed = true;
			}
		}
		else
		{
			wasKeyPressed = false;
		}

		if (sf::Mouse::getPosition(window).x > 0 &&
			sf::Mouse::getPosition(window).x < screenSizeX &&
			sf::Mouse::getPosition(window).y > 0 &&
			sf::Mouse::getPosition(window).y < screenSizeY)
		{
			sf::Vector2i cell{ searchCellInGrid(sf::Mouse::getPosition(window), pixelsPerCell + pixelsBetweenCells) };
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				grid[cell.y][cell.x] = true;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				grid[cell.y][cell.x] = false;
			}
		}

		window.clear(sf::Color::Black);

		population = 0;
		for (int y{ 0 }; y < size; ++y)
		{
			for (int x{ 0 }; x < size; ++x)
			{
				if (!grid[y][x])
					continue;
				sf::RectangleShape cell(sf::Vector2f(pixelsPerCell, pixelsPerCell));
				cell.setPosition(static_cast<float>(x * (pixelsPerCell + pixelsBetweenCells)), static_cast<float>(y * (pixelsPerCell + pixelsBetweenCells)));
				window.draw(cell);
				++population;
			}
		}

		if (!pause)
		{
			--updateCount;
			if (updateCount == 0)
			{
				updateCount = 4;
				for (int y{ 0 }; y < size; ++y)
				{
					for (int x{ 0 }; x < size; ++x)
					{
						neighbours = 0;
						if (y > 0)
						{
							if (x > 0)
								if (grid[y - 1][x - 1]) ++neighbours;

							if (x < size - 1)
								if (grid[y - 1][x + 1]) ++neighbours;

							if (grid[y - 1][x]) ++neighbours;
						}
						if (x > 0)
							if (grid[y][x - 1]) ++neighbours;

						if (x < size - 1)
							if (grid[y][x + 1]) ++neighbours;

						if (y < size - 1)
						{
							if (x > 0)
								if (grid[y + 1][x - 1]) ++neighbours;

							if (x < size - 1)
								if (grid[y + 1][x + 1]) ++neighbours;

							if (grid[y + 1][x]) ++neighbours;
						}

						if (grid[y][x])
							temp_grid[y][x] = neighbours == 2 || neighbours == 3;
						else
							temp_grid[y][x] = neighbours == 3;
					}
				}

				for (int y{ 0 }; y < size; ++y)
				{
					for (int x{ 0 }; x < size; ++x)
					{
						grid[y][x] = temp_grid[y][x];
						temp_grid[y][x] = false;
					}
				}
			}
		}
		else
		{
			window.draw(pauseRect1);
			window.draw(pauseRect2);
		}
		ss_pop.str("");
		ss_pop.clear();
		ss_pop << population;
		populationText.setString("Population: " + (ss_pop.str()));
		window.draw(populationText);

		window.display();
	}
	return 0;
}


sf::Vector2i searchCellInGrid(const sf::Vector2i mouse, const int cellSpace)
{
	sf::Vector2i result( static_cast<int>(static_cast<double>(mouse.x) / cellSpace), static_cast<int>(static_cast<double>(mouse.y) / cellSpace));
	return result;
}