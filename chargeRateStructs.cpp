#include "chargeRateStructs.h"

const char* delimiter = ",";
const int conversionBase = 10; 
const int max12BitCurrent = 10;
const int intMax12Bit = 4094;

bool chargeRange::calculateReadings(std::list<SessionVal> &samples){
    for(std::list<SessionVal>::iterator sampleIt = samples.begin(); 
        sampleIt != samples.end(); sampleIt++){
        if((*sampleIt >= lowValue) && (*sampleIt <= highValue)){
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