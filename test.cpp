#include "ex00/BitcoinExchange.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

bool isValidDate(const std::string& s) {
    std::tm tm = {};
    std::istringstream ss(s);
    ss >> std::get_time(&tm, "%Y-%m-%d");
    return !ss.fail();
}

int main(int ac, char**av)
{

    std::cout << isValidDate("") << std::endl;

}



// validate input
// - spaces
// - key or value empty
// - Year-Month-Day Format wrong => Get a function to parse this

