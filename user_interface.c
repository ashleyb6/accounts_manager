/**************************************************************
//
//    Name:        Ashley Burnett
//
//    Homework:    Project1
//
//    Class:       ICS 212
//
//    Instructor:  Ravi Narayan
//
//    Date:        February 8, 2021
//
//    File:        user_interface.c
//
//    Description:
//       Program models software to be used in a bank.
//       This program is specific for user interface so user may 
//       access 'companies' client database to view or update
//       information.
//         
**************************************************************/

#include <stdio.h>
#include <string.h>
#include "record.h"
#include "database.h"

int debug; /* On = 1 ... Off = 0 */

void menu();
void getaddress(char[], int);
int getAccountNum();

/*************************************************************
//
//    Function name: main
//
//    Description:   Will allow user_interface.c to run and access 
//                   database.c so user may easily manipulate 
//                   client information.
//
//    Parameters:    argc (int) : number of command line arguments
//                   argv (char*[]) : array of command line arguments
//
//    Return values: 0 : success
//
*************************************************************/

int main(int argc, char* argv[])
{

    int loop = 1;
    int added, deleted, found, fileWritten;
    char trash[80];
    char input[9];
    char a[2] = "a";
    char ad[3] = "ad";
    char add[4] = "add";
    char p[2] = "p";
    char pr[3] = "pr";
    char pri[4] = "pri";
    char prin[5] = "prin";
    char print[6] = "print";
    char printa[7] = "printa";
    char printal[8] = "printal";
    char printall[9] = "printall";
    char d[2] = "d";
    char de[3] = "de";
    char del[4] = "del";
    char dele[5] = "dele";
    char delet[6] = "delet";
    char delete[7] = "delete";
    char f[2] = "f";
    char fi[3] = "fi";
    char fin[4] = "fin";
    char find[5] = "find";
    char q[2] = "q";
    char qu[3] = "qu";
    char qui[4] = "qui";
    char quit[5] = "quit";
    char clientName[25];
    int accountNum;
    char clientAddress[50];
    struct record * start = NULL; /*to make and store new client records*/
    char records[8] = "records";

    if( argc == 1 )
    {
        
        loop = 1;
        debug = 0;
   
     }
    
    /* 2 arguments, second must be debug, otherwise error and exit */

    else if( argc == 2 && strcmp(argv[1], "debug") == 0 )     
    {
  
        printf("\n-----------------------*DEBUG MODE ON*---------------------------\n\n");
            
        loop = 1;
        debug = 1;
     
    }

    else
    {

        printf("\nCommand line error, unrecognized second argument or too many arguments.\n\n");

        loop = 0;

    }
  

    /* intro and instructions to user */
    
    if( loop != 0 )
    {

        readfile(&start, records);

        printf("\nWelcome to Bank 212's Client Database:\n\n");
        printf("\tUse the menu below to add a new client record,\n");
        printf("\tprint all records of existing clients,\n");
        printf("\tfind and view an existing clients record,\n");
        printf("\tor delete a clients record from the database.\n");
  
        menu();
  
    }

    while( loop != 0 ) /* keeps menu loop running as long as quit not selected */
    {

        scanf("%s", input); /* puts users choice into userInput array */

        fgets(trash, 80, stdin); /* clears \n from stdin */ 
        
        /* if user enters add, add a new record */

        if((strcmp(input, a) == 0)||(strcmp(input, ad) == 0)||(strcmp(input, add) == 0))
        {

            printf("\nEnter clients name: ");

            fgets(clientName, 25, stdin);

            clientName[strlen(clientName)-1] = '\0';

            getaddress(clientAddress, 50);

            clientAddress[strlen(clientAddress)-1] = '\0';

            accountNum = getAccountNum();

            added = addRecord(&start, accountNum, clientName, clientAddress);

            if( added == -1 )
            {

                printf("\nAccount number already in use, record could not be added.\n");

            }

            else if( added == 0 )
            {

                printf("\nSuccess! Client's record has been added to the system.\n");

            }

            menu();

        }

        /* if user enters printall, print all records */ 

        else if((strcmp(input, p) == 0)||(strcmp(input, pr) == 0)||(strcmp(input, pri) == 0)||(strcmp(input, prin) == 0)||(strcmp(input, print) == 0)||(strcmp(input, printa) == 0)||(strcmp(input, printal) == 0)||(strcmp(input, printall) == 0))
        {
            printAllRecords(start);
           
            menu();
        }

        /* if user enters find, find record based on account number */

        else if((strcmp(input, f) == 0)||(strcmp(input, fi) == 0)||(strcmp(input, fin) == 0)||(strcmp(input, find) == 0 ))
        {
          
            accountNum = getAccountNum();

            found = findRecord(start, accountNum);
          
            if( found == -1 )
            {

                printf("\nRecord with account number %d could not be found in the system.\n", accountNum);

            }

            menu();
        }

        /* if user enters delete, delete record based on account number */
       
        else if((strcmp(input, d) == 0)||(strcmp(input, de) == 0)||(strcmp(input, del) == 0)||(strcmp(input, dele) == 0 )||(strcmp(input, delet) == 0)||(strcmp(input, delete) == 0))
        {
        
            accountNum = getAccountNum();

            deleted = deleteRecord(&start, accountNum);

            if( deleted == -1 )
            {

                printf("\nClient's record was not found in the system.\n");

            }

            else if( deleted == 0 )
            {

                printf("\nSuccess! The record has been deleted from the system.\n");

            }

            menu();
        }

        /* if user enters quit, quit the program */

        else if((strcmp(input, q) == 0)||(strcmp(input, qu) == 0)||(strcmp(input, qui) == 0)||(strcmp(input, quit) == 0 ))
        {

            loop = 0;

            fileWritten = writefile(start, records);

            if( fileWritten == -1 )
            {

                printf("There was an error in closing, records may not be saved.\n");
     
            }

            else if( fileWritten == 0 )
            {

                printf("Progress saved!\n");

            }
            
            cleanup(&start);

            printf("\nThank you for using Bank 212's Client Database!\n");
            printf("Exiting program...\n\n");
  
        }
        
        /* if user enters none of the above, error and reprompt */
     
        else
        {
            printf("\n\nI'm sorry that was not a valid option. Please try again.\n\n");

            menu();
        }

    }

    return 0;

}

