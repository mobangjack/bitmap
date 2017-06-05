#include "bitmapio.h"

void BitMapIO_ToString(char* str, const BitMap_t* bitmap)
{
	uint32_t i, j, n, k, offset = 0;
	uint8_t l, mask;
	for (i = 0; i < bitmap->rows; i++) {
		for (j = 0; j < bitmap->cols; j++) {
			n = i * bitmap->cols + j;
			k = n / BIT_MAP_BIT_WIDTH;
			l = n % BIT_MAP_BIT_WIDTH;
			mask = 1u << l;
			if (bitmap->pbytes[k] & mask) {
				str[n + offset] = '1';
			}
			else {
				str[n + offset] = '0';
			}
		}
		offset++;
		str[n + offset] = '\n';
	}
}

void BitMapIO_Print(const BitMap_t* bitmap)
{
	uint32_t i, j;
	for (i = 0; i < bitmap->rows; i++) {
		for (j = 0; j < bitmap->cols; j++) {
			if (BitMap_Get(bitmap, i, j)) {
				printf("1");
			}
			else {
				printf("0");
			}
		}
		printf("\n");
	}
	printf("sum: %d\n", BitMap_Sum(bitmap));
	printf("\n");
}

