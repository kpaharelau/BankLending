#include "Utils.h"

UserInformation* readUserInformation();
int loginAdmin(UserInformation *);
UserInformation *firstUserInformation(UserInformation *ptrUserInformation);
UserInformation* lastUserInformation(UserInformation *ptrUserInformation);
void recordUserInformation(UserInformation *ptrUserInformation);

UserInformation* addUsers(UserInformation *ptrUserInformation);
UserInformation* deleteUsers(UserInformation *ptrUserInformation);
UserInformation* editUser(UserInformation *ptrUserInformation);
int viewAllUsers(UserInformation *ptrUserInformation);