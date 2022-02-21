struct record
{
   int                accountno;
   char               name[25];
   char               address[50];
   struct record*     next;
};

