#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    struct node *prev;
    char name[50];
    long num;
    int freq;
    struct node *next;
}*first=NULL,*last=NULL;
struct node *t;

struct history {
    long num;
    char name[50];
}arr[50];

void create() {
    first=(struct node*)malloc(sizeof(struct node));
    if(first==NULL)
        printf("Memory not allocated");
    else {
        first->prev=NULL;
        first->next=NULL;
        first->freq=0;
        printf("Enter Name: ");
        scanf("%s",first->name);
        printf("Enter Number: ");
        scanf("%ld",&first->num);
        last=first;
    }
}

void add() {
    t=(struct node*)malloc(sizeof(struct node));
    if(t==NULL)
        printf("Memory not allocated\n");
    else {
        printf("Enter Name: ");
        scanf("%s",t->name);
        printf("Enter Number: ");
        scanf("%ld",&t->num);
        t->next=NULL;
        t->prev=last;
        t->freq=0;
        last->next=t;
        last=t;
    }
}

int delContact(char c[]) {
    struct node* tempo;
    struct node* q=first;
    while(q!=NULL) {
        if(strcmp(c,q->name)==0) {
            if(q==first) {
                tempo=first;
                q->next->prev=NULL;
                first=q->next;
                q->next=NULL;
                free(tempo);
                return 1;
            }
            else if(q==last) {
                tempo=last;
                q->prev->next=NULL;
                last=q->prev;
                q->prev=NULL;
                free(tempo);
                return 1;
            }
            else {
                tempo=q;
                q->prev->next=q->next;
                q->next->prev=q->prev;
                q->next=NULL;
                q->prev=NULL;
                free(tempo);
                return 1;
            }
        }
        q=q->next;
    }
    return 0;
}

int editContact(char c[]) {
    int x;
    long n;
    char new[50];
    struct node* tempo;
    struct node* q=first;
    while(q!=NULL) {
        if(strcmp(c,q->name)==0) {
            printf("Enter 1 to edit the Contact Name\n");
            printf("Enter 2 to edit the Contact Number\n");
            printf("Enter your choice: ");
            scanf("%d",&x);
            switch(x) {
                case 1:
                    printf("Enter the new Contact Name: ");
                    scanf("%s",new);
                    strcpy(q->name,new);
                    break;
                
                case 2:
                    printf("Enter the new Contact Number: ");
                    scanf("%ld",&n);
                    q->num=n;
                    break;
                
                default:
                    printf("Invalid Input");
            }
            return 1;
        }
    q=q->next;
    }
    return 0;
}

struct node* searchContact(char c[]) {
    struct node* p=first;
    while(p!=NULL) {
        if(strcmp(c,p->name)==0)
            return p;
        else
            p=p->next;
    }
    return NULL;
}
    
void Display(struct node* p) {
    if(p==NULL) {
        printf("Contact List is empty!\n");
        return;
    }
    while(p->next!=NULL){
        printf("%s: %ld\n", p->name,p->num);
        p=p->next;
    }
    printf("%s: %ld\n", p->name,p->num);
}

void sortDisplay() {
    if(first==NULL){
        printf("Contact List is empty!\n");
        return;
    }
    char tempo[50];
    long x;
    struct node* p=first;
    struct node* q=first->next;
    while(p!=NULL) {
        q=p->next;
        while(q!=NULL) {
            if(strcmp(p->name,q->name)>0) {
                strcpy(tempo,p->name);
                x=p->num;
                strcpy(p->name,q->name);
                p->num=q->num;
                strcpy(q->name,tempo);
                q->num=x;
            }
            q=q->next;
        }
        p=p->next;
    }
    Display(first);
}

void call(long x) {
    int con=0;
    struct node* p=first;
    while(p!=NULL) {
        if(x==p->num) {
            printf("Calling %s\n",p->name);
            con++;
            p->freq++;
            break;
        }
        p=p->next;
    }
    if(con==0)
        printf("Calling %ld\n",x);
}

void freqCalled() {
    struct node* p=first;
    while(p!=NULL) {
        if(p->freq>1)
            printf("%s\n",p->name);
        p=p->next;
    }
}

