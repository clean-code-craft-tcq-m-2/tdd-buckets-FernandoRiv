#include "chargeRate.h"
//#include <stdio.h>

// Conversion successfull = true, error = false
bool addParsedSession(const char* session){
    char* sessionPtr;
    long sessionValue = strtol(session, &sessionPtr, conversionBase);
    if((errno == 0) && (*sessionPtr == '\0')){
        sessionValues.push_back(sessionValue);
        return true;
    }
    else
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
    sessionValues.sort();
    std::list<chargeRange>::iterator rangeIt = chargeRanges.begin();
    for(auto valueIt: sessionValues){
        long control = valueIt;
        for(auto samples: sessionValues){
            if (control+1 == samples){
                control++;
            }
        }
        if(control != valueIt){
            chargeRange cRange(valueIt, control);
            chargeRanges.insert(rangeIt, cRange);
        }
    }
    return chargeRanges;
}

void calculateReadings(){
    for(auto rangeIt: chargeRanges){
        for(auto value: sessionValues){
            if(value >= rangeIt.lowValue  || value <= rangeIt.highValue){
                rangeIt.readings++;
            }
        }
    }
}

void formatChargeSessions(){

}