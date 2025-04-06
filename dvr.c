#include <stdio.h>

#define  MAX 10
int nodes;
int cost[MAX][MAX],dist[MAX][MAX],nexthop[MAX][MAX];

void initialise(){
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            dist[i][j]=cost[i][j];
            nexthop[i][j]=j;
        }
    }
}

void update(){
    int updated;
    do{
        updated=0;
        for(int i=0;i<nodes;i++){
            for(int j=0;j<nodes;j++){
                for(int k=0;k<nodes;k++){
                    if(dist[i][j]>dist[i][k]+dist[k][j]){
                        dist[i][j]=dist[i][k]+dist[k][j];
                        nexthop[i][j]=nexthop[i][k];
                        updated=1;
                    }
                }
            }
        }
        
    }while(updated);
}
   
void display() {
    for (int i = 0; i < nodes; i++) {
        printf("\nRouter %d's Routing Table:\n", i + 1);
        printf("Destination\tCost\tNext Hop\n");
        for (int j = 0; j < nodes; j++) {
            printf("%d\t\t%d\t%d\n", j + 1, dist[i][j], nexthop[i][j] + 1);
        }
    }
}
int main(){
    printf("Enter the number of nodes:");
    scanf("%d",&nodes);
    
    printf("Enter the cost matrix:");
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            scanf("%d",&cost[i][j]);
            
            if(i==j){
                cost[i][j]=0;
            }
        }
    }
    
    initialise();
    update();
    display();
    
    return 0;
}
