#include "Header.h"
#include "Client.h"
#include "Credit.h"

void menuAdmin(BankData* ptrBankData, CreditType *ptrCreditType, Client *ptrClient, Credit *ptrCredit) {
    int test;
    while (true) {
        clearConsole();
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Добавление записи.\n"); // для пустого и нет                         //
        printf("2. Редактирование записи.\n");
        printf("3. Удаление записи.\n");                                                //
        printf("4. Просмотр всех данных в табличной форме.\n");                         //
        printf("5. Различные процедуры поиска и фильтрации данных.\n");
        printf("6. Управление пользователями.\n");                                      // разобраться в будущем че как
        printf("0. Возврат в главное меню.\n");
        int i;
        i = controlNumber();
        if (i == 0) break;
        switch (i) {
            case 1:
                add(ptrCreditType, ptrClient ,ptrCredit, ptrBankData);
                break;
            case 2:
                break;
            case 3:
                remove(ptrCreditType, ptrClient, ptrCredit, ptrBankData);
                break;
            case 4:
                test = viewAll(ptrCreditType, ptrClient, ptrCredit);
                if (test == 1) {
                    printf("Нет достаточного количества данных \n");
                }
                getchar();
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                printf("Вветите числа от 0 до 6:\n");
        }
    }
}

void menuUser() {
    while (true) {
        printf("1. Открытие файла с данными.\n");
        printf("2. Простмотр всех данных в табличной форме.\n");
        printf("3. Выполнение задачи.\n");
        printf("4. Различные процедуры поиска и фильтраций данных.\n");
        printf("0. Возврат в главное меню.\n");
        int i;
        i = controlNumber();
        if (i == 0) break;
        switch (i) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                printf("Введите числа от 0 до 5:\n");
        }
    }
}