#pragma warning (disable : 4996) // program coded in Visual Studio 2015
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int authenticate(void);
void printMessage(void);
int viewAccount(void);
int addAccount(void);
int editAccount(void);
int deleteAccount(void);
int addBalance(void);
int withdrawMoney(void);
double totalBalance(void);
double maxBalance(void);
double minBalance(void);
double avgBalance(void);

typedef struct {
	int serial;
	char name[46];
	int account_number;
	char type[15];
	double balance;
} Account;

typedef struct {
	long long id;
	char password[50];
} User;

int main(void)
{
	int choice;

	while (!authenticate())
		continue;

	printMessage();
	scanf("%d", &choice);

	while (choice != 11)
	{
		switch (choice)
		{
		case 1:
			viewAccount();
			break;
		case 2 :
			addAccount();
			break;
		case 3:
			editAccount();
			break;
		case 4:
			deleteAccount();
			break;
		case 5:
			addBalance();
			break;
		case 6:
			withdrawMoney();
			break;
		case 7:
			totalBalance();
			break;
		case 8:
			maxBalance();
			break;
		case 9:
			minBalance();
			break;
		case 10:
			avgBalance();
			break;
		default:
			printf("Wrong choice entered.\n\n");
		}
		printMessage();
		scanf("%d", &choice);
	}

	printf("\n\nThank you!\n\n");
	return 0;
}





int authenticate(void)
{
	int userCount; // the number of employees who can access the program
	long long idNo; // the id number of the user who will access the program
	char pass[50]; // the password entered by the user
	int found = 0;
	int i, j;

	FILE *userFile = fopen("eligible.txt", "r");
	if (userFile == NULL)
	{
		printf("Cannot grant access to the customer accounts now.\n");
		return 0;
	}

	fscanf(userFile, "%d", &userCount);

	User *user = malloc(sizeof(User) * userCount);

	for (i = 0; i < userCount; i++)
		fscanf(userFile, "%lld %s", &user[i].id, user[i].password);

	printf("Enter your ID number: ");
	scanf("%lld", &idNo);
	for (i = 0; i < userCount; i++)
	{
		if (user[i].id == idNo)
		{
			j = i;
			found = 1;
		}
	}

	if (!found)
	{
		printf("You do not have the access to the customer accounts.\n\n");
		fclose(userFile);
		free(user);
		return 0;
	}

	printf("Enter your password: ");
	scanf("%s", pass);
	while (strcmp(pass, user[j].password))
	{
		printf("Wrong password entered.\n");
		printf("\nEnter your password: ");
		scanf("%s", pass);
	}
	printf("\nWelcome!\n\n");

	//clean up
	fclose(userFile);
	free(user);
	return 1;
}





void printMessage(void)
{
	printf("-------------------------------------------------------------------------\n\n");
	printf("Enter the number that designates the operation");
	printf(" you would like to perform.\n\n");
	printf("1. View account.\n");
	printf("2. Add new account.\n");
	printf("3. Edit existing account.\n");
	printf("4. Delete an account.\n");
	printf("5. Add money to an account.\n");
	printf("6. Withdraw money from an account.\n");
	printf("7. Find total balance of all accounts.\n");
	printf("8. Display max balance holder.\n");
	printf("9. Display min balance holder.\n");
	printf("10. Display average of balances.\n");
	printf("11. Exit.\n\n");
	printf("Now, enter choice: ");
}




