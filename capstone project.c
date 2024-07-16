#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define RESET_COLOR "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define BOLD "\x1b[1m"

typedef struct
{
    int accountId;
    char name[100];
    char phoneNumber[20];
    char dob[20];
    char password[20];
    float balance;
} Customer;

typedef struct
{
    char name[100];
    char password[20];
} Employee;

typedef struct
{
    char name [100];
    char password [20];
} Admin;

void showMainMenu();
void customerLogin();
void registerCustomer();
void employeeLogin();
void adminLogin();
void displayLoadingScreen();
void clearScreen();
void welcomeMessage();
void balanceCheck(Customer customer);
void depositBalance(Customer *customer);
void withdrawBalance(Customer *customer);
void transferBalance(Customer *customer);
void paymentOption();
void loanManagement();
void statementCheck();
void reportProblem();
void feedback();
void deleteAccount();
void storeAccount(Customer customer);
void storeEmployee(Employee employee);
void storeAdmin(const char* username, const char* password);
int createAccount();
int generateAccountNumber();
int verifyAdmin(const char* username, const char* password);

int main()
{
    displayLoadingScreen();
    clearScreen();
    welcomeMessage();
    showMainMenu();
    return 0;
}

void displayLoadingScreen()
{
    const int barWidth = 30;
    const int consoleWidth = 80;
    int progress;
    int percentage;

    int leftPadding = (consoleWidth - (barWidth + 10)) / 2;
    printf("\n");
    for (progress = 0; progress <= barWidth; ++progress)
    {
        usleep(50000);
        percentage = (int)((progress * 100) / barWidth);
        printf("\r%*s[", leftPadding, "");
        for (int i = 0; i < progress; ++i)
        {
            printf(GREEN "_" RESET_COLOR);
        }

        for (int i = progress; i < barWidth; ++i)
        {
            printf(" ");
        }

        printf("]  %2d%%    ", percentage);
        fflush(stdout);
    }
    printf("\n\nLoading Complete!\n");
    usleep(100000);
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void welcomeMessage()
{
    printf(CYAN BOLD "\t\t\t\t\t\tWelcome to the Bank System!\n\n" RESET_COLOR);
    usleep(1000000);
}

void showMainMenu()
{
    int choice;
    do
    {
        printf(YELLOW "\t\t\t\t+------------------------------------------------------------+\n" RESET_COLOR);
        printf(YELLOW "\t\t\t\t|                      " BOLD "Bank System" RESET_COLOR YELLOW "                           |\n" RESET_COLOR);
        printf(YELLOW "\t\t\t\t+------------------------------------------------------------+\n" RESET_COLOR);
        printf("\t\t\t\t| 1. Customer                                                |\n");
        printf("\t\t\t\t| 2. Bank Employee Login                                     |\n");
        printf("\t\t\t\t| 3. Admin                                                   |\n");
        printf("\t\t\t\t| 4. Exit                                                    |\n");
        printf(YELLOW "\t\t\t\t+------------------------------------------------------------+\n" RESET_COLOR);
        printf("\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf (CYAN BOLD "Hi Sir Please Select Your Option\n"RESET_COLOR);
            printf("Enter 10 for Login\n OR Enter 20 for Registration:\n");
            int x;
            scanf("%d", &x);
            switch (x)
            {
            case 10:
                customerLogin();
                break;
            case 20:
                registerCustomer();
                break;
            default:
                printf("Invalid sub-choice.\n");
                break;
            }
            break;
        case 2:
            employeeLogin();
            break;
        case 3:
            adminLogin();
            break;
        case 4:
            printf(GREEN"Exiting system....\n"RESET_COLOR);
            break;
        default:
            printf(RED "Invalid choice, please try again.\n" RESET_COLOR);
        }
    }
    while (choice != 4);
}
void registerCustomer()
{
    Customer newCustomer;

    printf("Enter customer name: ");
    scanf(" %s", newCustomer.name);

    printf("Enter phone number: ");
    scanf("%s", newCustomer.phoneNumber);

    printf("Enter date of birth (dd-mm-yyyy): ");
    scanf("%s", newCustomer.dob);

    printf("Enter login password: ");
    scanf("%s", newCustomer.password);

    newCustomer.accountId = generateAccountNumber();
    newCustomer.balance =0.0;

    storeAccount(newCustomer);

    printf(GREEN "Account created successfully!\n" RESET_COLOR);
    printf("Your Bank ID Number: %d\n", newCustomer.accountId);
}
int generateAccountNumber()
{
    int lastAccountNumber = getLastAccountNumber();
    int newAccountNumber = lastAccountNumber + 1;
    updateLastAccountNumber(newAccountNumber);
    return newAccountNumber;
}

void updateLastAccountNumber(int lastAccountNumber)
{
    FILE *file = fopen("last_account_number.txt", "w");
    if (file != NULL)
    {
        fprintf(file, "%d", lastAccountNumber);
        fclose(file);
    }
    else
    {
        printf(RED "Error updating last account number.\n" RESET_COLOR);
    }
}

int getLastAccountNumber()
{
    FILE *file = fopen("last_account_number.txt", "r");
    int lastAccountNumber = 0;
    if (file != NULL)
    {
        fscanf(file, "%d", &lastAccountNumber);
        fclose(file);
    }
    else
    {
        printf(RED "Error reading last account number.\n" RESET_COLOR);
    }
    return lastAccountNumber;
}

void storeAccount(Customer customer)
{
    FILE *file;
    file = fopen("userdata.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "User Bank ID: %d\n", customer.accountId);
        fprintf(file, "Name: %s\n", customer.name);
        fprintf(file, "Phone Number: %s\n", customer.phoneNumber);
        fprintf(file, "Date of Birth: %s\n", customer.dob);
        fprintf(file, "Password: %s\n", customer.password);
        fprintf(file, "Balance: %.2f\n\n", customer.balance);
        fclose(file);
    }
    else
    {
        printf(RED "Error opening file for writing.\n" RESET_COLOR);
    }
}

void customerLogin()
{
    int accountId;
    char password[20];
    Customer loggedInCustomer;

    printf("Enter your Bank ID: ");
    scanf("%d", &accountId);
    printf("Enter your password: ");
    scanf("%s", password);

    if (validateLogin(accountId, password))
    {
        printf(GREEN "Login Successful\n" RESET_COLOR);

        // Fetch customer details from file
        FILE *file = fopen("userdata.txt", "r");
        if (file == NULL)
        {
            printf(RED "Error opening file.\n" RESET_COLOR);
            return;
        }

        int found = 0;
        while (fscanf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %f\n\n",
                      &loggedInCustomer.accountId, loggedInCustomer.name, loggedInCustomer.phoneNumber,
                      loggedInCustomer.dob, loggedInCustomer.password, &loggedInCustomer.balance) != EOF)
        {
            if (loggedInCustomer.accountId == accountId)
            {
                found = 1;
                break;
            }
        }

        fclose(file);

        if (!found)
        {
            printf(RED "Account not found.\n" RESET_COLOR);
            return;
        }

        int choice;
        do
        {
            printf(YELLOW "\t\t\t\t+--------------------------------------------------+\n" RESET_COLOR);
            printf(YELLOW "\t\t\t\t|               " BOLD "Customer Menu" RESET_COLOR YELLOW "                      |\n" RESET_COLOR);
            printf(YELLOW "\t\t\t\t+--------------------------------------------------+\n" RESET_COLOR);
            printf("\t\t\t\t| 1. Balance Check                                 |\n");
            printf("\t\t\t\t| 2. Deposit Balance                               |\n");
            printf("\t\t\t\t| 3. Withdraw Balance                              |\n");
            printf("\t\t\t\t| 4. Transfer Balance                              |\n");
            printf("\t\t\t\t| 5. Payment Option                                |\n");
            printf("\t\t\t\t| 6. Statement Check                               |\n");
            printf("\t\t\t\t| 7. Report Problem                                |\n");
            printf("\t\t\t\t| 8. Feedback                                      |\n");
            printf("\t\t\t\t| 9. Logout                                        |\n");
            printf(YELLOW "\t\t\t\t+--------------------------------------------------+\n" RESET_COLOR);
            printf("\t\t\t\tEnter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                balanceCheck(loggedInCustomer);
                break;
            case 2:
                depositBalance(&loggedInCustomer);
                break;
            case 3:
                withdrawBalance(&loggedInCustomer);
                break;
            case 4:
                transferBalance(&loggedInCustomer);
                break;
            case 5:
                paymentOption(&loggedInCustomer);
                break;
            case 6:
                statementCheck(loggedInCustomer.accountId);
                break;
            case 7:
                reportProblem();
                break;
            case 8:
                feedback();
                break;
            case 9:
                printf(GREEN "Logging out...\n" RESET_COLOR);
                break;
            default:
                printf(RED "Invalid choice, please try again.\n" RESET_COLOR);
            }
        }
        while (choice != 9);
    }
    else
    {
        printf(RED "Try Again With Valid Information\n" RESET_COLOR);
    }
}

