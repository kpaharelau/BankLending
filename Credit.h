#include "Header.h"

Credit* readCredit();                                  // чтение файла
void recordCredit(Credit *ptrStartCredit);         //

Credit* firstCredit(Credit* ptrCredit);         //определение конечного элемента
Credit* lastCredit(Credit* ptrCredit);          //определение первого элемента
Credit* inputCredit(CreditType *ptrCreditType, Client* ptrClient, Credit *ptrCredit );        //ввод вида кредита
Credit* deleteCredit(Credit *ptrCredit);
int viewCredit(Credit *ptrCredit);
void headCredit();
int CheckingPointers(CreditType *ptrCreditType, Client* ptrClient);