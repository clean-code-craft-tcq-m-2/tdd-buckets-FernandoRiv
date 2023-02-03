#include <list>
#include <stdio.h>
const unsigned int MINSTRBUFF = 100;

class chargeRange{
    public:
    long lowValue;
    long highValue;
    long readings;

    chargeRange(long lVal=0, long hVal=0, long reads=0):
        lowValue(lVal),
        highValue(hVal),
        readings(reads)
    {}

    bool calculateReadings(std::list<long> &samples);
    bool getRangeString(char *buffer, const unsigned int bufferSize);
};

extern const char* delimiter;
extern const int conversionBase; 
extern std::list<long> sessionValues;
extern std::list<chargeRange> chargeRanges;