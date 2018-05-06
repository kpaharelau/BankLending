#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sys/stat.h>
#define true 1


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
    Credit *prev;
};

struct BankData {
    CreditType *creditType;
    Client *client;
    Credit *credit;
};

int controlNumber();

void menuAdmin(BankData *,  CreditType *, Client *, Credit *);

void add(CreditType *, Client *, Credit *, BankData *);

void remove(CreditType *, Client *, Credit *, BankData *);

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

void clearConsole();

int isFileExists(const char *name);



// РАЗОБРАТЬСЯ С ФСЕЕК и функцией long getFileSize(FILE* input);
// ДОБАВИТЬ ПРОВЕРКИ НА ПУСТОТУ СТЕКА И НА ВВОД ЧИСЕЛ С ТЕКТСТОМ
// разобраться с удалением
// выяснить причину использования не прямых указателей, а передачей его сожержимого в другой и работой с другим