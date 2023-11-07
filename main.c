#include <stdio.h>    // Standard I/O library for input and output functions
#include <conio.h>   // Console I/O library for console-based functions
#include <string.h>  // String library for string manipulation functions
#include <ctype.h>   // Character handling library for character-related functions
#include <stdlib.h>  // Standard library for general-purpose functions
#include <time.h>    // Time library for date and time-related functions

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

void main()		// Starting point of the main program
{
	home();		// Calls the function home()
}

void home()		// Function definition of Home
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
			login();	// Option 1 calls the function login() for logging into the program
			break;
			
		case '2':
			createacc();	// Option 2 calls the function createacc() for new account creation
			break;
			
		case '0':
			exitMessage();		// Option 0 calls the function exitMessage() to exit the program
			break;
			
		default:
			goto mainmenu;		// Any invalid inputs redirects the user to mainmenu:
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

void menu(struct account a)		// Function definition of menu() with structure as an parameter
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
			deposit(&a);	// Option 1 calls the function deposit() with address of structure as an argument
			break;
			
		case '2':
			withdraw(&a);	// Option 2 calls the function withdraw() with address of structure as an argument
			break;
			
		case '3':
			balanceInq(a);		// Option 3 calls the function balanceInq() with structure as an argument
			break;
			
		case '4':
			displayhistory(&a);		// Option 4 calls the function displayhistory() with address of structure as an argument
			break;
			
		case '5':
			transfer(&a);	// Option 5 calls the function transfer() with address of structure as an argument
			break;
			
		case '6':
			csupport(a);	// Option 6 calls the function csupport() with structure as an argument
			break;	
			
		case '7':
			home();		// Option 7 calls the function home()
			
		case '0':
			exitMessage();		// Option 0 calls the function exitMessage()
			break;
			
		default:
			menu(a);	// Any invalid inputs redirects the user to Menu by calling the function menu() with structure as an argument
	}
}

