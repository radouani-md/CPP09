#ifndef __BITCOIN_EXCHANGE_HPP__
#define __BITCOIN_EXCHANGE_HPP__

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdlib>


class BitcoinExchange
{
    private:
        std::map<std::string, float> bitcoin;
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange &obj);
        BitcoinExchange& operator=(BitcoinExchange &obj);
        ~BitcoinExchange();
        bool    parseFile(char *str);
        bool    loadFile();

};





#endif