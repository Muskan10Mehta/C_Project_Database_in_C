/**
 * @Muskan, 1910990681, 05/08/2021
 * C project
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
//#include <time.h>

//ticket table
struct ticket
{
    
    int ticket_number;
    int team_code;
    int stack;
    char issue[500];
    int flag; 
    struct ticket* next;
    
};

//resolved ticket table
struct resolved_ticket
{
    
    int ticket_number;
    int team_code;
    int stack;
    char issue[500];
    int flag; 
    struct resolved_ticket* next;
    
};

typedef struct ticket Ticket;
typedef struct resolved_ticket Rticket;

Ticket* thead = NULL;
Ticket* ttail = NULL;
Rticket* rthead = NULL;
Rticket* rttail = NULL;
int ticket_counter = 100;

void compute_choice(int);
void print_stack_choice();
void generate_ticket();
void modify(Ticket**);
void delete(Ticket**, Ticket**);
void search(int, int);
void get_stack(int);
void display(Ticket*);

int main()
{
    int choice;
    
    while(1){
        
        printf("\t Got an Issue? Generate a ticket here!\t \n");
        printf("___________________________________________________________");
        printf("\n");

        printf("Enter the no corresponding to what you want to do\n\n1 Generate issue ticket\n2 Display all tickets\n3 Modify tickets\n4 Delete ticket\n5 Search ticket\n6 Resolve issue\n7 Dispaly resolved tickets\n");
        scanf("%d", &choice);

        if(choice >= 1 && choice <= 7){

           compute_choice(choice);

        } else {

           printf("\nEnter valid code\n\n");
           continue;

        }
        printf("Happy hacking\n");
        printf("\n");
        sleep(1);

    }
}

void compute_choice(int choice)
{
    int search_by;
    
    switch(choice){
        
        case 1: generate_ticket();
                break;
        case 2: display(thead);
                break;
        case 3:
        case 4: search(choice, 1);
                break;
        case 5: printf("Search by: \n1 Ticket Number\n2 Team Code\n3 Stack");
                scanf("%d", &search_by);
                search(choice, search_by);
                break;
       }
}

void print_stack_choice()
{
    printf("Stack:\n1 MERN/MEAN \n2 Flutter/Firebase\n3 Blockchain\n4 Android development\n5 Java/C++\n6 Other\n");
}
    
void generate_ticket()
{   
    Ticket* new_ticket = (Ticket*) malloc (sizeof(Ticket));
    
    printf("Enter team number: ");
    scanf("%d", &new_ticket -> team_code);
    printf("\n");
    
    print_stack_choice();
    scanf("%d", &new_ticket -> stack);
    printf("\n");
    
    printf("Enter your issue: ");
    //fgets(new_ticket -> issue, sizeof(new_ticket -> issue), stdin);
    scanf("%s", new_ticket -> issue);
    
    new_ticket -> ticket_number = ticket_counter;
    ticket_counter++;
    
    new_ticket -> flag = 1;
    new_ticket -> next = NULL;
    
    if((thead == NULL) && (ttail == NULL))
    {
       thead = new_ticket;
       ttail = thead;
    }else
    {
       ttail->next = new_ticket;
       ttail = ttail->next;
    }
   
   printf("Ticket Generated\n");
   
}

void modify(Ticket** ticket_modify)
{
    printf("Team number: ");
    scanf("%d", &(*ticket_modify) -> team_code);
    printf("\n");
    
    print_stack_choice();
    scanf("%d", &(*ticket_modify) -> stack);
    printf("\n");
    
    printf("Enter your issue: ");
    //fgets(new_ticket -> issue, sizeof(new_ticket -> issue), stdin);
    scanf("%s", (*ticket_modify) -> issue);
    
    printf("Ticket updated!\n");
}

void delete(Ticket** prev, Ticket** ticket_delete)
{
    Ticket* temp_head = thead;

    if((*prev) == NULL || (*ticket_delete) -> next == NULL){
        
        thead = temp_head->next;
        free(temp_head);
           
    } else {
         
         (*prev) -> next = (*ticket_delete) -> next;
         free((*ticket_delete));
         
    }

    printf("Ticket deleted. \n");
}

void search(int choice, int search_by)
{
    
    int ticket_number_input;
    int team_code_input;
    int stack_input;
    int flag = 0;
    
    Ticket* ticket_searched = (Ticket*) malloc (sizeof(Ticket));
    Ticket* prev = (Ticket*) malloc (sizeof(Ticket)); 
    Ticket* curr = (Ticket*) malloc (sizeof(Ticket));
    
    if(search_by == 1)
    {
        printf("Enter ticket number: ");
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
        
        if(flag == 1)
        {
             ticket_searched = curr;
             ticket_searched -> next = NULL;
             
             switch(choice){
                 
                case 3: modify(&ticket_searched);
                        break;
                case 4: delete(&prev, &ticket_searched);
                        break;
              }
        }else 
        {
             printf("Ticket not found. Try again.\n");
        }
    
    }else if(search_by == 2)
    {
        printf("Enter Team Code: ");
        scanf("%d", &team_code_input);
        
        curr = thead;
        flag = 0;
        
        while(curr){
            
            if(curr -> team_code == team_code_input){
                ticket_searched = curr;
                ticket_searched-> next = NULL;
                display(ticket_searched);
                flag = 1;
            }
            
            curr = curr -> next;
        }
        
        if(!flag){
            printf("Ticket not found. Try another team code.");
        }
        
    } else if(search_by == 3)
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
                ticket_searched-> next = NULL;
                display(ticket_searched);
                flag = 1;
                
            }
            
            curr = curr -> next;
        }
        
        if(!flag){
            printf("Ticket not found. Try another stack.");
        }
    }
}

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
            printf("Issue: %s\n", head -> issue);
            printf("__________________________________________\n\n");
        
            head = head->next;
        
        }
    }
}
