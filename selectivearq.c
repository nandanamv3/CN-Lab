#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#define LOSSPROB 20
#define TOTALFRAMES 10
#define WINDOWSIZE 4
int send_frame(int frameno){
    printf("Sending frame %d...\n", frameno);
    sleep(1); 
    int randvalue=rand()%100;
    if(randvalue<LOSSPROB){
        printf("Frame %d lost during transmission!\n",frameno);
        return 0;
    }
    printf("Frame %d sent successfully.\n",frameno);
    return 1;
}

int rec_frame(int frameno){
    printf("Receiving acknowledgment for frame %d...\n",frameno);
    sleep(1);
    int randvalue=rand()%100;
    if(randvalue<LOSSPROB){
        printf("Acknowledgment for frame %d lost!\n", frameno);
        return 0;
    }
    printf("Acknowledgment for frame %d received.\n", frameno);
    return 1;
}


void selectivearq(){
    int base=0;
    int sentframes[TOTALFRAMES]={0};
    int ackreceived[TOTALFRAMES]={0};
    while(base<TOTALFRAMES){
    for(int i=base;i<base+WINDOWSIZE&&i<TOTALFRAMES;i++){
        if(!sentframes[i]){
            sentframes[i]=send_frame(i);
        }  
    }
    for(int i=base;i<base+WINDOWSIZE&&i<TOTALFRAMES;i++){
        if(sentframes[i]&&!ackreceived[i]){
            ackreceived[i]=rec_frame(i);
        }  
    }
    
    
    while(base<TOTALFRAMES&&ackreceived[base]){
        printf("Sliding window forward. Frame %d fully acknowledged.\n", base);
        base++;
    }
}
    printf("All frames sent and acknowledged successfully.\n");
}


void main(){
    srand(time(0));
    selectivearq();
}
