#include "Header.h"

Client* readClient();                                  // чтение файла
void recordClient(Client *);         //

Client* firstClient(Client* ptrClient);        //определение конечного элемента
Client* lastClient(Client* ptrClient);          //определение первого элемента      || почему везде звездочки перед вызовом функции
Client* inputClient(Client *ptrClient);         //ввод вида кредита
Client* deleteClient(Client *ptrClient);       // удаление
int viewClient(Client *ptrClient);
void headClient();
Client* editClient(Client *ptrClient);