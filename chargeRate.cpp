#include "chargeRate.h"
#include <stdlib.h>
#include <stdio.h>

// Conversion successfull = true, error = false
bool addParsedSession(const char* session){
    char* sessionPtr;
    long sessionValue = strtol(session, &sessionPtr, conversionBase);
    if((errno == 0) && (*sessionPtr == '\0')){
        sessionValues.push_back(sessionValue);
        return true;
    }
    return false;
}

std::list<long> parseChargeSessions(char* sessions){
    char* rawSample;
    addParsedSession(sessions);
    rawSample = strtok(sessions, delimiter);
    while(rawSample != NULL){
        addParsedSession(rawSample);
        rawSample = strtok(NULL, delimiter);
    }
    return sessionValues;
}

std::list<chargeRange> calculateRanges(){
    std::list<long> values = sessionValues;
    values.sort();
    std::list<chargeRange>::iterator rangeIt = chargeRanges.begin();
    for(auto valueIt: sessionValues){
        long control = valueIt;
        for(auto samples: values){
            if (control+1 == samples){
                control++;
            }
        }
        if(control != valueIt){
            chargeRange cRange(valueIt, control);
            chargeRanges.insert(rangeIt, cRange);
            calculateReadings(values);
        }
    }
    return chargeRanges;
}

std::list<chargeRange> calculateReadings(std::list<long> &samples){
    for(std::list<chargeRange>::iterator rangeIt = chargeRanges.begin(); \
        rangeIt != chargeRanges.end(); rangeIt++){
        for(std::list<long>::iterator sampleIt = samples.begin(); 
            sampleIt != samples.end(); sampleIt++){
            if((*sampleIt >= rangeIt->lowValue) && \
               (*sampleIt <= rangeIt->highValue)){
                samples.erase(sampleIt);
                rangeIt->readings+=1;
            }
        }
    }
    return chargeRanges;
}

void formatChargeSessions(){

}