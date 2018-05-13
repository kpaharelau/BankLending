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

int edituser()
{
    int k = 0;

    while (1)
    {
        system("cls");
        printf("1.Показать всех пользователей\n");
        printf("2.Удалить пользователя\n");
        printf("3.Добавить пользователя\n");
        printf("0.Выход\n");
        k = checkint();
        switch (k)
        {
            case 1:
                system("cls");
                if (openuser() == 0)
                {
                    printf("Чтение успешно!\n");
                }
                else
                {
                    printf("Файл пуст!\n");
                }
                _getch();
                break;
            case 2:
                system("cls");
                openuser();
                if (deleteuser() == 0)
                {
                    printf("Удаление успешно!\n");
                }
                else
                {
                    printf("Ошибка!\n");
                }
                _getch();
                break;
            case 3:
                system("cls");
                if (adduser() == 0)
                {
                    printf("Добавление успешно!\n");
                }
                else
                {
                    printf("Ошибка!\n");
                }
                _getch();
                break;
            case 0: return 0;
            default: printf("Ошибка!\n"); _getch();
        }
    }
}

int openuser()
{
    FILE *fp;
    entrance temp, *mas;
    char check;
    int k = 0;

    fopen_s(&fp, "loginuser.txt", "r");
    if (fscanf_s(fp, "%c", &check, 1) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);
        while (!feof(fp))
        {
            fscanf_s(fp, "%s", temp.login, _countof(temp.login));
            fscanf_s(fp, "%s\n", temp.pass, _countof(temp.pass));
            ++k;
        }
        rewind(fp);
        mas = new entrance[k];
        for (int i = 0; i < k; i++)
        {
            fscanf_s(fp, "%s", mas[i].login, _countof(mas[i].login));
            fscanf_s(fp, "%s\n", mas[i].pass, _countof(mas[i].pass));
        }
        rewind(fp);
        fclose(fp);
        printf("Пользователи:\n");
        printf("--------------------------------\n");
        printf("|   № |     Логин пользователя |\n");
        printf("--------------------------------\n");
        for (int i = 0; i < k; i++)
        {
            printf("|%5d|%24s|\n", i + 1, mas[i].login);
            printf("--------------------------------\n");
        }
        return 0;
    }
    else
    {
        fclose(fp);
        return 1;
    }
}

int deleteuser()
{
    FILE *fp;
    entrance *mas, temp;
    char check;
    int k = 0, zapis = 0;

    fopen_s(&fp, "loginuser.txt", "r");
    if (fscanf_s(fp, "%c", &check, 1) != EOF)
    {
        fseek(fp, -1, SEEK_CUR);
        while (!feof(fp))
        {
            fscanf_s(fp, "%s", temp.login, _countof(temp.login));
            fscanf_s(fp, "%s\n", temp.pass, _countof(temp.pass));
            ++k;
        }
        rewind(fp);
        mas = new entrance[k];
        for (int i = 0; i < k; i++)
        {
            fscanf_s(fp, "%s", mas[i].login, _countof(mas[i].login));
            fscanf_s(fp, "%s\n", mas[i].pass, _countof(mas[i].pass));
        }
        fclose(fp);
        zapis = checkint();
        if (zapis < 1 || zapis > k)
        {
            return 1;
        }
        fopen_s(&fp, "loginuser.txt", "w");
        for (int i = 0; i < k; i++)
        {
            if (i + 1 == zapis) continue;
            fprintf(fp, "%s %s\n", mas[i].login, mas[i].pass);
        }
        rewind(fp);
        delete[] mas;
        fclose(fp);
        return 0;
    }
    else
    {
        fclose(fp);
        return 1;
    }
}

int adduser()
{
    FILE *fp;
    entrance temp;
    int k = 0, i = 0;

    printf("Введите логин:\n");
    gets_s(temp.login);
    printf_s("Введите пароль:\n");
    while (1)
    {
        temp.pass[i] = _getch();
        if (temp.pass[i] == '\r') break;
        if (temp.pass[i] == '\b')
        {
            printf("%s", "\b \b");
            --i;
        }
        else
        {
            printf("%c", '*');
            ++i;
        }
    }
    temp.pass[i] = '\0';
    printf("\n");
    if (i - 1 < 1)
    {
        return 1;
    }
    strcpy_s(temp.pass, crypt(temp.pass));
    fopen_s(&fp, "loginuser.txt", "a");
    fprintf(fp, "%s %s\n", temp.login, temp.pass);
    fclose(fp);
    return 0;
}

