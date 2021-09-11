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

// Initialize Counter for ticket number
int ticket_counter = 100;

// Functions for operating on Ticket Table
int is_empty(Ticket*, Ticket*);
void compute_choice(int, Ticket**, Ticket**, Rticket**, Rticket**);
void print_stack_choice();
void get_stack(int);
void generate_ticket(Ticket**, Ticket**);
void update(Ticket*, Ticket*);
void delete(Ticket**, Ticket**, int);
void display(Ticket*);
void save(Ticket*, Ticket*, Rticket*, Rticket*);
void search(Ticket*, Ticket*);

// Functions to operate on Resolved Ticket Table
void resolve_ticket(Ticket**, Ticket**, Rticket**, Rticket**);
void display_resolved(Rticket*);

int main()
{
    int choice;
    
    // initializing head and tail for Tickets and Resolved tickets table
    Ticket* thead = NULL;
    Ticket* ttail = NULL;
    Rticket* rthead = NULL;
    Rticket* rttail = NULL;
    
    // Infinite loop so we don't have to run program everytime to use another function
    while(1){
        
        printf("\t Got an Issue? Generate a ticket here!\t \n");
        printf("___________________________________________________________");
        printf("\n");

	    // User picks the operation they want to perform
        printf("Enter the no corresponding to what you want to do\n\n1 -> Generate issue ticket\n2 -> Display all tickets\n3 -> Update tickets\n4 -> Delete ticket\n5 -> Search ticket\n6 -> Resolve issue\n7 -> Display resolved tickets\n8 -> exit\n");

        scanf("%d", &choice);

	    // check if choice is valid
        if(choice >= 1 && choice <= 8){

	       // if valid send to compute the choice, where it will redirect to appropiate function
           compute_choice(choice, &thead, &ttail, &rthead, &rttail);

        } else {

           //if not valid skip over the the rest of the loop and start again
           printf("\nEnter valid code\n\n");
           continue;

        }

        printf("\t Happy hacking!\n");
        printf("\n");

        // To add some delay between operations, so that the operations choice doesn't immidiately appear again
        // adds one sec delay
        sleep(2);

    }
}

// checks if Table is empty or not
int is_empty(Ticket* head, Ticket* tail)
{
    if(head == NULL && tail == NULL){
        return 1;
    }
    return 0;
}

/**
 * Function to compute the operation user entered and redirect to appropiate function
 *
 * Parameters: 
 * integer choice: number corresponding to the operation
 */ 

