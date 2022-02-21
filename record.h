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
//  FILE:        record.h
//
//  DESCRIPTION:
//   Definition of new datatype, record, and its properties.
//
****************************************************************/

struct record
{
   int                accountno;
   char               name[25];
   char               address[50];
   struct record*     next;
};

