#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>

struct timeval get_timestamp();
void hex_to_bytes(const char* hex_str, uint8_t bytes[]);
char* bytes_to_hex(uint8_t bytes[], size_t len);
void sha256_padding(uint8_t in[], size_t len, uint8_t out[]);
