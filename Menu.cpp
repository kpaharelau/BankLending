#include "Header.h"
#include "Client.h"
#include "Credit.h"
#include "CreditType.h"

void menuAdmin(BankData* ptrBankData) {
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
                add(ptrBankData);
                break;
            case 2:
                break;
            case 3:
                remove(ptrBankData);
                break;
            case 4:
                test = viewAll(ptrBankData);
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
        printf("Пользователь ======= Выберите действие =======\n");
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ДОБАВЛЕНИЯ // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add(BankData* ptrBankData ) {
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Добавить вид кредита\n");
        printf("2. Добавить клиента\n");
        printf("3. Добавить кредит\n");
        printf("0. Возврат. \n");
        int i;
        i = controlNumber();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:
                ptrBankData->creditType = inputCreditType(ptrBankData->creditType);
                break;
            case 2:
                ptrBankData->client = inputClient(ptrBankData->client);
                break;
            case 3:
                ptrBankData->credit = inputCredit(ptrBankData->credit);
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ УДАЛЕНИЯ  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove(BankData* ptrBankData) {
    while (1) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Удалить все\n");
        printf("2. Удалить элемент\n");
        printf("0. Вход. \n");
        int i;
        i = controlNumber();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:
                removeAll(ptrBankData);
                break;
            case 2:
                removePart(ptrBankData);
                break;
            default:
                printf("Введите числа от 0 до 2:  ");
        }
    }
}

void removePart(BankData* ptrBankData) {
    while (1) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Удалить вид кредита\n");
        printf("2. Удалить клиента\n");
        printf("3. Удалить кредит\n");
        printf("0. Вход. \n");
        int i;
        i = controlNumber();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1: deleteCreditType(ptrBankData->creditType);
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

int removeAll(BankData* ptrBankData) {

    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Да\n");
        printf("2. Нет\n");
        int i = controlNumber();
        if (i == 2) break;
        clearConsole();
        switch (i) {
            case 1:
                /*void deleteDblLinkedList(DblLinkedList **list) {
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}*/

                ptrBankData->creditType = nullptr;

                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
    return 0;
}