void contact_history(long n,int i) {
    char ch[50];
    int flag=0;
    struct node *temp=first;
    while(temp!=NULL) {
        if(temp->num==n) {
            strcpy(ch,temp->name);
            flag=1;
            break;
        }
        temp=temp->next;
    }
    if(flag==0)
        strcpy(ch,"NULL");
    arr[i].num=n;
    strcpy(arr[i].name,ch);
}

void display_history(int n) {
    if(n==0)
        printf("Call History is Empty!\n");
    else {
        for(int i=n-1;i>=0;i--) {
            printf("Call %d:\n",i+1);
            if(strcmp(arr[i].name,"NULL")==0)
                printf("Name: Unknown\n");
            else
                printf("Name: %s\n",arr[i].name);
            printf("Phone Number: %ld\n\n",arr[i].num);
        }
    }
}

int main()
{
    struct node* temp;
    long x;
    int cnt=1,call_cnt=0,choice;
    char tem[50];
    printf("\t\t\tPHONE DIRECTORY\n");
    do {
        printf("\n");
        printf("--------------------------------------------------------------------\n");
        printf("Enter 1 to Add a Contact\n");
        printf("Enter 2 to Delete a Contact\n");
        printf("Enter 3 to Edit a Contact\n");
        printf("Enter 4 to Search a Contact\n");
        printf("Enter 5 to Display the Contact List\n");
        printf("Enter 6 to Sort & Display the Contact List\n");
        printf("Enter 7 to Call a Contact\n");
        printf("Enter 8 to view Frequently called Contacts\n");
        printf("Enter 9 to view Call History\n");
        printf("Enter 0 to Exit\n");
        printf("--------------------------------------------------------------------\n\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        
        switch(choice) {
            case 1:
                if(cnt==1)
                    create();
                else
                    add();
                break;
            
            case 2:
                if(first==NULL) {
                    printf("Contact List is Empty!\n");
                }
                else {
                    printf("Enter the contact name that you want to remove: ");
                    scanf("%s",tem);
                    int delete=delContact(tem);
                    if(delete==0)
                        printf("Contact not found!\n");    
                    else if(delete==1)
                        printf("%s successfully deleted\n",tem);
                }
                break;
            
            case 3:
                if(first==NULL) {
                    printf("Contact List is Empty!\n");
                }
                else {
                    printf("Enter the contact name you want to edit: ");
                    scanf("%s",tem);
                    int edit=editContact(tem);
                    if(edit==0)
                        printf("Contact not found!\n");    
                    else 
                        printf("Contact edited successfully\n");
                }
                break;
            
            case 4:
                if(first==NULL) {
                    printf("Contact List is Empty!\n");
                }
                else {
                    printf("Enter the name of the Contact: ");
                    scanf("%s",tem);
                    temp=searchContact(tem);
                    if(temp==NULL)
                        printf("Contact not found!\n");    
                    else {
                        int c;
                        printf("Contact Number: %ld\n",temp->num);
                        printf("Do you want to call %s?\n",temp->name);
                        printf("Enter 1 to call\n");
                        printf("Enter 0 to exit\n");
                        printf("Enter your choice: ");
                        scanf("%d",&c);
                        switch(c) {
                            case 1:
                                call(temp->num);
                                contact_history(temp->num,call_cnt);
                                call_cnt++;
                                break;
                            
                            case 0:
                                break;
                            
                            default:
                                printf("Invalid Input\n");
                                break;
                        }
                    }
                }
                break;
            
            case 5:
                Display(first);
                break;
            
            case 6:
                sortDisplay();
                break;
            
            case 7:
                printf("Enter the Contact Number: ");
                scanf("%ld",&x);
                call(x);
                contact_history(x,call_cnt);
                call_cnt++;
                break;
                
            case 8:
                if(call_cnt==0) {
                    printf("No calls are made till now!\n");
                }
                else {
                    printf("Frequently Contacted\n");
                    freqCalled();
                }
                break;
                
            case 9:
                display_history(call_cnt);
                break;
                
            case 0:
                exit(0);
                break;
                
            default:
                printf("Invalid Input\n");
                cnt--;
                break;
        }
        cnt++;
    }while(choice!=0);
    return 0;
}