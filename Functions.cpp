#include "Header.h"
#include "CreditType.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ВВОДА И ВЫВОДА // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int readOrCreateFile(CreditType *start_creditType, Credit *start_credit, Client *start_clients) {        // Запись в оперативку
    FILE *fp_creditType;
    FILE *fp_clients;
    FILE *fp_credit;
    CreditType *temp_creditType = new CreditType;
    Credit *temp_credit = new Credit;
    Client *temp_clients = new Client;
    int size, i;
/////////////////////////////////////////////////////////////////////////1
    fp_creditType = fopen("CreditType.txt", "r");
    if (!fp_creditType) {
        fp_creditType = fopen("CreditType.txt", "w");
        fclose(fp_creditType);
        return -1;
    } else {
        CreditType *end = NULL;
        size = static_cast<int>(getFileSize(fp_creditType));

        for (i = size; i > 0; i--) {
            if (start_creditType == NULL) {
                start_creditType = temp_creditType;
            }
            fscanf(fp_creditType, "%d", &temp_creditType->code_type);
            fscanf(fp_creditType, "%s", temp_creditType->credit_name);
            fscanf(fp_creditType, "%d", &temp_creditType->rate);
            fscanf(fp_creditType, "%d", &temp_creditType->loan_period);
            temp_creditType->next = NULL;
            if (end == NULL) {
                end = temp_creditType;
            } else {
                end->next = temp_creditType;
                end = temp_creditType; // пояснить
            }
        }
        fclose(fp_creditType);
        delete (temp_creditType);
    }
/////////////////////////////////////////////////////////////////////////2
    fp_credit = fopen("Credit.txt", "r");
    if (!fp_credit) {
        fp_credit = fopen("Credit.txt", "w");
        fclose(fp_credit);
        return 0;
    } else {
        Credit *end = NULL;
        size = static_cast<int>(getFileSize_Credit(fp_credit));

        for (i = size; i > 0; i--) {
            if (start_credit == NULL) {
                start_credit = temp_credit;
            }
            fscanf(fp_credit, "%d", &temp_credit->code_type);
            fscanf(fp_credit, "%d", &temp_credit->tel_number);
            fscanf(fp_credit, "%d", &temp_credit->amount);
            fscanf(fp_credit, "%d", &temp_credit->date.day);
            fscanf(fp_credit, "%d", &temp_credit->date.month);
            fscanf(fp_credit, "%d", &temp_credit->date.year);
            temp_clients->next = NULL;
            if (end == NULL) {
                end = temp_credit;
            } else {
                end->next = temp_credit;
                end = temp_credit; // пояснить
            }
        }
        fclose(fp_credit);
        delete (temp_credit);
    }
//////////////////////////////////////////////////////////////////////////3
    fp_clients = fopen("Client.txt", "r");
    if (!fp_clients) {
        fp_clients = fopen("Client.txt", "w");
        fclose(fp_clients);
        return 0;
    } else {
        Client *end = NULL;
        size = getFileSizeClients(fp_clients);

        for (i = size; i > 0; i--) {
            if (start_clients == NULL) {
                start_clients = temp_clients;
            }
            fscanf(fp_clients, "%d", &temp_clients->tel_number);
            fscanf(fp_clients, "%s", temp_clients->name_user.surname);
            fscanf(fp_clients, "%s", temp_clients->name_user.name);
            fscanf(fp_clients, "%s", temp_clients->address);
            fscanf(fp_clients, "%s", temp_clients->guarantor.surname);
            fscanf(fp_clients, "%s", temp_clients->guarantor.name);
            temp_clients->next = NULL;
            if (end == NULL) {
                end = temp_clients;
            } else {
                end->next = temp_clients;
                end = temp_clients; // пояснить
            }
        }
        fclose(fp_clients);
        delete (temp_clients);
    }
    return 0;
}

