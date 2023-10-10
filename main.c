#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX_PASSWORD_LENGTH 30

struct account{
	char firstname[100], lastname[100], password[MAX_PASSWORD_LENGTH];
	long long int phone;
	double balance;
};

void header();
void login();
void logpassword(struct account);
void menu(struct account);
void withdraw(struct account *);
void createacc();
void balanceInq(struct account);
void deposit(struct account *);
void csupport(struct account);
void exitMessage();

void main()
{
	char choice;
	
	header();
	
	printf("Homepage");
	printf("\n\n[1] Login");
	printf("\n[2] Create an Account");
	printf("\n[3] Exit");	
	
	printf("\n\nEnter your choice: ");
	fflush(stdin);
	choice = getch();
	
	switch(choice)
	{
		case '1':
			login();
			break;
			
		case '2':
			createacc();
			break;
			
		case '3':
			exitMessage();
			break;
			
		default:
			main();
	}
}

void login()
{
    FILE *fptr;
    int j = 0;
    long long int phn;
    char pw[MAX_PASSWORD_LENGTH], ch;
    struct account a;

    header();

    printf("Login");
    printf("\n\nEnter your mobile number: +977 ");
    fflush(stdin);
    scanf("%lld", &phn);
    printf("Enter password: ");
    fflush(stdin);
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
                pw[j] = ch;
                j++;
            }
            else
            {
                
            }
        }
    }
    pw[j] = '\0';

    fptr = fopen("accounts.bin", "rb");

    int userFound = 0; 

    while (fread(&a, sizeof(struct account), 1, fptr) != 0)
    {
        if ((a.phone == phn) && (strcmp(a.password, pw) == 0))
        {
            menu(a);
            userFound = 1; 
            break; 
        }
    }

    fclose(fptr);

    if (!userFound)
    {
        printf("\n\nUser not found.");
        sleep(1);
        
        printf("\n[1] Retry Login");
        printf("\n[2] Homepage");
        printf("\n\nEnter your choice: ");
        fflush(stdin);
        char choice = getch();
        if (choice == '1')
        {
            login(); 
        }
        else if (choice == '2')
        {
            main(); 
        }
    }
}

void menu(struct account a)
{
	char choice;
	
	header();
		
	printf("Welcome %s,", a.firstname);
	printf("\n\n[1] Deposit Cash");
	printf("\n[2] Withdraw Cash");
	printf("\n[3] Balance Inquiry");
	printf("\n[4] Transaction History");
	printf("\n[5] Customer Support");
	printf("\n[6] Exit");	
	
	printf("\n\nEnter your choice: ");
	fflush(stdin);
	choice = getch();
	
	switch(choice)
	{
		case '1':
			deposit(&a);
			break;
			
		case '2':
			withdraw(&a);
			break;
			
		case '3':
			balanceInq(a);
			break;
			
		case '4':
			break;
			
		case '5':
			csupport(a);
			break;			
			
		case '6':
			exitMessage();
			break;
			
		default:
			menu(a);
	}
}

void createacc()
{
	struct account a;
	
	header();
	
	printf("Enter first name: ");
	fflush(stdin);
	scanf("%s",a.firstname);
	
	printf("Enter last name: ");
	fflush(stdin);
	scanf("%s",a.lastname);
	
	printf("Enter Mobile No.: ");
	scanf("%lld",&a.phone);
	
	a.balance = 0.0;
	
	logpassword(a);
}

void logpassword(struct account a)
{
	FILE *fp;
	int i=0,j=0;
	char finalpw[MAX_PASSWORD_LENGTH],ch;
	
	fp=fopen("accounts.bin","ab");
	
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
		login();
	}
}

void balanceInq(struct account a)
{
	header();
	
	char choice;
	
	printf("Available Balance: %lf", a.balance);
	
	printf("\n\n[1] Back");
	printf("\n[2] Exit");
	printf("\n\nEnter your choice: ");
	fflush(stdin);
	choice = getch();
	
	if(choice =='1')
	{
		menu(a);
	}else if(choice == '2')
	{
		exitMessage();
	}else
	{
		balanceInq(a);
	}
}

void deposit(struct account *a)
{
	FILE *fptr;
	header();
	int amount;
	
	printf("Enter the amount you want to deposit: ");
	scanf("%d", &amount);
	
	a->balance += (double)amount;
	
	fptr = fopen("accounts.bin", "rb+");

    fseek(fptr, 0L, SEEK_CUR);

    fwrite(a, sizeof(struct account), 1, fptr);
    fclose(fptr);
	
	printf("Your amount has been successfully deposited!");
	sleep(1);
	
	balanceInq(*a);
}

void withdraw(struct account *a)
{
	FILE *fptr;
	header();
	int amount;
	
	amountinput:
	printf("Enter the amount you want to withdraw: ");
	scanf("%d", &amount);
	
	if((double)amount>a->balance)
	{
		printf("\n\nThe entered amount exceeds your bank balance. Please try again.");
		sleep(1);
		system("cls");
		header();
		goto amountinput;
	}
	
	a->balance -= (double)amount;
	
	fptr = fopen("accounts.bin", "rb+");

    fseek(fptr, 0L, SEEK_CUR);

    fwrite(a, sizeof(struct account), 1, fptr);
    fclose(fptr);
	
	printf("Your amount has been successfully withdrawn!");
	sleep(1);
	
	balanceInq(*a);
}

void csupport(struct account a)
{
	char choice;
	
	header();
		
	printf("Customer Support - Available 24/7 in 365 Days");
	printf("\n\nHotline: +977-1-2345678");
	printf("\nToll-Free: 1660-1-2345678");
	printf("\nPhone: +977-9845685245");
	printf("\nEmail: suppport@example.com");
	
	printf("\n\n[1] Back");
	printf("\n[2] Exit");
	printf("\n\nEnter your choice: ");
	fflush(stdin);
	choice = getch();
	
	if(choice =='1')
	{
		menu(a);
	}else if(choice == '2')
	{
		exitMessage();
	}else
	{
		csupport(a);
	}
}

void header()
{
	system("cls");
	printf("\t  C-BANK PRO");
	printf("\n\"Experience Banking, the PRO way\"");
	printf("\n=================================\n\n");
}

void exitMessage()
{
	header();
	
	printf("Thanks for trusting C-Bank Pro. Safe Banking, Safe Life.");
	sleep(1);
	exit(1);
}
