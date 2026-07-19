#include "BitcoinExchange.hpp"


bool    checkFile(char *str)
{
    struct stat inf;
    stat(str, &inf);
    if (S_ISDIR(inf.st_mode))
        return (false);
    int fd = access(str, F_OK);
    if (fd == -1)
        return (false);
    return (true);
}

int main(int ac, char**av)
{
    BitcoinExchange bit;
    if (ac != 2 || !checkFile(av[1]))
        return (std::cout << "Error: could not open file." << std::endl, 1);

    bit.loadFile();
    bit.parseFile(av[1]);
}