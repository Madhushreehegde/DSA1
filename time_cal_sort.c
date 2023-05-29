#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void bubble_sort(int n,int a[20])
{
    int i,j,temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(a[j+1]<a[j])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
    printf("Sorted array : ");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);



}


void insertion_sort(int n,int a[20])
{
    int i,j,temp;
    for(i=1;i<n;i++)
    {
        temp=a[i];
        for(j=i-1;j>=0 && a[j]>temp;j--)
            a[j+1]=a[j];
        a[j+1]=temp;
    }
    printf("Sorted array : ");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);

}

void selection_sort(int n,int a[20])
{
    int i,j,temp;
    for(i=0;i<n-1;i++)
    {
        int min=i;
        for(j=i+1;j<n;j++)
        {
            if(a[j]<a[min])
                min=j;
        }
        if(min!=i)
        {
            temp=a[i];
            a[i]=a[min];
            a[min]=temp;
        }
    }
    printf("Sorted array : ");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
}


int main()
{
    clock_t start, end;
    int n,a[20],ch;
     float time;
    printf("\nEnter the number of elements in an array :");
    scanf("%d",&n);
    printf("\nEnter the elements in an array : ");
    for(int i=0;i<n;i++)
       {
           a[i] = rand()%n;
           printf("%d ",a[i]);
       }
    while(1)
   {
       printf("\nMENU");
       printf("\n1.Bubble sort");
       printf("\n2.Insertion sort");
       printf("\n3.Selection sort");
       printf("\nEnter your choice : ");
       scanf("%d",&ch);
       switch(ch)
       {
           case 1:
                start = clock();
                bubble_sort(n,a);
                end = clock();
           break;
           case 2:
              start = clock();
               insertion_sort(n,a);
               end = clock();
           break;
           case 3:
              start = clock();
               selection_sort(n,a);
               end = clock();
           break;
           default:exit(0);
           break;
       }
       time = ((float)(end - start))/CLOCKS_PER_SEC;
       printf("\nExecution time = %f \n",time);
   }
    return 0;
}
