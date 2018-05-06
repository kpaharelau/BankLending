#include <pgtypes_date.h>
#include "Credit.h"
#include "Header.h"

Credit* readCredit(){
    Credit* ptrCredit = nullptr;
    if( isFileExists("Credit.txt")){
        FILE* ptrCreditFile = fopen("Credit.txt", "r"); // указатель для работы с файлами

        long size =  getFileSize(ptrCreditFile);
        int itemsCount = 2;
        Credit* ptrPrevCredit = nullptr;            // указатель для работы с чем??
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
Credit *firstCredit(Credit *ptrCredit) {
    while (ptrCredit != NULL && ptrCredit->prev != NULL) {
        ptrCredit = ptrCredit->prev;
    }
    return ptrCredit;
}

Credit* lastCredit(Credit* ptrCredit){
    while (ptrCredit != NULL && ptrCredit->next != NULL) {
        ptrCredit = ptrCredit->next;
    }
    return ptrCredit;
}

Credit * inputCredit(Credit *ptrCredit) {
    if (ptrCredit != NULL)
        ptrCredit = lastCredit(ptrCredit);

    int num;
    printf("Сколько вы хотите ввести кредитов:\n");
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        Credit *ptrNewCredit = new Credit;
        printf("%d. ", (i + 1));
        printf("\nВведите код кредита: "); // сделать проверку и вывести
        ptrNewCredit->code_type = controlNumber();
        fflush(stdin);
        printf("Введите телефонный номер: "); //сделать проверку на существование такого номера и вывести все номера перед вводом
        ptrNewCredit->tel_number = controlNumber();
        printf("Введите сумму кредита: ");
        fflush(stdin);
        ptrNewCredit->amount = controlNumber();
        printf("Введите дату выдачи\n: ");
        printf("д: ");
        fflush(stdin);
        ptrNewCredit->date.day = controlNumber();
        printf("м: ");
        fflush(stdin);
        ptrNewCredit->date.month = controlNumber();  // сделать дополнительные проверки
        printf("г: ");
        fflush(stdin);
        ptrNewCredit->date.year = controlNumber();
    }
    return ptrCredit;
}