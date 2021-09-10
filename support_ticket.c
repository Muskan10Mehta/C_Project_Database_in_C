/**
 * Project Statement: Setting up a whole database for programs with little requirements can be too much work, 
 *                    it is easier and faster to implement a database in C which is lightweight and easy to use.
 *                    This program implements database for a ticket management system for hackathons. 
 *                    It consists of two tables. Ticket table and Resolved ticket table, both are implemented using structs and linked lists.
 *                    It covers all the basic features of a database management system :
 *                    1. Create new entry
 *                    2. Read and display
 *                    3. Update previous entries
 *                    4. Delete entry
 *                    5. Search through table
 *                    continue at README.me file...
 *
 * Compilation: gcc -o ticket support_ticket.c
 * Execution: ./ticket
 *
 * @Muskan, 1910990681, 02/08/2021
 * C project - Database in C for Ticket management system
 *
 * Resources: 
 * 1. geeksforgeeks
 * 2. codeforwin
 * 3. stackoverflow
 * 4. tutorialspoint
 * 5. assignments
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#define ISSUE 500

/**
 * Structure for ticket table
 *
 * Stores: 
 *
 * integer ticket number
 * integer team code
 * int stack code 
 * char array of issue
 * structure tm for time added timestamp
 * pointer to next node in linked list
 *
 */

struct ticket
{
    
    int ticket_number;
    int team_code;
    int stack;
    char issue[ISSUE];
    struct tm* time_added;
    struct ticket* next;
    
};

/**
 * Structure for resolved ticket table
 *
 * Stores:
 *
 * integer ticket number
 * integer team code
 * int stack code
 * char array of issue
 * structure tm for time added timestamp
 * structure tm for time resolved timestamp 
 * pointer to next node in linked list
 *
 */

struct resolved_ticket
{
    
    int ticket_number;
    int team_code;
    int stack;
    char issue[ISSUE];
    struct tm* time_added;
    struct tm* time_resolved;
    struct resolved_ticket* next;
    
};

typedef struct ticket Ticket;
typedef struct resolved_ticket Rticket;

// initializing head and tail for Tickets and Resolved tickets table
Ticket* thead = NULL;
Ticket* ttail = NULL;
Rticket* rthead = NULL;
Rticket* rttail = NULL;

// Initialize Counter for ticket number
int ticket_counter = 100;


// Functions for operating on Ticket Table
void compute_choice(int);
void print_stack_choice();
void generate_ticket();
void modify(Ticket**);
void delete(Ticket**, Ticket**);
void search(int, int);
void get_stack(int);

// Functions to operate on Resolved Ticket Table
void display(Ticket*);
void add_resovled(Ticket**);
void resolve_ticket();
void display_resolved(Rticket*);


int main()
{
    int choice;

    // Infinite loop so we don't have to run program everytime to use another function
    while(1){
        
        printf("\t Got an Issue? Generate a ticket here!\t \n");
        printf("___________________________________________________________");
        printf("\n");

	// User picks the operation they want to perform
        printf("Enter the no corresponding to what you want to do\n\n1 Generate issue ticket\n2 Display all tickets\n3 Modify tickets\n4 Delete ticket\n5 Search ticket\n6 Resolve issue\n7 Display resolved tickets\n");
        scanf("%d", &choice);

	// check if choice is valid
        if(choice >= 1 && choice <= 7){

	   // if valid send to compute the choice, where it will redirect to appropiate function
           compute_choice(choice);

        } else {

           //if not valid skip over the the rest of the loop and start again
           printf("\nEnter valid code\n\n");
           continue;

        }
        printf("Happy hacking\n");
        printf("\n");

	// To add some delay between operations, so that the operations choice doesn't immidiately appear again
	// adds one sec delay
        sleep(1);

    }
}

/**
 * Function to compute the operation user entered and redirect to appropiate function
 *
 * Parameters: 
 * integer choice: number corresponding to the operation
 */ 

void compute_choice(int choice)
{
    // Search by stores the choice for parameter to search tickets 
    // 1 for search by ticket number
    // 2 for search by team code
    // 3 for search by stack
    int search_by;
    
    switch(choice){
        
        case 1: generate_ticket();
                break;
        case 2: display(thead);
                break;
        case 3:
        case 4:	search(choice, 1); // since we can only modify and delete one node at a time, so we are sending 1 for search by Ticket number as that is unique
                break;
        case 5: printf("Search by: \n1 Ticket Number\n2 Team Code\n3 Stack");
                scanf("%d", &search_by);
                search(choice, search_by);
                break;
        case 6: resolve_ticket();
                break;
        case 7: display_resolved(rthead);
                break;
       }
}

/**
 * Function to print stack choices text which consists of different stacks and technologies and their corresponding number
 *
 * The stack choices need to be printed a couple of time, hence made it into function for easy use
 */

void print_stack_choice()
{
    printf("Stack:\n1 MERN/MEAN \n2 Flutter/Firebase\n3 Blockchain\n4 Android development\n5 Java/C++\n6 Other\n");
}

