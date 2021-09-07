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

struct info_fields{

   int product_code;
   double product_prize;
   int product_quantity;
   struct info_fields* next;
};

typedef struct info_fields info_fields;

// creating head for the linked list i.e product_info table

info_fields *product_info;

info_fields* create_product_table() {

   int number_of_items = 0;
   int temp_product_code = 11;

   info_fields *connector_node;

   // initializing first entry in product_info table

   product_info = (info_fields *) malloc (sizeof(info_fields));
   product_info -> product_code = temp_product_code;
   product_info -> product_prize = 00.00;
   product_info -> product_quantity = 0;
   product_info -> next = NULL;
   connector_node = product_info;

   temp_product_code++;
   number_of_items++;

   // considering there are 6 rows and 6 columns in the vending machine
   // initializing the product_codes accordingly
   //

   while(number_of_items < 36){

       // if the counter reaches end of colums for a row
       // move to next row

       if(temp_product_code % 10 > 6 ){
           // upgrade to next row
           temp_product_code += 4;
       }

   info_fields* new_node = (info_fields*) malloc (sizeof(info_fields));
   new_node -> product_code = temp_product_code;
   new_node -> product_prize = 00.00;
   new_node -> product_quantity = 0;
   new_node -> next = NULL;

   connector_node -> next = new_node;
   connector_node = connector_node -> next;

   temp_product_code++;
   number_of_items++;

   }
}

void display(info_fields *table){

    if(table == NULL){
       printf(" TABLE EMPTY\n");
    }else{
       while(table != NULL){
           printf("code = %d\n", table -> product_code);
           table = table -> next;
       }

    }

}

void valid_product_quantity(info_fields *product_info, int product_code_input){
   printf("\n*******quantity and price function under construction, no food for you*******\n");
}

void valid_product_code(){

    int product_code_input;
    scanf("%d" , &product_code_input);
    if((product_code_input % 10 >= 1 && product_code_input % 10 <= 6) && (product_code_input / 10 >= 1 && product_code_input / 10 <= 6)){

        valid_product_quantity(product_info, product_code_input);

    } else {

        printf("\t PLEASE ENTER VALID FOOD CODE \t \n");
        valid_product_code();

    }

}

int main(){

   create_product_table();
   //display(product_info);

   int product_code_input;
   int item_quantity;

   printf("\t WELCOME TO FOOD VENDING MACHINE \t \n");
   printf("***************************************************\n");
   printf("\t PLEASE ENTER THE FOOD CODE FOR THE ITEM YOU WANT TO ORDER \t \n");
   valid_product_code();

   return 0;
}
