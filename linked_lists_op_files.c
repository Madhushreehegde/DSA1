#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    struct node *link;
};

struct node *create_node()
{
    struct node *newnode;
    newnode=(struct node*)malloc(sizeof(struct node));
    printf("Enter numbers\n");
    scanf("%d",&newnode->data);
    newnode->link=NULL;
    return newnode;
};

void display(struct node *head)
{
    struct node *cur;
    cur=head;
    while(cur!=NULL)
    {
        printf("%d",cur->data);
        cur=cur->link;
    }
}
struct node *insert_end(struct node *head,int n)
{
    struct node *cur;
    struct node *newnode;
    for(int i=0;i<n;i++)
      {
        newnode=create_node();
        if(head==NULL)
            head=newnode;
        else
        {
            cur=head;
            while(cur->link!=NULL)
                cur=cur->link;
        }
        cur->link=newnode;
      }
    return head;
};

struct node *delete_front(struct node *head)
{
    struct node *cur;
    if(head==NULL)
    {
        printf("SLL is empty\n");
    }
    else if(head->link==NULL)
    {
        printf("Deleted %d\n",head->data);
        free(head);
        head=NULL;
    }
    else
    {
        cur=head;
        head=head->link;
        cur->link=NULL;
        printf("Deleted %d\n",cur->data);
        free(cur);
    }
    return head;
}

int main()
{
    int ch,a[100],n;
    FILE *fp,*fp1,*fp2;
    int first,last;

    printf("Enter the interval\n");
    scanf("%d%d",&first,&last);
    printf("Enter number of random numbers to be generated\n ");
    scanf("%d",&n);
    int count=0;
    for(int i=0;i<n;i++)
    {

        a[i]=(rand()%(last+1-first)+first);
        fprintf(fp,"%d ",a[i]);

    }
}