int validateLogin(int accountId, char password[])
{
    FILE *file;
    file = fopen("userdata.txt", "r");
    if (file != NULL)
    {
        int id;
        char pass[20];
        while (fscanf(file, "User Bank ID: %d\nName: %*s\nPhone Number: %*s\nDate of Birth: %*s\nPassword: %s\nBalance: %*f\n\n", &id, pass) != EOF)
        {
            if (id == accountId && strcmp(pass, password) == 0)
            {
                fclose(file);
                return 1; // Login successful
            }
        }
        fclose(file);
    }
    return 0; // Login failed
}

void balanceCheck(Customer customer)
{
    printf(CYAN "Your current balance is: $%.2f\n" RESET_COLOR, customer.balance);
}

void depositBalance(Customer *customer)
{
    float amount;
    printf("Enter the amount to deposit: ");
    scanf("%f", &amount);
    customer->balance += amount;
    printf(GREEN "Deposit successful. New balance: $%.2f\n" RESET_COLOR, customer->balance);
    storeTrans(customer->accountId, "Deposit", amount, customer->balance);

    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf(RED "Error opening customer file.\n" RESET_COLOR);
        return;
    }

    // Read all customers into memory
    Customer *customers = NULL;
    size_t customerCount = 0;
    Customer tempCustomer;
    while (fscanf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %f\n\n",
                  &tempCustomer.accountId, tempCustomer.name, tempCustomer.phoneNumber,
                  tempCustomer.dob, tempCustomer.password, &tempCustomer.balance) != EOF)
    {
        customers = realloc(customers, sizeof(Customer) * (customerCount + 1));
        customers[customerCount++] = tempCustomer;
    }
    fclose(file);

    // Update customer balance in memory
    for (size_t i = 0; i < customerCount; ++i)
    {
        if (customers[i].accountId == customer->accountId)
        {
            customers[i].balance = customer->balance;
            break;
        }
    }

    // Write updated data back to file
    file = fopen("userdata.txt", "w");
    if (file == NULL)
    {
        printf(RED "Error opening customer file for writing.\n" RESET_COLOR);
        free(customers);
        return;
    }

    for (size_t i = 0; i < customerCount; ++i)
    {
        fprintf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %.2f\n\n",
                customers[i].accountId, customers[i].name, customers[i].phoneNumber,
                customers[i].dob, customers[i].password, customers[i].balance);
    }

    fclose(file);
    free(customers);
}

