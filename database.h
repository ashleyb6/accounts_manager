/*****************************************************************
//
//  NAME:        Ashley Burnett
//
//  HOMEWORK:    Project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        February 10, 2021
//
//  FILE:        database.h
//
//  DESCRIPTION:
//   Header file so prototypes of database.c functions may be 
//   added to user_interface.c
//
****************************************************************/

int addRecord(struct record **, int, char [], char[]);
void printAllRecords(struct record *);
int findRecord(struct record *, int);
int deleteRecord(struct record **, int);
int readfile(struct record **, char []);
int writefile(struct record *, char []);
void cleanup(struct record **);
void getaddressfromfile(char [], int, FILE *);

