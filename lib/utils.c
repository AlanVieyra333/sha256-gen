#include "utils.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct timeval get_timestamp() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv;
}

void hex_to_bytes(const char* hex_str, uint8_t bytes[]) {
  int len = strlen(hex_str);

  for (int i = 0; i < len / 2; i++) {
    sscanf(&hex_str[2 * i], "%02x", (unsigned int *) &bytes[i]);
  }
}

char* bytes_to_hex(uint8_t bytes[], size_t len) {
  char* hex = (char*)malloc(sizeof(char) * (2 * len + 1));

  for (int i = 0; i < len; i++) {
    sprintf(&hex[2 * i], "%02x", bytes[i]);
  }

  hex[2 * len + 1] = 0;

  return hex;
}

void sha256_padding(uint8_t in[], size_t len, uint8_t out[]) {
  size_t l = len * 8;
  size_t k = (512 + 448 - (l % 512 + 1)) % 512;
  size_t padded_len = len + 1 + (k / 8) + 8;

  memset(out, 0, padded_len);
  memcpy(out, in, len);
  out[len] = 0x80;

  for (uint8_t i = 0; i < 8; i++) {
    out[padded_len - (i + 1)] = l >> (8 * i);
  }
}
