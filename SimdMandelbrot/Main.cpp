#include <iostream>
#include <SFML/Graphics.hpp>
#include "UnoptimizedRenderer.h"
#include "RendererO1.h"
#include "SimdRendererO1.h"
#include "LessBranchesSimdRenderer.h"
#include "LessBranchesRenderer.h"
#include <chrono>

using namespace std;
using namespace chrono;

int main() {

	const int width = 1280;
	const int height = 720;

	sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot");
	window.setFramerateLimit(60);

	SimdRendererO1 render(width, height, false);

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