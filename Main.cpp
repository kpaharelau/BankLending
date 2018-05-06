#include "Header.h"
#include "CreditType.h"
#include "Client.h"
#include "Credit.h"

int main() {
    BankData* bankData = new BankData;
    bankData->creditType = readCreditTypes();
    bankData->client = readClient();
    bankData->credit = readCredit();
    //CreditType *ptrCreditType = readCreditTypes();   // разве строчки выше и это не одно и то же?
    //Credit *ptrCredit = readCredit();
    //Client*ptrClient = readClient();
    while (true) {
        printf("Главное меню ======= Выберите действие =======\n");
        printf("1. Вход под администратором.\n");
        printf("2. Вход под пользователем.\n");
        printf("0. Выход.\n");
        int i;
        i = controlNumber();
        switch (i) {
            case 1:
                menuAdmin(bankData);
                break;
            case 2:
                menuUser();
                break;
            case 0:
                recordCreditTypes(bankData->creditType);
                recordCredit(bankData->credit);
                recordClient(bankData->client);
                exit(0);
            default:
                printf("Вветите числа от 0 до 2\n");
                break;
        }
    }
}