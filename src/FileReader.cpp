#include "FileReader.h"

class FileReader::Impl
{
public:
    Impl(const std::string & file, std::ifstream::openmode mode)
        : m_stream(file, mode)
    {
        if (!m_stream)
            return;
       m_stream.seekg(0, m_stream.end);
       m_length = m_stream.tellg();
       m_stream.seekg (0, m_stream.beg);
    }
    ~Impl()
    {
        if (m_stream)
            m_stream.close();
    }
public:
    bool isOpened() const
        { return m_stream.is_open(); }
    unsigned long length() const
        { return m_length; }
    int readBuffer(char * buffer, int size)
    {
        if (!m_stream || m_stream.eof() || buffer == nullptr || size <= 0)
            return 0;
        const auto tillEnd = m_length - m_stream.tellg();
        const auto res = tillEnd > static_cast<unsigned long>(size)
                       ? size : tillEnd;
        m_stream.read(buffer, res);
        return res;
    }
private:
    std::ifstream m_stream;
    unsigned long m_length = 0;
};

FileReader::FileReader(const std::string & file, std::ifstream::openmode mode)
    : m_impl(new Impl(file, mode))
{}
FileReader::~FileReader() {}

bool FileReader::isOpened() const
    { return m_impl->isOpened(); }
unsigned long FileReader::length() const
    { return m_impl->length(); }
int FileReader::readBuffer(char * buffer, int size)
    { return m_impl->readBuffer(buffer, size); }
