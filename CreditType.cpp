#include "CreditType.h"


void headCreditType() // заголовок
{
    printf("-----------------------------------------------------------------\n");
    printf("|  №  | Номер  кредита |  Название кредита  |  Проценты |  Срок |\n");
    printf("-----------------------------------------------------------------\n");
}

///////////////////////// ВЫВОД ИЗ ФАЙЛА ///////////////////////////////////////////////////////////////////////////////
CreditType* readCreditTypes(){
    CreditType *ptrCreditType = nullptr;
    if(isFileExists("CreditType.txt")){
        FILE *ptrCreditTypeFile = fopen("CreditType.txt", "r");

        CreditType *ptrPrevCreditType = nullptr;
        while (true) {
            int code_type;          // код кредита
            char credit_name[20];  // имя кредита
            int rate;               // ставка
            int loan_period;        // срок выдачи
            int count = fscanf(ptrCreditTypeFile, "%d %s %d %d ",
                               &code_type,
                               credit_name,
                               &rate,
                               &loan_period);
            if (count != 4) {
                break;
            }
            ptrCreditType = new CreditType;
            ptrCreditType->code_type = code_type;
            strcpy(ptrCreditType->credit_name, credit_name);
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
///////////////////////// ВВОД В ФАЙЛ //////////////////////////////////////////////////////////////////////////////////
void recordCreditTypes(CreditType *ptrCreditType) {
    FILE *ptrCreditTypeFiles = fopen("CreditType.txt", "w+");
    ptrCreditType = firstCreditType(ptrCreditType);
    while (ptrCreditType != NULL) {
        fprintf(ptrCreditTypeFiles, "%d %s %d %d\n", ptrCreditType->code_type, ptrCreditType->credit_name,
                ptrCreditType->rate, ptrCreditType->loan_period);
        ptrCreditType = ptrCreditType->next;
    }
    fclose(ptrCreditTypeFiles);
}

///////////////////////// ПЕРВЫЙ ЭЛЕМЕНТ ///////////////////////////////////////////////////////////////////////////////
CreditType *firstCreditType(CreditType *ptrCreditType) {
    while (ptrCreditType != NULL && ptrCreditType->prev != NULL) {
        ptrCreditType = ptrCreditType->prev;
    }
    return ptrCreditType;
}

///////////////////////// ПОСЛЕДНИЙ ЭЛЕМЕНТ ////////////////////////////////////////////////////////////////////////////
CreditType* lastCreditType(CreditType* ptrCreditType){
    while (ptrCreditType != NULL && ptrCreditType->next != NULL) {
        ptrCreditType = ptrCreditType->next;
    }
    return ptrCreditType;
}

///////////////////////// ВВОД С КЛАВИАТУРЫ ////////////////////////////////////////////////////////////////////////////
CreditType * inputCreditType(CreditType *ptrCreditType) {
    if (ptrCreditType != NULL)                                     //Проверяем на пустоту, для возможной записи в конец файла
    ptrCreditType = lastCreditType(ptrCreditType);

    int num;
    printf("Сколько вы хотите ввести кредитов:\n");
    fflush(stdin);
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        CreditType *ptrNewCreditType = new CreditType;
        printf("%d. ", (i + 1));
        printf("Введите код кредита:\n");
        fflush(stdin);
        ptrNewCreditType->code_type = getNumberFromKeyboard();
        printf("Введите имя кредита:\n");
        fflush(stdin);
        scanf("%s", ptrNewCreditType->credit_name); // сделать проверки
        printf("Введите ставку кредита:\n");
        fflush(stdin);
        ptrNewCreditType->rate = getNumberFromKeyboard();
        printf("Введите срок выдачи(в месяцах):\n");
        fflush(stdin);
        ptrNewCreditType->loan_period = getNumberFromKeyboard();

        ptrNewCreditType->prev = ptrCreditType;
        if (ptrCreditType != NULL)
        ptrCreditType->next = ptrNewCreditType;
        ptrCreditType = ptrNewCreditType;
    }

    return ptrCreditType;
}

///////////////////////// УДАЛЕНИЕ ОДНОГО/ НЕСКОЛЬКИХ ЭЛЕМЕНТОВ ////////////////////////////////////////////////////////
CreditType* deleteCreditType(CreditType *ptrCreditType){
    if (ptrCreditType != nullptr) {
        int count = viewCreditType(ptrCreditType);
        printf("Выберите элемент для удаления или -1 для выхода.\n");
        fflush(stdin);
        int choice = askForChoice(count);
        if (choice != -1) {
            ptrCreditType = firstCreditType(ptrCreditType); // указатель возвращаем в первоначальное состояние
            for(int i = 0 ; i < choice-1 ; i ++){
                ptrCreditType = ptrCreditType->next;        // катаем цикл до нужного элемента
            }
            CreditType * ptrPrevCreditType = ptrCreditType->prev;
            CreditType * ptrNextCreditType = ptrCreditType->next;
            if (ptrNextCreditType != NULL)
                ptrNextCreditType->prev = ptrPrevCreditType;
            if (ptrPrevCreditType != NULL)
                ptrPrevCreditType->next = ptrNextCreditType;
            delete(ptrCreditType);

            if (ptrNextCreditType != NULL)
                return ptrNextCreditType;
            if (ptrPrevCreditType != NULL)
                return ptrPrevCreditType;
            return NULL;
        }
    }
    printf("Нет данных для удаления\n");
    fflush(stdin);
    return ptrCreditType;
}

///////////////////////// ПРОСМОТР ДАННЫХ В ТАБЛИЧНОЙ ФОРМЕ  ///////////////////////////////////////////////////////////
int viewCreditType(CreditType *ptrCreditType){
    int count = 0;
    headCreditType();
    ptrCreditType = firstCreditType(ptrCreditType);
    while (ptrCreditType != NULL) {                // подсказка для людей
        printf("|%-5d", (count + 1));
        printf("|%-16d|%-20s|%-11d|%-7d|\n", ptrCreditType->code_type, ptrCreditType->credit_name,
               ptrCreditType->rate, ptrCreditType->loan_period);
        printf("-----------------------------------------------------------------\n");
        ptrCreditType = ptrCreditType->next;
        count++;
    }
    return count;
}

///////////////////////// Редактирование записи ////////////////////////////////////////////////////////////////////////
CreditType* editCreditType(CreditType *ptrCreditType){
    ptrCreditType = firstCreditType(ptrCreditType); // указатель возвращаем в первоначальное состояние
    if(ptrCreditType == nullptr){
        printf("Нет элементов для редактирования\n");
    }
    else{
        int count = viewCreditType(ptrCreditType);
        printf("Выберите запись для ретактирования или -1 для выхода?\n");
        fflush(stdin);
        int choice = askForChoice(count);

        if (choice != -1) {
            ptrCreditType = firstCreditType(ptrCreditType); // указатель возвращаем в первоначальное состояние
            for(int i = 0 ; i < choice-1 ; i++){
                ptrCreditType = ptrCreditType->next;        // катаем цикл до нужного элемента
            }
            printf("Введите код кредита:\n");
            fflush(stdin);
            ptrCreditType->code_type = getNumberFromKeyboard();
            printf("Введите имя кредита:\n");
            fflush(stdin);
            scanf("%s", ptrCreditType->credit_name);
            printf("Введите ставку кредита:\n");
            fflush(stdin);
            ptrCreditType->rate = getNumberFromKeyboard();
            printf("Введите срок выдачи(в месяцах):\n");
            fflush(stdin);
            ptrCreditType->loan_period = getNumberFromKeyboard();
        }

    }
    return ptrCreditType;
}

CreditType* searchCreditType(CreditType *ptrCreditType){

}


