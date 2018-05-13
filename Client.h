#include "Utils.h"

Client* readClient();
void recordClient(Client *);
Client* firstClient(Client* ptrClient);
Client* lastClient(Client* ptrClient);
Client* inputClient(Client *ptrClient);
Client* deleteClient(Client *ptrClient);
int viewClient(Client *ptrClient);
void headClient();
Client* editClient(Client *ptrClient);