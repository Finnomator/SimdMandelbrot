#include "RendererO2.h"
#include <immintrin.h>
#include <iostream>

RendererO2::RendererO2(int width, int height, bool double_precision) : Renderer(width, height) {
	this->double_precision = double_precision;
}

void RendererO2::GenerateFractal() {
	if (double_precision)
		GenerateFractalDoublePrecision();
	else
		GenerateFractalSinglePrecision();
}

void RendererO2::GenerateFractalDoublePrecision() {

	const int step_size = 4;

	// constants

	const __m256d _one = _mm256_set1_pd(1);
	const __m256i _one_i = _mm256_set1_epi64x(1);
	const __m256d _two = _mm256_set1_pd(2);
	const __m256d _four = _mm256_set1_pd(4);
	const __m256d _height = _mm256_set1_pd(height);
	const __m256d _width = _mm256_set1_pd(width);
	const __m256d _ratio = _mm256_set1_pd(ratio);
	const __m256i _max_iteration = _mm256_set1_epi64x(max_iteration);
	const __m256d _x_offsets = _mm256_set_pd(0, 1, 2, 3);

	for (int py = 0; py < height; ++py) {

		__m256d _y0 = _mm256_sub_pd(_mm256_div_pd(_mm256_mul_pd(_two, _mm256_set1_pd(py)), _height), _one);

		for (int px = 0; px < width; px += step_size) {

			__m256d _x0 = _mm256_mul_pd(_mm256_sub_pd(_mm256_div_pd(_mm256_mul_pd(_two, _mm256_add_pd(_mm256_set1_pd(px), _x_offsets)), _width), _one), _ratio);
			__m256d _x = _mm256_set1_pd(0);
			__m256d _y = _mm256_set1_pd(0);
			__m256i _iteration = _mm256_set1_epi64x(0);

			__m256i _mask2 = _mm256_and_si256(
				_mm256_castpd_si256(_mm256_cmp_pd(_mm256_add_pd(_mm256_mul_pd(_x, _x), _mm256_mul_pd(_y, _y)), _four, _CMP_LT_OQ)),
				_mm256_cmpgt_epi64(_max_iteration, _iteration)
			);

			while (_mm256_movemask_pd(_mm256_castsi256_pd(_mask2)) != 0) {

				const __m256d _xsqr = _mm256_mul_pd(_x, _x);
				const __m256d _ysqr = _mm256_mul_pd(_y, _y);

				const __m256d _xtemp = _mm256_add_pd(_mm256_sub_pd(_xsqr, _ysqr), _x0);
				_y = _mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_two, _x), _y), _y0);
				_x = _xtemp;

				_mask2 = _mm256_and_si256(
					_mm256_and_si256(
						_mm256_castpd_si256(_mm256_cmp_pd(_mm256_add_pd(_xsqr, _ysqr), _four, _CMP_LT_OQ)),
						_mm256_cmpgt_epi64(_max_iteration, _iteration)
					), _mask2
				);

				_iteration = _mm256_add_epi64(_iteration, _mm256_and_si256(_mask2, _one_i));
			}

			for (int i = 0; i < step_size; ++i) {
				SetPixel(px + i, py, char(_iteration.m256i_i64[step_size - i - 1]));
			}
		}
	}
}

void RendererO2::GenerateFractalSinglePrecision() {

	const int step_size = 8;

	// constants

	const __m256 _one = _mm256_set1_ps(1);
	const __m256i _one_i = _mm256_set1_epi32(1);
	const __m256 _two = _mm256_set1_ps(2);
	const __m256 _four = _mm256_set1_ps(4);
	const __m256 _height = _mm256_set1_ps(height);
	const __m256 _width = _mm256_set1_ps(width);
	const __m256 _ratio = _mm256_set1_ps(ratio);
	const __m256i _max_iteration = _mm256_set1_epi32(max_iteration);
	const __m256 _x_offsets = _mm256_set_ps(0, 1, 2, 3, 4, 5, 6, 7);

	for (int py = 0; py < height; ++py) {

		const __m256 _y0 = _mm256_sub_ps(_mm256_div_ps(_mm256_mul_ps(_two, _mm256_set1_ps(py)), _height), _one);

		for (int px = 0; px < width; px += step_size) {

			const __m256 _x0 = _mm256_mul_ps(_mm256_sub_ps(_mm256_div_ps(_mm256_mul_ps(_two, _mm256_add_ps(_mm256_set1_ps(px), _x_offsets)), _width), _one), _ratio);
			__m256 _x = _mm256_set1_ps(0);
			__m256 _y = _mm256_set1_ps(0);
			__m256i _iteration = _mm256_set1_epi32(0);

			__m256i _mask2 = _mm256_and_si256(
				_mm256_castps_si256(_mm256_cmp_ps(_mm256_add_ps(_mm256_mul_ps(_x, _x), _mm256_mul_ps(_y, _y)), _four, _CMP_LT_OQ)),
				_mm256_cmpgt_epi32(_max_iteration, _iteration)
			);

			while (_mm256_movemask_ps(_mm256_castsi256_ps(_mask2)) != 0) {

				const __m256 _xsqr = _mm256_mul_ps(_x, _x);
				const __m256 _ysqr = _mm256_mul_ps(_y, _y);

				__m256 _xtemp = _mm256_add_ps(_mm256_sub_ps(_xsqr, _ysqr), _x0);
				_y = _mm256_add_ps(_mm256_mul_ps(_mm256_mul_ps(_x, _two), _y), _y0);
				_x = _xtemp;

				_mask2 = _mm256_and_si256(
					_mm256_and_si256(
						_mm256_castps_si256(_mm256_cmp_ps(_mm256_add_ps(_xsqr, _ysqr), _four, _CMP_LT_OQ)),
						_mm256_cmpgt_epi32(_max_iteration, _iteration)
					), _mask2
				);

				_iteration = _mm256_add_epi32(_iteration, _mm256_and_si256(_mask2, _one_i));
			}

			for (int i = 0; i < step_size; ++i) {
				SetPixel(px + i, py, char(_iteration.m256i_i32[step_size - i - 1]));
			}
		}
	}
}
