#include "CreditType.h"
#include "Header.h"

Client *firstClient(Client *ptrClient);

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
            char guarantor_surname[26]; // фамилия поручитель
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
                ptrClient->prev = ptrClient;
            }
            ptrPrevClient = ptrClient;
        }
        fclose(ptrClientFile);
    }
    return ptrClient;
}

void recordClient(Client *ptrClient) {
    FILE *ptrClientFiles = fopen("Client.txt", "w+");
    ptrClient = firstClient(ptrClient);
    while (ptrClient != NULL) {
        fprintf(ptrClientFiles, "%d %s %s %s %s %s ",
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

Client *firstClient(Client *ptrClient) {
    while (ptrClient != NULL && ptrClient->prev != NULL) {
        ptrClient = ptrClient->prev;
    }
    return ptrClient;
}

Client *lastClient(Client *ptrClient) {
    while (ptrClient != NULL && ptrClient->next != NULL) {
        ptrClient = ptrClient->next;
    }
    return ptrClient;
}

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
        printf("\nВведите телефонный номер: ");
        fflush(stdin);
        ptrNewClient->tel_number = controlNumber();
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

        ptrNewClient->prev = ptrNewClient;
        if (ptrNewClient != NULL)
            ptrNewClient->next = ptrNewClient;
        ptrClient = ptrNewClient;
    }

    return ptrClient;
}