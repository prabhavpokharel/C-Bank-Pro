#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<time.h>

#define MAX_PASSWORD_LENGTH 30

struct account{
	char firstname[100], lastname[100], password[MAX_PASSWORD_LENGTH];
	long long int phone;
	double balance;
};

void header();
void home();
void login();
void logpassword(struct account);
void menu(struct account);
void withdraw(struct account *);
void createacc();
void history(struct account *,int,long long int,int);
void displayhistory(struct account *);
void balanceInq(struct account);
void deposit(struct account *);
void transfer(struct account *);
void csupport(struct account);
void exitMessage();

void main()
{
	home();
}

void home()
{
	char choice;
	
	mainmenu:	
	header();
	
	printf("Homepage");
	printf("\n\n[1] Login");
	printf("\n[2] Create an Account");
	printf("\n\n[0] Exit\n\n");	
	
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
			
		case '0':
			exitMessage();
			break;
			
		default:
			goto mainmenu;
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
    while(1)
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
    
    sprintf(filename, "data/%lld.bin", phn);
    fptr = fopen(filename, "rb");
    if(fptr==NULL)
	{
		printf("\n\nUser not found.");
        
		sleep(1);
        
        printf("\n\n[1] Retry Login");
        printf("\n[2] Homepage\n\n");
        
        fflush(stdin);
        char choice = getch();
        if (choice == '1')
        {
            login(); 
        }
        else if (choice == '2')
        {
            home(); 
        }
	}

    while(fread(&a, sizeof(struct account), 1, fptr) != 0)
    {
        if ((a.phone == phn) && (strcmp(a.password, pw) == 0))
        {
            menu(a);
            break; 
        }
    }

    fclose(fptr);
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
	printf("\n[7] Log Out");
	printf("\n\n[0] Exit\n\n");	
	
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
			displayhistory(&a);
			break;
			
		case '5':
			transfer(&a);
			break;
			
		case '6':
			csupport(a);
			break;	
			
		case '7':
			home();		
			
		case '0':
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
	
	printf("Creating a new account\n\n");
	
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
	
	sprintf(filename, "data/%lld.bin", a.phone);
	fp = fopen(filename,"ab");
	if(fp==NULL)
	{
		printf("\nUser not found.");
		
		sleep(1);
		
		exit(1);
	}
	
	printf("\nEnter password: ");
    while(1) 
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
	while(1) 
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
		
		login();
	}
}

