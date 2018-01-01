#include <SFML/Graphics.hpp>
#include <iostream>
#include <process.h> // wymagane ze wzglêdu na _beginthread
#include <windows.h>

CRITICAL_SECTION g_Section;

double cX = -0.8;
double cY = 0.156;
bool cHasChanged = false;

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

void __cdecl ThreadProc(void * Args)
{
	double tempCX, tempCY;
	while (true) {
		std::cout << std::endl << "Zamiana parametru cX" << std::endl << "Podaj cX:" << std::endl;
		std::cin >> tempCX;
		std::cout << "Podaj cY:" << std::endl;
		std::cin >> tempCY;

		EnterCriticalSection(&g_Section);
		cX = tempCX;
		cY = tempCY;
		cHasChanged = true;
		LeaveCriticalSection(&g_Section);
	}

	_endthread();
}

int main()
{
	std::cout << "Zbiory Julii" << std::endl << "START PROGRAMU" << std::endl;
	int width = 1000;
	int height = 750;
	int zoom = 1;
	double moveX = 0.0;
	double moveY = 0.0;
	int i = 1;

	sf::RenderWindow * window = new sf::RenderWindow(sf::VideoMode(width, height), "Julia sets");

	draw(window, cX, cY, moveX, moveY, width, height, zoom);

	InitializeCriticalSection(&g_Section);

	HANDLE hThread = (HANDLE)_beginthread(ThreadProc, 0, NULL);

	while (window->isOpen())
	{
		EnterCriticalSection(&g_Section);
		if (cHasChanged == true) {
			zoom = 1;
			moveX = 0;
			moveY = 0;
			draw(window, cX, cY, moveX, moveY, width, height, zoom);
			cHasChanged = false;
		}
		LeaveCriticalSection(&g_Section);

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

					EnterCriticalSection(&g_Section);
					draw(window, cX, cY, moveX, moveY, width, height, zoom);
					LeaveCriticalSection(&g_Section);
				}
			}
		}
	}

	delete window;
	return 0;
} 