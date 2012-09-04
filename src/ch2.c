#include "cs.h"
#include <stdio.h>

static int x1 = 0x01010101;
static int x2 = 0;
static int x4 = 0x01010000;
static int x5 = 0xffffffff;

int tests_run = 0;

// 2.60
static char* test_replace_bytes() {
  w_assert("Failed: replace bytes - 0", replace_byte(x1, 0, 0xAB) == 0x010101ab);
  w_assert("Failed: replace bytes - 1", replace_byte(x1, 1, 0xAB) == 0x0101ab01);
  w_assert("Failed: replace bytes - 2", replace_byte(x1, 2, 0xAB) == 0x01ab0101);
  w_assert("Failed: replace bytes - 3", replace_byte(x1, 3, 0xAB) == 0xab010101);
  return 0;
}

// 2.61
static char* test_any_bit_equals_one() {
  w_assert("Failed: any bit equals one - x1", any_bit_equals_one(x1) == 1);
  w_assert("Failed: any bit equals one - x2", any_bit_equals_one(x2) == 0);
  w_assert("Failed: any bit equals one - x4", any_bit_equals_one(x4) == 1);
  return 0;
}

static char* test_any_bit_equals_zero() {
  w_assert("Failed: any bit equals zero - x1", abez(x1, sizeof(x1)) == 1);
  w_assert("Failed: any bit equals zero - x2", abez(x2, sizeof(x2)) == 1);
  w_assert("Failed: any bit equals zero - x4", abez(x4, sizeof(x4)) == 1);
  return 0;
}

static char* test_lsb_has_one() {
  w_assert("Failed: lsb has one - x1", lsb_has_one(x1) == 1);
  w_assert("Failed: lsb has one - x4", lsb_has_one(x4) == 0);
}

static char* test_msb_has_zero() {
  w_assert("Failed: msb has zero - x1", msb_has_zero(x1, sizeof(x1)) == 1);
  w_assert("Failed: msb has zero - x2", msb_has_zero(x2, sizeof(x2)) == 1);
  w_assert("Failed: msb has zero - x4", msb_has_zero(x4, sizeof(x4)) == 1);
  w_assert("Failed: msb has zero - x5", msb_has_zero(x5, sizeof(x5)) == 0);
  return 0;
}

static char* test_shifts_are_arithmetic() {
  w_assert("int shifts are not arithmetic", int_shifts_are_arithmetic() != 0);
  return 0;
}

static char* test_right_shifts() {
  unsigned x1 = 0x12345678;
  unsigned x2 = 0x1234;
  unsigned x3 = 0xffff;
  unsigned x4 = 0xf3ffffff;

  int x5 = 0x12345678;
  int x6 = 0x1234;
  int x7 = 0xffff;
  int x8 = 0xf3ffffff;
  w_assert("Failed: srl 4 x1", srl(x1, 4) == 0x1234567);
  w_assert("Failed: srl 24 x1", srl(x1, 24) == 0x12);

  w_assert("Failed: srl 4 x3", srl(x3, 4) == 0xfff);
  w_assert("Failed: srl 12 x3", srl(x3, 12) == 0xf);

  w_assert("Failed: sra 4 x1", sra(x1, 4) == 0x1234567);
  w_assert("Failed: sra 24 x1", sra(x1, 24) == 0x12);

  w_assert("Failed: sra 4 x4", sra(x4, 4) == 0xff3fffff);
  w_assert("Failed: sra 24 x4", sra(x4, 24) == 0xfffffff3);

  w_assert("Failed: sra 4 x8", sra(x8, 4) == 0xff3fffff);
  w_assert("Failed: sra 24 x8", sra(x8, 24) == 0xfffffff3);
  return 0;
}

static char* all_tests() {
  w_run_test(test_replace_bytes);
  w_run_test(test_any_bit_equals_one);
  w_run_test(test_any_bit_equals_zero);
  w_run_test(test_lsb_has_one);
  w_run_test(test_msb_has_zero);
  w_run_test(test_shifts_are_arithmetic);
  w_run_test(test_right_shifts);
  return 0;
}

int main() {
  char* result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  }
  else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
