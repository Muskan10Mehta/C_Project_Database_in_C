/**
 * Project description: This project is for implementing a compact database which will be light weight and fast. 
 * This will provide essential features of database management like - add, ammend ,search, delete, sort and display.
 * This database can be accomodated in devices with very low and constrained amount of resources like embedded systems, small scale projects etc
 *
 * The following program is to implement food vending machine database with the following structure and functions:
 *
 * Structure: 
 * Functions:
 *
 * Compilation: gcc -o vending_db index.c
 * Execution: ./vending_db
 *
 * @Muskan, 1910990681, 02/09/2021
 * C Project
 * Resouces: 
 */

#include <stdio.h>
#include <stdlib.h>

struct Fields{

   unsigned product_code;
   double prize;
   int quantity;
   int expiry_date;

};

int main(){

   printf("\t WELCOME TO FOOD VENDING MACHINE \t\n");
   Printf("\t PLEASE ENTER THE FOOD CODE FOR THE ITEM YOU WANT TO ORDER \t\n");
   
   return 0;
}
