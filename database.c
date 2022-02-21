#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "database.h"

extern int debug;

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Allows user to create a record and store it 
//                 in database
//
//  Parameters:    startAddress (struct record**) : address of pointer
//                           that stores address of first record in list
//                 accountNum (int) : clients account number
//                 name (char []) : clients name
//                 address (char []) : clients address
//
//  Return values:  0 : record successfully added
//                 -1 : duplicate record, do not add
//
****************************************************************/

int addRecord (struct record ** startAddress, int accountNum, char uname[], char uaddress[])
{

    int success;
    struct record *new, *cursor, *precursor;

    new = (struct record*)malloc(sizeof(struct record));

    new->accountno = accountNum;
    strcpy(new->name, uname);
    strcpy(new->address, uaddress);
    new->next = NULL;      

    if (debug == 1)
    {

        printf("\n----------*DEBUG* In addRecord function, params: startAddress(%p), accountNum(%d), uname(%s), uaddress(%s)----------\n", (void*)startAddress, accountNum, uname, uaddress);

    }

    if( *startAddress == 0 )
    {

        *startAddress = new;

        success = 0;

    }

    else if( new->accountno < (*startAddress)->accountno )
    {

        new->next = *startAddress;
        *startAddress = new;
        success = 0;

    }

    else
    {
  
        cursor = *startAddress;
    
        while( (cursor != 0) && (new->accountno > cursor->accountno) )
        {

            precursor = cursor;

            cursor = cursor->next;

        }

        if( (cursor != 0) && (new->accountno == cursor->accountno) )
        {

            free(new);

            success = -1;

        }

        else
        {

            new->next = cursor;

            precursor->next = new;

            success = 0;

        }

    }

    new = NULL;
    cursor = NULL;
    precursor = NULL;

    return success;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   prints all records in database
//                 
//  Parameters:    start (struct record *) : address of first record in list
//
//  Return values: void
//
****************************************************************/

void printAllRecords (struct record * start)
{

    int count;
    struct record *cursor;

    cursor = start;
    count = 1;

    if ( debug == 1 )
    {

        printf("\n----------*DEBUG* In printAllRecords function, params: start(%p)----------\n", (void*)start);

    }

    if( cursor == 0 )
    {

        printf("\nThere are no records on file.\n");

    }

    else
    {

        printf("\nALL RECORDS ON FILE.....\n");

    }

    while( cursor != NULL )
    {

        printf("\n->Record for Client %d:\n", count);
        printf("\nAccount Number: %d\n", cursor->accountno);
        printf("Name: %s\n", cursor->name);
        printf("Address:\n%s\n", cursor->address);

        count = count + 1;
        cursor = cursor->next;

    }

}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   finds a record from the database
//
//  Parameters:    start (struct record *) : address of first record in list
//                 accountNum (int) : account number of record to find
//
//  Return values: 0 : record found
//                 -1: record not fount
//
****************************************************************/

int findRecord (struct record * start, int accountNum)
{

    int success;
    struct record *cursor;

    success = -1;
    cursor = start;

    if ( debug == 1 )
    {

        printf("\n----------*DEBUG* In findRecord function, params: start(%p), accountNum(%d)----------\n", (void*)start, accountNum);

    }

    while( cursor != 0 )
    {

        if( accountNum == cursor->accountno )
        {

            printf("\nRECORD FOUND..\n");
            printf("\nAccount Number: %d\n", cursor->accountno);
            printf("Name: %s\n", cursor->name);
            printf("Address:\n%s\n", cursor->address);

            cursor = NULL;
            success = 0;

        }

        else
        {

            cursor = cursor->next;

        }

    }

    return success;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   deletes a record from the database
//
//  Parameters:    startAddress (struct record **) : address of pointer that
//                              stores address of first record in list
//                 accountNum (int) : account number of record to delete
//
//  Return values:  0 : record successfully deleted
//                  -1: record not found, cannot delete
//
****************************************************************/

int deleteRecord(struct record ** startAddress, int accountNum)
{

    int success;
    struct record *cursor, *precursor, *successor;

    cursor = *startAddress;
    precursor = NULL;
    successor = NULL;

    if ( debug == 1 )
    {

        printf("\n----------*DEBUG* In deleteRecord function, params: startAddress(%p), accountNum(%d)---------\n", (void*)startAddress, accountNum);

    }

    while( (cursor != 0) && (accountNum != cursor->accountno) )
    {

        precursor = cursor;
        cursor = cursor->next;

    }

    if( cursor == 0 )
    {

        precursor = NULL;
        success = -1;

    }

    else if( cursor == *startAddress )
    {

        cursor = cursor->next;

        free(*startAddress);

        *startAddress = cursor;
        cursor = NULL;
        success = 0;

    }

    else
    {

        successor = cursor->next;
        precursor->next = successor;

        free(cursor);

        cursor = NULL;
        precursor = NULL;
        successor = NULL;
        success = 0;

    }

    return success;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   reads file containing saved records from programs last use
//
//  Parameters:    startAddress (struct record **) : address of pointer that
//                      will store the address of the first record in the list
//                 file (char []) : name of file to read
//
//  Return values:  0 : able to open file
//                  -1: unable to open file
//
****************************************************************/

int readfile(struct record ** startAddress, char file[])
{

    int success, accountNum;
    char uname[25], uaddress[50];
    FILE * read;
    char trash[80];

    if( debug == 1 )
    {

        printf("\n----------*DEBUG* In readfile function, params: startAddress(%p), file(%s)----------\n", (void*)startAddress, file);
 
    }

    read = fopen(file, "r");

    if( read == NULL )
    {

        success = -1;

    }

    else
    {

        while( feof(read) == 0 )
        {        

            fscanf(read, "%d", &accountNum);

            fgets(trash, 80, read);

            fgets(uname, 25, read);

            uname[strlen(uname)-1] = '\0';
 
            getaddressfromfile(uaddress, 50, read);

            uaddress[strlen(uaddress)-1] = '\0';

            if( feof(read) == 0 )
            {

                addRecord(startAddress, accountNum, uname, uaddress);
     
            }

        }       

        fclose(read);

        success = 0;

    }

    return success;

}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   initially writes or overwrites file with new data
//
//  Parameters:    start (struct record *) : address of first record in list
//                 file (char []) : name of file to be written/overwritten
//
//  Return values:  0 : able to make or overwrite file
//                  -1: unable to write file
//
****************************************************************/

int writefile(struct record * start, char file[])
{

    int success;
    FILE * write;
    struct record * cursor;

    if( debug == 1 )
    {

        printf("\n----------*DEBUG* In writefile function, params: start(%p), file(%s)----------\n", (void*)start, file);

    }

    cursor = start;

    write = fopen(file, "w");

    if( write == NULL )
    {

        success = -1;

    }

    else
    {

        while( cursor != NULL )
        {

            (cursor->address)[strlen(cursor->address)] = '!';            

            fprintf(write, "%d\n", cursor->accountno);
            fprintf(write, "%s\n", cursor->name);
            fprintf(write, "%s\n", cursor->address);

            cursor = cursor->next;

        }

        success = 0;
        fclose(write);

    }

    return success;

}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   clears all records stored in heap to prevent memory leak
//
//  Parameters:    startAddress (struct record **) : address of pointer that 
//                        stores address of first record in list 
//
//  Return values:  void
//
****************************************************************/

void cleanup(struct record ** startAddress)
{

    struct record * cursor;
  
    cursor = *startAddress;

    if( debug == 1 )
    {

         printf("\n----------*DEBUG* In cleanup function, params: startAddress(%p)----------\n", (void*)startAddress);

    }

    while( cursor != 0 )
    {

        cursor = cursor->next;
        
        free(*startAddress);

        *startAddress = cursor;

    }

    return;

}

/*****************************************************************
//
//  Function name: getaddressfromfile
//
//  DESCRIPTION:   reads and stores each character of address from file
//                 including ! so it can be added to heap
//
//  Parameters:    address (char []) : array where address will be stored
//                 size (int) : size of address array so we do not overflow
//                 readFrom (FILE *) : pointer to file buffer that needs to be read
//
//  Return values:  void
//
****************************************************************/

void getaddressfromfile(char address[], int size, FILE * readFrom)
{

    int i;
    char c;

    i = 0;

    if (debug == 1)
    {

        printf("\n----------*DEBUG* In getaddressfromfile function, params: address(%s), size(%d), readFrom(%p)----------\n", address, size, (void*)readFrom);

    }

    while((c != '!') && (i < size-1))
    {

        c = fgetc(readFrom);

        address[i] = c;

        i = i + 1;
    }

    address[i] = '\0';

    return;

}

