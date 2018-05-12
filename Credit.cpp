#include "Credit.h"
#include "CreditType.h"
#include "Client.h"
#include "Header.h"

///////////////////////// ВЫВОД ИЗ ФАЙЛА ///////////////////////////////////////////////////////////////////////////////
Credit* readCredit(){
    Credit* ptrCredit = nullptr;
    if( isFileExists("Credit.txt")){
        FILE* ptrCreditFile = fopen("Credit.txt", "r"); // указатель для работы с файлами

        Credit* ptrPrevCredit = nullptr;                // указатель для работы с чем??
        while(true){
            int code_type;        // код типа кредита
            int tel_number;       // телефонный номер
            int amount;           // сумма
            int date_day;
            int date_month;
            int date_year;
            int count = fscanf(ptrCreditFile, "%d %d %d %d %d %d" ,
                    &code_type,
                    &tel_number,
                    &amount,
                    &date_day,
                    &date_month,
                    &date_year);
            if(count != 6){
                break;
            }
            ptrCredit = new Credit;             //создаем для указателя динамическую пямять с учетом того, что он пока равен null
            ptrCredit->code_type = code_type;
            ptrCredit->tel_number = tel_number;
            ptrCredit->amount = amount;
            ptrCredit->date.day = date_day;
            ptrCredit->date.month = date_month;
            ptrCredit->date.year = date_year;
            if (ptrPrevCredit != nullptr){
                ptrPrevCredit->next = ptrCredit;
                ptrCredit->prev = ptrPrevCredit;
            }
            ptrPrevCredit = ptrCredit;
        }
        fclose(ptrCreditFile);
    }
    return ptrCredit;
}

///////////////////////// ВВОД В ФАЙЛ //////////////////////////////////////////////////////////////////////////////////
void recordCredit(Credit *ptrCredit){
    FILE *ptrCreditFiles = fopen("Credit.txt", "w+");
    ptrCredit = firstCredit(ptrCredit);
    while (ptrCredit != NULL) {
        fprintf(ptrCreditFiles, "%d %d %d %d %d %d\n", ptrCredit->code_type , ptrCredit->tel_number , ptrCredit->amount, ptrCredit->date.day,  ptrCredit->date.month , ptrCredit->date.year );
        ptrCredit = ptrCredit->next;
    }
    fclose(ptrCreditFiles);
}
///////////////////////// ПЕРВЫЙ ЭЛЕМЕНТ ///////////////////////////////////////////////////////////////////////////////
Credit *firstCredit(Credit *ptrCredit) {
    while (ptrCredit != NULL && ptrCredit->prev != NULL) {
        ptrCredit = ptrCredit->prev;
    }
    return ptrCredit;
}

///////////////////////// ПОСЛЕДНИЙ ЭЛЕМЕНТ ////////////////////////////////////////////////////////////////////////////
Credit* lastCredit(Credit* ptrCredit){
    while (ptrCredit != NULL && ptrCredit->next != NULL) {
        ptrCredit = ptrCredit->next;
    }
    return ptrCredit;
}

///////////////////////// ВВОД С КЛАВИАТУРЫ ////////////////////////////////////////////////////////////////////////////
Credit* inputCredit(CreditType *ptrCreditType, Client* ptrClient, Credit *ptrCredit) {
    int count;
    if ( CheckingPointers(ptrCreditType, ptrClient) == 1){
        return ptrCredit;
    }
    if (ptrCredit != NULL)
        ptrCredit = lastCredit(ptrCredit);

    int num;

    printf("Сколько вы хотите ввести кредитов:\n");
    fflush(stdin);
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        Credit *ptrNewCredit = new Credit;
        printf("%d. ", (i + 1));
        printf("Выберите вид кредита или -1 для выхода.\n");
        fflush(stdin);
        count = viewCreditType(ptrCreditType);
        int choice = askForChoice(count);
        if (choice != -1) {
            ptrCreditType = firstCreditType(ptrCreditType); // указатель возвращаем в первоначальное состояние
            for(int i = 0 ; i < choice-1 ; i ++){
                ptrCreditType = ptrCreditType->next;        // катаем цикл до нужного элемента
            }
            ptrNewCredit->code_type = ptrCreditType->code_type;
        }
        else
            return ptrCredit;

        printf("Выберите клиента или -1 для выхода.\n");
        fflush(stdin);
        count = viewClient(ptrClient);
        choice = askForChoice(count);
        if (choice != -1) {
            ptrClient = firstClient(ptrClient); // указатель возвращаем в первоначальное состояние
            for(int i = 0 ; i < choice-1 ; i ++){
                ptrClient = ptrClient->next;        // катаем цикл до нужного элемента
            }
            ptrNewCredit->tel_number = ptrClient->tel_number;
        }
        else
            return ptrCredit;
        printf("Введите сумму кредита: ");
        fflush(stdin);
        ptrNewCredit->amount = getNumberFromKeyboard();
        printf("Введите дату выдачи:\n");
        printf("день: ");
        fflush(stdin);
        while(true){
            ptrNewCredit->date.day = getNumberFromKeyboard();
            if(ptrNewCredit->date.day >= 1 && ptrNewCredit->date.day <= 31){
                break;
            }
            else
            printf("Проверьте дату!\n");
        }
        printf("месяц: ");
        fflush(stdin);
        while(true){
            ptrNewCredit->date.month = getNumberFromKeyboard();
            if((ptrNewCredit->date.month >= 1) && (ptrNewCredit->date.month <= 12)){
                break;
            }
            printf("Проверьте дату!\n");
        }
        printf("год: ");
        fflush(stdin);
        while(true){
            ptrNewCredit->date.year = getNumberFromKeyboard();
            if((ptrNewCredit->date.year <= 2018) && (ptrNewCredit->date.year >= 2000 )){
                break;
            }
            printf("Проверьте дату!\n");
        }

        ptrNewCredit->prev = ptrCredit;
        if (ptrCredit != NULL)
            ptrCredit->next = ptrNewCredit;
        ptrCredit = ptrNewCredit;
    }
    return ptrCredit;
}