/**
 * Function to generate a ticket
 *
 * This function:
 * 1. Inputs the data for a new ticket
 * 2. Adds the time stamp
 * 3. Adds a new node to the Ticket table
 * 4. Increments the ticket number counter
 *
 */

void generate_ticket()
{   
    Ticket* new_ticket = (Ticket*) malloc (sizeof(Ticket));
    char temp;
    
    time_t time_added = time(NULL);
    new_ticket-> time_added = localtime(&time_added);
    
    printf("Enter team number: ");
    scanf("%d", &new_ticket -> team_code);
    printf("\n");
    
    print_stack_choice();
    scanf("%d", &new_ticket -> stack);
    printf("\n");
    
    printf("Enter your issue: ");
    scanf("%c",&temp); // temp node to clear buffer 
    fgets(new_ticket->issue, ISSUE, stdin); // fgets reads a line from the standard input stream and stores it in the given array
    
    new_ticket -> ticket_number = ticket_counter;
    new_ticket -> next = NULL;
    
    ticket_counter++;
    
    // add new node to Ticket linked list
    if((thead == NULL) && (ttail == NULL))
    {
       thead = new_ticket;
       ttail = thead;
    }else
    {
       ttail->next = new_ticket;
       ttail = ttail->next;
    }
   
   printf("Ticket Generated!\n");
   
}

/**
 * Function to update an existing ticket
 *
 * Parameters: 
 * Pointer to the ticket searched by the searched fucntion
 *
 * This function takes neew inputes for the ticket and over-writes the old data
 */

void modify(Ticket** ticket_modify)
{
    char temp;
    
    printf("Team number: ");
    scanf("%d", &(*ticket_modify) -> team_code);
    printf("\n");
    
    print_stack_choice();
    scanf("%d", &(*ticket_modify) -> stack);
    printf("\n");
    
    printf("Enter your issue: ");
    scanf("%c",&temp); //temp statement to clear buffer
    fgets((*ticket_modify) -> issue, ISSUE, stdin);
    
    printf("Ticket updated!\n");
}

/** 
 * Function to delete an existing ticket
 *
 * Parameters
 * Pointer the the ticket before the target ticket
 * Pointer the the the target ticket that is the ticket to be deleted
 *
 * both these parameters are computed in the seacrh function
 */

void delete(Ticket** prev, Ticket** ticket_delete)
{
    Ticket* temp_head = thead;

    // if the ticket to be deleted is the head of the Ticket linked list
    // Save head in temp node
    // make the node after head the new node and free the previous node 

    if((*prev) == NULL){
        
	// if there is only one element in the list
	// reset the list
        if(thead == ttail)
        {
            thead = NULL;
            ttail = NULL;
        }
        
        thead = temp_head->next;
        free(temp_head);
        
    }else {
         
         (*prev) -> next = (*ticket_delete) -> next;
         free((*ticket_delete));
         
    }
    
}

/**
 * Function to search a ticket in the ticket table
 *
 * Parameters: 
 * integer choice: the choice of operation initially given by the user
 * integer seacrh_by: the choice of search by field inputed by user
 *
 * this function searched the ticket by ticket number for 
 * Functions : modify(Ticket**) and delete(Ticket**, Ticket**)
 * It searches on basis of other parameters as specified by the user
 */

void search(int choice, int search_by)
{
    
    int ticket_number_input;
    int team_code_input;
    int stack_input;
    int flag = 0; // values changes to 1 if element is found
    
    Ticket* ticket_searched = (Ticket*) malloc (sizeof(Ticket)); // stores the ticket matched in search
    Ticket* prev = (Ticket*) malloc (sizeof(Ticket)); // pointer to node previous to current node
    Ticket* curr = (Ticket*) malloc (sizeof(Ticket)); // pointer to current node
    
    // search by ticket number
    if(search_by == 1)
    {
        printf("Enter Ticket number: ");
        scanf("%d", &ticket_number_input);
        
        prev = NULL;
        curr = thead;
        
        flag = 0;
        
        while(curr)
        {
            if(curr -> ticket_number == ticket_number_input)
            {
                flag = 1;
                break;
            }
            
            prev = curr;
            curr = curr -> next;
            
        }
        
	// if found it checks what the initial operation request was and calls that function
        if(flag == 1)
        {
             ticket_searched = curr;
             
             switch(choice){
                 
                case 3: modify(&ticket_searched);
                        break;
                case 4: delete(&prev, &ticket_searched);
                        printf("Ticket deleted. \n");
                        break;
		case 5: ticket_searched-> next = NULL;
			display(ticket_searched);
                case 6: // as only one ticket can be added and removed at once, so we are searching for ticket to be marked resolved by ticket number which is unique
                        add_resovled(&ticket_searched);
			// after marking the ticket resolved, delete it from ticket table
			delete(&prev, &ticket_searched);
                        break;
              }
        }else 
        {
             printf("Ticket not found. Try again.\n");
        }
    
    }else if(search_by == 2) // search by team code
    {
        printf("Enter Team Code: ");
        scanf("%d", &team_code_input);
        
        curr = thead;
        flag = 0;
        
        while(curr){
            
            if(curr -> team_code == team_code_input){
                ticket_searched = curr;
                ticket_searched-> next = NULL; // isolates the ticket from the rest of the list
                display(ticket_searched); // prints all tickets that matches the search by criteria
                flag = 1;
            }
            
            curr = curr -> next;
        }
        
        if(!flag){
            printf("Ticket not found. Try another team code.");
        }
        
    } else if(search_by == 3) // search by stack
    {
        printf("Enter stack Code: ");
        print_stack_choice();
        scanf("%d", &stack_input);
        
        curr = thead;
        flag = 0;
        
        while(curr){
            
            if(curr -> stack == stack_input || (stack_input >= 6) && (curr -> stack >= 6))
            {
                ticket_searched = curr;
                ticket_searched-> next = NULL; // isolates the ticket from the rest of the list
                display(ticket_searched); // prints all tickets that matches the search by criteria
                flag = 1;
                
            }
            
            curr = curr -> next;
        }
        
        if(!flag)
        {
            printf("Ticket not found. Try another stack.");
        }
    }
}

