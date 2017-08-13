#include "Application.h"

#include <cassert>
#include <iostream>

#include "ArgsDesc.h"
#include "Commander.h"
#include "FileReader.h"
#include "WordCounter.h"
#include "CheckSummator.h"

class Application::Impl
{
public:
    Impl(int argc, char *argv[])
        : m_argc(argc)
        , m_argv(argv)
    {}
    int exec()
    {
        Commander commander;
        const auto res = commander.retrieveCommand(m_argc, m_argv);
        using Command = Commander::Command;
        switch (res)
        {
        case Command::CountWord:
            return countWord(commander.file(), commander.word());
        case Command::CheckSum:
            return calculateCheckSum(commander.file());
        case Command::Help:
            return showHelp();
        case Command::Invalid:
            std::cout << "Invalid argumens, use -h for help." << std::endl;
            return 1;
        }
        return 0;
    }
private:
    int showHelp()
    {
        std::cout << "Help:" << std::endl;
        auto printParam = [](auto p) {
            std::cout << ArgsDesc::get().arg(p) << " " << ArgsDesc::get().desc(p)
                      << std::endl;
        };
        auto printMode = [](auto m) {
            std::cout << "   " << "\"" << ArgsDesc::get().arg(m) << "\""
                      << " - " << ArgsDesc::get().desc(m) << std::endl;
        };
        printParam(ArgsDesc::ArgType::File);
        printParam(ArgsDesc::ArgType::Mode);
        printMode (ArgsDesc::ModeType::CheckSum);
        printMode (ArgsDesc::ModeType::Words);
        printParam(ArgsDesc::ArgType::Word);
        printParam(ArgsDesc::ArgType::Help);
        return 0;
    }
    int countWord(const std::string & file, const std::string & word)
    {
        if (auto res = openFile(file, std::ifstream::in))
            return res;
        WordCounter wordCounter(word);
        std::unique_ptr<char[]> buffer(new char[m_bufferSize]);
        // TODO: fix utf encoding issues new buffer reading
        while (auto readSize = m_fileReader->readBuffer(buffer.get(), m_bufferSize))
            wordCounter.process(std::string(buffer.get(), readSize));

        std::cout <<  word << " : " << wordCounter.count()
                  << std::endl;
        return 0;
    }
    int calculateCheckSum(const std::string & file)
    {
        if (auto res = openFile(file, std::ifstream::in))
            return res;
        CheckSummator summator;
        std::unique_ptr<char[]> buffer(new char[m_bufferSize]);
        while (auto readSize = m_fileReader->readBuffer(buffer.get(), m_bufferSize))
            summator.checkSum(reinterpret_cast<uint8_t*>(buffer.get()), readSize);

        std::cout << "CheckSum = " << std::hex << summator.checkSum()
                  << std::endl;
        return 0;
    }
    int openFile(const std::string & file, std::ifstream::openmode mode)
    {
        assert(m_fileReader.get() == nullptr);
        m_fileReader.reset(new FileReader(file, mode));
        if (m_fileReader->isOpened())
            return 0;
        std::cout << "File can't be opened" << std::endl;
        m_fileReader.reset();
        return 1;
    }
private:
    int m_argc;
    char ** m_argv;
    int m_bufferSize = 1024 * 1024; // must be dividable by 4
    std::unique_ptr<FileReader> m_fileReader;
};

Application::Application(int argc, char *argv[])
    : m_impl(new Impl(argc, argv))
{}
Application::~Application() = default;

int Application::exec()
    { return m_impl->exec(); }
