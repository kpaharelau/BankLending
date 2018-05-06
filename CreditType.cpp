#include <w32api/dshow.h>
#include "CreditType.h"

CreditType* readCreditTypes(){
    CreditType *ptrCreditType = nullptr;
    if(isFileExists("CreditType.txt")){
        FILE *ptrCreditTypeFile = fopen("CreditType.txt", "r");

        long size = getFileSize(ptrCreditTypeFile);
        CreditType *ptrPrevCreditType = nullptr;
        while (true) {
            int code_type;          // код кредита
            char credit_name[100];  // имя кредита
            int rate;               // ставка
            int loan_period;        // срок выдачи
            int count = fscanf(ptrCreditTypeFile, "%d %s %d %d ",
                               &code_type,
                               credit_name,
                               &rate,
                               &loan_period);
            if (count != 4) {
                break;                                                   //почему четыре
            }
            ptrCreditType = new CreditType;
            ptrCreditType->code_type = code_type;
            strcpy(ptrCreditType->credit_name, credit_name);              //выдает ошибку, т.к что-то не так со strcpy
            ptrCreditType->rate = rate;
            ptrCreditType->loan_period = loan_period;

            if (ptrPrevCreditType != nullptr){
                ptrPrevCreditType->next = ptrCreditType;
                ptrCreditType->prev = ptrPrevCreditType;
            }
            ptrPrevCreditType = ptrCreditType;
        }
        fclose(ptrCreditTypeFile);
    }

    return ptrCreditType;
}

void recordCreditTypes(CreditType *ptrCreditType) {
    FILE *ptrCreditTypeFiles = fopen("CreditType.txt", "w+");
    ptrCreditType = firstCreditType(ptrCreditType);
    while (ptrCreditType != NULL) {
        fprintf(ptrCreditTypeFiles, "%d %s %d %d ", ptrCreditType->code_type, ptrCreditType->credit_name,
                ptrCreditType->rate, ptrCreditType->loan_period);
        ptrCreditType = ptrCreditType->next;
    }
    fclose(ptrCreditTypeFiles);
}

CreditType *firstCreditType(CreditType *ptrCreditType) {
    while (ptrCreditType != NULL && ptrCreditType->prev != NULL) {
        ptrCreditType = ptrCreditType->prev;
    }
    return ptrCreditType;
}

CreditType* lastCreditType(CreditType* ptrCreditType){
    while (ptrCreditType != NULL && ptrCreditType->next != NULL) {
        ptrCreditType = ptrCreditType->next;
    }
    return ptrCreditType;
}

CreditType * inputCreditType(CreditType *ptrCreditType) {
    if (ptrCreditType != NULL)
    ptrCreditType = lastCreditType(ptrCreditType);

    int num;
    printf("Сколько вы хотите ввести кредитов:\n");
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        CreditType *ptrNewCreditType = new CreditType;
        printf("%d. ", (i + 1));
        printf("Введите код кредита:\n");
        fflush(stdin);
        ptrNewCreditType->code_type = controlNumber();
        printf("Введите имя кредита:\n");
        fflush(stdin);
        scanf("%s", ptrNewCreditType->credit_name); // сделать проверки
        printf("Введите ставку кредита:\n");
        fflush(stdin);
        ptrNewCreditType->rate = controlNumber();
        printf("Введите срок выдачи(в месяцах):\n");
        ptrNewCreditType->loan_period = controlNumber();
        fflush(stdin);

        ptrNewCreditType->prev = ptrCreditType;
        if (ptrCreditType != NULL)
        ptrCreditType->next = ptrNewCreditType;
        ptrCreditType = ptrNewCreditType;
    }

    return ptrCreditType;
}