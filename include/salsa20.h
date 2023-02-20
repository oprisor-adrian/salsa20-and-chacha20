#ifndef STREAM_CIPHERS_INCLUDE_SALSA20_H_
#define STREAM_CIPHERS_INCLUDE_SALSA20_H_

#include <cstdint>
#include <vector>

#include "stream_ciphers.h"

class Salsa20: public StreamCipher{
  public:
    Salsa20() = default;
    Salsa20(const std::vector<uint8_t>& state, const uint32_t& rounds);
    ~Salsa20() = default;
    std::vector<uint8_t> Hash();
  private:
    void QuarterRound(const std::vector<uint8_t>& order, std::vector<uint32_t>& state);
    void DoubleRound(std::vector<uint32_t>& state);
    std::vector<uint8_t> state_;
    uint32_t rounds_;
};
#endif  // STREAM_CIPHERS_INCLUDE_SALSA20_H_

