#include <iostream>
#include <cstdint>
#include <vector>

#include "include/salsa20.h"

int main(){
  StreamCipher* test;
  Salsa20 salsa20({88, 118, 104, 54, 79, 201, 235, 79, 
                                                3, 81, 156, 47, 203, 26, 244, 243,
                                                191, 187, 234, 136, 211, 159, 13, 115,
                                                76, 55, 82, 183, 3, 117, 222, 37,
                                                86, 16, 179, 207, 49, 237, 179, 48,
                                                 1, 106, 178, 219, 175, 199, 166, 48,
                                               238, 55, 204, 36, 31, 240, 32, 63, 15,
                                                83, 93, 161, 116, 147, 48, 113}, 20);
  test = &salsa20;
  std::vector<uint8_t> output = test->Hash(); 
  for(auto it : output){
    std::cout << int(it) << "\n";
  }
  return 0;
}
