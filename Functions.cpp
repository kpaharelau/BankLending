#include "Header.h"
#include "CreditType.h"
#include "Client.h"
#include "Credit.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ДОБАВЛЕНИЯ // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void add(CreditType *ptrCreditType, Client *ptrClient, Credit *ptrCredit, BankData* ptrBankData ) {
    while (true) {
        printf("======= Выберите действие =======\n");
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
                ptrBankData->creditType = inputCreditType(ptrCreditType); // еще раз причину появления банка данных
                break;
            case 2:
                ptrBankData->client = inputClient(ptrClient);
                break;
            case 3:
                ptrBankData->credit = inputCredit(ptrCredit);
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ УДАЛЕНИЯ  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove(CreditType *ptrCreditType, Client *ptrClient, Credit *ptrCredit, BankData* ptrBankData ) {
    while (1) {
        printf("======= Выберите действие =======\n");
        printf("1. Удалить все\n");
        printf("2. Удалить элемент\n");
        printf("0. Вход. \n");
        printf("\nВаше действие: ");
        int i;
        i = controlNumber();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:
                removeAll(ptrCreditType, ptrClient, ptrCredit);
                break;
            case 2:
                removePart(ptrCreditType, ptrClient, ptrCredit);
                break;
            default:
                printf("Введите числа от 0 до 2:  ");
        }
    }
}

