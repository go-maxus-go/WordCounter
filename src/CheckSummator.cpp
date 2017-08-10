#include "CheckSummator.h"

uint32_t CheckSummator::checkSum() const
    { return m_cache; }
uint32_t CheckSummator::checkSum(uint32_t value)
    { return m_cache += value; }
uint32_t CheckSummator::checkSum(uint8_t const * data, int size)
{
    if (size <= 0)
        return checkSum();
    uint32_t temp = 0;
    for (int i = 0; i < size; ++i)
    {
        temp <<= 8;
        temp += data[i];
        if (i % 4 == 3)
        {
            checkSum(temp);
            temp = 0;
        }
    }
    // if temp was added it is equal zero and has no impact
    return checkSum(temp);
}
