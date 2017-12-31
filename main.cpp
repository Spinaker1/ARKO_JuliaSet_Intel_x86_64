#include <SFML/Graphics.hpp>
#include <iostream>

extern "C" void juliaSet(double cX, double cY, double moveX, double moveY, unsigned * pixels, int width, int height, int zoom);

void draw(sf::RenderWindow * window, double cX, double cY, double moveX, double moveY, int width, int height, int zoom) {
	sf::Texture texture;
	if (!texture.create(width, height))
	{
		// error...
	}
	sf::Uint8* pixels = new sf::Uint8[width * height * 4];


	for (int i = 0; i < width*height; i++) {
		pixels[4 * i] = 0;
		pixels[4 * i + 1] = 0;
		pixels[4 * i + 2] = 0;
		pixels[4 * i + 3] = 0;
	}

	juliaSet(cX, cY, moveX, moveY, (unsigned *)pixels, width, height, zoom);

	texture.update(pixels);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	window->clear();
	window->draw(sprite);
	window->display();
}

int main()
{
	int width = 800;
	int height = 600;
	int zoom = 1;
	double cX = -0.73;
	double cY = 0.19;
	double moveX = 0.0;
	double moveY = 0.0;
	double zX = -1.5;
	double zY = -1.0;
	int i = 1;

	sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(width, height), "Julia sets");
	draw(window, cX, cY, moveX, moveY, width, height, zoom);


	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					double x = (double)event.mouseButton.x;
					double w = (double)width;
					moveX = 1.5 * (x - w / 2) / (0.5 * w * (double)zoom) + moveX;

					double y = (double)event.mouseButton.y;
					double h = (double)height;
					moveY = (y - h / 2) / (0.5 * h * (double)zoom) + moveY;

					zoom *= 2;
					i++;
					moveX = 3.0 / pow(2.0,i) + moveX;
					moveY = 2.0 / pow(2.0,i) + moveY;

					draw(window, cX, cY, moveX, moveY, width, height, zoom);
				}
			}
		}
	}

	delete window;
	return 0;
} 