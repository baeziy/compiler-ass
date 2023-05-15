/*Program Name: in1.c
*Description:
Input file for assignment 1 ********************************/ 
#include <stdio.h>
#include <string.h>
#define TRUE 1
/*this file carries two MACROS*/ 
int main(int argc,char*argv[])
{
      //checking the arguments
      if(argc!=2)
      {
            printf("Error encountered\n");
            exit(0);//terminate the program
      }
      int i = strlen(argv[1]);
      if(i >= 10)
      {
            //do something
      }
      While(TRUE)
      {
            /*this is an infinite loop and will
            Iterate till the user terminates the program
            Using Ctrl+C*/
      }
      //end of program
return 0; 
}