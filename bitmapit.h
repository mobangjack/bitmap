#ifndef __BITMAPIT_H__
#define __BITMAPIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bitmap.h"

#define BITMAPIT_FLAG_CV ((uint8_t)0x01) // Current value flag
#define BITMAPIT_FLAG_BR ((uint8_t)0x02) // Row back return flag
#define BITMAPIT_FLAG_RD ((uint8_t)0x04) // Read flag
#define BITMAPIT_FLAG_WR ((uint8_t)0x08) // Write flag

typedef struct
{
	BitMap_t* bitmap; // Context
	uint32_t i; // Current row pointer
	uint32_t j; // Current col pointer
	uint32_t n; // Current bit pointer
	uint32_t k; // Current byte pointer
	uint8_t l; // Current bit offset (low bit first)
	uint8_t mask; // Current byte mask
	uint8_t flag; // IO Flag
	uint32_t s; // One count
}BitMapIt_t;

void BitMapIt_Init(BitMapIt_t* bitmapit, BitMap_t* bitmap);
void BitMapIt_Begin(BitMapIt_t* bitmapit);
uint8_t BitMapIt_Next(BitMapIt_t* bitmapit);
uint8_t BitMapIt_Get(BitMapIt_t* bitmapit);
void BitMapIt_Set(BitMapIt_t* bitmapit);
void BitMapIt_Clr(BitMapIt_t* bitmapit);
void BitMapIt_Tog(BitMapIt_t* bitmapit);

#ifdef __cplusplus
}
#endif

#endif
