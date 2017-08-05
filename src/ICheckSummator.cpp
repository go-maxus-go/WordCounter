#include "ICheckSummator.h"

#include "AdditionSummator.h"

std::shared_ptr<ICheckSummator> createCheckSummator()
{
    return std::move(std::make_shared<AdditionSummator>());
}
