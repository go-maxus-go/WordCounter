#pragma once

#include <memory>
#include <string>
#include <fstream>
#include <cstdint>

template<typename T>
class FileReader
{
public:
    FileReader(const std::string & file, std::ifstream::openmode m)
        : m_file(file, m)
    {
        if (!m_file)
            return;
        m_file.seekg(0, m_file.end);
        m_file.imbue(std::locale()); // global locale
        m_length = m_file.tellg();
        m_file.seekg (0, m_file.beg);
    }
    ~FileReader()
    {
        if (m_file)
            m_file.close();
    }
public:
    bool isOpened() const
        { return m_file.is_open(); }
    unsigned long length() const
        { return m_length; }
    int readBuffer(T * buffer, int size)
    {
        if (!m_file || m_file.eof() || buffer == nullptr || size <= 0)
            return 0;
        const auto tillEnd = m_length - m_file.tellg();
        const auto res = tillEnd > static_cast<unsigned long>(size)
                       ? size : tillEnd;
        m_file.read(buffer, res);
        return res;
    }
private:
    std::basic_ifstream<T> m_file;
    std::basic_string<T, std::char_traits<T>, std::allocator<T>> m_buffer;
    unsigned long m_length = 0;
};