/*****************************************************************
//
//  Function name: getaddress
//
//  DESCRIPTION:   Will allow user to fill address array to be
//                 used in the clients record.
//
//  Parameters:    address (char[]): brings in address array that
//                                   is to be filled
//                 size (int): used to keep track of address
//                             array size and stop loop when
//                             full  
//
//  Return values:  void
//
****************************************************************/

void getaddress (char address[], int size)
{
    int i;
    char c;
    i = 0;   

    if (debug == 1)
    {

        printf("\n----------*DEBUG* In getaddress function, params: address(%s), size(%d)----------\n", address, size);

    }

    printf("\nEnter clients address, type ! and Enter when done:\n\n");
   
    /* while loop so user may fill address array until ! */
 
    while((c != '!') && (i < size))
    {
        c = fgetc(stdin); /*read users character and store in c*/
        address[i] = c; /*store each character user enters into address array*/
        i = i + 1;
    }

    address[i] = '\0'; /*set last in array to null*/

    return;
}

/*****************************************************************
//
//  Function name: menu 
//
//  DESCRIPTION:   Reprints menu options in case of error or    
//                 user entering invalid data
//
//  Parameters:    no parameters
//
//  Return values: void
//
****************************************************************/

void menu()
{
    if (debug == 1)
    {
        
        printf("\n----------*DEBUG* In menu function, params: none----------\n");
    
    }

    printf("\n\nType name of one of the following options and press Enter:\n\n");
    printf("\tadd:       Add a new record in the database\n");
    printf("\tprintall:  Print all records in the database\n");
    printf("\tfind:      Find record(s) in the database\n");
    printf("\tdelete:    Delete existing record(s) from the database\n");
    printf("\tquit:      Exit from Client Database\n");
    return;
}
   
/*****************************************************************
//
//  Function name: getAccountNum
//
//  DESCRIPTION:   Allows user to keep entering account number
//                 until it is a usable value
//
//  Parameters:    none
//
//  Return values: input : accepted account number
//
****************************************************************/

int getAccountNum()
{
    int input;
    char buffer[80];  

    if (debug == 1)
    {
        
        printf("\n----------*DEBUG* In getAccountNum function, params: none----------\n");
   
     }

    printf("\nEnter clients account number: ");

    while((scanf("%d", &input) == 0) || (input <= 0))
    {
        fgets(buffer, 80, stdin);
        printf("\nClients account number must be greater than zero.\n");
        printf("\nPlease enter a new number: ");
    }

    return input;
}
