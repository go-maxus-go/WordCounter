#include "WordCounter.h"

#include <sstream>

class WordCounter::Impl
{
public:
    Impl(const std::string & word) : m_word(word) {}
public:
    void process(const std::string & data)
    {
        if (m_word.empty())
            return;
        std::stringstream ss(data);
        std::string word;
        while (ss >> word)
        {
            if (!m_buffer.empty())
            {
                word = m_buffer + word;
                m_buffer.clear();
            }
            // TODO: smart compare
            if (m_word == word)
                ++m_counter;
        }
        if (word.size() < m_word.size())
            m_buffer = word;
    }
    unsigned long count() const
        { return m_counter; }
private:
    const std::string m_word;
    unsigned long m_counter = 0;
    std::string m_buffer;
};

WordCounter::WordCounter(const std::string & word)
    : m_impl(new Impl(word))
{}
WordCounter::~WordCounter() = default;

void WordCounter::process(const std::string & data)
    { m_impl->process(data); }
unsigned long WordCounter::count() const
    { return m_impl->count(); }
