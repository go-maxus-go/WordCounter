#pragma once

#include <memory>

class Application
{
public:
    Application(int argc, char *argv[]);
    ~Application();
public:
    int exec();
private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
