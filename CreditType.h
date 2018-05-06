#include "Header.h"

CreditType* readCreditTypes();                                  // чтение файла
void recordCreditTypes(CreditType *ptrStartCreditType);         //

CreditType* firstCreditType(CreditType* ptrCreditType);        //определение конечного элемента
CreditType* lastCreditType(CreditType* ptrCreditType);         //определение первого элемента
CreditType* inputCreditType(CreditType *ptrCreditType);        //ввод вида кредита
CreditType* deleteCreditType(CreditType *ptrCreditType);       // удаление
int renderCreditTypes(CreditType *ptrCreditType);              // показывает виды кредита