void withdrawBalance(Customer *customer)
{
    float amount;
    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);
    if (amount > customer->balance)
    {
        printf(RED "Insufficient balance.\n" RESET_COLOR);
        return;
    }

    customer->balance -= amount;
    printf(GREEN "Withdrawal successful. New balance: $%.2f\n" RESET_COLOR, customer->balance);
    storeTrans(customer->accountId, "Withdraw", amount, customer->balance);

    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf(RED "Error opening customer file.\n" RESET_COLOR);
        return;
    }

    // Read all customers into memory
    Customer *customers = NULL;
    size_t customerCount = 0;
    Customer tempCustomer;
    while (fscanf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %f\n\n",
                  &tempCustomer.accountId, tempCustomer.name, tempCustomer.phoneNumber,
                  tempCustomer.dob, tempCustomer.password, &tempCustomer.balance) != EOF)
    {
        customers = realloc(customers, sizeof(Customer) * (customerCount + 1));
        customers[customerCount++] = tempCustomer;
    }
    fclose(file);

    // Update customer balance in memory
    for (size_t i = 0; i < customerCount; ++i)
    {
        if (customers[i].accountId == customer->accountId)
        {
            customers[i].balance = customer->balance;
            break;
        }
    }

    // Write updated data back to file
    file = fopen("userdata.txt", "w");
    if (file == NULL)
    {
        printf(RED "Error opening customer file for writing.\n" RESET_COLOR);
        free(customers);
        return;
    }

    for (size_t i = 0; i < customerCount; ++i)
    {
        fprintf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %.2f\n\n",
                customers[i].accountId, customers[i].name, customers[i].phoneNumber,
                customers[i].dob, customers[i].password, customers[i].balance);
    }

    fclose(file);
    free(customers);
}

