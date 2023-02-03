#include "chargeRateStructs.h"

const char* delimiter = ",";
const int conversionBase = 10; 
std::list<long> sessionValues = {};
std::list<chargeRange> chargeRanges = {};

bool chargeRange::calculateReadings(std::list<long> &samples){
    for(std::list<long>::iterator sampleIt = samples.begin(); 
        sampleIt != samples.end(); sampleIt++){
        if((*sampleIt >= lowValue) && (*sampleIt <= highValue)){
            samples.erase(sampleIt);
            readings+=1;
        }
    }
    return true;
}

bool chargeRange::getRangeString(char *buffer, const unsigned int bufferSize){
    if(bufferSize > MINSTRBUFF){
        sprintf(buffer, "%ld-%ld, %ld\n", lowValue, highValue, readings);
        return true;
    }
    return false;
}