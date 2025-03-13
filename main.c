#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function prototypes
void displayWelcomePage();
void displayBankIFSC();
void displayBankInstructions();
void displayMainMenu();
void createAccount();
void checkBalance(float balance);
void performTransaction(float *balance, const char *transactionFile);
void performDeposit(float *balance, const char *transactionFile);
void performWithdrawal(float *balance, const char *transactionFile);
void performTransfer(float *balance, const char *transactionFile, const char *senderFirstName, const char *senderLastName);
void displayAccountDetails(char *accountNumber);
void loginAccount();
void passbook(const char *transactionFile);
void printAllTransactions(const char *transactionFile);

int main() {
    int choice;

    while (1) { // Run code continuously
        // Display the welcome page
        displayWelcomePage();

        // Get user choice
        printf("\nEnter your choice (1-4): ");
        scanf("%d", &choice);

        // Process user choice
        switch (choice) {
            case 1:
                displayBankIFSC();
                break;
            case 2:
                displayBankInstructions();
                break;
            case 3:
                displayMainMenu();
                break;
            case 4:
                printf("\nThank you for using Bank of Baroda. Goodbye!\n");
                exit(0); // Exit the program
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}

void displayWelcomePage() {
    printf("=====================================================\n");
    printf("              WELCOME TO Bank of Baroda              \n");
    printf("=====================================================\n");
    printf("Please choose an option:\n");
    printf("1. View Bank IFSC Code\n");
    printf("2. View Bank Instructions & Policy\n");
    printf("3. Proceed to Main Menu\n");
    printf("4. Exit\n");
}

void displayBankIFSC() {
    printf("\nBank of Baroda Bank IFSC Code: BARB0SIDHIX\n");
    printf("Thank you for using our services!\n\n");
}

void displayBankInstructions() {
    printf("\nBank of Baroda Bank Instructions & Policy:\n");
    printf("1. Maintain a minimum balance of INR 1000.\n");
    printf("2. Provide valid KYC documents for account creation.\n");
    printf("3. Contact customer care for any issues: 1800-2484-5614.\n");
    printf("4. Follow RBI guidelines for secure transactions.\n");
    printf("Thank you for your cooperation!\n\n");
}

void displayMainMenu() {
    int menuChoice;

    do {
        printf("\n=======================================================\n");
        printf("                         MAIN MENU                     \n");
        printf("=======================================================\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            case 1:
                createAccount();
                break;
            case 2:
                loginAccount();
                break;
            case 3:
                printf("\nThank you for using Bank of Baroda. Have a great day!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (menuChoice != 3);
}

void createAccount() {
    char firstName[50], lastName[50], fatherName[100], motherName[100], dob[20];
    char mobile[11], aadhar[13], accountNumber[13], accountPin[7];
    float initialBalance;

    printf("\n=== Create Account ===\n");
    printf("Enter First Name: ");
    scanf("%s", firstName);
    printf("Enter Last Name: ");
    scanf("%s", lastName);
    getchar(); // Consume newline left by scanf
    printf("Enter Father Name: ");
    fgets(fatherName, sizeof(fatherName), stdin);
    fatherName[strcspn(fatherName, "\n")] = 0; // Remove newline character
    printf("Enter Mother Name: ");
    fgets(motherName, sizeof(motherName), stdin);
    motherName[strcspn(motherName, "\n")] = 0; // Remove newline character
    printf("Enter Date of Birth (DD/MM/YYYY): ");
    scanf("%s", dob);
    printf("Enter 10-digit Mobile Number: ");
    scanf("%s", mobile);
    printf("Enter 12-digit Aadhar Number: ");
    scanf("%s", aadhar);
    printf("Enter 12-digit Account Number: ");
    scanf("%s", accountNumber);
    printf("Enter 6-digit Account PIN: ");
    scanf("%s", accountPin);
    printf("Enter Initial Deposit Amount: ");
    scanf("%f", &initialBalance);

    FILE *file = fopen("./Account Details/accdetails.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "============================================\n");
    fprintf(file, "Account Details:\n");
    fprintf(file, "Account Number: %s\n", accountNumber);
    fprintf(file, "Account PIN: %s\n", accountPin);
    fprintf(file, "First Name: %s\n", firstName);
    fprintf(file, "Last Name: %s\n", lastName);
    fprintf(file, "Father Name: %s\n", fatherName);
    fprintf(file, "Mother Name: %s\n", motherName);
    fprintf(file, "Date of Birth: %s\n", dob);
    fprintf(file, "Mobile Number: %s\n", mobile);
    fprintf(file, "Aadhar Number: %s\n", aadhar);
    fprintf(file, "Initial Balance: %.2f\n", initialBalance);
    fprintf(file, "=============================================\n\n");

    fclose(file);


    printf("\nAccount created successfully with an initial deposit of Rs. %.2f \n", initialBalance);
}
void loginAccount() {
    char enteredAccount[13], enteredPin[7], accountNumber[13], accountPin[7];
    char buffer[256];
    int found = 0;
    float balance = 0.0;
    char transactionFile[100];

    printf("\n========== Login to Account ===========\n");
    printf("Enter Account Number: ");
    scanf("%s", enteredAccount);
    printf("Enter Account PIN: ");
    scanf("%s", enteredPin);

    FILE *file = fopen("./Account Details/accdetails.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (sscanf(buffer, "Account Number: %s", accountNumber) == 1) {
            fgets(buffer, sizeof(buffer), file);
            sscanf(buffer, "Account PIN: %s", accountPin);

            if (strcmp(enteredAccount, accountNumber) == 0 && strcmp(enteredPin, accountPin) == 0) {
                printf("\nLogin successful!\n");
                found = 1;

                // Read balance
                while (fgets(buffer, sizeof(buffer), file) != NULL) {
                    if (sscanf(buffer, "Initial Balance: %f", &balance) == 1) {
                        break;
                    }
                }

                // Generate transaction file name
                sprintf(transactionFile, "./Transection record/%s_transactions.txt", enteredAccount);

                // Display post-login menu
                int loginChoice;
                do {
                    printf("\n==================================================\n");
                    printf("                     ACCOUNT MENU                   \n");
                    printf("====================================================\n");
                    printf("1. Balance Check\n");
                    printf("2. Perform Transaction\n");
                    printf("3. Account Holder Details\n");
                    printf("4. Passbook\n"); // Added Passbook option
                    printf("5. Logout\n");
                    printf("\nEnter your choice: ");
                    scanf("%d", &loginChoice);

                    switch (loginChoice) {
                        case 1:
                            checkBalance(balance);
                            break;
                        case 2:
                            performTransaction(&balance, transactionFile);
                            break;
                        case 3:
                            displayAccountDetails(enteredAccount);
                            break;
                        case 4:
                            passbook(transactionFile); // Call passbook function
                            break;
                        case 5:
                            printf("\nLogging out... Returning to Main Menu.\n");
                            break;
                        default:
                            printf("\nInvalid choice! Please try again.\n");
                    }
                } while (loginChoice != 5);
                break;
            }
        }
    }

    if (!found) {
        printf("\nInvalid Account Number or PIN!\n");
    }

    fclose(file);
}

void checkBalance(float balance) {
    printf("\n=== Balance Check ===\n");
    printf("Your current balance is: %.2f\n", balance);
}

void performTransaction(float *balance, const char *transactionFile) {
    int transactionChoice;

    do {
        printf("\n=====================================================\n");
        printf("                     TRANSACTION MENU                  \n");
        printf("=======================================================\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Transfer\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &transactionChoice);

        switch (transactionChoice) {
            case 1:
                performDeposit(balance, transactionFile);
                break;
            case 2:
                performWithdrawal(balance, transactionFile);
                break;
            case 3:
                performTransfer(balance, transactionFile, "SenderFirstName", "SenderLastName");
                break;
            case 4:
                printf("\nExiting transaction menu...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (transactionChoice != 4);
}

void performDeposit(float *balance, const char *transactionFile) {
    float depositAmount;
    time_t t;
    time(&t);

    printf("\nEnter the amount to deposit: ");
    scanf("%f", &depositAmount);

    if (depositAmount <= 0) {
        printf("\nInvalid deposit amount! Please enter a positive value.\n");
        return;
    }

    *balance += depositAmount;

    FILE *file = fopen(transactionFile, "a");
    if (file == NULL) {
        printf("\nError opening transaction file!\n");
        return;
    }

    fprintf(file, "Deposit: +%.2f | Total Balance: %.2f | Date: %s", depositAmount, *balance, ctime(&t));
    fclose(file);

    printf("\nAmount deposited successfully! New balance: %.2f\n", *balance);
}

void performWithdrawal(float *balance, const char *transactionFile) {
    float withdrawalAmount;
    time_t t;
    time(&t);

    printf("\nEnter the amount to withdraw: ");
    scanf("%f", &withdrawalAmount);

    if (withdrawalAmount <= 0) {
        printf("\nInvalid withdrawal amount! Please enter a positive value.\n");
        return;
    }

    if (withdrawalAmount > *balance) {
        printf("\nInsufficient balance!\n");
        return;
    }

    *balance -= withdrawalAmount;

    FILE *file = fopen(transactionFile, "a");
    if (file == NULL) {
        printf("\nError opening transaction file!\n");
        return;
    }

    fprintf(file, "Withdrawal: -%.2f | Total Balance: %.2f | Date: %s", withdrawalAmount, *balance, ctime(&t));
    fclose(file);

    printf("\nAmount withdrawn successfully! New balance: %.2f\n", *balance);
}
void performTransfer(float *balance, const char *transactionFile, const char *senderFirstName, const char *senderLastName) {
    char recipientAccount[13], recipientFirstName[50], recipientLastName[50];
    float transferAmount;
    char buffer[256], recipientTransactionFile[100];
    float recipientBalance = -1.0; // Invalid balance until found

    printf("\n=== Transfer Money ===\n");
    printf("Enter Recipient's Account Number: ");
    scanf("%s", recipientAccount);
    printf("Enter Recipient's First Name: ");
    scanf("%s", recipientFirstName);
    printf("Enter Recipient's Last Name: ");
    scanf("%s", recipientLastName);

    FILE *file = fopen("./Account Details/accdetails.txt", "r");
    if (file == NULL) {
        printf("Error opening account details file!\n");
        return;
    }

    // Searching for the recipient's details in accdetails.txt
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char accountNumber[13], firstName[50], lastName[50];

        // Find Account Number
        if (sscanf(buffer, "Account Number: %s", accountNumber) == 1) {
            fgets(buffer, sizeof(buffer), file); // Read next line (Account PIN)
            fgets(buffer, sizeof(buffer), file); // Read next line (First Name)
            sscanf(buffer, "First Name: %s", firstName);

            fgets(buffer, sizeof(buffer), file); // Read next line (Last Name)
            sscanf(buffer, "Last Name: %s", lastName);

            // If account number and names match, get the balance
            if (strcmp(accountNumber, recipientAccount) == 0 &&
                strcmp(firstName, recipientFirstName) == 0 &&
                strcmp(lastName, recipientLastName) == 0) {
                
                // Get the balance from the next line
                while (fgets(buffer, sizeof(buffer), file) != NULL) {
                    if (sscanf(buffer, "Initial Balance: %f", &recipientBalance) == 1) {
                        break;
                    }
                }
                break;
            }
        }
    }

    fclose(file);

    // If the recipient was not found in the records
    if (recipientBalance < 0) {
        printf("\nRecipient not found in our records. Transfer aborted.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%f", &transferAmount);

    if (transferAmount <= 0) {
        printf("\nInvalid transfer amount!\n");
        return;
    }

    if (transferAmount > *balance) {
        printf("\nInsufficient balance for transfer!\n");
        return;
    }

    // Proceed with the transfer
    *balance -= transferAmount;
    recipientBalance += transferAmount;

    // Update transaction file for sender
    FILE *senderFile = fopen(transactionFile, "a");
    if (senderFile == NULL) {
        printf("\nError opening transaction file for sender!\n");
        return;
    }

    time_t t;
    time(&t);

    fprintf(senderFile, "Transfer to %s %s (Account: %s): -%.2f | Remaining Balance: %.2f | Date: %s",
            recipientFirstName, recipientLastName, recipientAccount, transferAmount, *balance, ctime(&t));
    fclose(senderFile);

    // Update transaction file for recipient
    sprintf(recipientTransactionFile, "./Transection record/%s_transactions.txt", recipientAccount);

    FILE *recipientFile = fopen(recipientTransactionFile, "a");
    if (recipientFile == NULL) {
        printf("\nError opening transaction file for recipient!\n");
        return;
    }

    fprintf(recipientFile, "Transfer from (Account: %s): +%.2f | New Balance: %.2f | Date: %s",
             recipientAccount, transferAmount, recipientBalance, ctime(&t));
    fclose(recipientFile);

    printf("\nTransfer successful! %.2f transferred to %s %s.\n", transferAmount, recipientFirstName, recipientLastName);
}



void displayAccountDetails(char *accountNumber) {
    char buffer[256], fileAccountNumber[13];
    FILE *file = fopen("./Account Details/accdetails.txt", "r");
    if (file == NULL) {
        printf("Error opening account details file!\n");
        return;
    }

    printf("\n======== Account Holder Details ========\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (sscanf(buffer, "Account Number: %s", fileAccountNumber) == 1) {
            if (strcmp(fileAccountNumber, accountNumber) == 0) {
                printf("%s", buffer); // Print Account Number
                while (fgets(buffer, sizeof(buffer), file) != NULL && strncmp(buffer, "===================================", 35) != 0) {
                    if (strstr(buffer, "Account PIN:") == NULL) {
                        printf("%s", buffer);
                    }
                }
                break;
            }
        }
    }

    fclose(file);
}

void passbook(const char *transactionFile) {
    int passbookChoice;
    char buffer[256];

    do {
        printf("\n===============================================\n");
        printf("                   PASSBOOK MENU                 \n");
        printf("=================================================\n");
        printf("1. All Transactions\n");
        printf("2. Back to Account Menu\n");
        printf("\nEnter your choice: ");
        scanf("%d", &passbookChoice);

        switch (passbookChoice) {
            case 1:
                printAllTransactions(transactionFile);
                break;
            case 2:
                printf("\nReturning to Account Menu...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (passbookChoice != 2);
}

void printAllTransactions(const char *transactionFile) {
    char buffer[256];
    FILE *file = fopen(transactionFile, "r");

    if (file == NULL) {
        printf("Error opening transaction file!\n");
        return;
    }

    printf("\n========= All Transactions ========\n");

    // Read all the lines from the transaction file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}

