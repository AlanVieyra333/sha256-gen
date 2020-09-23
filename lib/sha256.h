#include <stdint.h>

#define L_ROTATE(x, y) (((x) << (y)) | ((x) >> (32 - (y))))
#define R_ROTATE(x, y) (((x) >> (y)) | ((x) << (32 - (y))))
#define Sigma0(x) (R_ROTATE((x), 2) ^ R_ROTATE((x), 13) ^ R_ROTATE((x), 22))
#define Sigma1(x) (R_ROTATE((x), 6) ^ R_ROTATE((x), 11) ^ R_ROTATE((x), 25))
#define sigma0(x) (R_ROTATE((x), 7) ^ R_ROTATE((x), 18) ^ ((x) >> 3))
#define sigma1(x) (R_ROTATE((x), 17) ^ R_ROTATE((x), 19) ^ ((x) >> 10))

#define Ch(x, y, z) (((x) & (y)) ^ ((~(x)) & (z)))
#define Maj(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

void sha256_process(uint32_t state[8], const uint8_t data[], uint32_t length);