void compute_choice(int choice, Ticket **thead, Ticket **ttail, Rticket **rthead, Rticket **rttail)
{
    
    switch(choice){
        
        case 1: generate_ticket(&(*thead), &(*ttail));
                break;
        case 2: display(*thead);
                break;
        case 3: update(*thead, *ttail);
                break;
        case 4:	delete(&(*thead), &(*ttail), 0);
                break;
        case 5: search(*thead, *ttail);
                break;
        case 6: resolve_ticket(&(*thead), &(*ttail), &(*rthead), &(*rttail));
                break;
        case 7: display_resolved(*rthead);
                break;
        case 8: save(*thead, *ttail, *rthead, *rttail);
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
    printf("Stack:\n1 -> MERN/MEAN\n2 -> Flutter/Firebase\n3 -> Blockchain\n4 -> Android development\n5 -> Java/C++\n6 -> Other\n");
}

void get_stack(int stack){
    
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

void generate_ticket(Ticket **head, Ticket **tail){
    
    Ticket* new_ticket = (Ticket*) malloc (sizeof(Ticket));
    time_t timestamp = time(NULL);
    char temp;

    new_ticket -> ticket_number = ticket_counter;
    ticket_counter++;

    printf("Enter Team Number:");
    scanf("%d", &(new_ticket -> team_code));

    printf("Enter Stack Choice: ");
    print_stack_choice();
    scanf("%d", &(new_ticket -> stack));
    printf("\n");

    printf("Enter your issue(not more than 500 characters): ");
    scanf("%c",&temp); // temp node to clear buffer 
    fgets(new_ticket->issue, ISSUE, stdin); // fgets reads a line from the standard input stream and stores it in the given array

    new_ticket -> time_added = localtime(&timestamp);
    new_ticket -> next = NULL;

    if(is_empty(*head, *tail)){
        
        (*head) = (*tail) = new_ticket;
        printf("Ticket Generated!\n\n");
        return;
    } 
        
    (*tail)->next = new_ticket;
    (*tail) = new_ticket;

    printf("Ticket Generated!\n\n");
}

void update(Ticket* head, Ticket* tail){

    int ticket_number_in;
    int flag = 0;
    char temp;

    printf("Enter Ticket number for the ticket you want to update: ");
    scanf("%d", &ticket_number_in);

    if(is_empty(head, tail)){
        printf("Table Empty. Try generating ticket\n");
        return;
    }

    while(head){

        if(head-> ticket_number == ticket_number_in){
            flag = 1;
            break;
        }

        head = head -> next;
    }
    

    if(flag){

        printf("Enter Team Number:");
        scanf("%d", &(head -> team_code));

        printf("Enter Stack Choice: ");
        print_stack_choice();
        scanf("%d", &(head -> stack));
        printf("\n");

        printf("Enter your issue(not more than 500 characters): ");
        scanf("%c",&temp); // temp node to clear buffer 
        fgets(head->issue, ISSUE, stdin); // fgets reads a line from the standard input stream and stores it in the given array

    } else {
        printf("Ticket not found. Try again with valid ticket number");
    }


}
void delete(Ticket** head, Ticket** tail, int ticket_number_res){

    int ticket_number_in;
    int flag = 0;

    if(ticket_number_res){
        ticket_number_in = ticket_number_res;
    } else {
        printf("Enter Ticket number for the ticket you want to delete: ");
        scanf("%d", &ticket_number_in);
    }

    if(is_empty(*head, *tail)){
        printf("Table Empty. Try generating ticket\n");
        return;
    }

    Ticket *temp = (*head);
    Ticket *prev = NULL;

    if (temp != NULL && temp->ticket_number == ticket_number_in)
    {
        (*head)= temp->next; // Changed head
        free(temp); // free old head
        
        // if there was only one node
        if((*head) == NULL){
            (*tail) = NULL;
        }

        printf("Ticket Deleted");
        return;

    } else {

        while(temp){
            
            if(temp -> ticket_number == ticket_number_in){
                flag = 1;
                break;
            }

            prev = temp;
            temp = temp -> next;
        }

        if(flag){   
            prev -> next = temp -> next;
            printf("Ticket Deleted!");
        } else {
            printf("Ticket not found. Try again with valid ticket number");
        }
    }
}

void display(Ticket* temp){
   
    if(!temp){
       printf("No tickets\n");
    }
        while(temp){
            printf("\n__________________________________________\n\n");
            printf("|Ticket number : %d\n" , temp -> ticket_number);
            printf("|Team Code : %d\n", temp-> team_code);
            printf("|Stack : ");
            get_stack(temp -> stack);
            printf("\n");
            printf("|Time added : %s", asctime(temp -> time_added));
            printf("|Issue: %s\n", temp -> issue);
            printf("__________________________________________\n\n");
            
            temp = temp -> next;
        }
        
   
}

void save(Ticket* thead, Ticket* ttail, Rticket* rthead, Rticket* rttail){
    
    printf("Sorry you are trapped and can't exit now");

}

void search(Ticket* thead, Ticket* ttail){

    int search_by;
    Ticket* head = thead;
    Ticket* tail = ttail;

    printf("Search by : \n1 -> Ticket Number\n2 -> Team Number\n3 -> Stack\n");

    scanf("%d", &search_by);
    
    if(is_empty(head, tail)){
        printf("Table Empty. Try generating ticket");
        return;
    }

    if(search_by == 1){

        int ticket_number_in;
        int flag = 0;
        printf("Ticket Number: ");
        scanf("%d", &ticket_number_in);

        while(head){

            if(head-> ticket_number == ticket_number_in){
                
                Ticket* temp = head;
                display(temp);
                flag = 1;
            }

            head = head -> next;
        }

        if(!flag){
            printf("No tickets found.\n");
        }

    } else if(search_by == 2){

        int team_code_in;
        int flag = 0;
        printf("Team Number: ");
        scanf("%d", &team_code_in);

        while(head){

            if(head-> team_code == team_code_in){

                Ticket* temp = head;
                temp -> next = NULL;
                display(temp);
                flag = 1;
            }

            head = head -> next;
        }

        if(!flag){
            printf("No tickets found.\n");
        }

    } else if(search_by == 3){

        int stack_in;
        int flag = 0;
        printf("Stack: ");
        print_stack_choice();
        scanf("%d", &stack_in);
 
        while(head){

            if(head-> stack == stack_in){

                Ticket* temp = head;
                temp -> next = NULL;
                display(temp);
                flag = 1;
            }

            head = head -> next;
        }

        if(!flag){
            printf("No tickets found.\n");
        }

    } 

};

void resolve_ticket(Ticket** thead, Ticket** ttail, Rticket** rthead, Rticket** rttail){

    int ticket_number_in;
    int flag = 0;

    printf("Enter Ticket number for the ticket you want to mark resolved: ");
    scanf("%d", &ticket_number_in);

    if(is_empty(*thead, *ttail)){
        printf("Table Empty. Try generating ticket\n");
        return;
    }
    
    Ticket* temp = (*thead);

    while(temp){

        if(temp-> ticket_number == ticket_number_in){
            flag = 1;
            break;
        }
        temp = temp -> next;

    }

    if(flag){

        Rticket* new_resolved_ticket = (Rticket*) malloc (sizeof(Rticket));
        time_t time_resolved = time(NULL);
            
        new_resolved_ticket -> ticket_number = temp -> ticket_number;
        new_resolved_ticket -> team_code = temp -> team_code;
        new_resolved_ticket -> stack = temp-> stack;
        strcpy(new_resolved_ticket -> issue, temp -> issue);
        new_resolved_ticket -> time_added = temp -> time_added;
        new_resolved_ticket -> time_resolved =  localtime(&time_resolved);
        new_resolved_ticket -> next = NULL;
        
        if(rthead == NULL && rttail == NULL){
            (*rthead) = (*rttail) = new_resolved_ticket;
        } else {
            (*rttail)->next = new_resolved_ticket;
            (*rttail) = new_resolved_ticket;
        }

        delete(&(*thead), &(*ttail), ticket_number_in);

    } else {
        printf("Ticket not found. Try again with valid ticket number");
    }

}

void display_resolved(Rticket* head){

    if(head == NULL){
        printf("Its lonely here");
    }
    
     while(head){
            
        printf("\n__________________________________________\n\n");
        printf("|Ticket number : %d\n" , head -> ticket_number);
        printf("|Team Code : %d\n", head -> team_code);
        printf("|Stack : ");
        get_stack(head -> stack);
        printf("\n");
        printf("|Time added : %s", asctime(head -> time_added));
        printf("|Time resolved: %s", asctime(head -> time_resolved));
        printf("|Issue: %s\n", head -> issue);
        printf("__________________________________________\n\n");
        
        head = head->next;
        
    }

}

// end
