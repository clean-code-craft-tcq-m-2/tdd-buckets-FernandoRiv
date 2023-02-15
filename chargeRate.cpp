#include "chargeRate.h"
#include <stdlib.h>
#include <stdio.h>
#include <cerrno>
#include <cmath>

static bool cValToSVal(const char* cVal, SessionVal &parsedValue){
    char* sessionPtr;
    if (cVal != nullptr){
        long cValue = strtol(cVal, &sessionPtr, conversionBase);
        if((errno == 0) && (*sessionPtr == '\0')){
            parsedValue = cValue;
            return true;
        }
    }
    return false;
}

static bool parseChargeSessions(char* sessions,
        std::list<SessionVal> &sessionList,
        bool (*parseFunc)(const char* c, std::list<SessionVal> &sl)){
    char* rawSample;
    parseFunc(sessions, sessionList);
    rawSample = strtok(sessions, delimiter);
    while(rawSample != NULL){
        parseFunc(rawSample, sessionList);
        rawSample = strtok(NULL, delimiter);
    }
    return (sessionList.size() != 0);
}

bool addDirectSession(const char* session, 
        std::list<SessionVal> &sessionList){
    SessionVal sessionValue;
    if(cValToSVal(session, sessionValue)){
        sessionList.push_back(sessionValue);
        return true;
    }
    return false;
}

bool parseDirectChargeSession(char* sessions, 
        std::list<SessionVal> &sessionList){
    return parseChargeSessions(sessions, sessionList, addDirectSession);
}

bool add12BitSession(const char* session,
        std::list<SessionVal> &sessionList){
    SessionVal sessionValue;
    if(cValToSVal(session, sessionValue)){
        if((sessionValue <= intMax12Bit) && (sessionValue > 0)){
            sessionValue = round(((float)max12BitCurrent * (float)sessionValue)\
                                /(float)intMax12Bit);
            sessionList.push_back(sessionValue);
        }
        return true;
    }
    return false;
}

bool parse12BitChargeSession( char* sessions,
        std::list<SessionVal> &sessionList){
    return parseChargeSessions(sessions, sessionList, add12BitSession);
}

bool calculateRanges(std::list<SessionVal> &sessionList,
        std::list<chargeRange> &chargeRangeList){
    std::list<SessionVal> values = sessionList;
    values.sort();
    std::list<chargeRange>::iterator rangeIt = chargeRangeList.begin();
    for(std::list<SessionVal>::iterator valueIt = values.begin();
        valueIt != values.end(); valueIt++){
        SessionVal control = *valueIt;
        for(auto samples: values){
            if (control+1 == samples){
                control++;
            }
        }
        if(control != *valueIt){
            chargeRange cRange(*valueIt, control);
            cRange.calculateReadings(values);
            std::advance(valueIt,(cRange.readings-1));
            chargeRangeList.insert(rangeIt, cRange);
        }
    }
    return (chargeRangeList.size() != 0);
}