#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sha256.h"
#include "utils.h"

void padding(uint8_t out[]) {
  memset(out + 64, 0, 64);
  out[64] = 0x80;
  out[126] = 2;
}

void hash_msg(uint8_t message[128], uint8_t hash[32]) {
  /* initial state */
  uint32_t state[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                       0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  sha256_process(state, message, 128);

  for (uint8_t i = 0; i < 8; i++) {
    hash[i * 4 + 0] = (uint8_t)(state[i] >> 24);
    hash[i * 4 + 1] = (uint8_t)(state[i] >> 16);
    hash[i * 4 + 2] = (uint8_t)(state[i] >> 8);
    hash[i * 4 + 3] = (uint8_t)(state[i] >> 0);
  }
}

void test(const char message[64]) {
  uint8_t msg_padded[128];
  uint8_t hash_result[32];

  memcpy(msg_padded, message, 64);
  padding(msg_padded);

  hash_msg(msg_padded, hash_result);

  // printf("SHA256 hash:\n%s\n", bytes_to_hex(hash_result, 32));
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(
        stderr,
        "Example: ./sha256 "
        "50aa1d9bfd848b6560edcdb0a95ee3fa0ff36b8cb6cdc6a5ee0dfdc41087dc56\n");
    return 1;
  }

  test(argv[1]);

  return 0;
}