#include <iostream>

#include "../include/chacha20.h"

ChaCha20::ChaCha20(const std::vector<uint8_t>& key, 
		   const std::vector<uint8_t>& nonce,
		   const uint32_t& count, 
		   const uint32_t& rounds): rounds_(rounds){
  // add constant values
  state_.push_back(0x61707865); 
  state_.push_back(0x3320646e);
  state_.push_back(0x79622d32);
  state_.push_back(0x6b206574);

  // add key readed in little-endian order
  auto it_key = key.begin();
  while(it_key != key.end()){
    std::vector<uint8_t> sequence {it_key, it_key+4};
    state_.push_back(LittleEndian(sequence));
    it_key += 4;
  }

  // add counter
  state_.push_back(count);

  // add nonce readed in little-endian order
  auto it_nonce = nonce.begin();
  while(it_nonce != nonce.end()){
    std::vector<uint8_t> sequence{it_nonce, it_nonce+4};
    state_.push_back(LittleEndian(sequence));
    it_nonce += 4;
  }
}

std::vector<uint8_t> ChaCha20::Hash(){
  std::vector<uint32_t> state_copy(state_);

  for(unsigned int index = 0; index < rounds_; index++){
    DoubleRound(state_copy);
  }

  std::vector<uint8_t> output_state;
  for(unsigned int index = 0; index < 16; index++){
    std::vector<uint8_t> inv = LittleEndianInverse(state_[index] + state_copy[index]);
    for(auto it : inv){
      output_state.push_back(it);
    }
  }
  return output_state;
}

void ChaCha20::DoubleRound(std::vector<uint32_t>& state){
  std::vector<uint8_t> column_order {0, 4, 8, 12,
  				     1, 5, 9, 13,
                                     2, 6, 10, 14,
  				     3, 7, 11, 15};
  std::vector<uint8_t> diagonal_order {0, 5, 10, 15,
  				       1, 6, 11, 12,
  				       2, 7, 8, 13,
                                       3, 4, 9, 14};
  CustomRound(column_order, state);
  CustomRound(diagonal_order, state);
}

void ChaCha20::QuarterRound(const std::vector<uint8_t>& order, 
		            std::vector<uint32_t>& state){
  state[order[0]] += state[order[1]];
  state[order[3]] ^= state[order[0]];
  state[order[3]] = LeftBitRotation((state[order[3]]),16); 

  state[order[2]] += state[order[3]];
  state[order[1]] ^= state[order[2]];
  state[order[1]] = LeftBitRotation(state[order[1]], 12);
 
  state[order[0]] += state[order[1]];
  state[order[3]] ^= state[order[0]];
  state[order[3]] = LeftBitRotation((state[order[3]]), 8); 

  state[order[2]] += state[order[3]];
  state[order[1]] ^= state[order[2]];
  state[order[1]] = LeftBitRotation((state[order[1]]), 7);
}
