#include "chargeRate.h"
#include <stdlib.h>
#include <stdio.h>
#include <cerrno>

// Conversion successfull = true, error = false
bool addParsedSession(const char* session){
    char* sessionPtr;
    if (session != nullptr){
        long sessionValue = strtol(session, &sessionPtr, conversionBase);
        if((errno == 0) && (*sessionPtr == '\0')){
            sessionValues.push_back(sessionValue);
            return true;
        }
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
    for(std::list<long>::iterator valueIt = values.begin();
        valueIt != values.end(); valueIt++){
        long control = *valueIt;
        for(auto samples: values){
            if (control+1 == samples){
                control++;
            }
        }
        if(control != *valueIt){
            chargeRange cRange(*valueIt, control);
            cRange.calculateReadings(values);
            std::advance(valueIt,(cRange.readings-1));
            chargeRanges.insert(rangeIt, cRange);
        }
    }
    return chargeRanges;
}