void removePart(CreditType *ptrCreditType, Client *ptrClient, Credit *ptrCredit) {
    while (1) {
        printf("\n ======= Выберите действие =======\n");
        printf("1. Удалить вид кредита\n");
        printf("2. Удалить клиента\n");
        printf("3. Удалить кредит\n");
        printf("0. Вход. \n");
        printf("\nВаше действие: ");
        int i;
        i = controlNumber();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:
                if (deleteCreditType(ptrCreditType) == 1) {
                    puts("Вид кредита не найден");
                } else {
                    puts("Вид кредита удален.");
                }
                break;
            case 2:
                if (deleteClients(start_clients) == 1) {
                    puts("Вид кредита не найден");
                } else {
                    puts("Вид кредита удален.");
                }
                break;
            case 3:
                deleteCredit(start_credit);
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

int removeAll(CreditType *ptrCreditType, Client *ptrClient, Credit *ptrCredit) {

    while (true) {
        printf("\n======= Вы уверены? =======");
        printf("1. Да\n");
        printf("2. Нет\n");
        printf("\nВаше действие: ");
        int i = controlNumber();
        if (i == 0) break;
        clearConsole();
        CreditType *p_creditType = start_creditType;
        CreditType *p_temp = start_creditType;
        CreditType *p_tmp = start_creditType->next;
        Credit *p_credit = start_credit;
        Client *p_clients = start_clients;
        switch (i) {
            case 1:
                while (p_creditType != NULL) {
                    start_creditType = start_creditType->next;
                    delete p_temp;
                    p_temp = start_creditType;
                }
                while (p_clients != NULL) {

                }
                while (p_credit != NULL) {

                }

                /* int deleteNth(Node **head, int n) {
                   if (n == 0) {
                     return pop(head);
                   }
                   else {
                     Node *prev = getNth(*head, n - 1);
                     Node *elm = prev->next;
                     int val = elm->value;

                     prev->next = elm->next;
                     free(elm);
                     return val;
                   }
                 }*/

                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
    return 0;
}

int deleteCreditType(CreditType *start_creditType) {
    int count = 0, key;
    CreditType *p_creditType = start_creditType;
    while (p_creditType != NULL) {
        count++;
        printf("%d. %d\t%s", count, p_creditType->code_type, p_creditType->credit_name);
        p_creditType = p_creditType->next;

    }
    printf("Введите /№ вида кредита, который будет удален: ");
    key = controlNumber();
    if (count < key) {
        return 1;
    } else {
        CreditType *p_creditType = start_creditType;
        for (int i = 0; i < count; i++) {
            p_creditType = p_creditType->next;
        }
        CreditType *pre = start_creditType;
        while (pre != NULL) {
            if (pre->next == p_creditType)
                break;            //нашли предшествующий узел и выходим из цикла
            pre = pre->next;
        }
        pre->next = p_creditType->next;
        fflush(stdin);
        delete p_creditType;
    }
    return 0;
}

int deleteClients(Client *start_clients) {
    int count = 0, key;
    Client *p_clients = start_clients;
    while (p_clients != NULL) {
        count++;
        printf("%d. %d\t%s\t%s", count, p_clients->tel_number, p_clients->name_user.surname, p_clients->name_user.name);
        p_clients = p_clients->next;
    }
    printf("Введите /№ вида кредита, который будет удален: ");
    key = controlNumber();
    if (count < key) {
        return 1;
    } else {
        Client *p_clients = start_clients;
        for (int i = 0; i < count; i++) {
            p_clients = p_clients->next;
        }
        Client *pre = start_clients;
        while (pre != NULL) {
            if (pre->next == p_clients)
                break;            //нашли предшествующий узел и выходим из цикла
            pre = pre->next;
        }
        pre->next = p_clients->next;
        delete p_clients;
        fflush(stdin);
    }
    return 0;
}

int deleteCredit(Credit *start_credit) {
    int count = 0, key;
    Credit *p_credit = start_credit;
    while (p_credit != NULL) {
        printf("%d. %d\t%d\t%d", count, p_credit->code_type, p_credit->tel_number, p_credit->amount);
        p_credit = p_credit->next;
        count++;
    }
    printf("Введите /№ вида кредита, который будет удален: ");
    key = controlNumber();
    if (count < key) {
        return 1;
    } else {
        Credit *p_credit = start_credit;
        for (int i = 0; i < count; i++) {
            p_credit = p_credit->next;
        }
        Credit *pre = start_credit;
        while (pre != NULL) {
            if (pre->next == p_credit)
                break;            //нашли предшествующий узел и выходим из цикла
            pre = pre->next;
        }
        pre->next = p_credit->next;
        delete p_credit;
        fflush(stdin);
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ПРОСМОТРА  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void head() // заголовок
{
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("*|  №  | Номер кредита | Телеф. номер |         Фамилия         |       Имя       |           Адресс          |   Сумма   | Проценты |  Дата  |    Фамилия поручителя    |  Имя поручителя |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int viewAll(CreditType *start_creditType, Client *start_clients, Credit *start_credit) {
    if (start_creditType == NULL || start_creditType == NULL || start_creditType == NULL) {
        return 1;
    } else {
        int i = 1;
        Credit *p_credit = start_credit;
        head();
        while (p_credit != NULL) {
            CreditType *p_creditType = start_creditType;
            Client *p_clients = start_clients;
            while (p_credit->code_type != p_creditType->code_type) {
                p_creditType = p_creditType->next;
            }
            while (p_credit->tel_number != p_clients->tel_number) {
                p_clients = p_clients->next;
            }
            printf("*|%-6d|", i);
            printf("%-16d|%-15d|%-26s|%-18s|%-28s|%-12d|%-11d|%-2d.%-2d.%-4d|%-26s|%-18s*\n", p_credit->code_type,
                   p_credit->tel_number, p_clients->name_user.name, p_clients->name_user.surname, p_clients->address,
                   p_credit->amount, p_creditType->rate, p_credit->date.day, p_credit->date.month, p_credit->date.year,
                   p_clients->guarantor.surname, p_clients->guarantor.name);
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            p_credit = p_credit->next;
        }
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ПРОВЕРКИ  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getTime(tm &newtime) {
//  time_t now = time(0);
//  localtime(&newtime, &now);
//  newtime.tm_mon = 1 + newtime.tm_mon;
//  newtime.tm_year = 1900 + newtime.tm_year;
}
// функция считывания времени с компьютера

int controlNumber() {
    int res, i;
    do {
        res = scanf("%d", &i);
        while (getchar() != '\n');
        if (res != 1) printf("Введите число!\n");
    } while (res != 1);
    return i;
}
// Контроль ввода именно чисел

long getFileSize(FILE *input) {
    long fileSizeBytes;
    // set file pointer to end of file
    fseek(input, 0, SEEK_END);
    // get current pointer position in bytes (== file size in bytes)
    fileSizeBytes = ftell(input);
    // return pointer to begin of file (it's very IMPORTANT)
    fseek(input, 0, SEEK_SET);
    return fileSizeBytes;
}

void clearConsole() {
//  system("clear");
}

int isFileExists(const char *name){
    struct stat   buffer;                                //что делает эта функция|| желательно подробнее
    return (stat (name, &buffer) == 0);
}