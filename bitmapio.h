#ifndef __BITMAPIO_H__
#define __BITMAPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#include "bitmap.h"
#include "bitmapit.h"

void BitMapIO_ToString(char* str, const BitMap_t* bitmap);
void BitMapIO_Print(const BitMap_t* bitmap);

#ifdef __cplusplus
}
#endif

#endif