void createacc()	// Function definition of Create an Account
{
	struct account a;	// Structure to store firstname, lastname, phonenumber, password and balance
	
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
	
	a.balance = 0.0;	// Initializes the account balance to zero
	
	logpassword(a);		// Call the function logpassword() by passing the structure with user's info
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

void balanceInq(struct account a)	// Function definition of Balance Inquiry with structure of currently logged in user
{
	header();
	
	char choice;
	
	printf("Available Balance: %lf", a.balance);	// Displays balance by accessing structure variable a.balance
	
	printf("\n\n[1] Back");
	printf("\n[0] Exit\n\n");
	
	fflush(stdin);
	choice = getch();
	if(choice =='1')
	{
		menu(a);	// Option 1 calls the menu() function with structure as argument
	}else if(choice == '0')
	{
		exitMessage();	// Option 2 calls the exitMessage() function
	}else
	{
		balanceInq(a);	// Any other input from the user redirects to Balance Inquiry page by calling function balanceInq()
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

void transfer(struct account *a)	// Function definition of transfer() with address of structure as an parameter
{
	FILE *fptr1, *fptr2;	// File pointers for two users' file i.e, sender and receiver
	
	struct account b;
	char filename[60];
	long long int phn;
	double amount;
	
	header();
	
	printf("Transfer from +977 %lld", a->phone);
	printf("\n\nEnter Receiver's Mobile Number: +977 ");
	scanf("%lld", &phn); 
	
	sprintf(filename, "data/%lld.bin", phn);	// Creates a filename with phone number of the receiver for example, "data/1234567.bin"
	fptr2 = fopen(filename, "rb+");		// Receiver's file is opened in "rb+" mode
	if(fptr2==NULL)		// Checks if the receiver to whom the amount is supposed to be transferred exists or not
	{
		printf("\nThe user does not exist. Please try again!");
		
		sleep(1);
        
        checkpoint:
        printf("\n\n[1] Re-enter Receiver's Number");
        printf("\n[2] Back\n\n");
        
        fflush(stdin);
        char choice = getch();
        if (choice == '1')
        {
            transfer(a);	// Option 1 calls the funciton transfer() with structure as an argument
        }
        else if (choice == '2')
        {
            menu(*a); 	// Option 2 calls the function menu() with structure as an argument
        }else
		{
			system("cls");		// Clears the console screen
			goto checkpoint;	// Any invalid inputs redirects the user to checkpoint:
		}	
	}
	
	amountinput:
	printf("Enter transfer amount: ");
	scanf("%lf", &amount);
	
	if(amount>a->balance)		// Checks if the amount entered by the sender is available in the account or not
	{
		printf("\n\nThe entered amount exceeds your bank balance. Please try again!");
		
		sleep(1);
		
		header();
		
		goto amountinput;	// Returns the user to amountinput: for entering the appropriate amount
	}else if(amount<=0)		// Checks if the amount entered is zero or any negative value
	{
		printf("\nYour amount must be greater than 0. Please try again!");
		
		sleep(1);
        
        printf("\n\n[1] Re-enter Amount");
        printf("\n[2] Back\n\n");
        
        fflush(stdin);
        char choice = getch();
        if (choice == '1')
        {
            goto amountinput;	// Option 1 returns the user to amountinput: for entering the appropriate amount
        }
        else if (choice == '2')
        {
            menu(*a); 		// Option 2 calls the function menu() with structure as an argument
        }
	}else		// This block of code executes if the sender enters appropriate amount
	{
		a->balance -= amount;	// Deducts the amount from sender's account
	
		sprintf(filename, "data/%lld.bin", a->phone);	// Creates a filename of with sender's phone number, for example: "data/7654321.bin"
		fptr1 = fopen(filename, "rb+");		// Sender's file is opened in "rb+" mode
		if(fptr1==NULL)		// Checks if the sender's file exists or not
		{
			printf("\nError: File not Found");
			
			sleep(1);	// Adds delay of one second
			
			exit(1);	// Exits the program with status code 1, indicating the program has some error
		}
	    
		fseek(fptr1, 0L, SEEK_CUR);		// Moves the file pointer to the current position in fptr1
	    fwrite(a, sizeof(struct account), 1, fptr1);	// Writes the 'a' structure to fptr1
	    
	    history(a,2,phn,amount);	// Calls the function history(). First argument represents the user, second argument represents the sending type of transaction, third argument represents the receiver's phone number during transfer and the fourth argument represents the amount involved in the transaction
	    
		fclose(fptr1);
	    
	    fread(&b, sizeof(struct account), 1, fptr2);	// Reads an account structure from fptr2
	    
		b.balance += amount;	// Adds up the amount in receiver's account
	    
	    history(&b,3,a->phone,amount);		// Calls the function history(). First argument represents the user, second argument represents the receiving type of transaction, third argument represents the sender's phone number during transfer and the fourth argument represents the amount involved in the transaction
		
		fseek(fptr2, 0L, SEEK_SET);		// Moves the file pointer to the beginning of fptr2
	    fwrite(&b, sizeof(struct account), 1, fptr2);	// Write the modified 'b' structure back to fptr2
	    
		fclose(fptr2);
		
		printf("\nYour amount has been successfully transferred!");
		
		sleep(1);
		
		balanceInq(*a);		// Calls the function balanceInq() with structure as an argument to display user's balance
	}
}

void history(struct account *a, int trn_type, long long int phn, int amount)
{
	FILE *fptr;
	
	struct account b;
	char filename[60];
	time_t t = time(NULL);		// Get the current time in seconds since the epoch (Unix timestamp)
	struct tm tm = *localtime(&t);		// Convert the timestamp to a local time structure
	
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

void csupport(struct account a)		// Function definition of Customer Support with structure as a parameter
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
		menu(a);	// Option 1 calls the function menu with structure as an argument
	}else if(choice == '0')
	{
		exitMessage();		// Option 0 calls the function exitMessage() to exit the program
	}else
	{
		csupport(a);	// Any inputs other than 1 or 0 redirects the user to the same page, that is Customer Support
	}
}

void header()	// Function definition of header which is a banner-like text displayed at the top of screen
{
	system("cls");		// Clears the console screen specifically on Windows
	
	printf("\t  C-BANK PRO");
	printf("\n\"Experience Banking, the PRO way\"");
	printf("\n=================================\n\n");
}

void exitMessage()	// Funtion definition of Exit Message
{
	header();
	
	printf("Thank you for choosing C-Bank Pro - Your Trusted Banking Partner");
	printf("\n\nHave a great day!");
	
	sleep(2);	// Adds delay of 2 seconds
	
	exit(0);	// Exits the program with status code 0, indicating successful execution of the program
}
