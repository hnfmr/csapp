#ifndef INCLUDE_CS_LIB_H_
#define INCLUDE_CS_LIB_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* replaces the i-th byte of x with b */
unsigned replace_byte(unsigned x, int i, unsigned char b);

/* returns 1 if x contains 1, 0 otherwise */
int any_bit_equals_one(int x);

/* returns 1 if x contains 0, 1 otherwise. supports 8-bit and 32-bit, signed and unsigned*/
int abez(int x, size_t len);
int uabez(unsigned x, size_t len);

/* tests if lsb has 1 */
int lsb_has_one(int x);

/* tests if msb has 0 */
int msb_has_zero(int x, size_t len);
int umsb_has_zero(unsigned x, size_t len);

#define w_assert(message, test) do { if (!(test)) return message; } while (0)
#define w_run_test(test) do { char *message = test(); tests_run++; \
  if (message) return message; } while (0)
extern int tests_run;

#ifdef __cplusplus
}
#endif
#endif
