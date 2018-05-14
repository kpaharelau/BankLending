#include "Utils.h"
#include "Client.h"
#include "Credit.h"
#include "CreditType.h"
#include "UserInformation.h"

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

void menuUser(BankData* ptrBankData) {
    while (true) {
        printf("Пользователь ======= Выберите действие =======\n");
        printf("1. Просмотр всех данных в табличной форме.\n");
        printf("2. Вывод трех клиентов, которые взяли кредит на самый большой срок.\n");
        printf("3. Различные процедуры поиска и фильтраций данных.\n");
        printf("0. Возврат в главное меню.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        switch (i) {
            case 1: viewAll(ptrBankData->creditType, ptrBankData->client, ptrBankData->credit);
                break;
            case 2: task(ptrBankData->creditType);
                break;
            case 3: searchAndFiltering(ptrBankData);
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

int remove(BankData* ptrBankData) {
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
            case 1: if (removeAll(ptrBankData) == 0){
                return 0;
            }
                break;
            case 2:
                removePart(ptrBankData);
                break;
            default:
                printf("Введите числа от 0 до 2:  ");
        }
    }
    return 0;
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
                while (ptrCreditType != NULL && ptrCreditType->next != NULL) {
                    CreditType* ptrCreditTypeForRemove = ptrCreditType;
                    ptrCreditType = ptrCreditType->next;
                    delete ptrCreditTypeForRemove;
                }
                Client *ptrClient = firstClient(ptrBankData->client);
                while (ptrClient != NULL && ptrClient->next != NULL) {
                    Client* ptrClientForRemove = ptrClient;
                    ptrClient = ptrClient->next;
                    delete ptrClientForRemove;
                }
                Credit *ptrCredit = firstCredit(ptrBankData->credit);
                while (ptrCredit != NULL && ptrCredit->next != NULL) {
                    Credit* ptrCreditForRemove = ptrCredit;
                    ptrCredit = ptrCredit->next;
                    delete ptrCreditForRemove;
                }
                ptrBankData->creditType = NULL;
                ptrBankData->client = NULL;
                ptrBankData->credit = NULL;
            }
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
            case 2: filtering(ptrBankData->creditType, ptrBankData->client, ptrBankData->credit);
                break;
            default:
                printf("Введите числа от 0 до 2:  ");
        }
    }
}

void search(BankData* ptrBankData){
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("Поиск : \n");
        printf("1. Вид кредита\n");
        printf("2. Клиентов\n");
        printf("3. Кредитов\n");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1: searchCreditType(ptrBankData->creditType);
                break;
            case 2: searchClient(ptrBankData->client);
                break;
            case 3:
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

void searchCreditType(CreditType* ptrCreditType){
    while (true) {
        int count = 0;
        printf("Администратор ======= Выберите действие =======\n");
        printf("Поиск по: \n");
        printf("1. Коду кредита\n");
        printf("2. Имени кредита\n");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:{
                printf("Введите номер вида кредита:\n");
                int code_type = getNumberFromKeyboard();
                ptrCreditType = firstCreditType(ptrCreditType);
                headCreditType();
                while (ptrCreditType != NULL) {
                    if (ptrCreditType->code_type == code_type) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-20s|%-11d|%-7d|\n", ptrCreditType->code_type, ptrCreditType->credit_name,
                               ptrCreditType->rate, ptrCreditType->loan_period);
                        printf("-----------------------------------------------------------------\n");
                    }
                    ptrCreditType = ptrCreditType->next;
                }
            }
            break;
            case 2: {
                char credit_name[20];
                printf("Введите имя кредита:\n");
                scanf("%s", &credit_name);
                ptrCreditType = firstCreditType(ptrCreditType);
                headCreditType();
                while (ptrCreditType != NULL) {
                    if (ptrCreditType->credit_name == credit_name) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-20s|%-11d|%-7d|\n", ptrCreditType->code_type, ptrCreditType->credit_name,
                               ptrCreditType->rate, ptrCreditType->loan_period);
                        printf("-----------------------------------------------------------------\n");
                    }
                    ptrCreditType = ptrCreditType->next;
                }
            }
                break;
            default:
                printf("Введите числа от 0 до 2:  ");
        }
    }
}

