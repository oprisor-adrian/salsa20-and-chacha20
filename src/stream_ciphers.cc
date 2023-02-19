#include "../include/stream_ciphers.h"

std::vector<uint8_t> StreamCipher::Hash(){
  // This function is created only to be 
  // overloaded by derivated classes
  return {0};
}

void StreamCipher::DoubleRound(std::vector<uint32_t>& state){
  // This function is created only to be 
  // overloaded by derivated classes
}

void StreamCipher::QuarterRound(const std::vector<uint8_t>& order,
				std::vector<uint32_t>& state){
  // This function is created pnly to be
  //  overloaded by derivated classes
  //  Salsa20 -> change 8 output bits
  //  ChaCha20 -> change 12.5 output bits
}

void StreamCipher::CustomRound(const std::vector<uint8_t>& order,
		               std::vector<uint32_t>& state){
  for(auto it = order.begin(); it != order.end(); it += 4){
    QuarterRound({it, it+4}, state);
  }
}

uint32_t StreamCipher::LeftBitRotation(const uint32_t& value,
		                       const uint32_t& bits) const {
  return ((value << bits) | (value >> (32 - bits)));
}

uint32_t StreamCipher::LittleEndian(const std::vector<uint8_t>& sequence) const{
  uint32_t word = 0;
  for(unsigned int index = 0; index < 4; index++){
    word |= sequence[index] << (index * 8);
  }
  return word;
}

std::vector<uint8_t> StreamCipher::LittleEndianInverse(const uint32_t& word) const{
  std::vector<uint8_t> sequence;
  sequence.push_back((word & 0x000000ff));
  sequence.push_back((word & 0x0000ff00) >> 8);
  sequence.push_back((word & 0x00ff0000) >> 16);
  sequence.push_back((word & 0xff000000) >> 24);
  return sequence;
}
