#include <iostream>
#include <cstdint>
#include <vector>

#include "include/stream_ciphers.h"
#include "include/chacha20.h"
#include "include/salsa20.h"

int main(){
  StreamCipher* test = new StreamCipher;
  // chacha example | [RFC7539] example from section 2.3.2.
  ChaCha20 chacha({0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
		 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
		 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f},
		{0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00},
		1,10); 
  test = &chacha;
  std::vector<uint8_t> output_chacha = test->Hash();
  std::cout.flags(std::ios::hex | std::ios::showbase);
  for(auto it = output_chacha.begin(); it != output_chacha.end(); ++it){
    std::cout << int(*it) << " ";
  }
  std::cout << "\n\n";

  // salsa example | section 8 from Salsa20 specification document
  Salsa20 salsa({211,159, 13,115, 76, 55, 82,183, 3,117,222, 37,191,187,234,136,
		 49,237,179, 48, 1,106,178,219,175,199,166, 48, 86, 16,179,207,
		 31,240, 32, 63, 15, 83, 93,161,116,147, 48,113,238, 55,204, 36,
		 79,201,235, 79, 3, 81,156, 47,203, 26,244,243, 88,118,104, 54},20);
  test = &salsa;
  std::vector<uint8_t> output_salsa = test->Hash();
  std::cout.flags(std::ios::dec);
  for(auto it = output_salsa.begin(); it != output_salsa.end(); ++it){
    std::cout << int(*it) << " ";
  }
  std::cout << std::endl;
  return 0;
}
