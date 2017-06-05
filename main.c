#include "bitmap.h"
#include "bitmapio.h"
#include "bitmapit.h"
#include <stdio.h>
#include <math.h>

int main()
{
	uint32_t i = 0;

	BitMap_t* bitmap = BitMap_Create(5, 5);
	if (bitmap == NULL) {
		printf("Fail to create bitmap\n");
		return -1;
	}

	for (i = 0; i < bitmap->cols; i++) {
		BitMap_Set(bitmap, i, i, 1);
	}
	
	BitMap_t* copy = BitMap_CopyOf(bitmap);
	if (copy != NULL) {
		BitMap_Set(copy, 2, 2, 0);
		BitMapIO_Print(copy);
		BitMap_Xor(copy, bitmap);
		BitMapIO_Print(copy);
		BitMap_Destroy(copy);
	}

	BitMapIO_Print(bitmap);
	BitMap_Destroy(bitmap);

	getchar();
	
	return 0;
}
