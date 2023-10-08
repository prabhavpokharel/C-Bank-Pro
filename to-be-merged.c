#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

#define MAX_PASSWORD_LENGTH 20

struct account{
	char firstname[100],lastname[100],password[MAX_PASSWORD_LENGTH];
	long long int phoneno;
};

void login();
void logpassword(struct account);
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
	struct account a;
	
	printf("\n\nEnter first name: ");
	fflush(stdin);
	scanf("%s",a.firstname);
	
	printf("\nEnter last name: ");
	fflush(stdin);
	scanf("%s",a.lastname);
	
	printf("\nEnter Mobile No.: ");
	scanf("%lld",&a.phoneno);
	
	logpassword(a);
}

void logpassword(struct account a)
{
	FILE *fp;
	int i=0,j=0;
	char finalpw[MAX_PASSWORD_LENGTH],ch;
	
	fp=fopen("accounts.bin","wb");
	
	printf("\nEnter password: ");
	
	while (1) 
	{
        ch = getch();
        if (ch == 13)
		{
            break;
        }
		else if (ch == 8 || ch == 127)
		{
            if (i > 0)
			{
                i--;
                printf("\b \b");
            }
        }
		else if (!isspace(ch)) 
		{
            if (i < MAX_PASSWORD_LENGTH - 1)
			{
                putchar('*');
                a.password[i] = ch;
                i++;
            } 
			else
			{
				
            }
        }
    }
    a.password[i] = '\0';
	
	printf("\nConfirm password: ");
	while (1) 
	{
        ch = getch();
        if (ch == 13)
		{
            break;
        }
		else if (ch == 8 || ch == 127)
		{
            if (j > 0)
			{
                j--;
                printf("\b \b");
            }
        }
		else if (!isspace(ch)) 
		{
            if (j < MAX_PASSWORD_LENGTH - 1)
			{
                putchar('*');
                finalpw[j] = ch;
                j++;
            } 
			else
			{
				
            }
        }
    }
    finalpw[j] = '\0';
	
	if(strcmp(a.password,finalpw)!=0)
	{
		printf("\n\nPasswords do not match. Please try again");
		fclose(fp);
		logpassword(a);
	}
	else
	{
		fwrite(&a,sizeof(a),1,fp);
		fclose(fp);
		printf("\n\nRedirecting to login page...");
		sleep(1);
		system("cls");
		login(a);
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
