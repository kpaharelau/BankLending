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

void task(BankData *ptrBankData) {

    CreditType *array = sortByLoanPeriod(ptrBankData->creditType); // Сортировка массива пузырьком
    int size = count(ptrBankData->creditType);
    

    size = size < 3 ? size:3;

    headClient();

    for (int i = 0; i < size ; i++) {

        int code_type = array[i].code_type;
        Credit *pCredit = firstCredit(ptrBankData->credit);
        while (pCredit!=NULL) {
            if (pCredit->code_type == code_type) {
                Client *pClient = firstClient(ptrBankData->client);
                while (pClient!=NULL) {
                    if (pClient->tel_number == pCredit->tel_number) {
                        printf("|%-5d", (i + 1));
                        printf("|%-16d|%-26s|%-18s|%-28s|%-26s|%-18s|\n", pClient->tel_number, pClient->name_user.surname,
                               pClient->name_user.name, pClient->address, pClient->guarantor.surname, pClient->guarantor.name);
                        printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
                        break;
                    }
                    pClient = pClient->next;
                }

            }
            pCredit = pCredit->next;
        }
    }
    delete array;

}