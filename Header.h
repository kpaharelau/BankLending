#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

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
};

typedef struct {
    char name[18];    // имя
    char surname[26]; // фамилия
} nickname;

struct Clients {
    int tel_number;       // логин
    nickname name_user;   // кредитополучатель
    char address[28];     // адрес
    nickname guarantor;   // поручитель
    Clients *next;
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
};

int controlNumber();

int readOrCreateFile(CreditType *, Credit *, Clients *);

int recordFile(CreditType *, Credit *, Clients *);

void menuAdmin(CreditType *, Clients *, Credit *);

void add(CreditType *, Clients *, Credit *);

int addCreditType(CreditType **);

int addClients(Clients **);

int addCredit(Credit **, CreditType **, Clients **);

void inputCreditType(CreditType *);

int inputCredit(Credit *, CreditType *, Clients *);

void inputClients(Clients *);

void remove(CreditType *, Clients *, Credit *);

void removePart(CreditType *, Clients *, Credit *);

int deleteCreditType(CreditType *);

int deleteClients(Clients *);

int deleteCredit(Credit *);

int removeAll(CreditType *, Clients *, Credit *);

int viewAll(CreditType *, Clients *, Credit *);


void head();

void menuUser();

void getTime(tm &newtime);

long getFileSize_CreditType(FILE *input);

int calcItemsCount_CreditType(FILE *input);

long getFileSize_Credit(FILE *input);

int calcItemsCount_Credit(FILE *input);

long getFileSizeClients(FILE *input);

int calcItemsCount_Clients(FILE *input);

void clearConsole();


// РАЗОБРАТЬСЯ С ФСЕЕК и функцией long getFileSizeClients(FILE* input);
// ДОБАВИТЬ ПРОВЕРКИ НА ПУСТОТУ СТЕКА И НА ВВОД ЧИСЕЛ С ТЕКТСТОМ
// разобраться с удалением
// выяснить причину использования не прямых указателей, а передачей его сожержимого в другой и работой с другим