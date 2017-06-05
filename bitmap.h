#ifndef __BITMAP_H__
#define __BITMAP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define BIT_MAP_BIT_WIDTH 8

typedef struct
{
	uint32_t cols; // Bit map columns
	uint32_t rows; // Bit map rows
	uint32_t nbits; // Number of bits
	uint32_t nbytes; // Number of bytes
	uint8_t* pbytes; // Bit map memory block
}BitMap_t; // BitMap struct typedef

void BitMap_Init(BitMap_t* bitmap, uint32_t rows, uint32_t cols, uint8_t* pbytes);
BitMap_t* BitMap_Create(uint32_t rows, uint32_t cols);
BitMap_t* BitMap_CopyOf(const BitMap_t* src);
uint8_t BitMap_Get(const BitMap_t* src, uint32_t i, uint32_t j);
void BitMap_Set(BitMap_t* src, uint32_t i, uint32_t j, uint8_t val);
void BitMap_Tog(BitMap_t* src, uint32_t i, uint32_t j);
void BitMap_And(BitMap_t* dst, const BitMap_t* src);
void BitMap_Or(BitMap_t* dst, const BitMap_t* src);
void BitMap_Not(BitMap_t* dst, const BitMap_t* src);
void BitMap_Xor(BitMap_t* dst, const BitMap_t* src);
uint32_t BitMap_Sum(const BitMap_t* bitmap);
void BitMap_Destroy(BitMap_t* bitmap);

#ifdef __cplusplus
}
#endif

#endif
