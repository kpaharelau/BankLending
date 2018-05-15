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
    //int size = count(ptrBankData->creditType);;
    headCreditType();
    int kol = 0;
    while (true) {
        Credit *ptrCredit = firstCredit(ptrBankData->credit);
        while (array != NULL && array->prev != NULL) {
            array = array->prev;
        }
        while (ptrCredit != nullptr) {
            while (array != nullptr) {
                if (ptrCredit->code_type = array->code_type) {
                    if (kol != 3)
                        kol++;
                    else {
                        Client *ptrClient = firstClient(ptrBankData->client);
                        for (int i = 0; i < 3; i++) {
                            if (ptrCredit->tel_number = ptrClient->tel_number) {
                                printf("|%-5d", (i + 1));
                                printf("|%-16d|%-20s|%-11d|%-7d|\n", array[i].code_type, array[i].credit_name,
                                       array[i].rate, array[i].loan_period);
                                printf("-----------------------------------------------------------------\n");
                            }
                        }
                        goto end_loop;
                    }
                }
            }
            array = array->next;
        }
        ptrCredit = ptrCredit->next;
    }
    end_loop:;
}



   /* for (int i = 0; i < 3 ; i++) {

    }*/

    delete array;


//    int count;
//
//    ptrBankData = firstCreditType(ptrBankData);
//    while(ptrBankData != nullptr){
//        ptrBankData = ptrBankData->next;
//        count++;
//    }
//    CreditType * ptrNextCreditType = ptrBankData->next;
//    CreditType * tmp;
//    for(int i = 0 ; i < count-1; i++){
//            if (ptrNextCreditType < ptrBankData) {
//                tmp->loan_period = ptrNextCreditType->loan_period;
//                ptrNextCreditType->loan_period = ptrBankData->loan_period;
//                ptrBankData->loan_period = tmp->loan_period;
//                // тут надо что-то дописать, чтобы при следующем проходе все было ок
//            }
//        ptrBankData = ptrBankData->next;
//    }
//    for( int i = 0; i < 3 ; i++){
//        printf("%d. %d", (i+1), ptrBankData->loan_period);
//    }
}