#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include<sys/mman.h>
#include<sys/wait.h>

# define SIZE 4096
 

// the below function determines a given number is perfect number or not

int perfect_number(int p)
{
  
 unsigned long long int i ,sum = 0 ;   
 for(i = 1 ; i <p ; i++)   
  {   
   if(p % i == 0)   
     sum = sum + i ;   
  }    

  if (sum == p)    return 1; 
  else   return 0;
}

 // main process which creates child processes inside it and shares the memory with each of child process

void main_process(int n,int k)
{
  
 ////////// changed the data type of below four variables to int fron u_int8_t ///////////////

  // the below shared memory contains given n numbers in which child process reads
 int *sm = mmap(NULL, n*SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  // the below shared memory is to list all the perfect numbers from given n numbers found out by each of the child process
  int *sh = mmap(NULL, n*SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  // the below are the pointers in the shared memory which are required to access data in the above shared memory buffers.

  // out1 pointer is for accessing elements by child processes from sm shared memory.
  int *out1 = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); //*out1 = 0;

  // in2 is the pointer to input the perfect numbers into the sh shared memory
  int *in2 = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
 
  for(int i=0;i<n;i++)
   {
      sm[i] = i+1;
   }



 /* creating child process below in which each ith child process calculates the perfect numbers from n/k set
      except for the kth child process which calculates perfect numbers from remaing numbers in given n numbers 
      */

 for(int i=0;i<k;i++)
 {
   

   if(fork() == 0)
    { 
     
     char filename[1000];
     snprintf(filename,sizeof(filename),"OutFile%d.txt",i+1);
      int j=0;
     int pn[n/k] ;   int u;  int g = *out1;
    //  printf("%d ",*out1);               
/* sir here *out1 is not updating . its value is becoming zero here. but it should not be like that couldnt able to find the reason here. */
                                             
   

    if(i!= (k-1))  u = n/k;  
   else u = n ;
 
     // the below loop is to output the each log files "OutFilei" by ith child process

     for(g;g<u;g++) ////////// in this loop instead of *out1 , changed to g /////////
        {
               
           if(perfect_number(sm[g]))
            {
             FILE *ptr;
             ptr = fopen(filename, "a");
             fprintf(ptr,"%d:Is a perfect number\n",sm[g]);
             fclose(ptr);
           
             pn[j] = sm[g];
             j++;
            }           
           else {
             FILE *ptr;
             ptr = fopen(filename, "a");
             fprintf(ptr,"%d:Not a perfect number\n",sm[g]);
             fclose(ptr);
                }
         }
          *out1 = g; /* changed here but could not able to find why the value of  *out1 is not updating . */
    

    // the below loop is to list the perfect numbers in "sh" shared mempory using "in2" shared pointer  
     for(int r=0;r < j;r++) {
       sh[*in2] = pn[r];
       (*in2)++;
                            }
  
  exit(0);
    }
   
 }
   // this main process waits until the execution of the created child process 
   for(int i=0;i<k;i++)
    {
      wait(NULL);
    }

   // the below code is to output the "OutMain file"
   int v=0; int e;

    for(int l=0;l<k;l++)
     {
       
       if(l != k-1)  e = (l+1)*(n/k);
       else    e = n; 
     
       FILE *ptr;
       ptr = fopen("OutMain.txt", "a");
       fprintf(ptr,"\nP%d: ",l+1);
       fclose(ptr);
          
       for(int z=0;v<(*in2);z++) 
         {  
           
          if((e/(sh[v]))>=1) 
           { 
           
             FILE *ptr;
             ptr = fopen("OutMain.txt", "a");
             fprintf(ptr,"num%d ",sh[v]);
             v++;
             fclose(ptr);
           }
          else break;
        }
        
     }
   return ;
}
 
int main(){

 // this main program opens a file named "input.txt" and reads N and K seperated by a space and calls the main process.
  int n,k;
   FILE* ptr;
   ptr = fopen("input.txt", "r");  // "C:\Users\hp\Desktop\input.txt"
   fscanf(ptr, "%d %d",&n,&k); 
   fclose(ptr); 

   main_process(n,k);
  return 0;
}