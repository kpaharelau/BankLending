#include "Header.h"
#include "CreditType.h"
#include "Client.h"
#include "Credit.h"




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

int isFileExists(const char *name){
    struct stat   buffer;                                                                                                 //что делает эта функция|| желательно подробнее
    return (stat (name, &buffer) == 0);
}


///////////////////////// ПЕРЕСПРОС ДЕЙТВИЯ ////////////////////////////////////////////////////////////////////////////
int askForChoice(int count){
    int choice;
    while (true){
        scanf("%d" , &choice);                          // проверка
        if ( choice <= count || choice == -1) break;
        printf("Проверьте число!");
    }
    return choice;
}

///////////////////////// ВЫВОД ВСЕГО //////////////////////////////////////////////////////////////////////////////////
void viewAll(CreditType *ptrCreditType, Client* ptrClient, Credit *ptrCredit){                                           // можно сделать проверку
    if(ptrCreditType == nullptr){
        printf("Список видов кредитов пуст!\n");
    }else{
        printf("\nВиды кредитов.\n");
        fflush(stdin);
        viewCreditType(ptrCreditType);
    }
    if(ptrClient == nullptr){
        printf("Список клиентов пуст!\n");
    }else{
        printf("\nКлиенты.\n");
        fflush(stdin);
        viewClient(ptrClient);
    }
    if(ptrCredit == nullptr){
        printf("Список кредитов пуст!\n");
    }else{
        printf("\nВыданные кредиты.\n");
        fflush(stdin);
        viewCredit(ptrCredit);
    }

}
