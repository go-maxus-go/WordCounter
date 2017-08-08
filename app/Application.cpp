#include "Application.h"

#include <iostream>

#include "ArgsDesc.h"
#include "Commander.h"
#include "FileReader.h"
#include "WordCounter.h"
#include "ICheckSummator.h"

class Application::Impl
{
public:
    Impl(int argc, char *argv[])
        : m_argc(argc)
        , m_argv(argv)
    {
        m_buffer = new char[m_bufferSize];
    }
    ~Impl()
        { delete m_buffer; }
    int exec()
    {
        Commander commander;
        const auto res = commander.retrieveCommand(m_argc, m_argv);
        using Command = Commander::Command;
        switch (res)
        {
        case Command::CountWord:
            countWord(commander.file(), commander.word());
            break;
        case Command::CheckSum:
            calculateCheckSum(commander.file());
            break;
        case Command::Help:
            showHelp();
            break;
        case Command::Invalid:
            std::cout << "Invalid argumens, use -h for help." << std::endl;
            return 1;
        }
        return 0;
    }
private:
    void showHelp()
    {
        std::cout << "Help:" << std::endl;
    }
    void countWord(const std::string & file, const std::string & word)
    {
        FileReader fileReader(file, std::ifstream::in);
        if (!fileReader.isOpened())
        {
            std::cout << "File can't be opened";
            return;
        }
        WordCounter wordCounter(word);
        while (auto readSize = fileReader.readBuffer(m_buffer, m_bufferSize))
            wordCounter.process(std::string(m_buffer, readSize));

        std::cout <<  word << " : " << wordCounter.count() << std::endl;
    }
    void calculateCheckSum(const std::string & file)
    {
        FileReader fileReader(file, std::ifstream::binary);
        if (!fileReader.isOpened())
        {
            std::cout << "File can't be opened" << std::endl;
            return;
        }
        auto summator = createCheckSummator();
        uint32_t result = 0;
        while (auto readSize = fileReader.readBuffer(m_buffer, m_bufferSize))
        {
            uint32_t temp = 0;
            for (auto i = 0; i < readSize; ++i)
            {
                temp <<= 8;
                temp += m_buffer[i];
                if (i % 4 == 3)
                {
                    result = summator->checkSum(temp);
                    temp = 0;
                }
            }
            if (temp != 0)
                result = summator->checkSum(temp);
        }

        std::cout << "CheckSum = " << std::hex << result << std::endl;
    }
private:
    int m_argc;
    char ** m_argv;
    int m_bufferSize = 1024 * 1024;
    char * m_buffer = nullptr; // TODO: memorylead danger
};

Application::Application(int argc, char *argv[])
    : m_impl(new Impl(argc, argv))
{}
Application::~Application() = default;

int Application::exec()
    { return m_impl->exec(); }
