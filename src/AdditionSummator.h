#pragma once

#include "ICheckSummator.h"

class AdditionSummator : public ICheckSummator
{
public:
    uint32_t checkSum(uint32_t value) override
        { return m_cache += value; }
private:
    uint32_t m_cache = 0;
};
