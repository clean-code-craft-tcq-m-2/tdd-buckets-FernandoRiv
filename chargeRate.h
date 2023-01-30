#ifndef _CHARGE_RATE_H_
#define _CHARGE_RATE_H_

#include <string.h>
#include <stdlib.h>
#include <list>

class chargeRange{
    public:
    long lowValue;
    long highValue;
    long readings;
};

const char* delimiter = ",";
const int conversionBase = 10; 
std::list<long> sessionValues = {};
std::list<chargeRange> chargeRanges = {};

#endif // _CHARGE_RATE_H_