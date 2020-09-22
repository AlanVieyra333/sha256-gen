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

char* hash_msg(uint8_t message[128], uint8_t hash[32]) {
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

void gen_msg(uint8_t msg[128]) {
  // char test[64] =
  //     "50aa1d9bfd848b6560edcdb0a95ee3fa0ff36b8cb6cdc6a5ee0dfdc41087dc56";
  char characters[16] = "0123456789abcdef";

  for (uint8_t i = 0; i < 64; i++) {
    msg[i] = characters[rand() % 16];
  }
}

void find_hash(const char* hash_str) {
  uint8_t hash_target[32];
  uint8_t msg_padded[128];
  uint8_t hash_result[32];

  hex_to_bytes(hash_str, hash_target);
  // printf("Hash: %s\n", bytes_to_hex(hash_target, 32));
  padding(msg_padded);
  // printf("Padding: %s\n", bytes_to_hex(msg_padded, 128));

  while (1) {
    gen_msg(msg_padded);
    hash_msg(msg_padded, hash_result);

    if (!memcmp(hash_result, hash_target, 32)) {
      msg_padded[64] = 0;
      printf("Complete.\nMessage: %s\n", msg_padded);

      printf("SHA256 hash: ");
      printf("%02X%02X%02X...%02X%02X%02X\n", hash_result[0], hash_result[1],
            hash_result[2], hash_result[29], hash_result[30], hash_result[31]);
      break;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(
        stderr,
        "Example: ./find-message "
        "4852c8159c4fcde8444ec454acc21381680c990f2fc611e8a713513b494e6bc5\n");
    return 1;
  }

  srand(time(NULL));
  find_hash(argv[1]);

  return 0;
}