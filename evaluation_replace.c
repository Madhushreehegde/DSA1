#include<stdio.h>
#include<stdlib.h>


int main()
{
     FILE *fp1,*fp2;
     int l=0;
     char line[1000],key[100],word1[100];
     fp1=fopen("read.txt","r+");
     fp2=fopen("write.txt","w");
     if(fp1==NULL)
     {
         printf("File does not exist.\n");
        exit(0);
     }
     printf("Enter the word to be searched\n");
     scanf("%s",word1);
     printf("Enter the word to replace\n");
     scanf("%s",key);
     int q,i,j;
     while(!feof(fp1))
     {
         fgets(line,1000,fp1);
         q=0;
         j=0;
         while(line[q]!='\0')
         {
             if(line[q]==word1[j])
             {
                 while(line[q]==word1[j])
                 {
                     line[q]=key[j];
                     //printf("%c %c\n",line[q],word1[j]);
                     q++;
                     j++;
                 }
                 l++;
             }
             q++;
         }
     fputs(line,fp2);
     }
     if(l==0)
     {
         printf("There's no pattern with %s",word1);
         fputs("There's no pattern with given keyword",fp2);
     }
     fclose(fp1);
     fclose(fp2);
}

