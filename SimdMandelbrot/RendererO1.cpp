#include "RendererO1.h"

RendererO1::RendererO1(int width, int height) : Renderer(width, height)
{
}

void RendererO1::GenerateFractal()
{
	for(int py = 0; py < height; ++py) {

		const double y0 = 2.0 * py / height - 1.0;

		for (int px = 0; px < width; ++px) {

			const double x0 = (2.0 * px / width - 1.0) * ratio;
			double x = 0;
			double y = 0;
			int iteration = 0;

			for (; x * x + y * y <= 4 && iteration < max_iteration; ++iteration) {
				double xtemp = x * x - y * y + x0;
				y = 2.0 * x * y + y0;
				x = xtemp;
			}

			SetPixel(px, py, iteration, iteration, iteration);
		}
	}
}
