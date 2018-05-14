#include "Utils.h"
#include "CreditType.h"
#include "Client.h"
#include "Credit.h"
#include "UserInformation.h"

#define _XOPEN_SOURCE
#include <unistd.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ПРОВЕРКИ  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getNumberFromKeyboard() {
    int res, i;
    do {
        res = scanf("%d", &i);
        while (getchar() != '\n');
        if (res != 1) printf("Введите число!\n");
    } while (res != 1);
    return i;
}

void clearConsole() {
//  system("clear");
}

int isFileExists(const char *name) {
    struct stat buffer;                                                                                                 //что делает эта функция|| желательно подробнее
    return (stat(name, &buffer) == 0);
}


///////////////////////// ПЕРЕСПРОС ДЕЙТВИЯ ////////////////////////////////////////////////////////////////////////////
int askForChoice(int count) {
    int choice;
    while (true) {
        scanf("%d", &choice);                          // проверка
        if (choice <= count || choice == -1) break;
        printf("Проверьте число!");
    }
    return choice;
}

///////////////////////// ВЫВОД ВСЕГО //////////////////////////////////////////////////////////////////////////////////
void viewAll(CreditType *ptrCreditType, Client *ptrClient,
             Credit *ptrCredit) {                                           // можно сделать проверку
    if (ptrCreditType == nullptr) {
        printf("Список видов кредитов пуст!\n");
    } else {
        printf("\nВиды кредитов.\n");
        fflush(stdin);
        viewCreditType(ptrCreditType);
    }
    if (ptrClient == nullptr) {
        printf("Список клиентов пуст!\n");
    } else {
        printf("\nКлиенты.\n");
        fflush(stdin);
        viewClient(ptrClient);
    }
    if (ptrCredit == nullptr) {
        printf("Список кредитов пуст!\n");
    } else {
        printf("\nВыданные кредиты.\n");
        fflush(stdin);
        viewCredit(ptrCredit);
    }

}

char alf[] = "abcedfghijklmnopqrstuvwxyz0123456789#!@$%^&*-+=";//словарь
int k = 3;

char *encrypt(char *input) {

    for (int n = 0; n < strlen(input); n++) {
        for (int i = 0; i < 47; i++) {
            if (input[n] == alf[i]) {
                if (i >= 47)
                    input[n] = alf[i - 47];
                else
                    input[n] = alf[i + k];//сдвигаем вправо на показания шага ключа
                break;//принудительно выходим из цикла
            }
        }
    }
    return input;
}

char *decrypt(char *input) {
    for (int n = 0; n < 10; n++) {
        for (int i = 0; i < 47; i++) {
            if (input[n] == alf[i]) {
                if (i >= 47)
                    input[n] = alf[i - 47];
                else
                    input[n] = alf[i - k];//сдвигаем влево на показания шага ключа
                break;//принудительно выходим из цикла
            }
        }
    }
    return input;
}

/**
 * see https://www.gnu.org/software/libc/manual/html_node/crypt.html
 * @param input - то, что ввел пользователь
 * @return зашифрованный пароль
 */

char *createPassword(char *input) {
    char* password = encrypt(input);
    return password;
}

int checkPassword(char *input, char *pass) {
    int ok;
    decrypt(pass);
    /* Test the result. */
    ok = strcmp(input, pass) == 0;
    return ok;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               Выпольнение задачи // ПОЛЬЗОВАТЕЛЬ
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

void task(CreditType* ptrCreditType){
    int count, tmp;
    ptrCreditType = firstCreditType(ptrCreditType);
    while(ptrCreditType != nullptr){
        ptrCreditType = ptrCreditType->next;
        count++;
    }
    int mas[count];
    ptrCreditType = firstCreditType(ptrCreditType);
    while(ptrCreditType != nullptr){
        mas[count] = ptrCreditType->loan_period;
        ptrCreditType = ptrCreditType->next;
    }
    for(int i = 1 ; i < count; i++){
        if (mas[i] < mas[i-1]) {
            tmp = mas[i];
            mas[i] = mas[i-1];
            mas[i-1] = tmp;
        }
    }
    for( int i = count; i > (count-3); i--){
        printf("%d. %d ", (i+1), mas[i]);
    }
}*/
