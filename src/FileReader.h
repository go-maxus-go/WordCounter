#pragma once

#include <memory>
#include <string>
#include <fstream>
#include <cstdint>

class FileReader
{
public:
    FileReader(const std::string & file, std::ifstream::openmode);
    ~FileReader();
public:
    bool isOpened() const;
    unsigned long length() const;
    int readBuffer(char * buffer, int size);
private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