void transferBalance(Customer *customer)
{
    int targetAccountId;
    float amount;
    printf("Enter the target account ID: ");
    scanf("%d", &targetAccountId);
    printf("Enter the amount to transfer: ");
    scanf("%f", &amount);

    if (amount > customer->balance)
    {
        printf(RED "Insufficient balance.\n" RESET_COLOR);
        return;
    }

    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf(RED "Error opening customer file.\n" RESET_COLOR);
        return;
    }

    // Read all customers into memory
    Customer *customers = NULL;
    size_t customerCount = 0;
    Customer tempCustomer;
    while (fscanf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %f\n\n",
                  &tempCustomer.accountId, tempCustomer.name, tempCustomer.phoneNumber,
                  tempCustomer.dob, tempCustomer.password, &tempCustomer.balance) != EOF)
    {
        customers = realloc(customers, sizeof(Customer) * (customerCount + 1));
        customers[customerCount++] = tempCustomer;
    }
    fclose(file);

    // Find target customer
    Customer *targetCustomer = NULL;
    for (size_t i = 0; i < customerCount; ++i)
    {
        if (customers[i].accountId == targetAccountId)
        {
            targetCustomer = &customers[i];
            break;
        }
    }

    if (targetCustomer == NULL)
    {
        printf(RED "Target account not found.\n" RESET_COLOR);
        free(customers);
        return;
    }

    // Perform transfer
    customer->balance -= amount;
    targetCustomer->balance += amount;

    printf(GREEN "Transfer successful. New balance: $%.2f\n" RESET_COLOR, customer->balance);
    storeTrans(customer->accountId, "Transfer to Account", amount, customer->balance);
    storeTrans(targetCustomer->accountId, "Transfer from Account", amount, targetCustomer->balance);

    // Write updated data back to file
    file = fopen("userdata.txt", "w");
    if (file == NULL)
    {
        printf(RED "Error opening customer file for writing.\n" RESET_COLOR);
        free(customers);
        return;
    }

    for (size_t i = 0; i < customerCount; ++i)
    {
        fprintf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %.2f\n\n",
                customers[i].accountId, customers[i].name, customers[i].phoneNumber,
                customers[i].dob, customers[i].password, customers[i].balance);
    }

    fclose(file);
    free(customers);
}
void paymentOption(Customer *customer)
{
    int choice;
    do
    {
        printf(YELLOW "\t\t\t\t+-------------------------------------------------------+\n" RESET_COLOR);
        printf(YELLOW "\t\t\t\t|                   " BOLD "Payment Options" RESET_COLOR YELLOW "                     |\n" RESET_COLOR);
        printf(YELLOW "\t\t\t\t+-------------------------------------------------------+\n" RESET_COLOR);
        printf("\t\t\t\t| 1. Debit                                              |\n");
        printf("\t\t\t\t| 2. Credit                                             |\n");
        printf("\t\t\t\t| 3. Back to Customer Menu                              |\n");
        printf(YELLOW "\t\t\t\t+-------------------------------------------------------+\n" RESET_COLOR);
        printf("\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("You chose Debit option.\n");
            debit(customer);
            break;
        case 2:
            printf("You chose Credit option.\n");
            credit(customer);
            break;
        case 3:
            printf(GREEN "Going back to Customer Menu...\n" RESET_COLOR);
            break;
        default:
            printf(RED "Invalid choice, please try again.\n" RESET_COLOR);
        }
    }
    while (choice != 3);
}
void debit(Customer *customer)
{
    float amount;
    int n;
    printf("Enter Your Debit account number: ");
    scanf("%d", &n);
    printf("Enter the amount you want to payment: ");
    scanf("%f", &amount);
    if (amount > customer->balance)
    {
        printf(RED "Insufficient balance.\n" RESET_COLOR);
        return;
    }

    customer->balance -= amount;
    printf(GREEN "Payment successful. New balance: $%.2f\n" RESET_COLOR, customer->balance);
    storeTrans(customer->accountId, "Debit Payment", amount, customer->balance);

    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf(RED "Error opening customer file.\n" RESET_COLOR);
        return;
    }

    // Read all customers into memory
    Customer *customers = NULL;
    size_t customerCount = 0;
    Customer tempCustomer;
    while (fscanf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %f\n\n",
                  &tempCustomer.accountId, tempCustomer.name, tempCustomer.phoneNumber,
                  tempCustomer.dob, tempCustomer.password, &tempCustomer.balance) != EOF)
    {
        customers = realloc(customers, sizeof(Customer) * (customerCount + 1));
        customers[customerCount++] = tempCustomer;
    }
    fclose(file);

    // Update customer balance in memory
    for (size_t i = 0; i < customerCount; ++i)
    {
        if (customers[i].accountId == customer->accountId)
        {
            customers[i].balance = customer->balance;
            break;
        }
    }

    // Write updated data back to file
    file = fopen("userdata.txt", "w");
    if (file == NULL)
    {
        printf(RED "Error opening customer file for writing.\n" RESET_COLOR);
        free(customers);
        return;
    }

    for (size_t i = 0; i < customerCount; ++i)
    {
        fprintf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %.2f\n\n",
                customers[i].accountId, customers[i].name, customers[i].phoneNumber,
                customers[i].dob, customers[i].password, customers[i].balance);
    }

    fclose(file);
    free(customers);
}
void credit(Customer *customer)
{
    float amount;
    int n;
    printf("Enter Your Credit account number: ");
    scanf("%d", &n);
    printf("Enter the amount you want to payment: ");
    scanf("%f", &amount);
    if (amount > customer->balance)
    {
        printf(RED "Insufficient balance.\n" RESET_COLOR);
        return;
    }

    customer->balance -= amount;
    printf(GREEN "Payment successful. New balance: $%.2f\n" RESET_COLOR, customer->balance);
    storeTrans(customer->accountId, "Credit Payment", amount, customer->balance);

    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf(RED "Error opening customer file.\n" RESET_COLOR);
        return;
    }

    // Read all customers into memory
    Customer *customers = NULL;
    size_t customerCount = 0;
    Customer tempCustomer;
    while (fscanf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %f\n\n",
                  &tempCustomer.accountId, tempCustomer.name, tempCustomer.phoneNumber,
                  tempCustomer.dob, tempCustomer.password, &tempCustomer.balance) != EOF)
    {
        customers = realloc(customers, sizeof(Customer) * (customerCount + 1));
        customers[customerCount++] = tempCustomer;
    }
    fclose(file);

    // Update customer balance in memory
    for (size_t i = 0; i < customerCount; ++i)
    {
        if (customers[i].accountId == customer->accountId)
        {
            customers[i].balance = customer->balance;
            break;
        }
    }
    // Write updated data back to file
    file = fopen("userdata.txt", "w");
    if (file == NULL)
    {
        printf(RED "Error opening customer file for writing.\n" RESET_COLOR);
        free(customers);
        return;
    }

    for (size_t i = 0; i < customerCount; ++i)
    {
        fprintf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %.2f\n\n",
                customers[i].accountId, customers[i].name, customers[i].phoneNumber,
                customers[i].dob, customers[i].password, customers[i].balance);
    }

    fclose(file);
    free(customers);
}
void storeTrans(int accountId, const char *transactionType, double  amount, double balance)
{
    FILE *file = fopen("transactions.txt", "a");
    if (file == NULL)
    {
        printf(RED "Error opening transaction file.\n" RESET_COLOR);
        return;
    }
    fprintf(file, "Account ID: %d | Transaction: %s | Amount: $%.2lf | Balance: $%.2lf\n", accountId, transactionType, amount, balance);
    fclose(file);
}

