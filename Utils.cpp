#include "Utils.h"
#include "CreditType.h"
#include "Client.h"
#include "Credit.h"

#define _XOPEN_SOURCE
#include <unistd.h>

char *crypt(const char *key, const char *salt);

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

long getLongFromKeyboard() {
    long res, i;
    do {
        res = scanf("%li", &i);
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

/**
 * see https://www.gnu.org/software/libc/manual/html_node/crypt.html
 * @param input - то, что ввел пользователь
 * @return зашифрованный пароль
 */
char *createPassword(char *input) {
    unsigned long seed[2];
    char salt[] = "$1$........";
    const char *const seedchars =
            "./0123456789ABCDEFGHIJKLMNOPQRST"
            "UVWXYZabcdefghijklmnopqrstuvwxyz";
    char *password;
    int i;

    /* Generate a (not very) random seed.
       You should do it better than this... */
    seed[0] = time(NULL);
    seed[1] = getpid() ^ (seed[0] >> 14 & 0x30000);

    /* Turn it into printable characters from ‘seedchars’. */
    for (i = 0; i < 8; i++)
        salt[3 + i] = seedchars[(seed[i / 5] >> (i % 5) * 6) & 0x3f];

    /* Read in the user’s createPassword and encrypt it. */
    password = crypt(input, salt);
    return password;
}

int checkPassword(char *input, char *pass) {
    char *result;
    int ok;

    /* Read in the user’s password and encrypt it,
       passing the expected createPassword in as the salt. */
    result = crypt(input, pass);

    /* Test the result. */
    ok = strcmp(result, pass) == 0;
    return ok;

}