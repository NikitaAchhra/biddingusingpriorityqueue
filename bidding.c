#include<stdio.h>
#include<conio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>


typedef struct CAR
{
    char name[40],rn[20],model[40],color[40],age[40],fuel[20];
    float minBit;
    struct CAR *next;
}car;
car *cstart=NULL,*cend=NULL;


typedef struct priqueue
{
   char custname[40];
   float bid;
   struct priqueue *next;
}bidders;
bidders *front=NULL,*rear=NULL;


int flag=0;

int option1,option2,option3,option4=1;




void insert (char custname[] ,float bid) //devansh insert user's name and bit in priority queue in decending order of bid
{
    bidders *ptr,*p,*prev;
    ptr=(bidders*)malloc(sizeof(bidders));
    strcpy(ptr->custname,custname);
    ptr->bid=bid;
    ptr->next=NULL;
    if(front==NULL)
    {
        front=rear=ptr;
        return;
    }
    prev=NULL;
    p=front;
    while(p!=NULL&&p->bid>=bid)
    {
        prev=p;
        p=p->next;
    }
    if(p==front)
    {
        ptr->next=front;
        front=ptr;
        return;
    }
    if(p==NULL)
    {
        prev->next=ptr;
        rear=ptr;
        return;
    }
    prev->next=ptr;
    ptr->next=p;
    return;
}


void destroy() // devansh destroy the priority queue afterauction
{
    bidders *p,*prev;
    prev=NULL;
    p=front;
    front=rear=NULL;
    while(p!=NULL)
    {
        prev=p;
        p=p->next;
        prev->next=NULL;
        free(prev);
    }
}



void auction(car *a) //ekta minbit testing,taking users info and calls insert,displays winner and deletes that car and calls destrory.
{
    char name[40];
    float bid;
    car *p;
    do
    {
        fflush(stdin);
        printf("\n\t\tEnter your name: ");
        gets(name);
        printf("\n\t\tEnter your bid: ");
        scanf("%f",&bid);
        if(bid<(a->minBit))
        {
            printf("\n\n\tplease enter bid greater than %f",a->minBit);
        }
        else
        {
            insert(name,bid);
            printf("\n\t\tPRESS 1 TO ENTER NEXT BID");
            printf("\n\t\tPRESS 0 TO END AUCTION");
            scanf("%d",&option4);
            system("CLS");
            printf("\t\t\t\tAUCTION HUB-THE PLACE WHERE ONE CAN GET BETTER\n\n");
            printdetails(a,0);
        }
    }while(option4!=0);
    system("CLS");
    printf("\t\t\t\tAUCTION HUB-THE PLACE WHERE ONE CAN GET BETTER\n\n");
    printf("\n\t\t\t\t\tCONGRATULATIONS %s",front->custname);
    printf("\n\t\t\t\t\tYOU OWN THE %s",a->name);
    printf("\n\t\t\t\t\tPAY THE %f AMOUNT AND ENJOY YOUR RIDE",front->bid);
    if(a==cstart)
    {
        cstart=cstart->next;
        a->next=NULL;
    }
    else if(a==cend)
    {
        p=cstart;
        while(p->next!=cend)
        {
            p=p->next;
        }
        cend=p;
        p->next=NULL;
    }
    else
    {
        p=cstart;
        while(p->next!=a)
        {
            p=p->next;
        }
        p->next=a->next;
        a->next=NULL;
    }
    free(a);
    destroy();
    printf("\n\t\t\t");
    system("PAUSE");
    system("CLS");
    printf("\t\t\t\tAUCTION HUB-THE PLACE WHERE ONE CAN GET BETTER\n\n");
}