void statementCheck(int accountId)
{
    FILE *file = fopen("transactions.txt", "r");
    if (file == NULL)
    {
        printf(RED "Error opening file.\n" RESET_COLOR);
        return;
    }

    char line[256];
    int found = 0;
    printf("Account Statement for Account ID: %d\n", accountId);

    while (fgets(line, sizeof(line), file))
    {
        int accId;
        char transactionType[50];
        float amount, balance;
        if (sscanf(line, "Account ID: %d | Transaction: %49[^|] | Amount: $%f | Balance: $%f", &accId, transactionType, &amount, &balance) == 4)
        {
            if (accId == accountId)
            {
                found = 1;
                printf("%s", line);
            }
        }
    }

    if (!found)
    {
        printf("No transactions found for Account ID: %d\n", accountId);
    }

    fclose(file);
}
void reportProblem()
{
    char problem[200];
    printf("Please describe the problem you encountered: ");
    getchar(); // Clear input buffer
    fgets(problem, sizeof(problem), stdin);

    FILE *file = fopen("problem_reports.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "Problem Report: %s\n", problem);
        fclose(file);
        printf(CYAN"Thank you for reporting the problem. It has been noted.\n" RESET_COLOR);
    }
    else
    {
        printf(RED"Error: Could not open file to store problem report.\n"RESET_COLOR);
    }
}

