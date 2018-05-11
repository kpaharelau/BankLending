#include <cstring>
#include "Client.h"
#include "Header.h"

Client* firstClient(Client* ptrClient);

///////////////////////// ВЫВОД ИЗ ФАЙЛА ////////////////////////////////
Client *readClient() {
    Client *ptrClient = nullptr;
    if (isFileExists("Client.txt")) {
        FILE *ptrClientFile = fopen("Client.txt", "r");

        Client *ptrPrevClient = nullptr;
        while (true) {
            int tel_number;             // логин
            char user_name[18];         // имя
            char user_surname[26];      // фамилия   // кредитополучатель
            char address[28];           // адрес
            char guarantor_name[18];    // имя поручитель
            char guarantor_surname[26]; // фамилия поручителя
            int count = fscanf(ptrClientFile, "%d %s %s %s %s %s ",
                               &tel_number,
                               user_surname,
                               user_name,
                               address,
                               guarantor_surname,
                               guarantor_name);
            if (count != 6) {
                break;                    // если закончились
            }
            ptrClient = new Client;
            ptrClient->tel_number = tel_number;
            strcpy(ptrClient->name_user.surname, user_surname);     //выдает ошибку, т.к что-то не так со strcpy
            strcpy(ptrClient->name_user.name, user_name);
            strcpy(ptrClient->address, address);
            strcpy(ptrClient->guarantor.surname, guarantor_surname);
            strcpy(ptrClient->guarantor.name, guarantor_name);

            if (ptrPrevClient != nullptr) {
                ptrPrevClient->next = ptrClient;
                ptrClient->prev = ptrPrevClient;
            }
            ptrPrevClient = ptrClient;
        }
        fclose(ptrClientFile);
    }
    return ptrClient;
}

///////////////////////// ВВОД В ФАЙЛ ////////////////////////////////
void recordClient(Client *ptrClient) {
    FILE *ptrClientFiles = fopen("Client.txt", "w+");
    ptrClient = firstClient(ptrClient);
    while (ptrClient != NULL) {
        fprintf(ptrClientFiles, "%d %s %s %s %s %s\n",
                ptrClient->tel_number,
                ptrClient->name_user.surname,
                ptrClient->name_user.name,
                ptrClient->address,
                ptrClient->guarantor.surname,
                ptrClient->guarantor.name);
        ptrClient = ptrClient->next;
    }
    fclose(ptrClientFiles);
}

///////////////////////// ПЕРВЫЙ ЭЛЕМЕНТ ////////////////////////////////
Client *firstClient(Client *ptrClient) {
    while (ptrClient != NULL && ptrClient->prev != NULL) {
        ptrClient = ptrClient->prev;
    }
    return ptrClient;
}

///////////////////////// ПОСЛЕДНИЙ ЭЛЕМЕНТ ////////////////////////////////
Client *lastClient(Client *ptrClient) {
    while (ptrClient != NULL && ptrClient->next != NULL) {
        ptrClient = ptrClient->next;
    }
    return ptrClient;
}

///////////////////////// ВВОД С КЛАВИАТУРЫ ////////////////////////////////
Client *inputClient(Client *ptrClient) {
    if (ptrClient != NULL)
        ptrClient = lastClient(ptrClient);

    int num;
    printf("Сколько вы хотите ввести клиентов: ");
    scanf("%d", &num);
    fflush(stdin);
    for (int i = 0; i < num; i++) {
        Client *ptrNewClient = new Client;
        printf("%d. ", (i + 1));
        printf("Введите телефонный номер: ");
        fflush(stdin);
        while(true){
            ptrNewClient->tel_number = getNumberFromKeyboard();
            if((ptrNewClient->tel_number >= 375000000000) && (ptrNewClient->tel_number <= 375999999999)){
                break;
            }
            printf("Проверьте номер!\n");
        }
        printf("Введите фамилию клиента: ");
        fflush(stdin);
        scanf("%s", ptrNewClient->name_user.surname);
        printf("Введите имя клиента: ");
        fflush(stdin);
        scanf("%s", ptrNewClient->name_user.name);
        printf("Введите адресс клиента(без пробелов):  ");
        fflush(stdin);
        scanf("%s", ptrNewClient->address);
        printf("Введите фамилию поручителя: ");
        fflush(stdin);
        scanf("%s", ptrNewClient->guarantor.surname);
        printf("Введите имя поручителя: ");
        fflush(stdin);
        scanf("%s", ptrNewClient->guarantor.name);

        ptrNewClient->prev = ptrClient;
        if (ptrClient != NULL)
            ptrClient->next = ptrNewClient;
        ptrClient = ptrNewClient;
    }

    return ptrClient;
}

///////////////////////// УДАЛЕНИЕ ОДНОГО/ НЕСКОЛЬКИХ ЭЛЕМЕНТОВ ////////////////////////////////
Client* deleteClient(Client *ptrClient){

    if (ptrClient!= nullptr) {
        int count = viewClient(ptrClient);
        printf("Выберите элемент для удаления или -1 для выхода.\n");
        fflush(stdin);
        int choice = askForChoice(count);
        if (choice != -1) {
            ptrClient = firstClient(ptrClient); // указатель возвращаем в первоначальное состояние
            for(int i = 0 ; i < choice-1 ; i ++){
                ptrClient = ptrClient->next;        // катаем цикл до нужного элемента
            }
            Client * ptrPrevClient = ptrClient->prev;
            Client * ptrNextClient = ptrClient->next;
            if (ptrNextClient != NULL)
                ptrNextClient->prev = ptrPrevClient;
            if (ptrPrevClient != NULL)
                ptrPrevClient->next = ptrNextClient;
            delete(ptrClient);

            if (ptrNextClient != NULL)
                return ptrNextClient;
            if (ptrPrevClient != NULL)
                return ptrPrevClient;
            return NULL;
        }
    }
    printf("Нет данных для удаления\n");
    return ptrClient;
}

///////////////////////// ПРОСМОТР ДАННЫХ В ТАБЛИЧНОЙ ФОРМЕ  ////////////////////////////////
int viewClient(Client *ptrClient){
    int count = 0;
    headClient();
    ptrClient = firstClient(ptrClient);
    while (ptrClient != NULL) {                // подсказка для людей
        printf("|%-5d", (count + 1));
        printf("|%-16d|%-26s|%-18s|%-28d|%-26s|%-18s| \n", ptrClient->tel_number, ptrClient->name_user.surname,
               ptrClient->name_user.name, ptrClient->address, ptrClient->guarantor.surname, ptrClient->guarantor.name);
        printf("--------------------------------------------------------------------------------------------------------------------------------------------------\n");        ptrClient = ptrClient->next;
        count++;
    }
    return count;
}

void headClient() // заголовок
{
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------x--\n");
    printf("|  №  | Номер телефона |      Фамилия клиента     |   Имя  клиента   |          Адрес             |     Фамилия поручителя   |  Имя  поручителя |\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fflush(stdin);
}

Client* editClient(Client *ptrClient){

}