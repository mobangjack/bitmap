#include "bitmapit.h"

void BitMapIt_Init(BitMapIt_t* bitmapit, BitMap_t* bitmap)
{
	bitmapit->bitmap = bitmap;
	BitMapIt_Begin(bitmapit);
}

void BitMapIt_Begin(BitMapIt_t* bitmapit)
{
	bitmapit->i = 0;
	bitmapit->j = 0;
	bitmapit->n = 0;
	bitmapit->k = 0;
	bitmapit->l = 0;
	bitmapit->mask = 0;
	bitmapit->flag = 0;
	bitmapit->s = 0;
}

uint8_t BitMapIt_Next(BitMapIt_t* bitmapit)
{
	if (bitmapit->n < bitmapit->bitmap->nbits) {
		if (bitmapit->j < bitmapit->bitmap->cols - 1) {
			bitmapit->j++;
			bitmapit->flag &= ~BITMAPIT_FLAG_BR; // Clear row back return flag
		}
		else if (bitmapit->i < bitmapit->bitmap->rows - 1) {
			bitmapit->i++;
			bitmapit->j = 0;
			bitmapit->flag |= BITMAPIT_FLAG_BR; // Set row back return flag
		}
		bitmapit->n++;
		bitmapit->k = bitmapit->n / BIT_MAP_BIT_WIDTH;
		bitmapit->l = bitmapit->n % BIT_MAP_BIT_WIDTH;
		bitmapit->mask = 1u << bitmapit->l;
		if (bitmapit->bitmap->pbytes[bitmapit->k] & bitmapit->mask) {
			bitmapit->flag |= BITMAPIT_FLAG_CV; // Set current value flag
			bitmapit->s++;
		}
		else {
			bitmapit->flag &= ~BITMAPIT_FLAG_CV; // Clear current value flag
		}
		bitmapit->flag &= ~BITMAPIT_FLAG_RD; // Clear read flag
		bitmapit->flag &= ~BITMAPIT_FLAG_WR; // Clear write flag
		return 1;
	}
	return 0;
}

uint8_t BitMapIt_Get(BitMapIt_t* bitmapit)
{
	bitmapit->flag |= BITMAPIT_FLAG_RD; // Set read flag
	return bitmapit->flag & BITMAPIT_FLAG_CV; // Return bit value
}

void BitMapIt_Set(BitMapIt_t* bitmapit)
{
	if (!(bitmapit->flag & BITMAPIT_FLAG_CV)) {
		bitmapit->s++;
	}
	bitmapit->bitmap->pbytes[bitmapit->k] |= bitmapit->mask; // Set bit
	bitmapit->flag |= BITMAPIT_FLAG_WR; // Set write flag
}

void BitMapIt_Clr(BitMapIt_t* bitmapit)
{
	bitmapit->bitmap->pbytes[bitmapit->k] &= ~bitmapit->mask; // Clear bit
	bitmapit->flag |= BITMAPIT_FLAG_WR; // Set write flag
}

void BitMapIt_Tog(BitMapIt_t* bitmapit)
{
	if (bitmapit->bitmap->pbytes[bitmapit->k] & bitmapit->mask) {
		bitmapit->bitmap->pbytes[bitmapit->k] &= ~bitmapit->mask; // Clear bit
	}
	else {
		bitmapit->bitmap->pbytes[bitmapit->k] |= bitmapit->mask; // Set bit
	}
	bitmapit->flag |= BITMAPIT_FLAG_WR; // Set write flag
}
