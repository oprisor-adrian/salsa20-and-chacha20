#ifndef STREAM_CIPHERS_INCLUDE_SALSA20_H_
#define STREAM_CIPHERS_INCLUDE_SALSA20_H_

#include "stream_cipher.h"

template<class data_type>
class Salsa20: public StreamCipher{
  public:
    Salsa20() = default;
    Salsa20(const std::vector<uint32_t>& input, const uint32_t& rounds);
    ~Salsa20() = default;
    std::vector<uint8_t> Hash();
  private:
    void DoubleRound
    data_type state_;
    uint32_t rounds_;
};
#endif  // STREAM_CIPHERS_INCLUDE_SALSA20_H_

