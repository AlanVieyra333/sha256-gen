#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1

void gen_msg(uint8_t msg[64]) {
  char characters[16] = "0123456789abcdef";

  for (uint8_t i = 0; i < 64; i++) {
    msg[i] = characters[rand() % 16];
  }
}

void gen_msgs() {
  uint8_t msg[64];

  for (size_t i = 0; i < N; i++) {
    gen_msg(msg);
    printf("%s\n", msg);
  }
}

int main(int argc, char* argv[]) {
  srand(time(NULL));

  gen_msgs();

  return 0;
}