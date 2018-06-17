#include <stdio.h>          
#include <stdlib.h>        
#include <sys/types.h>      /* key_t, sem_t, pid_t      */
#include <sys/shm.h>        /* shmat(), IPC_RMID        */
#include <errno.h>          /* errno, ECHILD            */
#include <semaphore.h>      /* sem_open(), sem_destroy(), sem_wait().. */
#include <fcntl.h>          /* O_CREAT, O_EXEC          */
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

//state 0: thinking ........
//state 1: hungry and waiting ........
//state 2: eating .......

sem_t *fork1red ,*fork2red ,*fork1gr ,*fork2gr ,*spoon1red ,*spoon2red ,*spoon1green, *spoon2green;  
int redfork=2 , greenfork=2 , redspoon=2,greenspoon=2;
int value=1;


void phillospher(int id )
{   

    int state=0;//thinking......    
    while(1){
   
    if(state==0){
        printf("philosopher %d is thinking\n",id);
        state=1;
        sleep(2);
        printf("state is changed to 1.\n");
    }
    else if(state==1){
        printf("state 1 enters\n");
        if(sem_trywait(fork1red)==0){ 
            printf("inside redfork\n");
            if(!sem_trywait(spoon1red)){
                printf("philosopher id=%d is eating\n", id);
                sleep(2);
                printf("philosopher id=%d has finished eating\n", id);
                sem_post(fork1red);
                sem_post(spoon1red);
                state=0;
              //  sleep(1);
            }
            else {
                sem_wait(spoon2red);
                printf("philosopher id=%d is eating\n", id);        
                sleep(2);
                printf("philosopher id=%d has finished eating\n", id);
                sem_post(fork1red);
                sem_post(spoon2red);
                state=0;
            }
            

        }
        else if (sem_trywait(fork2red)==0) 
        {
            printf("inside redfork2\n");
            if(!sem_trywait(spoon1red)){
                printf("philosopher id=%d is eating\n", id);
            
                sleep(2);
                printf("philosopher id=%d has finished eating\n", id);
                sem_post(fork2red);
                sem_post(spoon1red);
                state=0;
            }
            else {
                sem_wait(spoon2red);
                printf("philosopher id=%d is eating\n", id);
                
                sleep(2);
                printf("philosopher id=%d has finished eating\n", id);
                sem_post(fork2red);
                sem_post(spoon2red);
                state=0;
            }
        }
        else if(sem_trywait(fork1gr)==0) {

            printf("inside \n");
            if(!sem_trywait(spoon2green)){
                printf("philosopher id=%d is eating\n", id);
                
                sleep(2);
                printf("philosopher id=%d has finished eating\n", id);
                sem_post(fork1gr);
                sem_post(spoon2green);
                state=0;
            }
            else {
                sem_wait(spoon1green);
                printf("philosopher id=%d is eating\n", id);
                
                sleep(2);
                printf("philosopher id=%d has finished eating\n", id);
                sem_post(fork1gr);
                sem_post(spoon1green);
                state=0;
            }
            

        }
        else {
            sem_wait(fork2gr);
            printf("inside \n");
            if(!sem_trywait(spoon2green)){
                printf("philosopher id=%d is eating\n", id);
                sleep(2);
                printf("philosopher id=%d has finished eating\n", id);
                sem_post(fork2gr);
                sem_post(spoon2green);
                state=0;
            }
            else {
                sem_wait(spoon1green);
                printf("philosopher id=%d is eating\n", id);
                sleep(2);
                printf("philosopher id=%d has finished eating\n", id);
                sem_post(fork2gr);
                sem_post(spoon1green);
                state=0;
            }
        }
        

        }
        }
    
}




int main(){

    sem_unlink ("pSemredfork1");   
sem_close(fork1red);    
sem_unlink ("pSemredfork2");   
sem_close(fork2red);    
sem_unlink ("pSemgreenfork1");   
sem_close(fork1gr);    
sem_unlink ("pSemgreenfork2");   
sem_close(fork2gr);    
sem_unlink ("pSemredspoon1");   
sem_close(spoon1red);    
sem_unlink ("pSemredspoon2");   
sem_close(spoon2red);    
sem_unlink ("pSemgreenspoon1");   
sem_close(spoon1green);    
sem_unlink ("pSemgreenspoon2");   
sem_close(spoon2green);    

    int i;                        
    key_t shmkey;                 /*      shared memory key       */
    int shmid;                    /*      shared memory id        */
          /*      synch semaphore         *//*shared */
    pid_t pid;                    /*      fork pid                */
    int *p;                       /*      shared variable         *//*shared */
    unsigned int n=5;               /*      fork count              */
    unsigned int value=1;           /*      semaphore value         */
    int status,ret;

    //printf ("shmkey for p = %d\n", shmkey);
    shmid = shmget (shmkey, sizeof (int), 0644 | IPC_CREAT);
    if (shmid < 0){                           /* shared memory error check */
        perror ("shmget\n");
        exit (1);
    }

    p = (int *) shmat (shmid, NULL, 0);   /* attach p to shared memory */
    *p = 0;
    //printf ("p=%d is allocated in shared memory.\n\n", *p);

    fork1red = sem_open("pSemredfork1", O_CREAT , 0644, value);
    fork2red = sem_open("pSemredfork2", O_CREAT | O_EXCL, 0644, value);
    fork1gr = sem_open("pSemgreenfork1", O_CREAT | O_EXCL, 0644, value);
    fork2gr = sem_open("pSemgreenfork2", O_CREAT | O_EXCL, 0644, value);
    spoon1red = sem_open("pSemredspoon1", O_CREAT | O_EXCL, 0644, value);
    spoon2red = sem_open("pSemredspoon2", O_CREAT | O_EXCL, 0644, value);
    spoon1green = sem_open("pSemgreenspoon1", O_CREAT | O_EXCL, 0644, value);
    spoon2green = sem_open("pSemgreenspoon2", O_CREAT | O_EXCL, 0644, value);

    for (i=0;i<n;i++){
        pid = fork ();
        if (pid < 0) {
            printf ("Fork error.\n");
        }

        else if (pid == 0){
            printf("child created...\n");
            phillospher(i);
            break;
        }
    }

while(waitpid(-1,NULL,0)!=-1);printf("all child destroyed\n");
/*
if ((ret = waitpid (pid, &status, 0)) == -1) 
    printf("parent:error\n"); 

*/
    return 0;
}
