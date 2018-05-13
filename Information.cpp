#include "Header.h"
#include "Information.h"

Information* readInformation(){
    Information *ptrInformation = nullptr;
    if(isFileExists("../Information.txt")) {
        FILE *ptrInformationFile = fopen("../Information.txt", "r");

        Information *ptrPrevInformation = nullptr;
        while (true) {
            char password[255];
            char login[255];
            int count = fscanf(ptrInformationFile, "%s %s ", password, login);
            if (count != 2) {
                break;

            }
            ptrInformation = new Information;
            strcpy(ptrInformation->login, login);
            strcpy(ptrInformation->password, password);

            if (ptrPrevInformation != nullptr) {
                ptrPrevInformation->next = ptrInformation;
                ptrInformation->prev = ptrPrevInformation;
            }
            ptrPrevInformation = ptrInformation;
        }
        fclose(ptrInformationFile);
    }
    return ptrInformation;
}

void recordInformation(Information *ptrInformation) {
    FILE *ptrInformationFiles = fopen("../Information.txt", "w+");
    ptrInformation = firstInformation(ptrInformation);
    while (ptrInformation != NULL) {
        fprintf(ptrInformationFiles, "%s %s\n", ptrInformation->login, ptrInformation->password);
        ptrInformation = ptrInformation->next;
    }
    fclose(ptrInformationFiles);
}

///////////////////////// ПЕРВЫЙ ЭЛЕМЕНТ ///////////////////////////////////////////////////////////////////////////////
Information *firstInformation(Information *ptrInformation) {
    while (ptrInformation != NULL && ptrInformation->prev != NULL) {
        ptrInformation = ptrInformation->prev;
    }
    return ptrInformation;
}

///////////////////////// ПОСЛЕДНИЙ ЭЛЕМЕНТ ////////////////////////////////////////////////////////////////////////////
Information* lastInformation(Information* ptrInformation){
    while (ptrInformation != NULL && ptrInformation->next != NULL) {
        ptrInformation = ptrInformation->next;
    }
    return ptrInformation;
}



char * readUserPasswordFromFile(const char* user){
    return "jhfjhdgfhgdhfg";
}

char * readAdminPasswordFromFile(){
    return readUserPasswordFromFile("user");
}

int writeAdminPasswordToFile(char* password){
    return 1;
}

int writeUserPasswordToFile(const char* user){
    return 1;
}

int loginAdmin(Information *information) {

    //вычитывает пароль
    char* password = readAdminPasswordFromFile();
    if (strlen(password) == 0){
        password = getpass("Пароль администратора не задан. Введите его:");
        password = createPassword(password);
        //записываем пароль
        return writeAdminPasswordToFile(password);
    }

    int res = checkPassword(getpass("Введите пароль:"), password);


    return res;
}

