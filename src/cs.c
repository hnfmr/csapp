#include "cs.h"
#include <assert.h>

/* last full byte */
#define LFB 0xff

/////utilities
int ibit(int x, int i) {
  return (x >> i) & 0x1;
}

int get_msb(int x) {
  return (x >> (sizeof(int) - 1) * 8) & LFB;
}

int get_lsb(int x) {
  return x & LFB;
}

/////

unsigned replace_byte(unsigned x, int i, unsigned char b) {
  int shift_offset = i * 8;
  return x & ~(LFB << shift_offset) | b << shift_offset;
}

int any_bit_equals_one(int x) {
  return ibit(x, 0) | ibit(x, 1) | ibit(x, 2) | ibit(x, 3) |
      ibit(x, 4) | ibit(x, 5) | ibit(x, 6) | ibit(x, 7) |
      ibit(x, 8) | ibit(x, 9) | ibit(x, 10) | ibit(x, 11) |
      ibit(x, 12) | ibit(x, 13) | ibit(x, 14) | ibit(x, 15) |
      ibit(x, 16) | ibit(x, 17) | ibit(x, 18) | ibit(x, 19) |
      ibit(x, 20) | ibit(x, 21) | ibit(x, 22) | ibit(x, 23) |
      ibit(x, 24) | ibit(x, 25) | ibit(x, 26) | ibit(x, 27) |
      ibit(x, 28) | ibit(x, 29) | ibit(x, 30) | ibit(x, 31);
}

int abez32(int x) {
  return !(ibit(x, 0) & ibit(x, 1) & ibit(x, 2) & ibit(x, 3) &
      ibit(x, 4) & ibit(x, 5) & ibit(x, 6) & ibit(x, 7) &
      ibit(x, 8) & ibit(x, 9) & ibit(x, 10) & ibit(x, 11) &
      ibit(x, 12) & ibit(x, 13) & ibit(x, 14) & ibit(x, 15) &
      ibit(x, 16) & ibit(x, 17) & ibit(x, 18) & ibit(x, 19) &
      ibit(x, 20) & ibit(x, 21) & ibit(x, 22) & ibit(x, 23) &
      ibit(x, 24) & ibit(x, 25) & ibit(x, 26) & ibit(x, 27) &
      ibit(x, 28) & ibit(x, 29) & ibit(x, 30) & ibit(x, 31));
}

int uabez32(unsigned x) {
  return !(ibit(x, 0) & ibit(x, 1) & ibit(x, 2) & ibit(x, 3) &
      ibit(x, 4) & ibit(x, 5) & ibit(x, 6) & ibit(x, 7) &
      ibit(x, 8) & ibit(x, 9) & ibit(x, 10) & ibit(x, 11) &
      ibit(x, 12) & ibit(x, 13) & ibit(x, 14) & ibit(x, 15) &
      ibit(x, 16) & ibit(x, 17) & ibit(x, 18) & ibit(x, 19) &
      ibit(x, 20) & ibit(x, 21) & ibit(x, 22) & ibit(x, 23) &
      ibit(x, 24) & ibit(x, 25) & ibit(x, 26) & ibit(x, 27) &
      ibit(x, 28) & ibit(x, 29) & ibit(x, 30) & ibit(x, 31));
}

int uabez8(unsigned char x) {
  return !(ibit(x, 0) & ibit(x, 1) & ibit(x, 2) & ibit(x, 3) &
	   ibit(x, 4) & ibit(x, 5) & ibit(x, 6) & ibit(x, 7));
}

int abez8(char x) {
  return !(ibit(x, 0) & ibit(x, 1) & ibit(x, 2) & ibit(x, 3) &
     ibit(x, 4) & ibit(x, 5) & ibit(x, 6) & ibit(x, 7));
}

int uabez(unsigned x, size_t len) {
  switch (len) {
  case 1:
    return uabez8(x);
  case 4:
    return uabez32(x);
  default:
    assert(0);
  }
}

int abez(int x, size_t len) {
  switch (len) {
  case 1:
    return abez8(x);
  case 4:
    return abez32(x);
  default:
    assert(0);
  }
}

int lsb_has_one(int x) {
  return any_bit_equals_one(get_lsb(x));
}

int msb_has_zero(int x, size_t len) {
  return abez((char)get_msb(x), sizeof(char));
}

int umsb_has_zero(unsigned x, size_t len) {
  return uabez((unsigned char)get_msb(x), sizeof(unsigned char));
}

int int_shifts_are_arithmetic() {
  return ~0>>3 == ~0;
}

unsigned srl(unsigned x, int k) {
  unsigned xsra = (int) x >> k;
  size_t leftShiftSize = sizeof(int) * 8 - k;
  return xsra & ~(~0<<leftShiftSize);
}

int sra(int x, int k) {
  int xsrl = (unsigned) x >> k;
  size_t leftShiftSize = sizeof(int) * 8 - k;
  /* This might break coding convention. But no better solution I could find.*/
  const int bit8 = 0x80000000;
  if (x & bit8) {
    return xsrl | (~0<<leftShiftSize);
  }
  return xsrl;
}