void feedback()
{
    char feedback[200];
    printf("Please provide your feedback: ");
    getchar(); // Clear input buffer
    fgets(feedback, sizeof(feedback), stdin);

    FILE *file = fopen("feedbacks.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "Feedback: %s\n", feedback);
        fclose(file);
        printf(CYAN"Thank you for your feedback. It is valuable to us.\n", RESET_COLOR);
    }
    else
    {
        printf("Error: Could not open file to store feedback.\n");
    }
}

void employeeLogin()
{
    char password[100];
    char name[100];
    printf("Enter Employee name: ");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", password);
    if (empStore(name, password))
    {
        printf (GREEN"Login Successful\n"RESET_COLOR);
        int choice;
        do
        {
            printf(BLUE "\t\t\t\t+------------------------------------------------------+\n" RESET_COLOR);
            printf(BLUE "\t\t\t\t|                   " BOLD "Employee Menu" RESET_COLOR BLUE "                       |\n" RESET_COLOR);
            printf(BLUE "\t\t\t\t+------------------------------------------------------+\n" RESET_COLOR);
            printf("\t\t\t\t| 1. Add Account                                       |\n");
            printf("\t\t\t\t| 2. Check Report                                      |\n");
            printf("\t\t\t\t| 3. Check Feedback                                    |\n");
            printf("\t\t\t\t| 4. Check Interest                                    |\n");
            printf("\t\t\t\t| 5. Exit                                              |\n");
            printf(BLUE "\t\t\t\t+------------------------------------------------------+\n" RESET_COLOR);
            printf("\t\t\t\tEnter your choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                createAccount();
                break;
            case 2:
                readReports();
                break;
            case 3:
                readFeedbacks();
                break;
            case 4:
                checkInterest();
                break;
            case 5:
                printf(GREEN "Exiting employee menu...\n" RESET_COLOR);
                break;
            default:
                printf(RED "Invalid choice, please try again.\n" RESET_COLOR);
            }
        }
        while (choice != 5);
    }
    else
    {
        printf (RED"Try Again With Valid Information\n"RESET_COLOR);
    }
}
int empStore(const char *employeename, const char *password)
{
    FILE *file;
    file = fopen("employee.txt", "r");
    if (file != NULL)
    {
        char name[100];
        char pass[20];
        while (fscanf(file, "Name: %s\nPassword: %s\n", name, pass) != EOF)
        {
            if (strcmp(name, employeename) == 0 && strcmp(pass, password) == 0)
            {
                fclose(file);
                return 1; // Login successful
            }
        }
        fclose(file);
    }
    return 0; // Login failed
}
int createAccount()
{
    Customer newCustomer;
    printf("Enter customer name: ");
    scanf(" %s", newCustomer.name);

    printf("Enter phone number: ");
    scanf("%s", newCustomer.phoneNumber);

    printf("Enter date of birth (dd-mm-yyyy): ");
    scanf("%s", newCustomer.dob);

    printf("Enter login password: ");
    scanf("%s", newCustomer.password);

    newCustomer.accountId = generateAccountNumber();
    newCustomer.balance = 0.0;

    storeAccount(newCustomer);

    printf(GREEN "Account created successfully!\n" RESET_COLOR);
    printf("Your Account Number: %d\n", newCustomer.accountId);

    return newCustomer.accountId;
}
void readReports()
{
    FILE *file = fopen("problem_reports.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file to read problem reports.\n");
        return;
    }

    char line[256];
    printf("Problem Reports:\n");
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    fclose(file);
}
void readFeedbacks()
{
    FILE *file = fopen("feedbacks.txt", "r");
    if (file == NULL)
    {
        printf(RED"Error: Could not open file to read problem reports.\n"RESET_COLOR);
        return;
    }

    char line[256];
    printf("Feedbacks:\n");
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    fclose(file);
}

