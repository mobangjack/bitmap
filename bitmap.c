#include "bitmap.h"

void BitMap_Init(BitMap_t* bitmap, uint32_t rows, uint32_t cols, uint8_t* pbytes)
{
	bitmap->rows = rows;
	bitmap->cols = cols;
	bitmap->nbits = rows * cols;
	bitmap->nbytes = (uint32_t)ceil(((double)bitmap->nbits) / BIT_MAP_BIT_WIDTH);
	bitmap->pbytes = pbytes;
}

BitMap_t* BitMap_Create(uint32_t rows, uint32_t cols)
{
	BitMap_t* bitmap = (BitMap_t*)malloc(sizeof(BitMap_t));
	if (bitmap == NULL) return NULL;
	memset(bitmap, 0, sizeof(BitMap_t));
	bitmap->rows = rows;
	bitmap->cols = cols;
	bitmap->nbits = rows * cols;
	bitmap->nbytes = (uint32_t)ceil(((double)bitmap->nbits) / BIT_MAP_BIT_WIDTH);
	bitmap->pbytes = (uint8_t*)malloc(bitmap->nbytes);
	if (bitmap->pbytes == NULL) {
		free(bitmap);
		bitmap = NULL;
		return NULL;
	}
	memset(bitmap->pbytes, 0, bitmap->nbytes);
	return bitmap;
}

BitMap_t* BitMap_CopyOf(const BitMap_t* src)
{
	BitMap_t* bitmap = BitMap_Create(src->rows, src->cols);
	if (bitmap == NULL) return NULL;
	memcpy(bitmap->pbytes, src->pbytes, src->nbytes);
	return bitmap;
}

uint8_t BitMap_Get(const BitMap_t* src, uint32_t i, uint32_t j)
{
	uint32_t n = i * src->cols + j;
	uint32_t k = n / BIT_MAP_BIT_WIDTH;
	uint8_t l = n % BIT_MAP_BIT_WIDTH;
	uint8_t mask = 1u << l;
	return src->pbytes[k] & mask;
}

void BitMap_Set(BitMap_t* src, uint32_t i, uint32_t j, uint8_t val)
{
	uint32_t n = i * src->cols + j;
	uint32_t k = n / BIT_MAP_BIT_WIDTH;
	uint8_t l = n % BIT_MAP_BIT_WIDTH;
	uint8_t mask = 1u << l;
	if (val) {
		src->pbytes[k] |= mask;
	}
	else {
		src->pbytes[k] &= ~mask;
	}
}

void BitMap_Tog(BitMap_t* src, uint32_t i, uint32_t j)
{
	uint32_t n = i * src->cols + j;
	uint32_t k = n / BIT_MAP_BIT_WIDTH;
	uint8_t l = n % BIT_MAP_BIT_WIDTH;
	uint8_t mask = 1u << l;
	if (src->pbytes[k] & mask) {
		src->pbytes[k] &= ~mask;
	}
	else {
		src->pbytes[k] |= mask;
	}
}

void BitMap_And(BitMap_t* dst, const BitMap_t* src)
{
	uint32_t i = 0;
	for (; i < src->nbytes; i++) {
		dst->pbytes[i] &= src->pbytes[i];
	}
}

void BitMap_Or(BitMap_t* dst, const BitMap_t* src)
{
	uint32_t i = 0;
	for (; i < src->nbytes; i++) {
		dst->pbytes[i] |= src->pbytes[i];
	}
}

void BitMap_Not(BitMap_t* dst, const BitMap_t* src)
{
	uint32_t i = 0;
	for (; i < src->nbytes; i++) {
		dst->pbytes[i] = ~src->pbytes[i];
	}
}

void BitMap_Xor(BitMap_t* dst, const BitMap_t* src)
{
	uint32_t i = 0;
	for (; i < src->nbytes; i++) {
		dst->pbytes[i] ^= src->pbytes[i];
	}
}

uint32_t BitMap_Sum(const BitMap_t* bitmap)
{
	uint32_t i, j, s = 0;
	for (i = 0; i < bitmap->rows; i++) {
		for (j = 0; j < bitmap->cols; j++) {
			if (BitMap_Get(bitmap, i, j)) {
				s++;
			}
		}
	}
	return s;
}

void BitMap_Destroy(BitMap_t* bitmap)
{
	if (bitmap != NULL) {
		if (bitmap->pbytes != NULL) {
			free(bitmap->pbytes);
			bitmap->pbytes = NULL;
		}
		free(bitmap);
		bitmap = NULL;
	}
}

