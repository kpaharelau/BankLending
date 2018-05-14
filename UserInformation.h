#include "Utils.h"

UserInformation* read();
int loginAdmin();
UserInformation *firstUserInformation(UserInformation *ptrUserInformation);
UserInformation* lastUserInformation(UserInformation *ptrUserInformation);
void recordUserInformation(UserInformation *ptrUserInformation);

void addUsers();
void deleteUsers();
void editUser(UserInformation *ptrUserInformation);
int viewAllUsers();