float calculateMonthlyInterest(float balance)
{
    float annualInterestRate = 3.0; // 3% per annum
    float monthlyInterestRate = annualInterestRate / 12.0;
    return balance * (monthlyInterestRate / 100.0);
}
void checkInterest()
{
    int accountId;
    Customer customer;

    printf("Enter the Account ID to check: ");
    scanf("%d", &accountId);

    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf(RED "Error opening file.\n" RESET_COLOR);
        return;
    }

    int found = 0;
    while (fscanf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %f\n\n",
                  &customer.accountId, customer.name, customer.phoneNumber,
                  customer.dob, customer.password, &customer.balance) != EOF)
    {
        if (customer.accountId == accountId)
        {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found)
    {
        printf(GREEN "Account found.\n" RESET_COLOR);
        printf("Account ID: %d\n", customer.accountId);
        printf("Name: %s\n", customer.name);
        printf("Balance: $%.2f\n", customer.balance);

        float interest = calculateMonthlyInterest(customer.balance);
        printf("Monthly Interest: $%.2f\n", interest);
    }
    else
    {
        printf(RED "Account ID not found.\n" RESET_COLOR);
    }
}
void adminLogin()
{
    char name[100], password[20];
    printf("Enter Admin name: ");
    scanf("%s", name);
    printf("Enter password: ");
    scanf("%s", password);
    if(adminStore(name, password))
    {
        printf(GREEN "Login Successful. Welcome Admin %s\n" RESET_COLOR,name);

        int choice;
        do
        {
            printf(MAGENTA "\t\t\t\t+------------------------------------------------------+\n" RESET_COLOR);
            printf(MAGENTA "\t\t\t\t|                  " BOLD " Admin Menu " RESET_COLOR MAGENTA "                        |\n" RESET_COLOR);
            printf(MAGENTA "\t\t\t\t+------------------------------------------------------+\n" RESET_COLOR);
            printf("\t\t\t\t| 1. View Regular Activities                           |\n");
            printf("\t\t\t\t| 2. Delete Account                                    |\n");
            printf("\t\t\t\t| 3. Bank Balance                                      |\n");
            printf("\t\t\t\t| 4. Reset Bank System                                 |\n");
            printf("\t\t\t\t| 5. Exit                                              |\n");
            printf(MAGENTA "\t\t\t\t+------------------------------------------------------+\n" RESET_COLOR);
            printf("\t\t\t\tEnter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                printf("Option 1: View Regular Activities\n");
                activities();
                break;
            case 2:
                printf("Option 2: Delete Account\n");
                deleteAccount();
                break;
            case 3:
                printf("Option 3: Bank Balance\n");
                bankBalance();
                break;
            case 4:
                printf("Option 4: Reset Bank system\n");
                resetBankSystem();
                break;
            case 5:
                printf(BLUE "Exiting admin menu...\n" RESET_COLOR);
                break;
            default:
                printf(RED "Invalid choice, please try again.\n" RESET_COLOR);
            }
        }
        while (choice != 5);
    }
    else
    {
        printf(RED "Login failed. Invalid credentials.\n" RESET_COLOR);
    }
}