int viewAccount(void)
{
	int accCount; // number of accounts
	int show; // the account number of the account to be shown
	int i;
	int found = 0;

	FILE *originalFile = fopen("masterfile.txt", "r");
	if (originalFile == NULL)
	{
		printf("Error!! File not found.");
		return -1;
	}

	fscanf(originalFile, "%*[A-Z a-z:] %d %*[^\n] %*[^\n]", &accCount);

	Account *accounts = malloc(sizeof(Account) * accCount);

	printf("Enter account number of the account you want to view: ");
	scanf("%d", &show);

	for (i = 0; i < accCount; i++)
	{
		fscanf(originalFile, "%d %45[A-Z a-z.] %d %s %lf", &accounts[i].serial, accounts[i].name,
			&accounts[i].account_number, accounts[i].type, &accounts[i].balance);

		if (accounts[i].account_number == show)
		{
			found = 1;
			break;
		}
	}

	if (found)
	{
		printf("\nAccount holder: %s\n", accounts[i].name);
		printf("Account number: %d\n", accounts[i].account_number);
		printf("Account type: %s\n", accounts[i].type);
		printf("Account balance: $%.2f\n\n", accounts[i].balance);
	}

	else
	{
		printf("\nNo such account exists.\n\n");
	}

	// clean up
	fclose(originalFile);
	free(accounts);

	return 1;
}





