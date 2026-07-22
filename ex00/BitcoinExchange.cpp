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

std::string trim(const std::string& str)
{
    size_t start = 0;
    while (start < str.length() && std::isspace(str[start]))
        start++;

    size_t end = str.length();
    while (end > start && std::isspace(str[end - 1]))
        end--;

    return str.substr(start, end - start);
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
            key = trim(key);
            value = trim(value);
            bitcoin[key] = parseNumber(value);
        }
    }
    return (true);
}

bool countYear(unsigned int day, unsigned int month, unsigned int year)
{
    bool isLeapYear = false;
    if (year == 0 || year > 2026 || month == 0 || month > 12 || day == 0 || day > 31)
        return (false);
    if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
        isLeapYear = true;
    int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear)
        months[1] = 29;

    int monthselcted = month;
    // std::cout << month << " -- " << months[monthselcted + 1] << " -- " << day << std::endl;
    if (day >= 1 && (int)day <= months[monthselcted - 1])
        return(true);
    return (false);
}

bool validateInput(std::string key, std::string value)
{
    unsigned int day = 0;
    unsigned int month = 0;
    unsigned int year = 0;
    
    int count = 0;
    if (key.empty() || count_space(key) > 1 || value.empty() || count_space(value) > 1)
        return (std::cout << "Error: bad input => " << key << std::endl, false);
    std::stringstream iss(key);
    std::string tmp;
    while (std::getline(iss, tmp, '-'))
    {
        if (count == 0)
            year = atoi(tmp.c_str());
        else if (count == 1 && tmp.length() == 2)
            month = atoi(tmp.c_str());
        else if (count == 2 && tmp.length() == 3)
            day = atoi(tmp.c_str());
        else
            return (std::cout << "Error: bad input => " << key << std::endl, false);
        count++;
    }
    if (count != 3)
        return (std::cout << "Error: bad input => " << key << std::endl, false);
    if (!countYear(day, month, year))
        return (std::cout << "Error: bad input => " << key << std::endl, false);
    return (true);
}


bool validateValue(std::string value, float *val)
{
    char *end;
    *val = strtod(value.c_str(), &end);
    if (*end)
        return (std::cout << "Error: not a valid number" << std::endl, false);
    else if (*val < 0)
        return (std::cout << "Error: not a positive number" << std::endl, false);
    else if (*val > 1000)
        return (std::cout << "Error: too large a number" << std::endl, false);

    return (true);
}

bool    searchPureDate(std::string key, float value, std::map<std::string, float> btc)
{
    key = trim(key);
    std::map<std::string, float>::iterator it = btc.find(key); 
    if (it == btc.end())
        return (false);
    std::cout << key << " => " << value << " = " << it->second * value << std::endl;
    return (true);
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
            float bitcNum = 0;
            size_t pipe = line.find('|');
            if (pipe == std::string::npos)
                pipe = line.length() - 1;
            std::string key = line.substr(0, pipe);
            std::string value = line.substr(pipe + 1);
            if (!validateInput(key, value))
                continue ;
            if (!validateValue(value, &bitcNum))
                continue ;
            if (searchPureDate(key, bitcNum, bitcoin))
                continue ;
            else
                /*searchLowerDate()*/std::cout << "Done\n";
        }
    }
    // std::map<std::string, float>::iterator it = bitcoin.begin();
    // while (it != bitcoin.end())
    // {
    //     std::cout << it->first << " : " << it->second << std::endl;
    //     it++;
    // }
    return (true);
}