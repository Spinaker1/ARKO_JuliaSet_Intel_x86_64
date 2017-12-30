#include <SFML/Graphics.hpp>
#include <iostream>

extern "C" void juliaSet(double cX, double cY, double moveX, double moveY, unsigned * pixels, int width, int height, int zoom);

int main()
{
	int width = 800;
	int height = 600;
	int zoom = 1;
	double cX = -0.73;
	double cY = 0.19;
	double moveX = 0;
	double moveY = 0;

	sf::RenderWindow window(sf::VideoMode(width, height), "Julia sets");

	sf::Texture texture;
	if (!texture.create(width, height))
	{
		// error...
	}
	sf::Uint8* pixels = new sf::Uint8[width * height * 4]; 


	for (int i = 0; i < width*height; i++) {
		pixels[4*i] = 0;
		pixels[4*i+1] = 0;
		pixels[4*i+2] = 255;
		pixels[4*i+3] = 255;
	}

	juliaSet(cX, cY, moveX, moveY, (unsigned *)pixels, width, height, zoom);

	texture.update(pixels);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	window.clear();
	window.draw(sprite);
	window.display();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				}
			}
		}
	}

	return 0;
} 