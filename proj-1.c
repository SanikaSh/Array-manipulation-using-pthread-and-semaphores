/*
Write a program that does the following.
1. The main (parent) thread initializes an array of 3 integers to zero.
2. The parent creates 3 children. Child i adds 1 to array[i], where i = 0, 1, 2.
3. The parent waits for the children to finish adding, and then prints the values in the array.
4. The children wait for the parent to finish printing and then repeats (adds 1 to an an element of the array)
5. Continues forever
*/

#include <stdio.h>
#include <stdlib.h>
#include "sem.h"

semaphore_t s0, s1, s2, s3;
int arr[3];

void Increment_Child0()
{
    while(1)
    {
        P(&s1);
        arr[0]++;
        V(&s0);    
    }
}
void Increment_Child1()
{
    while(1)
    {
        P(&s2);
        arr[1]++;
        V(&s0); 
    }
}
void Increment_Child2()
{
    while(1)
    {
        P(&s3);
        arr[2]++;
        V(&s0); 
    }
}

void Parent(void)
{
    arr[0] = 0; arr[1]=0; arr[2]=0;
    start_thread(Increment_Child0, NULL);
    start_thread(Increment_Child1, NULL);
    start_thread(Increment_Child2, NULL);

    while(1)
    {
        P(&s0);P(&s0);P(&s0);
        printf("Array is: arr[0]=%d, arr[1]=%d, arr[2]=%d\n", arr[0], arr[1], arr[2]);
        V(&s1);V(&s2);V(&s3);
    }
}
        
    


int main()
{

    init_sem(&s0, 0);
    init_sem(&s1, 1);
    init_sem(&s2, 1);
    init_sem(&s3, 1);

    start_thread(Parent, NULL);

    while(1);sleep(1);

    return 0;
}