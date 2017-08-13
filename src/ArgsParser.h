#pragma once

#include <list>
#include <string>

class ArgsParser
{
public:
    ArgsParser();
    ~ArgsParser();
public:
    void setOption(const std::string & option);
    bool parse(const std::list<std::string> & args);
    bool isSet(const std::string & option) const;
    std::list<std::string> values(const std::string & option) const;
private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
