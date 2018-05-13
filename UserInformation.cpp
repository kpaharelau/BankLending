#include "Utils.h"
#include "UserInformation.h"

UserInformation *readUserInformation() {
    UserInformation *ptrInformation = nullptr;
    if (isFileExists("../Users.txt")) {
        FILE *ptrInformationFile = fopen("../Users.txt", "r");

        UserInformation *ptrPrevInformation = nullptr;
        while (true) {
            char password[255];
            char login[255];
            int count = fscanf(ptrInformationFile, "%s %s ",login,  password);
            if (count != 2) {
                break;

            }
            ptrInformation = new UserInformation;
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

void recordUserInformation(UserInformation *ptrUserInformation) {
    FILE *ptrInformationFiles = fopen("../Users.txt", "w+");
    ptrUserInformation = firstUserInformation(ptrUserInformation);
    while (ptrUserInformation != NULL) {
        fprintf(ptrInformationFiles, "%s %s\n", ptrUserInformation->login, ptrUserInformation->password);
        ptrUserInformation = ptrUserInformation->next;
    }
    fclose(ptrInformationFiles);
}

UserInformation *findUserInformationByLogin(const char *login) {
    UserInformation *ptrUserInformation = firstUserInformation(readUserInformation());
    while (ptrUserInformation != NULL) {
        if (strcmp(ptrUserInformation->login, login) == 0)
            return ptrUserInformation;
        ptrUserInformation = ptrUserInformation->next;
    }
    return NULL;
}

///////////////////////// ПЕРВЫЙ ЭЛЕМЕНТ ///////////////////////////////////////////////////////////////////////////////
UserInformation *firstUserInformation(UserInformation *ptrUserInformation) {
    while (ptrUserInformation != NULL && ptrUserInformation->prev != NULL) {
        ptrUserInformation = ptrUserInformation->prev;
    }
    return ptrUserInformation;
}

///////////////////////// ПОСЛЕДНИЙ ЭЛЕМЕНТ ////////////////////////////////////////////////////////////////////////////
UserInformation *lastUserInformation(UserInformation *ptrUserInformation) {
    while (ptrUserInformation != NULL && ptrUserInformation->next != NULL) {
        ptrUserInformation = ptrUserInformation->next;
    }
    return ptrUserInformation;
}


char *readUserPasswordFromFile(const char *login) {
    UserInformation *ptrInformation = findUserInformationByLogin(login);
    return ptrInformation ? ptrInformation->password : NULL;
}

char *readAdminPasswordFromFile() {
    return readUserPasswordFromFile("admin");
}

void writeUserPasswordToFile(const char *login, const char *password) {
    UserInformation *ptrUserInformation = firstUserInformation(readUserInformation());
    while (ptrUserInformation != NULL) {
        if (strcmp(ptrUserInformation->login, login) == 0) {
            strcpy(ptrUserInformation->password, password);
            recordUserInformation(ptrUserInformation);
            return;
        }
        ptrUserInformation = ptrUserInformation->next;
    }
    UserInformation *ptrNewUserInformation = new UserInformation();

    strcpy(ptrNewUserInformation->login, login);
    strcpy(ptrNewUserInformation->password, password);

    ptrNewUserInformation->prev = ptrUserInformation;
    if (ptrUserInformation != NULL) {
        ptrUserInformation->next = ptrNewUserInformation;
    }

    recordUserInformation(ptrNewUserInformation);
}

void writeAdminPasswordToFile(char *password) {
    writeUserPasswordToFile("admin", password);
}


int loginAdmin(UserInformation *information) {

    //вычитывает пароль
    char *password = readAdminPasswordFromFile();
    if (password == NULL || strlen(password) == 0) {
        password = getpass("Пароль администратора не задан. Введите его:");
        password = createPassword(password);
        //записываем пароль
        writeAdminPasswordToFile(password);
        return 1;
    }

    int res = checkPassword(getpass("Введите пароль:"), password);


    return res;
}

