#include "RendererO2.h"
#include <immintrin.h>
#include <iostream>

RendererO2::RendererO2(int width, int height) : Renderer(width, height) {
}

void RendererO2::GenerateFractal() {

	const int step_size = 4;

	__m256i _color = _mm256_set1_epi64x(123);

	// constants

	__m256d _one = _mm256_set1_pd(1);
	__m256i _one_i = _mm256_set1_epi64x(1);
	__m256d _two = _mm256_set1_pd(2);
	__m256d _four = _mm256_set1_pd(4);
	__m256d _height = _mm256_set1_pd(height);
	__m256d _width = _mm256_set1_pd(width);
	__m256d _ratio = _mm256_set1_pd(ratio);
	__m256i _max_iteration = _mm256_set1_epi64x(max_iteration);


	for (int py = 0; py < height; ++py) {

		__m256d _y0 = _mm256_sub_pd(_mm256_div_pd(_mm256_mul_pd(_two, _mm256_set1_pd(py)), _height), _one);

		for (int px = 0; px < width; px += step_size) {

			__m256d _x0 = _mm256_mul_pd(_mm256_sub_pd(_mm256_div_pd(_mm256_mul_pd(_two, _mm256_add_pd(_mm256_set1_pd(px), _mm256_set_pd(0, 1, 2, 3))), _width), _one), _ratio);
			__m256d _x = _mm256_set1_pd(0);
			__m256d _y = _mm256_set1_pd(0);
			__m256i _iteration = _mm256_set1_epi64x(0);

			__m256i _mask2 = _mm256_and_si256(
				_mm256_castpd_si256(_mm256_cmp_pd(_mm256_add_pd(_mm256_mul_pd(_x, _x), _mm256_mul_pd(_y, _y)), _four, _CMP_LT_OQ)),
				_mm256_cmpgt_epi64(_max_iteration, _iteration)
			);

			while (_mm256_movemask_pd(_mm256_castsi256_pd(_mask2)) != 0) {

				__m256d _xsqr = _mm256_mul_pd(_x, _x);
				__m256d _ysqr = _mm256_mul_pd(_y, _y);

				__m256d _xtemp = _mm256_add_pd(_mm256_sub_pd(_xsqr, _ysqr), _x0);
				_y = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_two, _x), _y), _y0);
				_x = _xtemp;

				_mask2 = _mm256_and_si256(
					_mm256_and_si256(
						_mm256_castpd_si256(_mm256_cmp_pd(_mm256_add_pd(_xsqr, _ysqr), _four, _CMP_LT_OQ)),
						_mm256_cmpgt_epi64(_max_iteration, _iteration)
					), _mask2
				);

				_iteration = _mm256_add_epi64(_iteration, _mm256_and_si256(_mask2, _one_i));
				_color = _iteration;
			}

			for (int i = 0; i < step_size; ++i) {

				SetPixel(px + i, py, char(_color.m256i_i64[step_size - i - 1]));
			}
		}
	}
}
