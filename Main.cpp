#include "Header.h"
#include "CreditType.h"

int main() {
    CreditType *start_creditType = nullptr;
    Credit *start_credit = nullptr;
    Client *start_clients = nullptr;
    BankData* bankData = new BankData;
    bankData->creditType = readCreditTypes();
    CreditType *ptrCreditType = readCreditTypes();
//    readOrCreateFile(start_creditType, start_credit, start_clients);
    while (true) {
        printf("Главное меню ======= Выберите действие =======\n");
        printf("1. Вход под администратором.\n");
        printf("2. Вход под пользователем.\n");
        printf("0. Выход.\n");
        int i;
        i = controlNumber();
        switch (i) {
            case 1:
                menuAdmin(bankData, ptrCreditType, start_clients, start_credit);
                break;
            case 2:
                menuUser();
                break;
            case 0:
                recordCreditTypes(bankData->creditType);
//                recordFile(start_creditType, start_credit, start_clients);
                exit(0);
            default:
                printf("Вветите числа от 0 до 2\n");
                break;
        }
    }
}