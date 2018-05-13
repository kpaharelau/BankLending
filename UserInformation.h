#include "Utils.h"

UserInformation* readUserInformation();
int loginAdmin(UserInformation *);
UserInformation *firstUserInformation(UserInformation *ptrUserInformation);
UserInformation* lastUserInformation(UserInformation *ptrUserInformation);
void recordUserInformation(UserInformation *ptrUserInformation);
void addUser();