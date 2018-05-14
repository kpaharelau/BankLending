#define _XOPEN_SOURCE
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
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
    int tel_number;       // логин
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

struct UserInformation {
    char login[30];
    char password[30];
    UserInformation *next= NULL;
    UserInformation *prev= NULL;
};

struct BankData {
    CreditType *creditType= NULL;
    Client *client= NULL;
    Credit *credit= NULL;
};



int getNumberFromKeyboard();

void menuAdmin(BankData *);

void add(BankData *);

int remove(BankData *);

void removePart(BankData *);

int removeAll(BankData *);

void viewAll(CreditType *ptrCreditType, Client* ptrClient, Credit *ptrCredit);

int askForChoice(int count);

void menuUser(BankData* ptrBankData);

void clearConsole();

int isFileExists(const char *name);

void edit(BankData *);

void searchAndFiltering(BankData* ptrBankData);

void search(BankData* ptrBankData);

void filtering(CreditType *ptrCreditType, Client* ptrClient, Credit *ptrCredit);

void userManagement();

char *createPassword(char *input);

int checkPassword(char *input, char *pass);

void searchCreditType(CreditType* ptrCreditType);

void searchClient(Client* ptrClient);

void task(CreditType* ptrCreditType) ;

char *encrypt(char *input) ;

char *decrypt(char *input);



// перестал нормально работать просмотр клиентов
//), в противном случае появится сообщение о том, что такая запись не найдена. поиск , фильтрация,
// проверку на логины и пароли

// РАЗОБРАТЬСЯ С ФСЕЕК
// три кредитополучателя , который взяли кредит на самый большой срок.
//сделать проверку видов кредитов и клиентов, чтобы похожего не было

// переделать поиск