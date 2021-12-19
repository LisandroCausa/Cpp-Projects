// Using SFML 2.5.1
#include <SFML/Graphics.hpp>
#include <sstream>


sf::Vector2i searchCellInGrid(sf::Vector2i mouse, unsigned short cellSpace);


int main()
{
	const unsigned int screenSizeX = 800;
	const unsigned int screenSizeY = 800;

	sf::RenderWindow window(sf::VideoMode(screenSizeX, screenSizeY), "Conway's Game of Life - by Lisandro Causa");
	window.setFramerateLimit(45);
	unsigned short updateCount = 1;

	const sf::Vector2f pauseRectSize = sf::Vector2f(50, 115);

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

	bool pause = false;
	bool wasKeyPressed = false;

	const unsigned int size = 72; // grid size

	bool grid[size][size];
	bool temp_grid[size][size];

	unsigned short neighbours;

	unsigned int population = 0;

	const unsigned short pixelsPerCell = 10;
	const unsigned short pixelsBetweenCells = 1;

	for (unsigned int y = 0; y < size; y++) // Start all cells at 0
	{
		for (unsigned int x = 0; x < size; x++)
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i* cellXY = new sf::Vector2i;
				*cellXY = searchCellInGrid(sf::Mouse::getPosition(window), pixelsPerCell + pixelsBetweenCells);
				grid[cellXY->y][cellXY->x] = true;
				delete cellXY;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				sf::Vector2i* cellXY = new sf::Vector2i;
				*cellXY = searchCellInGrid(sf::Mouse::getPosition(window), pixelsPerCell + pixelsBetweenCells);
				grid[cellXY->y][cellXY->x] = false;
				delete cellXY;
			}
		}

		window.clear(sf::Color::Black);

		population = 0;
		for (unsigned int y = 0; y < size; y++)
		{
			for (unsigned int x = 0; x < size; x++)
			{
				if (grid[y][x])
				{
					sf::RectangleShape* cell = new sf::RectangleShape(sf::Vector2f(pixelsPerCell, pixelsPerCell));
					cell->setPosition(x * (pixelsPerCell + pixelsBetweenCells), y * (pixelsPerCell + pixelsBetweenCells));
					window.draw(*cell);
					delete cell;
					population++;
				}
			}
		}

		if (!pause)
		{
			updateCount--;
			if (updateCount == 0)
			{
				updateCount = 4;
				for (unsigned int y = 0; y < size; y++)
				{
					for (unsigned int x = 0; x < size; x++)
					{
						neighbours = 0;
						if (y > 0)
						{
							if (x > 0)
								if (grid[y - 1][x - 1]) neighbours++;

							if (x < size - 1)
								if (grid[y - 1][x + 1]) neighbours++;

							if (grid[y - 1][x]) neighbours++;
						}
						if (x > 0)
							if (grid[y][x - 1]) neighbours++;

						if (x < size - 1)
							if (grid[y][x + 1]) neighbours++;

						if (y < size - 1)
						{
							if (x > 0)
								if (grid[y + 1][x - 1]) neighbours++;

							if (x < size - 1)
								if (grid[y + 1][x + 1]) neighbours++;

							if (grid[y + 1][x]) neighbours++;
						}

						if (grid[y][x])
							temp_grid[y][x] = neighbours == 2 || neighbours == 3;
						else
							temp_grid[y][x] = neighbours == 3;
					}
				}

				for (unsigned int y = 0; y < size; y++)
				{
					for (unsigned int x = 0; x < size; x++)
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


sf::Vector2i searchCellInGrid(sf::Vector2i mouse, unsigned short cellSpace)
{
	sf::Vector2i result;
	result.x = int(mouse.x / cellSpace);
	result.y = int(mouse.y / cellSpace);
	return result;
}