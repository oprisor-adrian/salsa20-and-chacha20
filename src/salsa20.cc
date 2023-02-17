#include "../include/salsa20.h"

Salsa20::Salsa20(const std::vector<uint8_t>& state, const uint32_t& rounds)
    : state_(state), rounds_(rounds){}

void Salsa20::DoubleRound(std::vector<uint32_t>& state){
  std::vector<uint8_t> row_order {0, 1, 2, 3, 5, 6, 7, 4,
                                  10, 11, 8, 9, 15, 12, 13, 14};
  std::vector<uint8_t> column_order {0, 4, 8, 12, 5, 9 , 13, 1,
   				     10, 14, 2, 6, 15, 3, 7, 11};
  CustomRound(kbits_, column_order, state);
  CustomRound(kbits_, row_order, state);
}

std::vector<uint8_t> Salsa20::Hash(){
  std::vector<uint32_t> output;
  auto it = state_.begin();
  for( unsigned int index = 0; index < 64; index++ ){
    std::vector<uint8_t> sec(it, it+4);
    output.push_back(LittleEndian(sec));
    it += 4;
  }
  std::vector<uint32_t> output_copy(output);
  for( unsigned int index=0; index < rounds_; index+=2){
    DoubleRound(output);
  }
  std::vector<uint8_t> output_sequence;
  for( unsigned int index = 0; index < 16; index++){
    std::vector<uint8_t> inv = LittleEndianInverse(output_copy[index] + output[index]);
    for(auto it : inv )
      output_sequence.push_back(it);
  }
  return output_sequence;
}
