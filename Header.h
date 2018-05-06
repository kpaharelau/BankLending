#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sys/stat.h>

#pragma once

/*
* Ориентировочные примеры полей структур для некоторых вариантов (подчёркнутые поля являются ключевыми).
*  Цифры обозначают необходимое количество записей в файле:
*
ВидыКредитов (КодВида, Название, УсловияПолучения, Ставка, Срок) 5
Клиенты (КодКлиента, Название, ВидСобственности, Адрес, Телефон, КонтактноеЛицо) 10
Кредиты (КодВида, КодКлиента, Сумма, ДатаВыдачи) 30
*/

struct CreditType {
    int code_type;          // код кредита
    char credit_name[100];  // имя кредита
    int rate;               // ставка
    int loan_period;        // срок выдачи
    CreditType *next;
    CreditType *prev;
};

typedef struct Nickname {
    char name[18];    // имя
    char surname[26]; // фамилия
};

struct Client {
    int tel_number;       // логин
    Nickname name_user;   // кредитополучатель
    char address[28];     // адрес
    Nickname guarantor;   // поручитель
    Client *next;
    Client *prev;
};

typedef struct {
    int year;
    int month;
    int day;
} Date;

struct Credit {
    int code_type;        // код типа кредита
    int tel_number;       // телефонный номер
    int amount;           // сумма
    Date date;            // дата выдачи
    Credit *next;
    CreditType *prev;
};

struct BankData {
    CreditType *creditType;
    Client *client;
    Credit *credit;
};

int controlNumber();

int readOrCreateFile(CreditType *, Credit *, Client *);

int recordFile(CreditType *, Credit *, Client *);

void menuAdmin(BankData *,  CreditType *, Client *, Credit *);

void add(CreditType *, Client *, Credit *, BankData *ptrBankData);

int addCreditType(CreditType **);

int addClients(Client **);

int addCredit(Credit **, CreditType **, Client **);

CreditType * inputCreditType(CreditType *);

int inputCredit(Credit *, CreditType *, Client *);

void inputClients(Client *);

void remove(CreditType *, Client *, Credit *);

void removePart(CreditType *, Client *, Credit *);

int deleteCreditType(CreditType *);

int deleteClients(Client *);

int deleteCredit(Credit *);

int removeAll(CreditType *, Client *, Credit *);

int viewAll(CreditType *, Client *, Credit *);


void head();

void menuUser();

void getTime(tm &newtime);

long getFileSize(FILE *input);

int calcItemsCount_CreditType(FILE *input);

long getFileSize_Credit(FILE *input);

int calcItemsCount_Credit(FILE *input);

long getFileSizeClients(FILE *input);

int calcItemsCount_Clients(FILE *input);

void clearConsole();

int isFileExists(const char *name);



// РАЗОБРАТЬСЯ С ФСЕЕК и функцией long getFileSize(FILE* input);
// ДОБАВИТЬ ПРОВЕРКИ НА ПУСТОТУ СТЕКА И НА ВВОД ЧИСЕЛ С ТЕКТСТОМ
// разобраться с удалением
// выяснить причину использования не прямых указателей, а передачей его сожержимого в другой и работой с другим
// задефайнить тру и фолс