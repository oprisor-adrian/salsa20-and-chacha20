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

void StreamCipher::QuarterRound(const std::vector<uint32_t>& bit,
		                const std::vector<uint8_t>& order,
				std::vector<uint32_t>& state){
  state[order[1]] ^= LeftBitRotation((state[order[0]] + state[order[3]]), bit[0]);
  state[order[2]] ^= LeftBitRotation((state[order[1]] + state[order[0]]), bit[1]);
  state[order[3]] ^= LeftBitRotation((state[order[2]] + state[order[1]]), bit[2]);
  state[order[0]] ^= LeftBitRotation((state[order[3]] + state[order[2]]), bit[3]);
}

void StreamCipher::CustomRound(const std::vector<uint32_t>& bit,
		               const std::vector<uint8_t>& order,
		               std::vector<uint32_t>& state){
  for(auto it = order.begin(); it != order.end(); it += 4){
    QuarterRound(bit, {it, it+4}, state);
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
