#include<stdio.h>
#include<conio.h>

void login();
void menu();
void createacc();
void csupport();

void main()
{
	char input;
	
	system("cls");
	printf("\t  C-BANK PRO");
	printf("\n\"Experience Banking, the PRO way\"");
	printf("\n=================================");
		
	printf("\n\nHomepage");
	printf("\n\n[1] Login");
	printf("\n[2] Create an Account");
	printf("\n[3] Exit");	
	
	printf("\n\nEnter your choice: ");
	fflush(stdin);
	input = getch();
	
	switch(input)
	{
		case '1':
			login();
			break;
			
		case '2':
			createacc();
			break;
			
		case '3':
			printf("\nThanks for trusting C-Bank Pro. Safe Banking, Safe Life!");
			getch();
			break;
			
		default:
			printf("\nError: Option not available");
	}
}

void login()
{
	
}

void menu()
{
	char input;
	
	system("cls");
	printf("\t  C-BANK PRO");
	printf("\n\"Experience Banking, the PRO way\"");
	printf("\n=================================");
		
	printf("\n\nWelcome usersName,");
	printf("\n[1] Deposit Cash");
	printf("\n[2] Withdraw Cash");
	printf("\n[3] Balance Inquiry");
	printf("\n[4] Transaction History");
	printf("\n[5] Customer Support");
	printf("\n[6] Exit");	
	
	printf("\n\nEnter your choice: ");
	fflush(stdin);
	input = getch();
	
	switch(input)
	{
		case '1':
			break;
			
		case '2':
			break;
			
		case '3':
			break;
			
		case '4':
			break;
			
		case '5':
			csupport();
			break;			
			
		case '6':
			printf("\nThanks for trusting C-Bank Pro. Safe Banking, Safe Life!");
			getch();
			break;
			
		default:
			printf("\nError: Option not available");
	}
}

void createacc()
{
	
}

void csupport()
{
	char input;
	
	system("cls");
	printf("\t  C-BANK PRO");
	printf("\n\"Experience Banking, the PRO way\"");
	printf("\n=================================");
		
	printf("\n\nCustomer Support - Available 24/7 in 365 Days");
	printf("\n\nHotline: +977-1-2345678");
	printf("\nToll-Free: 1660-1-2345678");
	printf("\nPhone: +977-9845685245");
	printf("\nEmail: suppport@example.com");
	
	printf("\n\n[1] Back");
	printf("\n[2] Exit");
	printf("\n\nEnter your choice: ");
	fflush(stdin);
	input = getch();
	
	if(input =='1')
	{
		menu();
	}else if(input == '2')
	{
		printf("\nThanks for trusting C-Bank Pro. Safe Banking, Safe Life!");
		getch();
	}else
	{
		printf("\nError: Option not available");
	}
}


