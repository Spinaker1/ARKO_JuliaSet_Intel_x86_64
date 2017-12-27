#include <SFML/Graphics.hpp>
#include <iostream>

extern "C" void juliaSet(unsigned* pPixelBuffer, int width, int height);

int main()
{
	int width = 600;
	int height = 450;
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

	sf::Texture texture;
	if (!texture.create(width, height))
	{
		// error...
	}
	sf::Uint8* pixels = new sf::Uint8[width * height * 4]; 


	for (int i = 0; i < width*height; i++) {
		pixels[4*i] = 0;
		pixels[4*i+1] = 0;
		pixels[4*i+2] = 0;
		pixels[4*i+3] = 255;
	}


	juliaSet((unsigned *)pixels, width, height);

	texture.update(pixels);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
} 