#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(){}
BitcoinExchange::BitcoinExchange(BitcoinExchange &obj) {*this = obj;}
BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange &obj)
{
    this->bitcoin = obj.bitcoin;
    return (*this);
}
BitcoinExchange::~BitcoinExchange(){}

float    parseNumber(std::string str)
{
    float value;
    char *end;
    value = strtod(str.c_str(), &end);
    return(value);
}

int    count_space(std::string str)
{
    int count = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str.at(i) == ' ')
            count++;
    }
    return (count);
}

bool    BitcoinExchange::loadFile()
{
    std::ifstream file("/home/mradouan/Desktop/CPP09/ex00/cpp_09/data.csv");
    if (!file)
        return (std::cout << "Error: could not open file." << std::endl, false);
    std::string line ;
    while (std::getline(file, line))
    {
        while (std::getline(file, line))
        {
            size_t pipe = line.find(',');
            std::string key = line.substr(0, pipe);
            std::string value = line.substr(pipe + 1);
            bitcoin[key] = parseNumber(value);
        }
    }
    return (true);
}

bool validateInput(std::string key, std::string value)
{
    int count = 0;
    if (count_space(key) > 1 || count_space(value) > 1)
        return (false);
    if (key.empty() || value.empty())
        return (false);
    std::stringstream iss(key);
    std::string tmp;
    while (std::getline(iss, tmp, '-'))
    {
        
        count++;
    }
}

bool    BitcoinExchange::parseFile(char *str)
{
    std::ifstream file(str);
    std::string   line;

    if (!file)
        return (std::cout << "Error: could not open file." << std::endl, false);
    while (std::getline(file, line))
    {
        if (line != "date | value")
            return (false);
        while (std::getline(file, line))
        {
            size_t pipe = line.find('|');
            if (pipe == std::string::npos)
                pipe = line.length() - 1;
            std::string key = line.substr(0, pipe);
            std::string value = line.substr(pipe + 1);
            if (!validateInput(key, value))
                value = "";
        }
    }
    std::map<std::string, float>::iterator it = bitcoin.begin();
    while (it != bitcoin.end())
    {
        std::cout << it->first << " : " << it->second << std::endl;
        it++;
    }
    return (true);
}