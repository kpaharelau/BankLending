#include "Utils.h"
#include "CreditType.h"
#include "Client.h"
#include "Credit.h"
#include "UserInformation.h"

int main() {
    BankData* bankData = new BankData;
    bankData->creditType = readCreditTypes();
    bankData->client = readClient();
    bankData->credit = readCredit();
    while (true) {
        printf("Главное меню ======= Выберите действие =======\n");
        printf("1. Вход под администратором.\n");
        printf("2. Вход под пользователем.\n");
        printf("0. Выход.\n");
        int i;
        i = getNumberFromKeyboard();
        switch (i) {
            case 1: {
                if (loginAdmin() == 1) {
                    menuAdmin(bankData);
                }
                else {
                    printf("Неверный пароль!\n");
                }
            }
                break;
            case 2: {
                int res = loginUser();
                if (res == 1) {
                    menuUser(bankData);
                } else if (res == 0) {
                    printf("Неверный пароль!\n");
                } else if (res == -1) {
                    printf("Пользователь отсутствует!\n");
                }
            }

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