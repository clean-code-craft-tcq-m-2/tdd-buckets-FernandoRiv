#ifndef _CHARGE_RATE_H_
#define _CHARGE_RATE_H_

#include <string.h>
#include <stdlib.h>
#include "chargeRateStructs.h"

#ifdef UTEST
bool addParsedSession(const char* session);
std::list<long> parseChargeSessions(char* sessions);
std::list<chargeRange> calculateRanges();
#endif // UTEST

#endif // _CHARGE_RATE_H_