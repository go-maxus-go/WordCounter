#include "Application.h"

#include <codecvt>
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
        FileReader<wchar_t> reader(file, std::ifstream::in | std::ifstream::binary);
        if (!reader.isOpened())
            return fileErrorMessage();
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        WordCounter wordCounter(conv.from_bytes(word.data()));
        std::unique_ptr<wchar_t[]> buffer(new wchar_t[m_bufferSize]);
        while (auto readSize = reader.readBuffer(buffer.get(), m_bufferSize))
        {
            wordCounter.process(std::wstring(buffer.get(), readSize));
            std::fill_n(buffer.get(), m_bufferSize, 0); // TODO: clear all time?
        }

        std::cout <<  word << " : " << wordCounter.count()
                  << std::endl;
        return 0;
    }
    int calculateCheckSum(const std::string & file)
    {
        FileReader<char> reader(file, std::ifstream::in | std::ifstream::binary);
        if (!reader.isOpened())
            return fileErrorMessage();
        CheckSummator summator;
        std::unique_ptr<char[]> buffer(new char[m_bufferSize]);
        while (auto readSize = reader.readBuffer(buffer.get(), m_bufferSize))
            summator.checkSum(reinterpret_cast<uint8_t*>(buffer.get()), readSize);

        std::cout << "CheckSum = " << std::hex << summator.checkSum()
                  << std::endl;
        return 0;
    }
    int fileErrorMessage()
    {
        std::cout << "File can't be opened" << std::endl;
        return 1;
    }
private:
    int m_argc;
    char ** m_argv;
    int m_bufferSize = 1024 * 1024; // must be dividable by 4
};

Application::Application(int argc, char *argv[])
    : m_impl(new Impl(argc, argv))
{}
Application::~Application() = default;

int Application::exec()
    { return m_impl->exec(); }
