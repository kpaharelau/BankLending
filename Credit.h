#include "Utils.h"

Credit* readCredit();
void recordCredit(Credit *ptrStartCredit);

Credit* firstCredit(Credit* ptrCredit);
Credit* lastCredit(Credit* ptrCredit);
Credit* inputCredit(CreditType *ptrCreditType, Client* ptrClient, Credit *ptrCredit );
Credit* deleteCredit(Credit *ptrCredit);
Credit* editCredit(Credit *ptrCredit);
int viewCredit(Credit *ptrCredit);
void headCredit();
int CheckingPointers(CreditType *ptrCreditType, Client* ptrClient);