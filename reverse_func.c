#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sha256.h"
#include "utils.h"


//#define Sigma0_inv(x) (L_ROTATE((x), 2) ^ ROTATE((x), 13) ^ ROTATE((x), 22))

void Sigma0_inv(uint32_t s0, uint32_t *x) {

}

int main(int argc, char* argv[]) {
  srand(time(NULL));

  uint32_t x = 0x00000001;
  uint32_t s0 = Sigma0(x);
  uint32_t x_base;

  printf("x = %u, Sigma0 = %u\n", x, s0);
  
  Sigma0_inv(s0, &x_base);
  printf("Test: %u\n", x_base);

  return 0;
}