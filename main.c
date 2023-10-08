#include<stdio.h>
#include<conio.h>

struct user
{
	long long int phone;
	char password[30];
}u;

void header();
void login();
void menu(long long int);
void createacc();
void csupport(long long int);

void main()
{
	char input;
	
	header();
	
	printf("\n\nHomepage");
	printf("\n\n[1] Login");
	printf("\n[2] Create an Account");
	printf("\n[3] Exit");	
	
	tryagain:
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
			printf("\n\nThanks for trusting C-Bank Pro. Safe Banking, Safe Life!");
			getch();
			break;
			
		default:
			printf("\nError: Option not available");
			goto tryagain;
	}
}

void login()
{
	FILE *fptr;
	long long int phn;
	char pw[30];
	
	header();
		
	printf("\n\nLogin");
	printf("\n\nEnter your mobile number: +977 ");
	fflush(stdin);
	scanf("%lld", &phn);
	printf("Enter password: ");
	fflush(stdin);
	scanf("%s", pw);
	
	fptr = fopen("userlogin.txt", "r");
	
	while(&u, sizeof(u), 1, fptr)
	{
		if((u.phone==phn) && (strcmp(u.password,pw)==0))
		{
			menu(phn);
		}else
		{
			printf("\nUser not found");
		}
	}
	
	fclose(fptr);
}

void menu(long long int phn)
{
	char input;
	
	header();
		
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
			csupport(phn);
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

void csupport(long long int phn)
{
	char input;
	
	header();
		
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
		menu(phn);
	}else if(input == '2')
	{
		printf("\nThanks for trusting C-Bank Pro. Safe Banking, Safe Life!");
		getch();
	}else
	{
		printf("\nError: Option not available");
	}
}

void header()
{
	system("cls");
	printf("\t  C-BANK PRO");
	printf("\n\"Experience Banking, the PRO way\"");
	printf("\n=================================");
}

