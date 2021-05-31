/* sha256.c - SHA reference implementation using C            */

#include "sha256.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

static const uint32_t K256[64] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1,
    0x923F82A4, 0xAB1C5ED5, 0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3,
    0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174, 0xE49B69C1, 0xEFBE4786,
    0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147,
    0x06CA6351, 0x14292967, 0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13,
    0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85, 0xA2BFE8A1, 0xA81A664B,
    0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A,
    0x5B9CCA4F, 0x682E6FF3, 0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208,
    0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2};

/* Avoid undefined behavior                    */
/* https://stackoverflow.com/q/29538935/608639 */
uint32_t B2U32(uint8_t val, uint8_t sh) { return ((uint32_t)val) << sh; }

void hash_round(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d, uint32_t *e,
                uint32_t *f, uint32_t *g, uint32_t *h, uint32_t W, uint32_t K) {
  uint32_t T1 = Sigma1(*e) + Ch(*e, *f, *g) + *h + K + W;
  uint32_t T2 = Sigma0(*a) + Maj(*a, *b, *c);

  *h = *g;
  *g = *f;
  *f = *e;
  *e = *d + T1;
  *d = *c;
  *c = *b;
  *b = *a;
  *a = T1 + T2;
}

void print_w(uint32_t W[16]) {
  printf("W:\n");
  for (size_t i = 0; i < 16; i++) {
    printf("%08x,", W[i]);
  }
  printf("\n");
}

void print_st(uint32_t state[8]) {
  printf("State:\n");
  for (size_t i = 0; i < 8; i++) {
    printf("%08x,", state[i]);
  }
  printf("\n");
}

/**
 * Create W matrix with the input data block (64 bytes).
*/
void create_matrix_w(uint32_t W[64], const uint8_t data_block[64]) {
  uint32_t s0, s1;
  uint8_t i;
  
  for (i = 0; i < 64; i++) {
    if (i < 16){
      W[i] = B2U32(data_block[4*i + 0], 24) |
              B2U32(data_block[4*i + 1], 16) |
              B2U32(data_block[4*i + 2], 8) |
              B2U32(data_block[4*i + 3], 0);
    } else {
      // Depends of vars (4 bytes): a, b, c, d, e, f, g, h, W, K256
      s0 = sigma0(W[i - 15]);
      s1 = sigma1(W[i - 2]);
      W[i] = W[i - 16] + s0 + W[i - 7] + s1;
    }
  }
}

/* Process multiple blocks. The caller is responsible for setting the initial */
/*  state, and the caller is responsible for padding the final block.        */
void sha256_process(uint32_t state[8], const uint8_t data[], uint32_t length) {
  uint32_t a, b, c, d, e, f, g, h;
  uint8_t i;
  uint32_t W[64];

  size_t blocks = length / 64;

  for (uint8_t block_num=0; block_num < blocks; block_num++) {
    a = state[0];
    b = state[1];
    c = state[2];
    d = state[3];
    e = state[4];
    f = state[5];
    g = state[6];
    h = state[7];

    printf("\n########## ROUND: %d\n", block_num);

    create_matrix_w(W, &data[block_num*64]);
    print_w(W);

    // Depends of vars (4 bytes): a, b, c, d, e, f, g, h, W, K256
    for (i = 0; i < 64; i++) {
      // printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", a, b, c, d, e, f, g, h, Wi,
      //        K256[i]);
      hash_round(&a, &b, &c, &d, &e, &f, &g, &h, W[i], K256[i]);
      // printf(",%u,%u,%u,%u,%u,%u,%u,%u\n", a, b, c, d, e, f, g, h);
    }
    
    print_st(state);
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    state[4] += e;
    state[5] += f;
    state[6] += g;
    state[7] += h;
    print_st(state);

    // NOTE:
    // c = A + b
    // E = c + d
    // then
    // E = A + b + d
    // E - A = b + d
  }
}
