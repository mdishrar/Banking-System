#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   // for usleep

int count_account = 1, max_account = 100;

struct Account {
    int account_number;
    float balance;
    char name[50];
    struct Account* next;
};

// Initialize first dummy account
void dummy_account(struct Account* account) {
    account->account_number = 1;
    account->balance = 40.0;
    strcpy(account->name, "Admin");
    account->next = NULL;
}

// Authentication
int Authentication(struct Account* account) {
    int pass;
    printf("Enter the account number: ");
    scanf("%d", &pass);

    while (account != NULL) {
        if (account->account_number == pass) {
            printf("Loading");
            for (int i = 0; i < 5; i++) {
                printf(".");
                usleep(300000);
            }
            printf("\n");
            return pass;
        }
        account = account->next;
    }

    printf("Wrong account number!\n");
    return 0;
}

// Open new account
void open_account(struct Account* account) {

    struct Account* new_account = (struct Account*)malloc(sizeof(struct Account));

    while (getchar() != '\n'); // clear buffer

    printf("Enter the name: ");
    fgets(new_account->name, sizeof(new_account->name), stdin);

    size_t len = strlen(new_account->name);
    if (len > 0 && new_account->name[len - 1] == '\n') {
        new_account->name[len - 1] = '\0';
    }

    count_account++;
    new_account->account_number = count_account;
    new_account->balance = 0;
    new_account->next = NULL;

    // Traverse to end
    struct Account* temp = account;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_account;

    // Save to file
    FILE* ptr = fopen("accounts.txt", "a"); // append mode
    if (ptr == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(ptr, "%s %d %f\n",
            new_account->name,
            new_account->account_number,
            new_account->balance);

    fclose(ptr);

    printf("\nAccount created successfully!\n");
    printf("Account Number: %d\n", new_account->account_number);
    printf("Balance: %.2f\n", new_account->balance);
}

// Close account (delete node)
void close_account(struct Account* account) {

    int result = Authentication(account);
    if (result == 0) return;

    struct Account* temp = account;
    struct Account* prev = NULL;

    while (temp != NULL) {
        if (temp->account_number == result) {

            if (prev == NULL) {
                printf("Cannot delete first account\n");
                return;
            }

            prev->next = temp->next;
            free(temp);
            count_account--;

            printf("Account deleted successfully\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

// Deposit
void add_amount(struct Account* account) {

    int amount;
    printf("Enter amount to deposit: ");
    scanf("%d", &amount);

    int result = Authentication(account);
    if (result == 0) return;

    struct Account* temp = account;

    while (temp != NULL) {
        if (temp->account_number == result) {
            temp->balance += amount;
            printf("Updated balance: %.2f\n", temp->balance);
            return;
        }
        temp = temp->next;
    }
}

// Withdraw
void Withdraw_amount(struct Account* account) {

    int amount;
    printf("Enter amount to withdraw: ");
    scanf("%d", &amount);

    int result = Authentication(account);
    if (result == 0) return;

    struct Account* temp = account;

    while (temp != NULL) {
        if (temp->account_number == result) {

            if (temp->balance >= amount) {
                temp->balance -= amount;
                printf("Remaining balance: %.2f\n", temp->balance);
            } else {
                printf("Insufficient balance\n");
            }
            return;
        }
        temp = temp->next;
    }
}

// Display all accounts
void display_accounts(struct Account* account) {
    printf("\n--- All Accounts ---\n");

    while (account != NULL) {
        printf("Name: %s | Acc No: %d | Balance: %.2f\n",
               account->name,
               account->account_number,
               account->balance);
        account = account->next;
    }
}

int main() {

    struct Account* account = (struct Account*)malloc(sizeof(struct Account));
    dummy_account(account);

    int choice;

    while (1) {
        printf("\n------ Banking System ------\n");
        printf("1. Open Account\n");
        printf("2. Close Account\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Display Accounts\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                open_account(account);
                break;
            case 2:
                close_account(account);
                break;
            case 3:
                add_amount(account);
                break;
            case 4:
                Withdraw_amount(account);
                break;
            case 5:
                display_accounts(account);
                break;
            case 6:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
