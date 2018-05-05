#include "Header.h"

int main() {
    CreditType *start_creditType = nullptr;
    Credit *start_credit = nullptr;
    Clients *start_clients = nullptr;
    readOrCreateFile(start_creditType, start_credit, start_clients);
    while (true) {
        printf("Главное меню ======= Выберите действие =======\n");
        printf("1. Вход под администратором.\n");
        printf("2. Вход под пользователем.\n");
        printf("0. Выход. \n");
        int i;
        i = controlNumber();
        switch (i) {
            case 1:
                menuAdmin(start_creditType, start_clients, start_credit);
                break;
            case 2:
                menuUser();
                break;
            case 0:
                recordFile(start_creditType, start_credit, start_clients);
                exit(0);
            default:
                printf("Вветите числа от 0 до 2\n");
                break;
        }
    }
}