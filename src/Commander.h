#pragma once

#include <string>
#include <memory>

class Commander
{
public:
    Commander();
    ~Commander();

    enum class Command {
        Invalid,
        CountWord,
        CheckSum,
        Help,
    };
    Command retrieveCommand(int argc, char * argv[]);
    std::string file() const;
    std::string word() const;
private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
