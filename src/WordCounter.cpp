#include "WordCounter.h"

#include <sstream>
#include <algorithm>

class WordCounter::Impl
{
public:
    Impl(const std::wstring & w)
    {
        m_word.resize(w.size());
        std::transform(w.begin(), w.end(), m_word.begin(), std::towupper);
    }
public:
    void process(const std::wstring & data)
    {
        if (m_word.empty() || data.empty())
            return;
        if (std::isspace(*data.begin()))
            m_buffer.clear();
        std::wstringstream ss(data);
        std::wstring word;
        while (ss >> word)
        {
            if (!m_buffer.empty()) // TODO: take out of the loop?
            {
                word = m_buffer + word;
                m_buffer.clear();
            }
            if (isSame(word))
                ++m_counter;
        }
        if (word.size() < m_word.size() && !std::isspace(*data.rbegin()))
            m_buffer = word;
    }
    unsigned long count() const
        { return m_counter; }
private:
    bool isSame(const std::wstring & word) const
    {
        // TODO: smart compare, exept symbols like: ,.!? and so on ...
        auto toUpper= [](auto w) {
            std::transform(w.begin(), w.end(), w.begin(), std::towupper);
            return w;
        };
        // search with overlaps, like in text editors
        return std::wstring::npos != toUpper(word).find(m_word);
    }
private:
    std::wstring m_word;
    unsigned long m_counter = 0;
    std::wstring m_buffer;
};

WordCounter::WordCounter(const std::wstring & word)
    : m_impl(new Impl(word))
{}
WordCounter::~WordCounter() = default;

void WordCounter::process(const std::wstring & data)
    { m_impl->process(data); }
unsigned long WordCounter::count() const
    { return m_impl->count(); }