int adminStore(const char adminname[200], const char password[20])
{
    FILE *file;
    file = fopen("admin.txt", "r");
    if (file != NULL)
    {
        char name[100];
        char pass[20];
        while (fscanf(file, "Name: %s\nPassword: %s\n", name, pass) != EOF)
        {
            if (strcmp(name, adminname) == 0 && strcmp(pass, password) == 0)
            {
                fclose(file);
                return 1; // Login successful
            }
        }
        fclose(file);
    }
    return 0; // Login failed
}
void activities()
{

    system("cls");
    FILE *file= fopen("userdata.txt", "r");
    char c = fgetc(file);
    if (c == EOF)
    {
        printf(CYAN "TRANSACTION DETAILS\n" RESET_COLOR);
        printf("\n**NO RECENT TRANSACTION\n");
    }
    else
    {
        printf(CYAN"TRANSACTION DETAILS\n" RESET_COLOR);
        while (c != EOF) // EOF=End of file
        {
            printf("%c", c);
            c = fgetc(file);
        }
    }
}
void deleteAccount(int accountIdToDelete)
{
    printf("Enter your account Number: ");
    scanf("%d", &accountIdToDelete);
    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf(RED "Error: Could not open userdata.txt file.\n" RESET_COLOR);
        return;
    }

    FILE *tempFile = fopen("temp_userdata.txt", "w");
    if (tempFile == NULL)
    {
        printf(RED "Error: Could not open temporary file.\n" RESET_COLOR);
        fclose(file);
        return;
    }

    Customer tempCustomer;
    int found = 0;

    while (fscanf(file, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %f\n\n",
                  &tempCustomer.accountId, tempCustomer.name, tempCustomer.phoneNumber,
                  tempCustomer.dob, tempCustomer.password, &tempCustomer.balance) != EOF)
    {
        if (tempCustomer.accountId == accountIdToDelete)
        {
            found = 1;
            continue; // Skip writing this record to the temp file
        }
        fprintf(tempFile, "User Bank ID: %d\nName: %s\nPhone Number: %s\nDate of Birth: %s\nPassword: %s\nBalance: %.2f\n\n",
                tempCustomer.accountId, tempCustomer.name, tempCustomer.phoneNumber,
                tempCustomer.dob, tempCustomer.password, tempCustomer.balance);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("userdata.txt");
        rename("temp_userdata.txt", "userdata.txt");
        printf(GREEN "Account ID %d has been successfully deleted.\n" RESET_COLOR,accountIdToDelete);
    }
    else
    {
        remove("temp_userdata.txt");
        printf("Account ID %d not found.\n", accountIdToDelete);
    }
}
void bankBalance()
{
    float totalBalance = 0.0;
    FILE *file = fopen("userdata.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (!feof(file))
    {
        Customer customer;
        fscanf(file, "User Bank ID: %d\nName: %*s\nPhone Number: %*s\nDate of Birth: %*s\nPassword: %*s\nBalance: %f\n\n", &customer.accountId, &customer.balance);
        totalBalance += customer.balance;
    }

    fclose(file);

    printf(GREEN "Total bank balance: $%.2f\n" RESET_COLOR, totalBalance);
}

void resetBankSystem()
{
    char confirmation;
    printf("Resetting the bank system will clear all data. Are you sure? (Y/N): ");
    scanf(" %c", &confirmation);

    if (confirmation == 'Y' || confirmation == 'y')
    {
        // Assuming you have functions to clear all data and reset the system
        clearAllData();
        printf(GREEN "Bank system reset successfully.\n"RESET_COLOR);
    }
    else
    {
        printf(RED "Reset operation cancelled.\n"RESET_COLOR);
    }
}
void clearAllData()
{
    // Clear customer data
    FILE *customerFile = fopen("userdata.txt", "w");
    if (customerFile != NULL)
    {
        fclose(customerFile);
    }
    else
    {
        printf("Error clearing customer data.\n");
    }
    // Clear employee data
    FILE *employeeFile = fopen("employee.txt", "w");
    if (employeeFile != NULL)
    {
        fclose(employeeFile);
    }
    else
    {
        printf("Error clearing employee data.\n");
    }
    // Clear admin data
    FILE *adminFile = fopen("admin.txt", "w");
    if (adminFile != NULL)
    {
        fclose(adminFile);
    }
    else
    {
        printf("Error clearing admin data.\n");
    }
    // Clear transaction data
    FILE *transactionFile = fopen("transactions.txt", "w");
    if (transactionFile != NULL)
    {
        fclose(transactionFile);
    }
    else
    {
        printf("Error clearing transaction data.\n");
    }
    // Reset last account number
    FILE *lastAccountFile = fopen("last_account_number.txt", "w");
    if (lastAccountFile != NULL)
    {
        fprintf(lastAccountFile, "%d", 0); // Reset to 0
        fclose(lastAccountFile);
    }
    else
    {
        printf("Error resetting last account number.\n");
    }
    printf("All data cleared successfully.\n");
}
