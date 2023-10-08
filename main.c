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
	int input;
	
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
	char home;
	
	system("cls");
	printf("\t  C-BANK PRO");
	printf("\n\"Experience Banking, the PRO way\"");
	printf("\n=================================");
		
	printf("\n\nCustomer Support");
	printf("\nAvailable 24/7 in 365 Days");
	printf("\n\nHotline: +977-1-2345678");
	printf("\nToll-Free: 1660-1-2345678");
	printf("\nPhone: +977-9845685245");
	
	printf("\n\nEnter H to go to HOMEPAGE: ");
	fflush(stdin);
	home = getch();
	
	if(home =='h' || home == 'H')
	{
		homepage();
	}else
	{
		printf("Invalid Input");
		getch();
	}
}