int addAccount(void)
{
	int accCount; // number of accounts
	char accCount_str[25]; // will read "Number of accounts: "
	char tbl_head_1[200];  // will contain the table headers
	char tbl_head_2[200];  // will contain the dashes
	int i;
	char response; // to check if the account is being created in the way wanted
	int field; // the field to be edited

	FILE *originalFile = fopen("masterfile.txt", "r");

	if (originalFile == NULL)
	{
		printf("Error!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%[A-Z a-z:] %d %[^\n] %[^\n]", accCount_str,  &accCount, tbl_head_1, tbl_head_2);

	Account *accounts = malloc(sizeof(Account) * (accCount + 1));

	for (i = 0; i < accCount; i++)
		fscanf(originalFile, "%d %45[A-Z a-z.] %d %s %lf", &accounts[i].serial, accounts[i].name,
			&accounts[i].account_number, accounts[i].type, &accounts[i].balance);

	printf("\nEnter new account holder's name: ");
	scanf("%*c %44[A-Z a-z.]", accounts[i].name);

	printf("Enter the account type: ");
	scanf("%s", accounts[i].type);

	printf("Enter balance: ");
	scanf("%lf", &accounts[i].balance);

	++accCount;
	accounts[i].account_number = accounts[i - 1].account_number + 1;
	accounts[i].serial = accCount;

	while(1)
	{
		printf("\nThe account is being created in this way-\n");
		printf("Account name: %s\n", accounts[i].name);
		printf("Account number: %d\n", accounts[i].account_number);
		printf("Account type: %s\n", accounts[i].type);
		printf("Account balance: $%.2f\n\n", accounts[i].balance);

		printf("Would you like to edit any field? ( y / n ): ");
		scanf(" %c", &response);

		if (response != 'y')
			break;

		printf("\nEnter the number designating the field you would like to edit.\n\n");
		printf("1. Name\n");
		printf("2. Account type\n");
		printf("3. Balance\n\n");
		printf("Now, enter choice: ");
		scanf("%d", &field);

		switch (field)
		{
		case 1:

			printf("\nEnter new name: ");
			scanf("%*c %44[^\n]", accounts[i].name);
			break;

		case 2:

			printf("\nEnter new account type: ");
			scanf("%*c %[^\n]", accounts[i].type);
			break;

		case 3:

			printf("\nEnter new balance: ");
			scanf("%lf", &accounts[i].balance);
			break;

		default:
			printf("\nWrong choice.\n");
		}
	}

	FILE *newFile = fopen("tempmaster.txt", "w");
	if (newFile == NULL)
	{
		printf("Error in adding account.\n\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	fprintf(newFile, "%s%d\n\n%s\n%s\n", accCount_str, accCount, tbl_head_1, tbl_head_2);
	for (i = 0; i < accCount; i++)
		fprintf(newFile, "%-6d  %-45s   %-12d    %-9s       %-15.2f\n", accounts[i].serial,
			accounts[i].name, accounts[i].account_number, accounts[i].type, accounts[i].balance);

	// clean up
	fclose(originalFile);
	fclose(newFile);
	free(accounts);

	// modification
	remove("masterfile.txt");
	rename("tempmaster.txt", "masterfile.txt");

	printf("Account added successfully.\n\n");

	return 1;
}





int editAccount(void)
{
	int accCount; // number of accounts
	char accCount_str[25]; // will read "Number of accounts: "
	char tbl_head_1[200];  // will contain the table headers
	char tbl_head_2[200];  // will contain the dashes
	int edit; // account number of the account to be edited
	char response; // to make sure the right account is being edited
	int choice; // to choose the field that has to be edited
	char repeat; // to decide if further editing is needed
	int i, j = -1;

	FILE *originalFile = fopen("masterfile.txt", "r");
	if (originalFile == NULL)
	{
		printf("Error!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%[A-Z a-z:] %d %[^\n] %[^\n]", accCount_str, &accCount, tbl_head_1, tbl_head_2);

	Account *accounts = malloc(sizeof(Account) * accCount);

	for (i = 0; i < accCount; i++)
		fscanf(originalFile, "%d %45[A-Z a-z.] %d %s %lf", &accounts[i].serial, accounts[i].name,
			&accounts[i].account_number, accounts[i].type, &accounts[i].balance);

	printf("Enter the account number of the account to be edited: ");
	scanf("%d", &edit);

	for (i = 0; i < accCount; i++)
	{
		if (accounts[i].account_number == edit)
		{
			j = i;
			break;
		}
	}

	if (j < 0)
	{
		printf("\nNo such account exists.\n\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	printf("\nCurrently, the account is stored in this way:\n");
	printf("Name: %s\n", accounts[j].name);
	printf("Account type: %s\n", accounts[j].type);
	printf("Balance:$ %.2f\n", accounts[j].balance);

	printf("\nIs this the account to be edited? ( y / n ): ");
	scanf(" %c", &response);

	if (response != 'y')
	{
		printf("\nNo account edited.\n\n");
		fclose(originalFile);
		free(accounts);
		return 1;
	}

	while (1)
	{
		printf("Enter the number designating the field you would like to edit.\n\n");
		printf("1. Name\n");
		printf("2. Account type\n");
		printf("3. Balance\n\n");
		printf("Now, enter choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:

			printf("Enter new name: ");
			scanf("%*c %44[^\n]", accounts[j].name);
			break;

		case 2:

			printf("Enter new account type: ");
			scanf("%*c %[^\n]", accounts[j].type);
			break;

		case 3:

			printf("Enter new balance: ");
			scanf("%lf", &accounts[j].balance);
			break;

		default:
			printf("Wrong choice.\n");
		}

		printf("\nThe edited account is stored in this way:\n");
		printf("Name: %s\n", accounts[j].name);
		printf("Account type: %s\n", accounts[j].type);
		printf("Balance: $%.2f\n", accounts[j].balance);

		printf("\nWould you like to edit more fields ( y / n )?\n");
		scanf(" %c", &repeat);

		if (repeat == 'n')
			break;
		else
			continue;
	}

	FILE *newFile = fopen("tempmaster.txt", "w");
	if (newFile == NULL)
	{
		printf("\nError in editing account.\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	fprintf(newFile, "%s%d\n\n%s\n%s\n", accCount_str, accCount, tbl_head_1, tbl_head_2);
	for (i = 0; i < accCount; i++)
		fprintf(newFile, "%-6d  %-45s   %-12d    %-9s       %-15.2f\n", accounts[i].serial,
			accounts[i].name, accounts[i].account_number, accounts[i].type, accounts[i].balance);

	// clean up
	fclose(originalFile);
	fclose(newFile);
	free(accounts);

	// modification
	remove("masterfile.txt");
	rename("tempmaster.txt", "masterfile.txt");

	printf("\nAccount edited successfully.\n\n");

	return 1;
}





int deleteAccount(void)
{
	int accCount; // number of accounts
	char accCount_str[25]; // will read "Number of accounts: "
	char tbl_head_1[200];  // will contain the table headers
	char tbl_head_2[200];  // will contain the dashes
	int del; // account number of the account to be deleted
	int i, j = -1;
	int serial;
	char response;

	FILE *originalFile = fopen("masterfile.txt", "r");
	if (originalFile == NULL)
	{
		printf("Error!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%[A-Z a-z:] %d %[^\n] %[^\n]", accCount_str, &accCount, tbl_head_1, tbl_head_2);

	Account *accounts = malloc(sizeof(Account) * accCount);

	for (i = 0; i < accCount; i++)
		fscanf(originalFile, "%d %45[A-Z a-z.] %d %s %lf", &accounts[i].serial, accounts[i].name,
			&accounts[i].account_number, accounts[i].type, &accounts[i].balance);

	printf("Enter the account number of the account to be deleted: ");
	scanf("%d", &del);

	for (i = 0; i < accCount; i++)
	{
		if (accounts[i].account_number == del)
		{
			j = i;
			break;
		}
	}

	if (j < 0)
	{
		printf("\nNo such account exists.\n\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	printf("\nAccount holder: %s\n", accounts[j].name);
	printf("Account number: %d\n", accounts[j].account_number);
	printf("Account type: %s\n", accounts[j].type);
	printf("Account balance: $%.2f\n\n", accounts[j].balance);

	printf("Is this the account to be deleted? ( y / n ): ");
	scanf(" %c", &response);

	if (response != 'y')
	{
		printf("No account deleted.\n\n");
		fclose(originalFile);
		free(accounts);
		return 1;
	}

	FILE *newFile = fopen("tempmaster.txt", "w");
	if (newFile == NULL)
	{
		printf("Error in deleting account.\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	accCount--; // Since the number of accounts has just decreased by one
	fprintf(newFile, "%s%d\n\n%s\n%s\n", accCount_str, accCount, tbl_head_1, tbl_head_2);
	for (i = 0, serial = 1; i <= accCount; i++)
	{
		if (i != j)
		{
			fprintf(newFile, "%-6d  %-45s   %-12d    %-9s       %-15.2f\n", serial++,
				accounts[i].name, accounts[i].account_number, accounts[i].type, accounts[i].balance);
		}
	}

	// clean up
	fclose(originalFile);
	fclose(newFile);
	free(accounts);

	// modification
	remove("masterfile.txt");
	rename("tempmaster.txt", "masterfile.txt");

	printf("Account deleted successfully.\n\n");

	return 1;
}





int addBalance(void)
{
	int accCount; // number of accounts
	char accCount_str[25]; // will read "Number of accounts: "
	char tbl_head_1[200];  // will contain the table headers
	char tbl_head_2[200];  // will contain the dashes
	int edit; // account number of the account to which money is to be added
	char response; // to make sure the right account is selected and right amount of money was added
	double amount; // the amount of money that is to be added
	int i, j = -1;

	FILE *originalFile = fopen("masterfile.txt", "r");
	if (originalFile == NULL)
	{
		printf("Error!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%[A-Z a-z:] %d %[^\n] %[^\n]", accCount_str, &accCount, tbl_head_1, tbl_head_2);

	Account *accounts = malloc(sizeof(Account) * accCount);

	for (i = 0; i < accCount; i++)
		fscanf(originalFile, "%d %45[A-Z a-z.] %d %s %lf", &accounts[i].serial, accounts[i].name,
			&accounts[i].account_number, accounts[i].type, &accounts[i].balance);

	printf("\nEnter the account number of the account to which money is to be added: ");
	scanf("%d", &edit);

	for (i = 0; i < accCount; i++)
	{
		if (accounts[i].account_number == edit)
		{
			j = i;
			break;
		}
	}

	if (j < 0)
	{
		printf("\nNo such account exists.\n\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	printf("\nCurrently, the account is stored in this way:\n");
	printf("Name: %s\n", accounts[j].name);
	printf("Account type: %s\n", accounts[j].type);
	printf("Balance: $%.2f\n\n", accounts[j].balance);

	printf("Is this the right account? ( y / n ): ");
	scanf(" %c", &response);

	if (response != 'y')
	{
		printf("\nNo changes were made.\n\n");
		fclose(originalFile);
		free(accounts);
		return 1;
	}

	do {
		printf("\nEnter the amount of money to be added: ");
		scanf("%lf", &amount);
		printf("\nDo you want to add $%.2f? ( y / n ): ", amount);
		scanf(" %c", &response);
	} while (response != 'y');

	accounts[j].balance += amount;

	FILE *newFile = fopen("tempmaster.txt", "w");
	if (newFile == NULL)
	{
		printf("\nError in saving changes.\n\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	fprintf(newFile, "%s%d\n\n%s\n%s\n", accCount_str, accCount, tbl_head_1, tbl_head_2);
	for (i = 0; i < accCount; i++)
		fprintf(newFile, "%-6d  %-45s   %-12d    %-9s       %-15.2f\n", accounts[i].serial,
			accounts[i].name, accounts[i].account_number, accounts[i].type, accounts[i].balance);

	printf("\nAfter adding balance, the account is stored in this way:\n");
	printf("Name: %s\n", accounts[j].name);
	printf("Account type: %s\n", accounts[j].type);
	printf("Balance: $%.2f\n\n", accounts[j].balance);

	// clean up
	fclose(originalFile);
	fclose(newFile);
	free(accounts);

	// modification
	remove("masterfile.txt");
	rename("tempmaster.txt", "masterfile.txt");

	return 1;
}




int withdrawMoney(void)
{
	int accCount; // number of accounts
	char accCount_str[25]; // will read "Number of accounts: "
	char tbl_head_1[200];  // will contain the table headers
	char tbl_head_2[200];  // will contain the dashes
	int edit; // account number of the account from which money is to be withdrawn
	char response; // to make sure the right account is selected and the right amount of money is being withdrawn
	double amount; // the amount of money to be withdrawn
	int i, j = -1;

	FILE *originalFile = fopen("masterfile.txt", "r");
	if (originalFile == NULL)
	{
		printf("\nError!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%[A-Z a-z:] %d %[^\n] %[^\n]", accCount_str, &accCount, tbl_head_1, tbl_head_2);

	Account *accounts = malloc(sizeof(Account) * accCount);

	for (i = 0; i < accCount; i++)
		fscanf(originalFile, "%d %45[A-Z a-z.] %d %s %lf", &accounts[i].serial, accounts[i].name,
			&accounts[i].account_number, accounts[i].type, &accounts[i].balance);

	printf("\nEnter the account number of the account from which money is to be withdrawn: ");
	scanf("%d", &edit);

	for (i = 0; i < accCount; i++)
	{
		if (accounts[i].account_number == edit)
		{
			j = i;
			break;
		}
	}

	if (j < 0)
	{
		printf("\nNo such account exists.\n\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	printf("\nCurrently, the account is stored in this way:\n");
	printf("Name: %s\n", accounts[j].name);
	printf("Account type: %s\n", accounts[j].type);
	printf("Balance: $%.2f\n", accounts[j].balance);

	printf("\nIs this the right account? ( y / n ): ");
	scanf(" %c", &response);

	if (response != 'y')
	{
		printf("No changes were made.\n\n");
		fclose(originalFile);
		free(accounts);
		return 1;
	}

	do {
		printf("\nEnter the amount of money to be withdrawn: ");
		scanf("%lf", &amount);
		printf("\nDo you want to withdraw $%.2f? ( y / n ): ", amount);
		scanf(" %c", &response);
	} while (response != 'y');

	accounts[j].balance -= amount;

	FILE *newFile = fopen("tempmaster.txt", "w");
	if (newFile == NULL)
	{
		printf("\nError in saving changes.\n");
		fclose(originalFile);
		free(accounts);
		return -1;
	}

	fprintf(newFile, "%s%d\n\n%s\n%s\n", accCount_str, accCount, tbl_head_1, tbl_head_2);
	for (i = 0; i < accCount; i++)
		fprintf(newFile, "%-6d  %-45s   %-12d    %-9s       %-15.2f\n", accounts[i].serial,
			accounts[i].name, accounts[i].account_number, accounts[i].type, accounts[i].balance);

	printf("\nAfter withdrawing money, the account is stored in this way:\n");
	printf("Name: %s\n", accounts[j].name);
	printf("Account type: %s\n", accounts[j].type);
	printf("Balance: $%.2f\n\n", accounts[j].balance);

	// clean up
	fclose(originalFile);
	fclose(newFile);
	free(accounts);

	// modification
	remove("masterfile.txt");
	rename("tempmaster.txt", "masterfile.txt");

	return 1;
}



double totalBalance(void)
{
	int accCount; // number of accounts
	int i;
	double total = 0;

	FILE *originalFile = fopen("masterfile.txt", "r");

	if (originalFile == NULL)
	{
		printf("\nError!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%*[A-Z a-z:] %d %*[^\n] %*[^\n]", &accCount);
	Account *accounts = malloc(sizeof(Account) * accCount);

	for (i = 0; i < accCount; i++)
	{
		fscanf(originalFile, "%*d %*[A-Z a-z.] %*d %*s %lf", &accounts[i].balance);
		total += accounts[i].balance;
	}

	printf("\nThe total balance of all accounts is $%.2f\n\n", total);

	// clean up
	fclose(originalFile);
	free(accounts);

	return total;
}





double maxBalance(void)
{
	double max;
	int i, j;
	int accCount; // number of accounts

	FILE *originalFile = fopen("masterfile.txt", "r");
	if (originalFile == NULL)
	{
		printf("\nError!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%*[A-Z a-z:] %d %*[^\n] %*[^\n]", &accCount);

	Account *accounts = malloc(sizeof(Account) * accCount);

	for (i = 0; i < accCount; i++)
	{
		fscanf(originalFile, "%*d %45[A-Z a-z.] %d %*s %lf", accounts[i].name,
			&accounts[i].account_number, &accounts[i].balance);
	}

	for (i = 0, j = 0, max = accounts[i].balance; i < accCount; i++)
	{
		if (accounts[i].balance > max)
		{
			max = accounts[i].balance;
			j = i;
		}
	}

	printf("\nAccount no. %d has the maximum balance of $%.2lf\n", accounts[j].account_number, accounts[j].balance);
	printf("The ownwer of that account is %s\n\n", accounts[j].name);

	// clean up
	fclose(originalFile);
	free(accounts);

	return max;
}





double minBalance(void)
{
	double min;
	int i, j;
	int accCount; // number of accounts

	FILE *originalFile = fopen("masterfile.txt", "r");
	if (originalFile == NULL)
	{
		printf("\nError!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%*[A-Z a-z:] %d %*[^\n] %*[^\n]", &accCount);

	Account *accounts = malloc(sizeof(Account) * accCount);

	for (i = 0; i < accCount; i++)
	{
		fscanf(originalFile, "%*d %45[A-Z a-z.] %d %*s %lf", accounts[i].name,
			&accounts[i].account_number, &accounts[i].balance);
	}

	for (i = 0, j = 0, min = accounts[i].balance; i < accCount; i++)
	{
		if (accounts[i].balance < min)
		{
			min = accounts[i].balance;
			j = i;
		}
	}

	printf("\nAccount no. %d has the minimum balance of $%.2lf\n", accounts[j].account_number, accounts[j].balance);
	printf("The ownwer of that account is %s\n\n", accounts[j].name);

	// clean up
	fclose(originalFile);
	free(accounts);

	return min;
}





double avgBalance(void)
{
	int accCount; // number of accounts
	int i;
	double total = 0;
	double average;

	FILE *originalFile = fopen("masterfile.txt", "r");
	if (originalFile == NULL)
	{
		printf("\nError!! File not found.\n\n");
		return -1;
	}

	fscanf(originalFile, "%*[A-Z a-z:] %d %*[^\n] %*[^\n]", &accCount);

	Account *accounts = malloc(sizeof(Account) * accCount);

	for (i = 0; i < accCount; i++)
	{
		fscanf(originalFile, "%*d %*[A-Z a-z.] %*d %*s %lf", &accounts[i].balance);
		total += accounts[i].balance;
	}
	average = total / (double)accCount;
	printf("\nThe average of the balances is $%.2f\n\n", average);

	// clean up
	fclose(originalFile);
	free(accounts);

	return average;
}
