// Breath First Search
// Language: C99

#include <stdio.h>
#include <stdbool.h>

#define SIZE 5
#define VERBOSE

int graph[SIZE][SIZE];
int accessed[SIZE];
int curRoute[SIZE];

void bfs(int startNode, int goalNode){
    int queue[SIZE];
    int front = 0, rear = 1;
    int times = 0;
    int father[SIZE];

    queue[front] = startNode;
    accessed[startNode] = true;
    father[startNode] = -1;

    while(front < rear){
        int nodeIndex = queue[front];
        if(nodeIndex == goalNode){
            int curIndex = nodeIndex;
            int step = 1;
            while(curIndex != startNode){
                printf("%d <- ", curIndex + 1);
                curIndex = father[curIndex];
                // accessed[curIndex] = false;
                step++;
            }
            printf("%d, step: %d\n", startNode + 1, step);
        }else{
            for(int i = 0;i < SIZE;i++){
                if(graph[nodeIndex][i] && !accessed[i]){
#ifdef VERBOSE
                    printf("adding %d -> %d to queue\n", nodeIndex + 1, i + 1);
#endif
                    queue[rear] = i;
                    rear++;
                    father[i] = nodeIndex;
                    accessed[i] = true;
                }
            }
        }
        front++;
    }
}

int main(){
    printf("Input a graph matrix: ");
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            scanf("%d", &graph[i][j]);
        }
    }

    int start, end;
    printf("Start node num: ");
    scanf("%d", &start);
    printf("End node num: ");
    scanf("%d", &end);

    bfs(start - 1, end - 1);
    getchar();
    return 0;
}