///////////////////////// УДАЛЕНИЕ ОДНОГО/ НЕСКОЛЬКИХ ЭЛЕМЕНТОВ ////////////////////////////////////////////////////////
Credit* deleteCredit(Credit *ptrCredit){
    if (ptrCredit != nullptr) {
        int count = viewCredit(ptrCredit);
        printf("Выберите элемент для удаления или -1 для выхода.\n");
        fflush(stdin);
        int choice = askForChoice(count);
        if (choice != -1) {
            ptrCredit = firstCredit(ptrCredit); // указатель возвращаем в первоначальное состояние
            for(int i = 0 ; i < choice-1 ; i ++){
                ptrCredit = ptrCredit->next;        // катаем цикл до нужного элемента
            }
            Credit* ptrPrevCredit = ptrCredit->prev;
            Credit* ptrNextCredit = ptrCredit->next;
            if (ptrNextCredit != NULL)
                ptrNextCredit->prev = ptrPrevCredit;
            if (ptrPrevCredit != NULL)
                ptrPrevCredit->next = ptrNextCredit;
            delete(ptrCredit);

            if (ptrNextCredit != NULL)
                return ptrNextCredit;
            if (ptrPrevCredit != NULL)
                return ptrPrevCredit;
            return NULL;
        }
    }
    printf("Нет данных для удаления\n");
    fflush(stdin);
    return ptrCredit;
}

///////////////////////// ВЫВОД НА ЭКРАН ///////////////////////////////////////////////////////////////////////////////
int viewCredit(Credit *ptrCredit){
        int count = 0;
        headCredit();
        ptrCredit = firstCredit(ptrCredit);
        while (ptrCredit != NULL) {                // подсказка для людей
            printf("|%-5d", (count + 1));
            printf("|%-16d|%-16d|%-11d| %-2d.%-2d.%-4d |\n", ptrCredit->code_type, ptrCredit->tel_number,
                   ptrCredit->amount, ptrCredit->date.day, ptrCredit->date.month , ptrCredit->date.year);
            printf("------------------------------------------------------------------\n");
            ptrCredit = ptrCredit->next;
            count++;
        }
        return count;
}

void headCredit(){
    {
        printf("------------------------------------------------------------------\n");
        printf("|  №  | Номер  кредита |  Телеф. номер  |   Сумма   |Дата выдачи |\n");
        printf("------------------------------------------------------------------\n");
        fflush(stdin);
    }
}

///////////////////////// ПРОВЕРКА УКАЗАТЕЛЕЙ НА ПУСТОТУ ///////////////////////////////////////////////////////////////
int CheckingPointers(CreditType *ptrCreditType, Client* ptrClient){
    ptrCreditType = firstCreditType(ptrCreditType);
    ptrClient= firstClient(ptrClient);
        if(ptrClient == nullptr || ptrCreditType == nullptr ){
            return 1;
        }
        return 0;
}


Credit* editCredit(Credit *ptrCredit){
    ptrCredit = firstCredit(ptrCredit); // указатель возвращаем в первоначальное состояние
    if(ptrCredit == nullptr){
        printf("Нет элементов для редактирования\n");
    }
    else{
        int count = viewCredit(ptrCredit);
        printf("Выберите запись для ретактирования или -1 для выхода? ");
        fflush(stdin);
        int choice = askForChoice(count);

        if (choice != -1) {
            ptrCredit = firstCredit(ptrCredit); // указатель возвращаем в первоначальное состояние
            for(int i = 0 ; i < choice-1 ; i++){
                ptrCredit = ptrCredit->next;        // катаем цикл до нужного элемента
            }
            printf("Введите сумму кредита: ");
            fflush(stdin);
            ptrCredit->amount = getNumberFromKeyboard();
            printf("Введите дату выдачи:\n");
            printf("день: ");
            fflush(stdin);
            while(true){
                ptrCredit->date.day = getNumberFromKeyboard();
                if(ptrCredit->date.day >= 1 && ptrCredit->date.day <= 31){
                    break;
                }
                else
                    printf("Проверьте дату!\n");
            }
            printf("месяц: ");
            fflush(stdin);
            while(true){
                ptrCredit->date.month = getNumberFromKeyboard();
                if((ptrCredit->date.month >= 1) && (ptrCredit->date.month <= 12)){
                    break;
                }
                printf("Проверьте дату!\n");
            }
            printf("год: ");
            fflush(stdin);
            while(true){
                ptrCredit->date.year = getNumberFromKeyboard();
                if((ptrCredit->date.year <= 2018) && (ptrCredit->date.year >= 2000 )){
                    break;
                }
                printf("Проверьте дату!\n");
            }
        }

    }
    return ptrCredit;
}

Credit* searchCredit(Credit *ptrCredit){

}