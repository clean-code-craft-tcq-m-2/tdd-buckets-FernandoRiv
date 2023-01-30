#include "chargeRate.h"

// Conversion successfull = 0, otherwise = error
bool addParsedSession(char* session){
    char* sessionPtr;
    long sessionValue = strtol(session, &sessionPtr, conversionBase);
    if(errno != 0)
        sessionValues.push_back(sessionValue);
    return errno;
}

void parseChargeSessions(char* sessions){
    char* rawSample;
    rawSample = strtok(sessions, delimiter);
    addParsedSession(rawSample);
    while(rawSample != NULL){
        rawSample = strtok(sessions, delimiter);
        addParsedSession(rawSample);
    }
}

void calculateRanges(){
    for(auto session: sessionValues){
        
    }
}

void formatChargeSessions(){

}