/**
 * Function to add ticket from Ticket table to the Resolved ticket table
 *
 * Parameters: 
 * Pointer to the ticket that is to be marked resolved as searched by the search function
 *
 * This functions:
 * 1. Copies the data from the ticket to be marked resolved
 * 2. Adds the resolved timestamp
 * 3. Adds the Resolved ticket to the resolved ticket table
 */

void add_resovled(Ticket** ticket_resolved)
{
    Rticket* new_resolved_ticket = (Rticket*) malloc (sizeof(Rticket));
    time_t time_resolved = time(NULL);
    
    new_resolved_ticket -> ticket_number = (*ticket_resolved) -> ticket_number;
    new_resolved_ticket -> team_code = (*ticket_resolved) -> team_code;
    new_resolved_ticket -> stack = (*ticket_resolved) -> stack;
    strcpy(new_resolved_ticket -> issue, (*ticket_resolved) -> issue);
    new_resolved_ticket -> time_added = (*ticket_resolved) -> time_added;
    new_resolved_ticket -> time_resolved =  localtime(&time_resolved);
    new_resolved_ticket -> next = NULL;
    
    if(rthead == NULL && rttail == NULL)
    {
       rthead = new_resolved_ticket;
       rttail = rthead;
    }else
    {
       rttail->next = new_resolved_ticket;
       rttail = rttail->next;
    }
    
    printf("Ticket resolved!\n");
      
}

/**
 * Function to mark a ticket to be resolved
 */
void resolve_ticket()
{
    printf("Good Job on solving an issue! Mark ticket resolved here -> \n");
    // calls a search for choice 6 resolve ticket and 1 for search by ticket number
    search(6,1);
    
}

/* 
 * Function to display the Resolved tickets table
 *
 * Parametrs: 
 * Head of the resolved ticket table linked list
 */

void display_resolved(Rticket* head)
{
    
     if(head == NULL){
        
        printf("No tickets resolved yet.\n");
        
    }else{
        
        while(head){
            
            printf("\n__________________________________________\n\n");
            printf("Ticket number : %d\n" , head -> ticket_number);
            printf("Team Code : %d\n", head -> team_code);
            printf("Stack : ");
            get_stack(head -> stack);
            printf("\n");
            printf("Time added : %s", asctime(head -> time_added));
            printf("Time resolved: %s", asctime(head -> time_resolved));
            printf("Issue: %s\n", head -> issue);
            printf("__________________________________________\n\n");
        
            head = head->next;
        
        }
    }
}

/**
 * Function to print the stack corresponding to the stack code when display ticket function is called
 *
 * Parameter: 
 * integer stack code
 */

void get_stack(int stack)
{
    switch(stack){
        case 1: printf("MERN/MEAN");
                break;
        case 2: printf("Flutter/Firebase");
                break;
        case 3: printf("Blockchain");
                break;
        case 4: printf("Android development");
                break;
        case 5: printf("Java/c++");
                break;
        case 6: printf("Other");
                break;
        default: printf("Other");
    }
    
}

/**
 * Function to print the ticket table, or a single ticket information
 *
 * Paramter:
 * Head of the Ticket node or Ticket table linked list
 */

void display(Ticket* head)
{
    
    if(head == NULL){
        
        printf("No tickets generated yet. Generate one!\n");
        
    }else{
        
        while(head){
            
            printf("\n__________________________________________\n\n");
            printf("Ticket number : %d\n" , head -> ticket_number);
            printf("Team Code : %d\n", head -> team_code);
            printf("Stack : ");
            get_stack(head -> stack);
            printf("\n");
            printf("Time added: %s", asctime(head-> time_added));
            printf("Issue: %s\n", head -> issue);
            printf("__________________________________________\n\n");
        
            head = head->next;
        
        }
    }
}

// end of file 
