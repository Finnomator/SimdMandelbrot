#include "LessBranchesSimdRenderer.h"
#include <immintrin.h>
#include <iostream>

using namespace std;

LessBranchesSimdRenderer::LessBranchesSimdRenderer(int width, int height, bool double_precision) : SimdRenderer(width, height, double_precision) {
}

void LessBranchesSimdRenderer::GenerateFractalDoublePrecision() {
	const int step_size = 4;

	// constants

	const __m256d _zero = _mm256_set1_pd(0);
	const __m256i _zero_i = _mm256_set1_epi64x(0);
	const __m256d _one = _mm256_set1_pd(1);
	const __m256i _one_i = _mm256_set1_epi64x(1);
	const __m256d _two = _mm256_set1_pd(2);
	const __m256d _four = _mm256_set1_pd(4);
	const __m256i _height = _mm256_set1_epi64x(height);
	const __m256i _width = _mm256_set1_epi64x(width);
	const __m256d _ratio = _mm256_set1_pd(ratio);
	const __m256i _max_iteration = _mm256_set1_epi64x(max_iteration);
	const __m256i _step_size = _mm256_set1_epi64x(step_size);
	const __m256i _x_offsets = _mm256_set_epi64x(0, 1, 2, 3);

	__m256i _px = _x_offsets;
	__m256i _py = _zero_i;
	__m256d _y0 = _mm256_set1_pd(-1.0);
	__m256d _x0 = _mm256_mul_pd(_mm256_sub_pd(_mm256_div_pd(_mm256_mul_pd(_two, _mm256_castsi256_pd(_px)), _mm256_castsi256_pd(_width)), _one), _ratio);
	__m256d _x = _zero;
	__m256d _y = _zero;
	__m256i _iteration = _zero_i;

	__m256i _width_with_offset = _mm256_add_epi64(_width, _x_offsets);

	while (_py.m256i_i64[0] < height && _py.m256i_i64[1] < height && _py.m256i_i64[2] < height && _py.m256i_i64[3] < height) {

		const __m256d _xsqr = _mm256_mul_pd(_x, _x);
		const __m256d _ysqr = _mm256_mul_pd(_y, _y);

		const __m256i _mask = _mm256_and_si256(
			_mm256_castpd_si256(_mm256_cmp_pd(_mm256_add_pd(_xsqr, _ysqr), _four, _CMP_LE_OQ)),
			_mm256_cmpgt_epi64(_max_iteration, _iteration)
		);

		for (int i = 0; i < step_size; ++i) {
			if (_mask.m256i_i64[i] != 0)
				SetPixel(_px.m256i_i64[i], _py.m256i_i64[i], _iteration.m256i_i64[i]);
		}

		const __m256d _xtemp = _mm256_add_pd(_mm256_sub_pd(_xsqr, _ysqr), _x0);
		_y = _mm256_castsi256_pd(_mm256_and_si256(_mm256_castpd_si256(_mm256_add_pd(_mm256_mul_pd(_mm256_mul_pd(_two, _x), _y), _y0)), _mask));
		_x = _mm256_and_pd(_xtemp, _mm256_castsi256_pd(_mask));
	
		_iteration = _mm256_and_si256(_mm256_add_epi64(_iteration, _mm256_and_si256(_mask, _one_i)), _mask);
		_px = _mm256_add_epi64(_px, _mm256_andnot_si256(_mask, _step_size));
		const __m256i _px_reached_width = _mm256_or_si256(_mm256_cmpgt_epi64(_px, _width), _mm256_cmpeq_epi64(_px, _width));
		_py = _mm256_add_epi64(_py, _mm256_and_si256(_px_reached_width, _one_i));
		_px = _mm256_andnot_si256(_px_reached_width, _px);
		_px = _mm256_add_epi64(_px, _mm256_and_si256(_px_reached_width, _x_offsets));

		_y0 = _mm256_sub_pd(_mm256_div_pd(_mm256_mul_pd(_two, _mm256_castsi256_pd(_py)), _mm256_castsi256_pd(_height)), _one);
		_x0 = _mm256_mul_pd(_mm256_sub_pd(_mm256_div_pd(_mm256_mul_pd(_two, _mm256_castsi256_pd(_px)), _mm256_castsi256_pd(_width)), _one), _ratio);
	}
}

void LessBranchesSimdRenderer::GenerateFractalSinglePrecision() {
}
