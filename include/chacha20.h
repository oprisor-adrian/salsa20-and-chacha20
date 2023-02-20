#ifndef STREAM_CIPHERS_INCLUDE_CHACHA20_H_
#define STREAM_CIPHERS_INCLUDE_CHACHA20_H_

#include <cstdint>
#include <vector>

#include "stream_ciphers.h"

class ChaCha20: public StreamCipher{
  public:
    ChaCha20() = default;
    ChaCha20(const std::vector<uint8_t>& key, const std::vector<uint8_t>& nonce,
	     const uint32_t& count, const uint32_t& rounds);
    ~ChaCha20() = default;
    std::vector<uint8_t> Hash();
  private:
    void QuarterRound(const std::vector<uint8_t>& order, std::vector<uint32_t>& state);
    void DoubleRound(std::vector<uint32_t>& state);
    std::vector<uint32_t> state_;
    uint32_t rounds_;
};

#endif  // STREAM_CIPHERS_INCLUDE_CHACHA20_H_
