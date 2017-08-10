#include "WordCounter.h"

#include <cctype>
#include <sstream>
#include <algorithm>

class WordCounter::Impl
{
public:
    Impl(const std::string & word) : m_word(word) {}
public:
    void process(const std::string & data)
    {
        if (m_word.empty() || data.empty())
            return;
        if (std::isspace(*data.begin()))
            m_buffer.clear();
        std::stringstream ss(data);
        std::string word;
        while (ss >> word)
        {
            if (!m_buffer.empty())
            {
                word = m_buffer + word;
                m_buffer.clear();
            }
            if (isEqual(m_word, word))
                ++m_counter;
        }
        if (word.size() < m_word.size() && !std::isspace(*data.rbegin()))
            m_buffer = word;
    }
    unsigned long count() const
        { return m_counter; }
private:
    bool isEqual(const std::string & l, const std::string & r) const
    {
        // TODO: smart compare, exept symbols like: ,.!? and so on ...
        return _stricmp(l, r);
    }
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
