#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<windows.h>

#define MAX_PASSWORD_LENGTH 30
#define MAX_TRANSACTION_LIMIT 100

struct trnhistory{
	int depo, with;
};

struct account{
	char firstname[100], lastname[100], password[MAX_PASSWORD_LENGTH];
	long long int phone;
	struct trnhistory t[MAX_TRANSACTION_LIMIT];
	double balance;
};

void header();
void login();
void logpassword(struct account);
void menu(struct account);
void withdraw(struct account *);
void createacc();
void history(struct account *,int,int);
void balanceInq(struct account);
void deposit(struct account *);
void transfer(struct account *);
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
    char pw[MAX_PASSWORD_LENGTH], ch, filename[60];
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
    
    sprintf(filename, "%lld.bin", phn);

    fptr = fopen(filename, "rb");

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
	printf("\n[5] Transfer");
	printf("\n[6] Customer Support");
	printf("\n[7] Exit");	
	
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
			transfer(&a);
			break;
			
		case '6':
			csupport(a);
			break;			
			
		case '7':
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
	char finalpw[MAX_PASSWORD_LENGTH], ch, filename[60];
	
	sprintf(filename, "%lld.bin", a.phone);
	
	fp = fopen(filename,"ab");
	
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
	char filename[60];
	
	sprintf(filename, "%lld.bin", a->phone);
	
	printf("Enter the amount you want to deposit: ");
	scanf("%d", &amount);
	history(a,0,amount);
	a->balance += (double)amount;
	
	fptr = fopen(filename, "rb+");

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
	char filename[60];
	
	sprintf(filename, "%lld.bin", a->phone);
	
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
	history(a,1,amount);
	a->balance -= (double)amount;
	
	fptr = fopen(filename, "rb+");

    fseek(fptr, 0L, SEEK_CUR);

    fwrite(a, sizeof(struct account), 1, fptr);
    fclose(fptr);
	
	printf("Your amount has been successfully withdrawn!");
	sleep(1);
	
	balanceInq(*a);
}

void history(struct account *a, int n, int amount)
{
	int i=0;
	if(n==0)
	{
		while(i<MAX_TRANSACTION_LIMIT)
		{
			if (a->t[i].depo==0)
        	{
            	a->t[i].depo = amount;
            	break;
        	}
        	i++;
		}
	}
	else if(n==1)
	{
		while(i<MAX_TRANSACTION_LIMIT)
		{
			if (a->t[i].with==0)
        	{
            	a->t[i].with = amount;
            	break;
        	}
        	i++;
		}
	}
}

void transfer(struct account *a)
{
	FILE *fptr1, *fptr2;
	struct account b;
	char filename[60];
	long long int phn;
	double amount;
	
	header();
	
	sprintf(filename, "%lld.bin", a->phone);
	
	printf("Transfer from +977 %lld", a->phone);
	printf("\n\nEnter Receiver's Mobile Number: +977 ");
	scanf("%lld", &phn);
	
	amountinput:
	printf("Enter transfer amount: ");
	scanf("%lf", &amount);
	
	if(amount>a->balance)
	{
		printf("\n\nThe entered amount exceeds your bank balance. Please try again.");
		sleep(1);
		header();
		goto amountinput;
	}
	
	a->balance -= amount;
	
	fptr1 = fopen(filename, "rb+");
    
	fseek(fptr1, 0L, SEEK_CUR);
    fwrite(a, sizeof(struct account), 1, fptr1);
    
	fclose(fptr1);
	
	sprintf(filename, "%lld.bin", phn);
	fptr2 = fopen(filename, "rb+");
    
    fread(&b, sizeof(struct account), 1, fptr2);
    b.balance += amount;
    
	fseek(fptr2, 0L, SEEK_SET);
    fwrite(&b, sizeof(struct account), 1, fptr2);
    
	fclose(fptr2);
	
	printf("\nYour amount has been successfully transfered!");
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
