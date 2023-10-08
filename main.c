#include<stdio.h>
#include<conio.h>

void homepage();
void csupport();

void main()
{
	homepage();
}

void homepage()
{
	char input;
	
	system("cls");
	printf("\t  C-BANK PRO");
	printf("\n\"Experience Banking, the PRO way\"");
	printf("\n=================================");
		
	printf("\n\nHomepage");
	printf("\n\n[1] Login");
	printf("\n[2] Create an Account");
	printf("\n[3] Deposit Cash");
	printf("\n[4] Withdraw Cash");
	printf("\n[5] Balance Inquiry");
	printf("\n[6] Transaction History");
	printf("\n[7] Customer Support");
	printf("\n[8] Exit");	
	
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
			break;
		
		case '6':
			break;
			
		case '7':
			csupport();
			break;
			
		case '8':
			printf("\nThanks for trusting C-Bank Pro. Safe Banking, Safe Life!");
			getch();
			break;
			
		default:
			printf("\nError: Option not available");
	}
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
	
	printf("\n\n[1] Homepage");
	printf("\n[2] Exit");
	printf("\n\nEnter your choice: ");
	fflush(stdin);
	input = getch();
	
	if(input =='1')
	{
		homepage();
	}else if(input == '2')
	{
		printf("\nThanks for trusting C-Bank Pro. Safe Banking, Safe Life!");
		getch();
	}else
	{
		printf("\nError: Option not available");
	}
}


