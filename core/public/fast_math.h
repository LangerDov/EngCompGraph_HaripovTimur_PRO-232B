#pragma once
#define USE_AVX
#ifdef USE_AVX
#include <intrin.h>

void vec4_sum_f(const float* a,const float *b, float* res)
{
	__m256 mmA = _mm256_loadu_ps(a);
	__m256 mmB = _mm256_loadu_ps(b);
	__m256 c = _mm256_add_ps(mmA, mmB);
	_mm256_storeu_ps(res, c);
}

void vec4_mul_onk_f(const float* a, const float k, float* res)
{
	__m256 mmA = _mm256_loadu_ps(a);
	float b[] = { k,k,k,k };
	__m256 mmB = _mm256_loadu_ps(b);
	__m256 c = _mm256_mul_ps(mmA, mmB);
	_mm256_storeu_ps(res, c);
}
#endif