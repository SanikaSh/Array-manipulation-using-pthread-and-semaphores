// Sanika Shinde (ASU ID: 1217215480)  , Sukirti Ranga (ASU ID: 1218539348)

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// definition of structure semaphore (copied from file sem.h)
typedef struct semaphore_t {
     pthread_mutex_t mutex;
     pthread_cond_t cond;
     int count;
} semaphore_t;


// initialize semaphore (copied from file sem.h)
void init_sem(semaphore_t *s, int i)
{   
    s->count = i;
    pthread_mutex_init(&(s->mutex), NULL);
    pthread_cond_init(&(s->cond), NULL);
}

// definition of wait() for semaphore (copied from file sem.h)
void P(semaphore_t *sem)
{   
    pthread_mutex_lock (&(sem->mutex)); 
    sem->count--;
    if (sem->count < 0) pthread_cond_wait(&(sem->cond), &(sem->mutex));
    pthread_mutex_unlock (&(sem->mutex)); 
}

// definition of  signal() for semaphore (copied from file sem.h)
void V(semaphore_t * sem)
{   
    pthread_mutex_lock (&(sem->mutex)); 
    sem->count++;
    if (sem->count <= 0) {
	pthread_cond_signal(&(sem->cond));
    }
    pthread_mutex_unlock (&(sem->mutex)); 
    pthread_yield();
}


//******************** Actual Project 1 Implementation *****************************

//declaring 4 semaphore variables
semaphore_t s0,s1,s2,s3;

 //child 1
void *f1(int * arg)
{
    while(1)
    {
        P(&s1);
        (*arg)+=1;
        V(&s0);
    }
}

//child 2
void *f2(int * arg)
{
    while(1)
    {
        P(&s2);
        *arg+=1;
        V(&s0);
    }
}

//child3
void *f3(int *arg)
{
    while(1)
    {
        P(&s3);
        *arg+=1;
        V(&s0);
    }
}

int main()
{
        //initializing semaphore variables
        init_sem(&s0, 0);
        init_sem(&s1,1);
        init_sem(&s2,1);
        init_sem(&s3,1);

        //declaring and initializing array
        int arr[3]={0};

        // creating three child threads
        pthread_t myThread[3];
        pthread_create(&myThread[0], 0, f1, &arr[0]);
        pthread_create(&myThread[1], 0, f2, &arr[1]);
        pthread_create(&myThread[2], 0, f3, &arr[2]);

        //infinite main loop to print array values after all 3 children add 1 to respective array elements
        while(1)
        {
            P(&s0); P(&s0);P(&s0);
            printf("Array is: arr[0]=%d, arr[1]=%d, arr[2]=%d\n", arr[0], arr[1], arr[2]);
            V(&s1);V(&s2);V(&s3);
        }

        return 0;
}