int recordFile(CreditType *start_creditType, Credit *start_credit, Client *start_clients) {        // Запись в файл
    FILE *fp_creditType;
    FILE *fp_credit;
    FILE *fp_clients;
////////////////////////////////////////////////////////////////////////////////////////////////////////
    fp_creditType = fopen("CreditType.txt", "w+");
    if (start_creditType != NULL) {
        CreditType *temp_creditType = start_creditType;
        while (start_creditType != NULL) {
            fprintf(fp_creditType, "%d %s %d %d", temp_creditType->code_type, temp_creditType->credit_name,
                    temp_creditType->rate, temp_creditType->loan_period);
            temp_creditType = temp_creditType->next;
        }
    }
    fclose(fp_creditType);
////////////////////////////////////////////////////////////////////////////////////////////////////////
    fp_credit = fopen("Credit.txt", "w+");
    if (start_credit != NULL) {
        Credit *temp_credit = start_credit;
        while (start_credit != NULL) {
            fprintf(fp_credit, "%d %d %d  %d.%d.%d ", temp_credit->code_type, temp_credit->tel_number,
                    temp_credit->amount, temp_credit->date.day, temp_credit->date.month, temp_credit->date.year);
            temp_credit = temp_credit->next;
        }
    }
    fclose(fp_credit);
////////////////////////////////////////////////////////////////////////////////////////////////////////
    fp_clients = fopen("Client.txt", "w+");
    if (start_clients != NULL) {
        Client *temp_clients = start_clients;
        while (start_clients != NULL) {
            fprintf(fp_clients, "%d %s %s %s %s %s ", temp_clients->tel_number, temp_clients->name_user.surname,
                    temp_clients->name_user.name, temp_clients->address, temp_clients->guarantor.surname,
                    temp_clients->guarantor.name);
            temp_clients = temp_clients->next;
        }
    }
    fclose(fp_clients);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ АДМИНИСТРАТОРА // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void add(CreditType *ptrCreditType, Client *start_clients, Credit *start_credit, BankData *ptrBankData) {
    while (true) {
        printf("======= Выберите действие =======\n");
        printf("1. Добавить вид кредита\n");
        printf("2. Добавить клиента\n");
        printf("3. Добавить кредит\n");
        printf("0. Возврат. \n");
        int i;
        i = controlNumber();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:
                ptrBankData->creditType = inputCreditType(ptrCreditType);
                break;
            case 2:
                addClients(&start_clients);
                break;
            case 3:
                addCredit(&start_credit, &ptrCreditType, &start_clients);
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

int addCreditType(CreditType **start_creditType) {
    if (*start_creditType != NULL) {// если не пустой
        CreditType *p_creditType = new CreditType;
        inputCreditType(p_creditType);

        CreditType *prev_creditType = *start_creditType, *post_creditType = *start_creditType;
        while (post_creditType != NULL) {
            if (post_creditType->code_type > p_creditType->code_type) {
                //поместим новый узел между узлами, задаваемыми prev и post
                p_creditType->next = post_creditType;
                if (post_creditType == *start_creditType)
                    *start_creditType = p_creditType;
                else
                    prev_creditType->next = p_creditType;
                return 0;
            }
            prev_creditType = post_creditType;
            post_creditType = post_creditType->next;
        }
        //поместим новый узел в конец списка
        p_creditType->next = NULL;
        prev_creditType->next = p_creditType;
    } else {                        // если он пустой
        CreditType *p_creditType = new CreditType;
        inputCreditType(p_creditType);
        p_creditType->next = NULL;
        *start_creditType = p_creditType;
    }
    return 0;
}

int addClients(Client **start_clients) {
    if (*start_clients != NULL) {// если не пустой
        Client *p_clients = new Client;
        inputClients(p_clients);

        Client *prev_clients = *start_clients, *post_clients = *start_clients;// спросить у яны
        while (post_clients != NULL) {
            if (post_clients->tel_number > p_clients->tel_number) {
                //поместим новый узел между узлами, задаваемыми prev и post
                p_clients->next = post_clients;
                if (post_clients == *start_clients)
                    *start_clients = p_clients;
                else
                    prev_clients->next = p_clients;
                return 0;
            }
            prev_clients = post_clients;
            post_clients = post_clients->next;
        }
        //поместим новый узел в конец списка
        p_clients->next = NULL;
        prev_clients->next = p_clients;
    } else {                        // если он пустой
        Client *p_clients = new Client;
        inputClients(p_clients);
        p_clients->next = NULL;
        *start_clients = p_clients;
    }
    return 0;
}

int addCredit(Credit **start_credit, CreditType **start_creditType, Client **start_clients) {
    if (*start_credit != NULL) {// если не пустой
        Credit *p_credit = new Credit;
        inputCredit(p_credit, *start_creditType, *start_clients);

        Credit *prev_credit = *start_credit, *post_credit = *start_credit;// спросить у яны
        while (post_credit != NULL) {
            if (post_credit->code_type > p_credit->code_type) {
                //поместим новый узел между узлами, задаваемыми prev и post
                p_credit->next = post_credit;
                if (post_credit == *start_credit)
                    *start_credit = p_credit;
                else
                    prev_credit->next = p_credit;
                return 0;
            }
            prev_credit = post_credit;
            post_credit = post_credit->next;
        }
        //поместим новый узел в конец списка
        p_credit->next = NULL;
        prev_credit->next = p_credit;
    } else {                        // если он пустой
        Credit *p_credit = new Credit;
        inputCredit(p_credit, *start_creditType, *start_clients);
        p_credit->next = NULL;
        *start_credit = p_credit;
    }
    return 0;
}

void inputClients(Client *p_clients) {
    int num;
    printf("Сколько вы хотите ввести клиентов: ");
    scanf("%d", &num);
    fflush(stdin);
    for (int i = 0; i < num; i++) {
        printf("%d. ", (i + 1));
        printf("\nВведите телефонный номер: ");
        fflush(stdin);
        p_clients->tel_number = controlNumber();
        printf("Введите фамилию клиента: ");
        fflush(stdin);
        scanf("%s", p_clients->name_user.surname);
        printf("Введите имя клиента: ");
        fflush(stdin);
        scanf("%s", p_clients->name_user.name);
        printf("Введите адресс клиента(без пробелов):  ");
        fflush(stdin);
        scanf("%s", p_clients->address);
        printf("Введите фамилию поручителя: ");
        fflush(stdin);
        scanf("%s", p_clients->guarantor.surname);
        printf("Введите имя поручителя: ");
        fflush(stdin);
        scanf("%s", p_clients->guarantor.name);

    }
}

int inputCredit(Credit *p_credit, CreditType *start_creditType, Client *start_clients) {
    if (start_clients == NULL || start_creditType == NULL) {
        printf("Нехватка данных для создания выданного кредита\n");
        return 1;
    }
    int num;
    printf("Сколько вы хотите ввести кредитов: ");
    scanf("%d", &num);
    fflush(stdin);
    for (int i = 0; i < num; i++) {
        printf("%d. ", (i + 1));
        printf("\nВведите код кредита: "); // сделать проверку и вывести
        p_credit->code_type = controlNumber();
        fflush(stdin);
        printf("Введите телефонный номер: "); //сделать проверку на существование такого номера и вывести все номера перед вводом
        p_credit->tel_number = controlNumber();
        printf("Введите сумму кредита: ");
        fflush(stdin);
        p_credit->amount = controlNumber();
        printf("Введите дату выдачи\n: ");
        printf("д: ");
        fflush(stdin);
        p_credit->date.day = controlNumber();
        printf("м: ");
        fflush(stdin);
        p_credit->date.month = controlNumber();  // сделать дополнительные проверки
        printf("г: ");
        fflush(stdin);
        p_credit->date.year = controlNumber();

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ УДАЛЕНИЯ  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void remove(CreditType *start_creditType, Client *start_clients, Credit *start_credit) {
    while (1) {
        printf("======= Выберите действие =======\n");
        printf("1. Удалить все\n");
        printf("2. Удалить элемент\n");
        printf("0. Вход. \n");
        printf("\nВаше действие: ");
        int i;
        i = controlNumber();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:
                removeAll(start_creditType, start_clients, start_credit);
                break;
            case 2:
                removePart(start_creditType, start_clients, start_credit);
                break;
            default:
                printf("Введите числа от 0 до 2:  ");
        }
    }
}

void removePart(CreditType *start_creditType, Client *start_clients,
                Credit *start_credit) { // находиться в разработке, т.к. фигня с указателями
    while (1) {
        printf("\n ======= Выберите действие =======\n");
        printf("1. Удалить вид кредита\n");
        printf("2. Удалить клиента\n");
        printf("3. Удалить кредит\n");
        printf("0. Вход. \n");
        printf("\nВаше действие: ");
        int i;
        i = controlNumber();
        if (i == 0) break;
        clearConsole();
        switch (i) {
            case 1:
                if (deleteCreditType(start_creditType) == 1) {
                    puts("Вид кредита не найден");
                } else {
                    puts("Вид кредита удален.");
                }
                break;
            case 2:
                if (deleteClients(start_clients) == 1) {
                    puts("Вид кредита не найден");
                } else {
                    puts("Вид кредита удален.");
                }
                break;
            case 3:
                deleteCredit(start_credit);
                break;
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
}

int removeAll(CreditType *start_creditType, Client *start_clients, Credit *start_credit) {

    while (true) {
        printf("\n======= Вы уверены? =======");
        printf("1. Да\n");
        printf("2. Нет\n");
        printf("\nВаше действие: ");
        int i = controlNumber();
        if (i == 0) break;
        clearConsole();
        CreditType *p_creditType = start_creditType;
        CreditType *p_temp = start_creditType;
        CreditType *p_tmp = start_creditType->next;
        Credit *p_credit = start_credit;
        Client *p_clients = start_clients;
        switch (i) {
            case 1:
                while (p_creditType != NULL) {
                    start_creditType = start_creditType->next;
                    delete p_temp;
                    p_temp = start_creditType;
                }
                while (p_clients != NULL) {

                }
                while (p_credit != NULL) {

                }

                /* int deleteNth(Node **head, int n) {
                   if (n == 0) {
                     return pop(head);
                   }
                   else {
                     Node *prev = getNth(*head, n - 1);
                     Node *elm = prev->next;
                     int val = elm->value;

                     prev->next = elm->next;
                     free(elm);
                     return val;
                   }
                 }*/

                break; // добавить удаление всего
            default:
                printf("Введите числа от 0 до 3:  ");
        }
    }
    return 0;
}

int deleteCreditType(CreditType *start_creditType) {
    int count = 0, key;
    CreditType *p_creditType = start_creditType;
    while (p_creditType != NULL) {
        count++;
        printf("%d. %d\t%s", count, p_creditType->code_type, p_creditType->credit_name);
        p_creditType = p_creditType->next;

    }
    printf("Введите /№ вида кредита, который будет удален: ");
    key = controlNumber();
    if (count < key) {
        return 1;
    } else {
        CreditType *p_creditType = start_creditType;
        for (int i = 0; i < count; i++) {
            p_creditType = p_creditType->next;
        }
        CreditType *pre = start_creditType;
        while (pre != NULL) {
            if (pre->next == p_creditType)
                break;            //нашли предшествующий узел и выходим из цикла
            pre = pre->next;
        }
        pre->next = p_creditType->next;
        fflush(stdin);
        delete p_creditType;
    }
    return 0;
}

int deleteClients(Client *start_clients) {
    int count = 0, key;
    Client *p_clients = start_clients;
    while (p_clients != NULL) {
        count++;
        printf("%d. %d\t%s\t%s", count, p_clients->tel_number, p_clients->name_user.surname, p_clients->name_user.name);
        p_clients = p_clients->next;
    }
    printf("Введите /№ вида кредита, который будет удален: ");
    key = controlNumber();
    if (count < key) {
        return 1;
    } else {
        Client *p_clients = start_clients;
        for (int i = 0; i < count; i++) {
            p_clients = p_clients->next;
        }
        Client *pre = start_clients;
        while (pre != NULL) {
            if (pre->next == p_clients)
                break;            //нашли предшествующий узел и выходим из цикла
            pre = pre->next;
        }
        pre->next = p_clients->next;
        delete p_clients;
        fflush(stdin);
    }
    return 0;
}

int deleteCredit(Credit *start_credit) {
    int count = 0, key;
    Credit *p_credit = start_credit;
    while (p_credit != NULL) {
        printf("%d. %d\t%d\t%d", count, p_credit->code_type, p_credit->tel_number, p_credit->amount);
        p_credit = p_credit->next;
        count++;
    }
    printf("Введите /№ вида кредита, который будет удален: ");
    key = controlNumber();
    if (count < key) {
        return 1;
    } else {
        Credit *p_credit = start_credit;
        for (int i = 0; i < count; i++) {
            p_credit = p_credit->next;
        }
        Credit *pre = start_credit;
        while (pre != NULL) {
            if (pre->next == p_credit)
                break;            //нашли предшествующий узел и выходим из цикла
            pre = pre->next;
        }
        pre->next = p_credit->next;
        delete p_credit;
        fflush(stdin);
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ПРОСМОТРА  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void head() // заголовок
{
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("*|  №  | Номер кредита | Телеф. номер |         Фамилия         |       Имя       |           Адресс          |   Сумма   | Проценты |  Дата  |    Фамилия поручителя    |  Имя поручителя |\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

int viewAll(CreditType *start_creditType, Client *start_clients, Credit *start_credit) {
    if (start_creditType == NULL || start_creditType == NULL || start_creditType == NULL) {
        return 1;
    } else {
        int i = 1;
        Credit *p_credit = start_credit;
        head();
        while (p_credit != NULL) {
            CreditType *p_creditType = start_creditType;
            Client *p_clients = start_clients;
            while (p_credit->code_type != p_creditType->code_type) {
                p_creditType = p_creditType->next;
            }
            while (p_credit->tel_number != p_clients->tel_number) {
                p_clients = p_clients->next;
            }
            printf("*|%-6d|", i);
            printf("%-16d|%-15d|%-26s|%-18s|%-28s|%-12d|%-11d|%-2d.%-2d.%-4d|%-26s|%-18s*\n", p_credit->code_type,
                   p_credit->tel_number, p_clients->name_user.name, p_clients->name_user.surname, p_clients->address,
                   p_credit->amount, p_creditType->rate, p_credit->date.day, p_credit->date.month, p_credit->date.year,
                   p_clients->guarantor.surname, p_clients->guarantor.name);
            printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            p_credit = p_credit->next;
        }
        return 0;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ФУНКЦИИ ПРОВЕРКИ  // АДМИНИСТРАТОР
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getTime(tm &newtime) {
//  time_t now = time(0);
//  localtime(&newtime, &now);
//  newtime.tm_mon = 1 + newtime.tm_mon;
//  newtime.tm_year = 1900 + newtime.tm_year;
}
// функция считывания времени с компьютера

int controlNumber() {
    int res, i;
    do {
        res = scanf("%d", &i);
        while (getchar() != '\n');
        if (res != 1) printf("Введите число!\n");
    } while (res != 1);
    return i;
}
// Контроль ввода именно чисел

long getFileSize(FILE *input) {
    long fileSizeBytes;
    // set file pointer to end of file
    fseek(input, 0, SEEK_END);
    // get current pointer position in bytes (== file size in bytes)
    fileSizeBytes = ftell(input);
    // return pointer to begin of file (it's very IMPORTANT)
    fseek(input, 0, SEEK_SET);
    return fileSizeBytes;
}

int calcItemsCount_CreditType(FILE *input) {
    return (int) getFileSize(input) / sizeof(CreditType);
}

long getFileSizeClients(FILE *input) {
    long fileSizeBytes;
    // set file pointer to end of file
    fseek(input, 0, SEEK_END);
    // get current pointer position in bytes (== file size in bytes)
    fileSizeBytes = ftell(input);
    // return pointer to begin of file (it's very IMPORTANT)
    fseek(input, 0, SEEK_SET);
    return fileSizeBytes;
}

int calcItemsCount_Clients(FILE *input) {
    return (int) getFileSizeClients(input) / sizeof(Client);
}

long getFileSize_Credit(FILE *input) {
    long fileSizeBytes;
    // set file pointer to end of file
    fseek(input, 0, SEEK_END);
    // get current pointer position in bytes (== file size in bytes)
    fileSizeBytes = ftell(input);
    // return pointer to begin of file (it's very IMPORTANT)
    fseek(input, 0, SEEK_SET);
    return fileSizeBytes;
}

int calcItemsCount_Credit(FILE *input) {
    return (int) getFileSize_Credit(input) / sizeof(Credit);
}

// подсчет размера файлов

void clearConsole() {
//  system("clear");
}

int isFileExists(const char *name){
    struct stat   buffer;
    return (stat (name, &buffer) == 0);
}