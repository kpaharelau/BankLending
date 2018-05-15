#include "Utils.h"

CreditType* readCreditTypes();
void recordCreditTypes(CreditType *ptrStartCreditType);
CreditType* firstCreditType(CreditType* ptrCreditType);
CreditType* lastCreditType(CreditType* ptrCreditType);
CreditType* inputCreditType(CreditType *ptrCreditType);
CreditType* deleteCreditType(CreditType *ptrCreditType);
int viewCreditType(CreditType *ptrCreditType);
void headCreditType();
CreditType* editCreditType(CreditType *ptrCreditType);

int count(CreditType *ptrCreditType);
CreditType* toArray(CreditType *ptrCreditType);
CreditType *sortByLoanPeriod(CreditType *ptrCreditType);