int printdetails(car *p,int flag) // Nikita print the details of car selected by user and calls auction function if user wants to
{
    printf("\n\t\t\t\t CAR DETAILS\n\n");
    printf("\n\t\tCar Name: %s",p->name);
    printf("\n\t\tModel: %s",p->model);
    printf("\n\t\tColor: %s",p->color);
    printf("\n\t\tCar Age: %s",p->age);
    printf("\n\t\tFuel Source: %s",p->fuel);
    printf("\n\t\tRegistration Number: %s",p->rn);
    printf("\n\t\tBidding starts from: %f",p->minBit);
    if(flag==1)
    {

        printf("\n\t\tDo You Want To Start Auction(1-yes and 0-No): ");
        scanf("%d",&option3);
        if(option3==0)
        {
            system("CLS");
            printf("\t\t\t\tAUCTION HUB-THE PLACE WHERE ONE CAN GET BETTER\n\n");
            return 0;
        }
        else
        {
            auction(p);
            return 1;
        }
    }
}





void buy() //ekta diplay all cars available for auction an calls printdetails by passing selected car
{
    car *b;
    int i=1;
    b=cstart ;
    if (b==NULL)
    {
        printf ("\n\t\tNOTHING TO SELL\n");
        return;
    }
    while (b!=NULL)
    {
        printf ("\n\t\t%d. %s ",i,b->name);
        b=b->next;
        i++;
    }
    printf ("\n\t\tEnter your option : ");
    scanf ("%d",&option2);
    b=cstart;
    for (i=1;i<=option2-1;i++)
    {
        b=b->next;
          if (b==NULL)
            break;
    }
    if (b==NULL)
    {
        printf ("\nInvalid input\n");
        return;
    }
    system("CLS");
    printf("\t\t\t\tAUCTION HUB-THE PLACE WHERE ONE CAN GET BETTER\n\n");
    printdetails (b,1);
}

void file(FILE *fp)
{

    car *c=(car*)malloc(sizeof(car));
    fgets(c->name,sizeof(c->name),fp);
    fgets(c->model,sizeof(c->model),fp);
    fgets(c->color,sizeof(c->color),fp);
    fgets(c->age,sizeof(c->age),fp);
    fgets(c->fuel,sizeof(c->fuel),fp);
    fgets(c->rn,sizeof(c->rn),fp);
    fscanf(fp,"%f\n",&c->minBit);
    if (cstart==NULL)
    {
        cstart=cend=c;
        c->next=NULL;
    }
         else
         {
          cend->next=c;
          c->next=NULL;
          cend=c;
         }
}

void sell ()    //Nikita   create a linklist to store the details of
{

    car *c=(car*)malloc(sizeof(car));
    printf("\n\t\tEnter Details of car: ");
    fflush(stdin);
    printf("\n\t\tName : ");
    gets(c->name);
    fflush(stdin);
    printf("\n\t\tModel :");
    gets(c->model);
    fflush(stdin);
    printf("\n\t\tColor :");
    gets(c->color);
    fflush(stdin);
    printf("\n\t\tCar age:");
    gets(c->age);
    fflush(stdin);
    printf("\n\t\tFuel Source :");
    gets(c->fuel);
    fflush(stdin);
    printf("\n\t\tRegistered Number :");
    gets(c->rn);
    printf("\n\t\tEnter Minimum rate of car: ");
    scanf("%f",&c->minBit);
    if (cstart==NULL)
    {
        cstart=cend=c;
        c->next=NULL;
    }
         else
         {
          cend->next=c;
          c->next=NULL;
          cend=c;
         }
        system("pause");
    system("CLS");
    printf("\t\t\t\tAUCTION HUB-THE PLACE WHERE ONE CAN GET BETTER\n\n");
    fflush(stdin);
}




int main()
{
    int i;
    FILE *fp;
    fp=fopen("bidding.txt","r");
    if(fp==NULL)
        printf("null");

    for(i=1;i<=5;i++)
        file(fp);
    fclose(fp);
    printf("\t\t\t\tAUCTION HUB-THE PLACE WHERE ONE CAN GET BETTER\n\n");
     do
    {
        printf("\n\t\t1.SELL\n\t\t2.BUY\n\t\t3.EXIT\n");
        printf("\n\t\tEnter your option: ");
        scanf("%d",&option1);

        switch(option1)
        {
            case 1: sell();break;
            case 2: buy ();break;
            case 3:system("CLS");break;
        }
    }while(option1!=3);
    printf("\n\n\n\n\n\n\n\t\t\t\t\t   ********THANKYOU**********\n\n\n");
    getch();
    return 0;
}

