#include "Header.h"
#include "CreditType.h"
#include "Client.h"
#include "Credit.h"

void head() // заголовок
{
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("*|  №  | Номер кредита | Телеф. номер |         Фамилия         |       Имя       |           Адресс          |   Сумма   | Проценты |  Дата  |    Фамилия поручителя    |  Имя поручителя |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

/*
int viewAll(CreditType *start_creditType, Client *start_clients, Credit *start_credit) {
    if (start_creditType == NULL || start_clients == NULL || start_credit == NULL) {
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
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ПРОВЕРКИ  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getTime(tm &newtime) {
//  time_t now = time(0);
//  localtime(&newtime, &now);
//  newtime.tm_mon = 1 + newtime.tm_mon;
//  newtime.tm_year = 1900 + newtime.tm_year;
}

int getNumberFromKeyboard() {
    int res, i;
    do {
        res = scanf("%d", &i);
        while (getchar() != '\n');
        if (res != 1) printf("Введите число!\n");
    } while (res != 1);
    return i;
}

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


///////////////////////// ПЕРЕСПРОС ДЕЙТВИЯ ////////////////////////////////
int askForChoice(int count){
    int choice;
    while (true){
        scanf("%d" , &choice);                       // проверка
        if ( choice <= count || choice == -1) break;
        printf("Проверьте число!");
    }
    return choice;
}

int viewAll(BankData *){

}
