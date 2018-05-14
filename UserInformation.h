#include "Utils.h"

UserInformation* read();
int loginAdmin();
int loginUser();
UserInformation *firstUserInformation(UserInformation *ptrUserInformation);
UserInformation* lastUserInformation(UserInformation *ptrUserInformation);
void recordUserInformation(UserInformation *ptrUserInformation);

void addUsers();
void deleteUsers();
int viewAllUsers();