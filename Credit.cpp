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
            Date date;
            int count = fscanf(ptrCreditFile, "%d %d %d %d %d %d " ,
                    &code_type,
                    &tel_number,
                    &amount,
                    &date.day,
                    &date.month,
                    &date.year);
            if(count != 6){
                break;
            }
            Credit* ptrCredit = new Credit;             //создаем для указателя динамическую пямять с учетом того, что он пока равен null
            ptrCredit->code_type = code_type;
            ptrCredit->tel_number = tel_number;
            ptrCredit->amount = amount;
            ptrCredit->date.day = date.day;
            ptrCredit->date.month = date.month;
            ptrCredit->date.year = date.year;
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
        fprintf(ptrCreditFiles, "%d %d %d %d %d\n", ptrCredit->code_type , ptrCredit->amount , ptrCredit->amount, ptrCredit->date.day,  ptrCredit->date.month , ptrCredit->date.year );
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
    if ( CheckingPointers(ptrCreditType, ptrClient) == 1){
        return ptrCredit;
    }
    if (ptrCredit != NULL)
        ptrCredit = lastCredit(ptrCredit);

    int num;
    printf("Сколько вы хотите ввести кредитов:\n");
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        Credit *ptrNewCredit = new Credit;
        printf("%d. ", (i + 1));
        printf("Введите код кредита: "); // сделать проверку и вывести
        ptrCreditType = firstCreditType(ptrCreditType);
        ptrNewCredit->code_type = getNumberFromKeyboard();
        while(true){
            if(ptrNewCredit->code_type == ptrCreditType->code_type){
                break;
            }
            ptrCreditType = ptrCreditType->next;
            if(ptrCreditType == nullptr){
                printf("Такого кредита нет. Попробуйте еще.");
                ptrNewCredit->code_type = getNumberFromKeyboard();
                ptrCreditType = firstCreditType(ptrCreditType);
            }
        }
        fflush(stdin);
        printf("Введите телефонный номер: ");
        ptrClient= firstClient(ptrClient);
        ptrNewCredit->tel_number = getNumberFromKeyboard();                       //сделать проверку на существование такого номера и вывести все номера перед вводом
        while(true){
            if(ptrNewCredit->tel_number == ptrClient->tel_number){
                break;
            }
            ptrClient = ptrClient->next;
            if(ptrClient == nullptr){
                printf("Такого клиента. Попробуйте еще.");
                ptrNewCredit->tel_number = getNumberFromKeyboard();
                ptrClient= firstClient(ptrClient);
            }
        }
        printf("Введите сумму кредита: ");
        fflush(stdin);
        ptrNewCredit->amount = getNumberFromKeyboard();
        printf("Введите дату выдачи:\n");
        printf("д: ");
        fflush(stdin);
        ptrNewCredit->date.day = getNumberFromKeyboard();
        printf("м: ");
        fflush(stdin);
        ptrNewCredit->date.month = getNumberFromKeyboard();  // сделать дополнительные проверки
        printf("г: ");
        fflush(stdin);
        ptrNewCredit->date.year = getNumberFromKeyboard();
    }
    return ptrCredit;
}

///////////////////////// УДАЛЕНИЕ ОДНОГО/ НЕСКОЛЬКИХ ЭЛЕМЕНТОВ ////////////////////////////////////////////////////////
Credit* deleteCredit(Credit *ptrCredit){
    if (ptrCredit != nullptr) {
        int count = viewCredit(ptrCredit);
        printf("Выберите элемент для удаления или -1 для выхода.\n");
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
    printf("Нет данных для удаления");
    return ptrCredit;
}

int viewCredit(Credit *ptrCredit){
        int count = 0;
        headCredit();
        ptrCredit = firstCredit(ptrCredit);
        while (ptrCredit != NULL) {                // подсказка для людей
            printf("|%-5d", (count + 1));
            printf("|%-10d|%-16s|%-12d| %-2d.%-2d.%-4d |\n", ptrCredit->code_type, ptrCredit->tel_number, ptrCredit->amount,
                   ptrCredit->date.day, ptrCredit->date.month , ptrCredit->date.year);
            printf("-----------------------------------------------------------------\n");
            ptrCredit = ptrCredit->next;
            count++;
        }
        return count;
}

void headCredit(){
    {
        printf("-----------------------------------------------------------------\n");
        printf("|  №  | Номер  кредита |  Телефонный номер  | Дата выдачи |\n");
        printf("-----------------------------------------------------------------\n");
    }
}

int CheckingPointers(CreditType *ptrCreditType, Client* ptrClient){
    ptrCreditType = firstCreditType(ptrCreditType);
    ptrClient= firstClient(ptrClient);
        if(ptrClient == nullptr || ptrCreditType == nullptr ){
            return 1;
        }
        return 0;
}