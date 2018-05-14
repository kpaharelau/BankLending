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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ РАБОТЫ С ЮЗЕРАМИ // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void addUsers(UserInformation *ptrUserInformation){
    if (ptrUserInformation != NULL)                                     //Проверяем на пустоту, для возможной записи в конец файла
        ptrUserInformation = lastUserInformation(ptrUserInformation);

    int num;
    printf("Сколько вы хотите ввести пользователей:\n");
    fflush(stdin);
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        UserInformation *ptrNewUserInformation = new UserInformation;
        printf("%d. ", (i + 1));
        printf("Введите логин:\n");
        fflush(stdin);
        scanf("%s", ptrNewUserInformation->login);
        printf("Введите пароль:\n");
        fflush(stdin);
        scanf("%s", ptrNewUserInformation->password);
        strcpy(ptrNewUserInformation->password, createPassword(ptrNewUserInformation->password)); // тут тоже подправить , но не переписывать

        ptrNewUserInformation->prev = ptrUserInformation;
        if (ptrUserInformation != NULL)
            ptrUserInformation->next = ptrNewUserInformation;
        ptrUserInformation = ptrNewUserInformation;
    }


    recordUserInformation(ptrUserInformation);
}

void deleteUsers(UserInformation *ptrUserInformation){
    if (ptrUserInformation != nullptr) {
        int count = viewAllUsers(ptrUserInformation);;
        printf("Выберите элемент для удаления или -1 для выхода.\n");
        fflush(stdin);
        int choice = askForChoice(count);
        if (choice != -1) {
            ptrUserInformation = firstUserInformation(ptrUserInformation); // указатель возвращаем в первоначальное состояние
            for(int i = 0 ; i < choice-1 ; i ++){
                ptrUserInformation = ptrUserInformation->next;        // катаем цикл до нужного элемента
            }
            UserInformation * ptrPrevUserInformation = ptrUserInformation->prev;
            UserInformation * ptrNextUserInformation = ptrUserInformation->next;
            if (ptrNextUserInformation != NULL)
                ptrNextUserInformation->prev = ptrPrevUserInformation;
            if (ptrPrevUserInformation != NULL)
                ptrPrevUserInformation->next = ptrNextUserInformation;
            delete(ptrUserInformation);

            if (ptrNextUserInformation != NULL)
                recordUserInformation(ptrNextUserInformation);
            if (ptrPrevUserInformation != NULL)
                recordUserInformation(ptrPrevUserInformation);
        }
    }
    printf("Нет данных для удаления\n");
    fflush(stdin);
}


int viewAllUsers(UserInformation *ptrUserInformation){
    int count = 0;
    printf("---------------------------------------------------------------------\n");
    printf("|   № |     Логин пользователя       |             Пароль           |\n");
    printf("---------------------------------------------------------------------\n");

    ptrUserInformation = firstUserInformation(ptrUserInformation);
    while (ptrUserInformation != NULL) {
        char password[30];
        strcpy(password, ptrUserInformation->password);
        decrypt(password);  // сейчас три ночи и я хзхз как это зрабить
        printf("|%-5d", ++count);
        printf("|%-30s|%-30s|\n", ptrUserInformation->login , password);
        printf("---------------------------------------------------------------------\n");
        ptrUserInformation = ptrUserInformation->next;
    }
   
    return count;
}