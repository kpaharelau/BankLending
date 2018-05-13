#include "Header.h"
#include "Client.h"
#include "Credit.h"
#include "CreditType.h"

void menuAdmin(BankData* ptrBankData) {
    int test;
    while (true) {
        clearConsole();
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Добавление записи.\n");
        printf("2. Редактирование записи.\n");
        printf("3. Удаление записи.\n");
        printf("4. Просмотр всех данных в табличной форме.\n");
        printf("5. Различные процедуры поиска и фильтрации данных.\n");         // поиск по записям и сортировка их
        printf("6. Управление пользователями.\n");                              // просмотр и удаление юзеров
        printf("0. Возврат в главное меню.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        switch (i) {
            case 1:
                add(ptrBankData);
                break;
            case 2: edit(ptrBankData);
                break;
            case 3:
                remove(ptrBankData);
                break;
            case 4:
                viewAll(ptrBankData->creditType, ptrBankData->client, ptrBankData->credit);
                getchar();
                break;
            case 5: searchAndFiltering(ptrBankData);
                break;
            case 6: userManagement(ptrBankData);
                break;
            default:
                printf("Вветите числа от 0 до 6:\n");
        }
    }
}

void menuUser() {
    while (true) {
        printf("Пользователь ======= Выберите действие =======\n");
        printf("1. Просмотр всех данных в табличной форме.\n");
        printf("2. Выполнение задачи.\n");
        printf("3. Различные процедуры поиска и фильтраций данных.\n");
        printf("0. Возврат в главное меню.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        switch (i) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Введите числа от 0 до 3:\n");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ДОБАВЛЕНИЯ // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void add(BankData* ptrBankData ) {
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Добавить вид кредита\n");
        printf("2. Добавить клиента\n");
        printf("3. Добавить кредит\n");
        printf("0. Возврат. \n");
        int i;
        i = getNumberFromKeyboard();
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
                ptrBankData->credit = inputCredit(ptrBankData->creditType, ptrBankData->client, ptrBankData->credit);
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ УДАЛЕНИЯ  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove(BankData* ptrBankData) {
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Удалить все\n");
        printf("2. Удалить элемент\n");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
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
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Удалить вид кредита\n");
        printf("2. Удалить клиента\n");
        printf("3. Удалить кредит\n");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1: ptrBankData->creditType = deleteCreditType(ptrBankData->creditType);
                break;
            case 2: ptrBankData->client = deleteClient(ptrBankData->client);
                break;
            case 3: ptrBankData->credit = deleteCredit(ptrBankData->credit);
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

int removeAll(BankData *ptrBankData) {

    while (true) {
        printf("Вы уверены, что хотите удалить все?\n");
        printf("1. Да\n");
        printf("2. Нет\n");
        int i = getNumberFromKeyboard();
        if (i == 2) break;
        clearConsole();
        switch (i) {
            case 1: {
                CreditType *ptrCreditType = firstCreditType(ptrBankData->creditType);
                while (ptrCreditType != NULL) {
                    ptrCreditType->prev = ptrCreditType;
                    ptrCreditType = ptrCreditType->next;
                    delete ptrCreditType->prev;
                }
                ptrBankData->creditType = NULL;
            }
             /*   Client* ptrClient = firstClient(ptrBankData->client);
                while (ptrClient != NULL) {
                    ptrClient = ptrClient->next;
                    delete ptrClient->prev;
                }
                ptrBankData->client = NULL;

                Credit* ptrCredit= firstCredit(ptrBankData->credit);
                while (ptrCredit != NULL) {
                    ptrCredit = ptrCredit->next;
                    delete ptrCredit->prev;
                }
                ptrBankData->credit = NULL;
            }*/
                return 0;
            default:
                printf("Введите числа от 1 до 2:  ");
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ РЕДАКТИРОВАНИЯ // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void edit(BankData* ptrBankData){
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Редактирование вида кредита\n");
        printf("2. Редактирование клиента\n");
        printf("3. Редактирование кредит\n");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1: ptrBankData->creditType = editCreditType(ptrBankData->creditType);
                break;
            case 2: ptrBankData->client = editClient(ptrBankData->client);
                break;
            case 3: ptrBankData->credit = editCredit(ptrBankData->credit);
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ПОИСКА И ФИЛЬТРАЦИИ // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void searchAndFiltering(BankData* ptrBankData) {
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Поиск\n");
        printf("2. Фильтрация\n");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1: search(ptrBankData);
                break;
            case 2: filtering(ptrBankData);
                break;
            default:
                printf("Введите числа от 0 до 2:  ");
        }
    }
}

void search(BankData* ptrBankData){
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("Поиск по: \n");
        printf("1. Видам кредитов ");
        printf("2. Клиентам");
        printf("3. Кредитам");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1: ptrBankData->creditType = searchCreditType(ptrBankData->creditType);
                break;
            case 2: ptrBankData->client = searchClient(ptrBankData->client);
                break;
            case 3: ptrBankData->credit = searchCredit(ptrBankData->credit);
                break;
            default:
                printf("Введите числа от 0 до 2:  ");
        }
    }
}

void userManagement(BankData* ptrBankData){
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1.Показать всех пользователей\n");
        printf("2.Удалить пользователя\n");
        printf("3.Добавить пользователя\n");
        printf("0.Выход\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:
                clearConsole();
                if (openuser() == 0)
                {
                    printf("Чтение успешно!\n");
                }
                else
                {
                    printf("Файл пуст!\n");
                }
                break;
            case 2:
                clearConsole();
                openuser();
                if (deleteuser() == 0)
                {
                    printf("Удаление успешно!\n");
                }
                else
                {
                    printf("Ошибка!\n");
                }
                break;
            case 3:
                clearConsole();
                if (adduser() == 0)
                {
                    printf("Добавление успешно!\n");
                }
                else
                {
                    printf("Ошибка!\n");
                }
                break;
            default: printf("Ошибка!\n");
        }
    }
}