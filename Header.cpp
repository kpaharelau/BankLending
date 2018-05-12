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
        printf("Список кредитов пуст!");
    }else{
        printf("\nВиды кредитов.\n");
        fflush(stdin);
        viewCreditType(ptrCreditType);
    }
    if(ptrClient == nullptr){
        printf("Список клиентов пуст!");
    }else{
        printf("\nКлиенты.\n");
        fflush(stdin);
        viewClient(ptrClient);
    }
    if(ptrCredit == nullptr){
        printf("Список кредитов пуст!");
    }else{
        printf("\nВыданные кредиты.\n");
        fflush(stdin);
        viewCredit(ptrCredit);
    }

}

int loginadmin(){
    if(isFileExists("LoginPassord.txt")){
        FILE *ptrCreditTypeFile = fopen("LoginPassord.txt", "r");

        /*errno_t err;
        FILE *fp;
        entrance temp;
        char login[255], pass[255];
        int k = 0, i = 0;

        printf("Введите логин:\n");
        gets_s(login);
        printf_s("Введите пароль от двух символов:\n");
        while (1)
        {
            pass[i] = _getch();
            if (pass[i] == '\r') break;
            if (pass[i] == '\b')
            {
                printf("%s", "\b \b");
                --i;
            }
            else
            {
                printf("%c", '*');
                ++i;
            }
        }
        pass[i] = '\0';
        printf("\n");
        if (i - 1 < 1)
        {
            return 1;
        }
        strcpy_s(pass, crypt(pass));
        err = fopen_s(&fp, "loginadmin.txt", "r");
        while (!feof(fp))
        {
            fscanf_s(fp, "%s", temp.login, _countof(temp.login));
            fscanf_s(fp, "%s\n", temp.pass, _countof(temp.pass));
            if (strcmp(login, temp.login) == 0 && strcmp(pass, temp.pass) == 0)
            {
                fclose(fp);
                return 0;
            }
        }
        fclose(fp);
        return 1;*/
}