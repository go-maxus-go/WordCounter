#pragma once

#include <memory>
#include <cstdint>

class ICheckSummator
{
public:
    virtual ~ICheckSummator() = default;
    virtual uint32_t checkSum(uint32_t) = 0;
};

std::shared_ptr<ICheckSummator> createCheckSummator();
