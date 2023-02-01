#include <list>

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
};

extern const char* delimiter;
extern const int conversionBase; 
extern std::list<long> sessionValues;
extern std::list<chargeRange> chargeRanges;