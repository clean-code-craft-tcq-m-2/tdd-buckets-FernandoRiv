#ifndef _CHARGE_RATE_H_
#define _CHARGE_RATE_H_

#include <string.h>
#include "chargeRateStructs.h"


bool parseDirectChargeSession(char* sessions, 
        std::list<SessionVal> &sessionList);
bool parse12BitChargeSession( char* sessions,
        std::list<SessionVal> &sessionList);
#ifdef UTEST
bool addDirectSession(const char* session, std::list<SessionVal> &sessionList);
bool add12BitSession(const char* session, std::list<SessionVal> &sessionList);
bool calculateRanges(std::list<SessionVal> &sessionList,\
                     std::list<chargeRange> &chargeRangeList);
#endif // UTEST

#endif // _CHARGE_RATE_H_