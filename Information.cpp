#include "Header.h"
#include "Information.h"

Information* readInformation(){
    Information *ptrInformation = nullptr;
    if(isFileExists("Information.txt")) {
        FILE *ptrInformationFile = fopen("Information.txt", "r");

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
    FILE *ptrInformationFiles = fopen("Information.txt", "w+");
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


int loginAdmin(Information *information) {
//    int i = 0;
//    char password[255];
//    char login[255];
//    printf("Введите логин:\n");
//    gets(login);
//    while (1) {
//        password[i] = getchar();
//        if (password[i] == '\r') break;
//        if (password[i] == '\b') {
//            printf("%s", "\b \b");
//            --i;
//        }
//        else {
//            printf("%c", '*');
//            ++i;
//        }
//    }
//    password[i] = '\0';
//    printf("\n");
//    if (i - 1 < 1)
//    {
//        return 1;
//    }
//    strcpy(password, crypt(password, reinterpret_cast<const char *>('q11')));
//    //err = fopen_s(&fp, "loginAdmin.txt", "r");
//    ptrInformation = firstInformation(ptrInformation);
//    while (true) {
//
//        if (strcmp(login, temp.login) == 0 && strcmp(pass, temp.pass) == 0)
//        {
//            fclose(fp);
//            return 0;
//        }
//    }
//    fclose(fp);
//    return 1;
//}
    return 0;
}

