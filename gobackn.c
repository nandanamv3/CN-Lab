#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TOTALPACKETS 5
#define WINDOWSIZE 4

int simulateack(){
    return rand()%10<7;
}

void main(){
    srand(time(0));
    
    int base=1;
    int nextseq=1;
  
    while(base<=TOTALPACKETS){
        printf("Sending window\n");
        while(nextseq<base+WINDOWSIZE&&nextseq<=TOTALPACKETS){
            printf("Sender:Sending packet%d\n",nextseq);
            nextseq++;
        }
        sleep(1);
        printf("Waiting for acks");
        for(int i=base;i<nextseq;i++){
            if(simulateack()){
                printf("Ack received %d\n",i);
            }
            else{
                printf("Ack lost.retransmitting %d\n",i);
                nextseq=i;
                break;
            }
        }
        base=nextseq;
        sleep(1);
    }
    printf("Successful");
}
