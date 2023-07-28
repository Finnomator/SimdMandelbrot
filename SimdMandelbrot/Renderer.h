#pragma once
#include <SFML/Graphics.hpp>
class Renderer
{
public:
	Renderer(int width, int height);
	sf::Sprite* Render();
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Uint8* pixels;
	int width;
	int height;
	const int max_iteration = 100;
	double ratio;
	virtual void GenerateFractal() = 0;
	virtual void SetPixel(int i, char r, char g, char b);
	void SetPixel(int x, int y, char all_channels);
	virtual void SetPixel(int x, int y, char r, char g, char b);
};
