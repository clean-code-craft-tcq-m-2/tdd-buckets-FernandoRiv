#include <list>
#include <stdio.h>
const unsigned int MINSTRBUFF = 100;

typedef long SessionVal;

class chargeRange{
    public:
    SessionVal lowValue;
    SessionVal highValue;
    SessionVal readings;

    chargeRange(SessionVal lVal=0, SessionVal hVal=0, SessionVal reads=0):
        lowValue(lVal),
        highValue(hVal),
        readings(reads)
    {}

    bool calculateReadings(std::list<SessionVal> &samples);
    bool getRangeString(char *buffer, const unsigned int bufferSize);
};

extern const char* delimiter;
extern const int conversionBase; 
extern const int max12BitCurrent;
extern const int intMax12Bit;