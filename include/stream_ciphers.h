#ifndef STREAM_CIPHERS_INCLUDE_STREAM_CIPHERS_H_
#define STREAM_CIPHERS_INCLUDE_STREAM_CIPHERS_H_

#include <vector>
#include <cstdint>

class StreamCipher{
  public:
    StreamCipher() = default;
    ~StreamCipher() = default;
    virtual std::vector<uint8_t> Hash();
  protected:
    virtual void QuarterRound(const std::vector<uint8_t>& order,
		     	      std::vector<uint32_t>& state);
    virtual void DoubleRound(std::vector<uint32_t>& state);
    void CustomRound(const std::vector<uint8_t>& order, 
		     std::vector<uint32_t>& state);
    uint32_t LeftBitRotation(const uint32_t& value, const uint32_t& bits) const;
    uint32_t LittleEndian(const std::vector<uint8_t>& sequence) const;
    std::vector<uint8_t> LittleEndianInverse(const uint32_t& word) const;
};
#endif  // STREAM_CIPHERS_INCLUDE_STREAM_CIPHERS_H_
