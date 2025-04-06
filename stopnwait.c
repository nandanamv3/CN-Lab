#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define TOTAL_PACKETS 5
#define TIMEOUT 3 
int simulate_ack(){
    return rand()%10<7;
}

int main(){
    srand(time(0));
    int packet=1;
    
    while(packet<=TOTAL_PACKETS){
        printf("Sender: Sending packet %d...\n", packet);
        sleep(1);
        
        if(simulate_ack()){
            printf("Receiver: ACK for packet %d received.\n\n", packet);
            packet++;
        }
        
        else{
            printf("Receiver: ACK for packet %d lost! Retransmitting...\n\n", packet);
            sleep(TIMEOUT);
        }
    }
    printf("All packets sent successfully!\n");
    return 0;
    
    
}
