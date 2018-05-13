#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/stat.h>
#define _XOPEN_SOURCE
#include <unistd.h>

char *crypt(const char *key, const char *salt);
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
    char credit_name[20];  // имя кредита
    int rate;               // ставка
    int loan_period;        // срок выдачи
    CreditType *next = NULL;
    CreditType *prev = NULL;
};

struct Nickname {
    char name[18];    // имя
    char surname[26]; // фамилия
};

struct Client {
    long tel_number;       // логин
    Nickname name_user;   // кредитополучатель
    char address[28];     // адрес
    Nickname guarantor;   // поручитель
    Client *next = NULL;
    Client *prev = NULL;
};

struct Date{
    int year;
    int month;
    int day;
};

struct Credit {
    int code_type;        // код типа кредита
    int tel_number;       // телефонный номер
    int amount;           // сумма
    Date date;            // дата выдачи
    Credit *next = NULL;
    Credit *prev= NULL;
};

struct Information {
    char login[255];
    char password[255];
    Information *next= NULL;
    Information *prev= NULL;
};

struct BankData {
    CreditType *creditType= NULL;
    Client *client= NULL;
    Credit *credit= NULL;
    Information *information= NULL;
};




int getNumberFromKeyboard();

long getLongFromKeyboard();

void menuAdmin(BankData *);

void add(BankData *);

void remove(BankData *);

void removePart(BankData *);

int removeAll(BankData *);

void viewAll(CreditType *ptrCreditType, Client* ptrClient, Credit *ptrCredit);

int askForChoice(int count);

void menuUser();

void clearConsole();

int isFileExists(const char *name);

void edit(BankData *);

void searchAndFiltering(BankData* ptrBankData);

void search(BankData* ptrBankData);

void filtering(BankData* ptrBankData);

void userManagement(BankData* ptrBankData);


// РАЗОБРАТЬСЯ С ФСЕЕК
// разобраться с удалением
// три кредитополучателя , который взяли кредит на самый большой срок.
//сделать проверку видов кредитов и клиентов, чтобы похожего не было
// что за функция проверки файлна на существование




//удаление всего
//фильтрация , поиск
//пароль админа и юзера( функции , которые отвечают за запись в отдельный файл , ввод )с