void balanceInq(struct account a)
{
	header();
	
	char choice;
	
	printf("Available Balance: %lf", a.balance);
	
	printf("\n\n[1] Back");
	printf("\n[0] Exit\n\n");
	
	fflush(stdin);
	choice = getch();
	if(choice =='1')
	{
		menu(a);
	}else if(choice == '0')
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
	
	int amount;
	char filename[60];
	
	sprintf(filename, "data/%lld.bin", a->phone);
	
	header();
	
	printf("Deposit");
	
	checkpoint:
	printf("\n\nEnter the amount you want to deposit: ");
	scanf("%d", &amount);
	
	if(amount<=0)
	{
		printf("\nYour amount must be greater than 0. Please try again!");
		
		sleep(1);
        
        printf("\n\n[1] Re-enter Amount");
        printf("\n[2] Back\n\n");
        
        fflush(stdin);
        char choice = getch();
        if (choice == '1')
        {
            goto checkpoint;
        }
        else if (choice == '2')
        {
            menu(*a); 
        }
	}
	
	history(a,0,a->phone,amount);
	
	a->balance += (double)amount;
	
	fptr = fopen(filename, "rb+");
	if(fptr == NULL)
	{
		printf("\nError: File not Found");
		
		sleep(1);
		exit(1);
	}

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
	
	int amount;
	char filename[60];
	
	sprintf(filename, "data/%lld.bin", a->phone);
	
	amountinput:	
	header();
		
	printf("Withdraw");
		
	printf("\n\nEnter the amount you want to withdraw: ");
	scanf("%d", &amount);
	
	if((double)amount>a->balance)
	{
		printf("\n\nThe entered amount exceeds your bank balance. Please try again!");
		
		sleep(1);
		
		goto amountinput;
	}
	else if(amount<=0)
	{
		printf("\nYour amount must be greater than 0. Please try again!");
		
		sleep(1);
        
        printf("\n\n[1] Re-enter Amount");
        printf("\n[2] Back\n\n");
        
        fflush(stdin);
        char choice = getch();
        if (choice == '1')
        {
            goto amountinput;
        }
        else if (choice == '2')
        {
            menu(*a); 
        }
	}else
	{
		history(a,1,a->phone,amount);
	
		a->balance -= (double)amount;
		
		fptr = fopen(filename, "rb+");
		if(fptr==NULL)
		{
			printf("\nError: File not Found");
			
			sleep(1);
			
			exit(1);
		}
	
	    fseek(fptr, 0L, SEEK_CUR);
	    fwrite(a, sizeof(struct account), 1, fptr);
	    
		fclose(fptr);
		
		printf("Your amount has been successfully withdrawn!");
		
		sleep(1);
		
		balanceInq(*a);	
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
	
	printf("Transfer from +977 %lld", a->phone);
	printf("\n\nEnter Receiver's Mobile Number: +977 ");
	scanf("%lld", &phn);
	
	sprintf(filename, "data/%lld.bin", phn);
	fptr2 = fopen(filename, "rb+");
	if(fptr2==NULL)
	{
		printf("\nThe user does not exist. Please try again!");
		
		sleep(1);
        
        printf("\n\n[1] Re-enter Receiver's Number");
        printf("\n[2] Back\n\n");
        
        fflush(stdin);
        char choice = getch();
        if (choice == '1')
        {
            transfer(a); 
        }
        else if (choice == '2')
        {
            menu(*a); 
        }		
	}
	
	amountinput:
	printf("Enter transfer amount: ");
	scanf("%lf", &amount);
	
	if(amount>a->balance)
	{
		printf("\n\nThe entered amount exceeds your bank balance. Please try again!");
		
		sleep(1);
		
		header();
		
		goto amountinput;
	}else if(amount<=0)
	{
		printf("\nYour amount must be greater than 0. Please try again!");
		
		sleep(1);
        
        printf("\n\n[1] Re-enter Amount");
        printf("\n[2] Back\n\n");
        
        fflush(stdin);
        char choice = getch();
        if (choice == '1')
        {
            goto amountinput;
        }
        else if (choice == '2')
        {
            menu(*a); 
        }
	}else
	{
		a->balance -= amount;
	
		sprintf(filename, "data/%lld.bin", a->phone);
		fptr1 = fopen(filename, "rb+");
		if(fptr1==NULL)
		{
			printf("\nError: File not Found");
			
			sleep(1);
			
			exit(1);
		}
	    
		fseek(fptr1, 0L, SEEK_CUR);
	    fwrite(a, sizeof(struct account), 1, fptr1);
	    
	    history(a,2,phn,amount);
	    
		fclose(fptr1);
	    
	    fread(&b, sizeof(struct account), 1, fptr2);
	    
		b.balance += amount;
	    
	    history(&b,3,a->phone,amount);
		
		fseek(fptr2, 0L, SEEK_SET);
	    fwrite(&b, sizeof(struct account), 1, fptr2);
	    
		fclose(fptr2);
		
		printf("\nYour amount has been successfully transferred!");
		
		sleep(1);
		
		balanceInq(*a);	
	}
}

void history(struct account *a, int trn_type, long long int phn, int amount)
{
	FILE *fptr;
	
	struct account b;
	char filename[60];
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	
	if(trn_type==0)
	{
		sprintf(filename, "data/%lld.txt", a->phone);
		fptr = fopen(filename, "a");
		if(fptr==NULL)
		{
			printf("\nError: File not Found");
			
			sleep(1);
			
			exit(1);
		}
				
        fprintf(fptr,"%d-%02d-%02d %02d:%02d:%02d\t Deposited: NPR %d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, amount);
		
		fclose(fptr);
	}
	else if(trn_type==1)
	{
		sprintf(filename, "data/%lld.txt", a->phone);
		fptr = fopen(filename, "a");
		if(fptr==NULL)
		{
			printf("\nError: File not Found");
			
			sleep(1);
			
			exit(1);
		}
		
		fprintf(fptr,"%d-%02d-%02d %02d:%02d:%02d\t Withdrawn: NPR %d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, amount);
    	
		fclose(fptr);
	}
	else if(trn_type==2)
	{
    	sprintf(filename, "data/%lld.txt", a->phone);
		fptr = fopen(filename, "a");
		if(fptr==NULL)
		{
			printf("\nError: File not Found");
			
			sleep(1);
			
			exit(1);
		}
    	
		fprintf(fptr,"%d-%02d-%02d %02d:%02d:%02d\t Transferred to +977 %lld: NPR %d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, phn, amount);
    	
		fclose(fptr);
	}
	else if(trn_type==3)
	{
		sprintf(filename, "data/%lld.txt", a->phone);
		fptr = fopen(filename, "a");
		if(fptr==NULL)
		{
			printf("\nError: File not Found");
			
			sleep(1);
			
			exit(1);
		}
    	
		fprintf(fptr,"%d-%02d-%02d %02d:%02d:%02d\t Received from +977 %lld: NPR %d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, phn, amount);
    	
		fclose(fptr);
	}
}

void displayhistory(struct account *a)
{
	FILE *fptr;
	
	char c, choice, filename[60];
	
	sprintf(filename, "data/%lld.txt", a->phone);
	
	header();
	
	printf("Transactions\n\n");
	
	fptr = fopen(filename, "r");
	if(fptr==NULL)
	{
		printf("\nError: File not Found");
		
		sleep(1);
		
		exit(1);
	}
	
	rewind(fptr);
	while(feof(fptr) == 0)
	{
		fscanf(fptr, "%c", &c);
		printf("%c", c);
	}
	
	fclose(fptr);
	
	printf("\n\n[1] Back");
	printf("\n[0] Exit\n\n");
	
	fflush(stdin);
	choice = getch();
	if(choice =='1')
	{
		menu(*a);
	}else if(choice == '0')
	{
		exitMessage();
	}else
	{
		displayhistory(a);
	}
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
	printf("\n[0] Exit\n\n");
	
	fflush(stdin);
	choice = getch();
	if(choice =='1')
	{
		menu(a);
	}else if(choice == '0')
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
	
	printf("Thank you for choosing C-Bank Pro - Your Trusted Banking Partner");
	printf("\n\nHave a great day!");
	
	sleep(2);
	
	exit(0);
}
