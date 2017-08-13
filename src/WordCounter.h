#pragma once

#include <memory>
#include <string>

class WordCounter
{
public:
    WordCounter(const std::string & word);
    ~WordCounter();
public:
    void process(const std::string & data);
    unsigned long count() const;
private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
