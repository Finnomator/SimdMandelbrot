#include <iostream>
#include <SFML/Graphics.hpp>
#include "UnoptimizedRenderer.h"
#include "RendererO1.h"
#include "RendererO2.h"
#include <chrono>

using namespace std;
using namespace chrono;

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Mandelbrot");
	window.setFramerateLimit(60);

	RendererO2 render(window.getSize().x, window.getSize().y, false);

	bool redraw = true;

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				redraw = true;
		}

		if (!redraw)
			continue;

		window.clear();

		auto start = high_resolution_clock::now();
		sf::Sprite* sprite = render.Render();
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		cout << "Rendered in " << duration.count() << "ms" << endl;

		window.draw(*sprite);
		window.display();
		redraw = false;
	}
}