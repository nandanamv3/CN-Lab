#include<stdio.h>
#include<stdlib.h>

void leakybucket(int bucket_cap,int leakrate,int packets[],int num_packets){
    int bucket=0;
    
    printf("time\tincoming\tbucket\tleaked\tremaining\n");
    for(int i=0;i<num_packets;i++){
        printf("%d%10d",i+1,packets[i]);
        
        bucket+=packets[i];
        if(bucket>bucket_cap){
            printf("%10d(overflowed,dropped %d)",bucket_cap,bucket-bucket_cap);
            bucket=bucket_cap;
        }
        else{
            printf("%10d",bucket);
        }
        int leaked=(bucket>=leakrate)?leakrate:bucket;
        bucket-=leaked;
        
        printf("%10d%10d\n",leaked,bucket);
        
    }
    int time=num_packets+1;
    while(bucket>0){
        int leaked=(bucket>=leakrate)?leakrate:bucket;
        printf("%d%10d%10d%10d%10d\n", time,0,bucket, leaked, bucket - leaked);
        bucket-=leaked;
        time++;
    }
}

void main(){
    int leakrate,bucket_cap,num_packets;
    
    printf("Enter the bucket cap");
    scanf("%d",&bucket_cap);
    
     printf("Enter the leakrate");
    scanf("%d",&leakrate);
     printf("Enter the number of packets");
    scanf("%d",&num_packets);
    
    int packets[num_packets];
    for(int i=0;i<num_packets;i++){
        printf("Enter the bucket cap");
        scanf("%d",&packets[i]);
    }
    
    leakybucket(bucket_cap,leakrate,packets,num_packets);
    
}