void searchClient(Client* ptrClient){
    while (true) {
        int count = 0;
        printf("Администратор ======= Выберите действие =======\n");
        printf("Поиск по: \n");
        printf("1. Номеру телефона\n");
        printf("2. Фамилии\n");
        printf("3. Имени\n");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:{
                printf("Введите номер телефона:\n");
                int tel_number = getNumberFromKeyboard();
                ptrClient = firstClient(ptrClient);
                headClient();
                while (ptrClient != NULL) {
                    if (ptrClient->tel_number == tel_number) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-26s|%-18s|%-28s|%-26s|%-18s| \n", ptrClient->tel_number, ptrClient->name_user.surname,
                               ptrClient->name_user.name, ptrClient->address, ptrClient->guarantor.surname, ptrClient->guarantor.name);
                        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");        ptrClient = ptrClient->next;

                    }
                    ptrClient = ptrClient->next;
                }
            }
                break;
            case 2: {
                printf("Введите Фамилию:\n");
                char surname[26];
                printf("Введите имя кредита:\n");
                scanf("%s", &surname);
                ptrClient = firstClient(ptrClient);
                headClient();
                while (ptrClient != NULL) {
                    if (ptrClient->name_user.surname == surname) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-26s|%-18s|%-28s|%-26s|%-18s| \n", ptrClient->tel_number,
                               ptrClient->name_user.surname,
                               ptrClient->name_user.name, ptrClient->address, ptrClient->guarantor.surname,
                               ptrClient->guarantor.name);
                        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");        ptrClient = ptrClient->next;
                   }
                    ptrClient = ptrClient->next;
                }
            }
                break;
            case 3: {
                printf("Введите Имя:\n");
                char name[18];
                printf("Введите имя кредита:\n");
                scanf("%s", &name);
                ptrClient = firstClient(ptrClient);
                headClient();
                while (ptrClient != NULL) {
                    if (ptrClient->name_user.name == name) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-26s|%-18s|%-28s|%-26s|%-18s| \n", ptrClient->tel_number, ptrClient->name_user.surname,
                               ptrClient->name_user.name, ptrClient->address, ptrClient->guarantor.surname, ptrClient->guarantor.name);
                        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");        ptrClient = ptrClient->next;
                    }
                    ptrClient = ptrClient->next;
                }
            }
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

void filtering(CreditType *ptrCreditType, Client* ptrClient, Credit *ptrCredit) {

    while (true) {
        int count = 0;
        printf("Администратор ======= Выберите действие =======\n");
        printf("Фильтрация:\n");
        printf("1. Выданных кредитов по виду кредита\n");
        printf("2. Выданных кредитов по номеру телефона\n");
        printf("3. По кредитной ставке\n");
        printf("4. По сроку выдачи\n");
        printf("0. Возврат.\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:{
                printf("Введите номер вида кредита:\n");
                int code_type = getNumberFromKeyboard();
                ptrCredit = firstCredit(ptrCredit);
                headCredit();
                while (ptrCredit != NULL) {
                    if (ptrCredit->code_type == code_type) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-16li|%-11d| %2d.%2d.%4d |\n", ptrCredit->code_type, ptrCredit->tel_number,
                               ptrCredit->amount, ptrCredit->date.day, ptrCredit->date.month, ptrCredit->date.year);
                        printf("------------------------------------------------------------------\n");
                    }
                    ptrCredit = ptrCredit->next;
                }
            }
                break;
            case 2: {
                printf("Введите номер телефона:\n");
                int tel_number = getNumberFromKeyboard();
                ptrCredit = firstCredit(ptrCredit);
                headCredit();
                while (ptrCredit != NULL) {
                    if (ptrCredit->tel_number == tel_number) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-16li|%-11d| %2d.%2d.%4d |\n", ptrCredit->code_type, ptrCredit->tel_number,
                               ptrCredit->amount, ptrCredit->date.day, ptrCredit->date.month, ptrCredit->date.year);
                        printf("------------------------------------------------------------------\n");
                    }
                    ptrCredit = ptrCredit->next;
                }
            }
                break;
            case 3: {
                printf("Введите ставку:\n");
                int rate = getNumberFromKeyboard();
                headCreditType();
                ptrCreditType = firstCreditType(ptrCreditType);
                while (ptrCreditType != NULL) {
                    if (ptrCreditType->rate == rate) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-20s|%-11d|%-7d|\n", ptrCreditType->code_type, ptrCreditType->credit_name,
                               ptrCreditType->rate, ptrCreditType->loan_period);
                        printf("-----------------------------------------------------------------\n");
                    }
                    ptrCreditType = ptrCreditType->next;
                }
            }
                break;
            case 4: {
                printf("Введите срок выдачи:\n");
                int loan_period = getNumberFromKeyboard();
                headCreditType();
                ptrCreditType = firstCreditType(ptrCreditType);
                while (ptrCreditType != NULL) {
                    if (ptrCreditType->loan_period == loan_period) {
                        printf("|%-5d", (count + 1));
                        printf("|%-16d|%-20s|%-11d|%-7d|\n", ptrCreditType->code_type, ptrCreditType->credit_name,
                               ptrCreditType->rate, ptrCreditType->loan_period);
                        printf("-----------------------------------------------------------------\n");
                    }
                    ptrCreditType = ptrCreditType->next;
                }
            }
                break;
            default:
                printf("Введите числа от 0 до 4: \n");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ РАБОТЫ С ЮЗЕРАМИ // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void userManagement(BankData* ptrBankData){
    while (true) {
        printf("Администратор ======= Выберите действие =======\n");
        printf("1. Показать всех пользователей\n");
        printf("2. Удалить пользователя\n");
        printf("3. Добавить пользователя\n");
        printf("0. Выход\n");
        int i;
        i = getNumberFromKeyboard();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1: clearConsole();
                viewAllUsers(ptrBankData->information);
                break;
            case 2: clearConsole();
                ptrBankData->information = deleteUsers(ptrBankData->information);
                break;
            case 3: clearConsole();
                ptrBankData->information = addUsers(ptrBankData->information);
                break;
            default: printf("Введите числа от 0 до 3: ");
        }
    }
}


