#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include <string>
#include <map>

using MonthMap = std::map<std::string, int>;

static MonthMap monthMap{
    {"Jan", 1},
    {"Feb", 2},
    {"Mar", 3},
    {"Apr", 4},
    {"May", 5},
    {"Jun", 6},
    {"Jul", 7},
    {"Aug", 8},
    {"Sep", 9},
    {"Oct", 10},
    {"Nov", 11},
    {"Dec", 12},
};

int get_month_from_string(std::string& month)
{
    return monthMap.at(month);
}

#endif