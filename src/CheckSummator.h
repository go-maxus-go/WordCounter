#pragma once

#include <cstdint>

class CheckSummator
{
public:
    uint32_t checkSum(uint32_t);
    // regular buffer must be dividable by 4
    uint32_t checkSum(uint8_t const * data, int size);
    uint32_t checkSum() const;
private:
    uint32_t m_cache = 0;
};
