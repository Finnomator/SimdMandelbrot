#include "LessBranchesRenderer.h"
#include <iostream>

using namespace std;

LessBranchesRenderer::LessBranchesRenderer(int width, int height) : Renderer(width, height) {
}

void LessBranchesRenderer::GenerateFractal() {
	int py = 0;
	int px = 0;

	double x = 0;
	double y = 0;

	int iteration = 0;

	double y0 =  -1.0;
	double x0 = -ratio;

	while (py < height) {

		const bool mask = x * x + y * y <= 4 && iteration < max_iteration;

		if (!mask)
			SetPixel(px, py, iteration);

		const double xtemp = x * x - y * y + x0;
		y = (2.0 * x * y + y0) * mask;
		x = xtemp * mask;

		iteration = (iteration + mask) * mask;
		px += !mask;
		const bool px_reached_width = px == width;
		py += px_reached_width;
		px *= !px_reached_width;

		y0 = 2.0 * py / height - 1.0;
		x0 = (2.0 * px / width - 1.0) * ratio;
	}
}
