// Depth First Search
// Language: C99

#include <stdio.h>
#include <stdbool.h>

#define SIZE 5
#define VERBOSE

int graph[SIZE][SIZE];
int accessed[SIZE];
int curRoute[SIZE];

void dfs(int nodeNum, int pos, int goalNum){
    if(nodeNum == goalNum){
        int i;
        for(i = 0;i < pos;i++){
            printf("%d ", curRoute[i]);
        }
        printf(" length: %d\n", i);
        return;
    }

    // enum connected node
    for(int i = 0;i < SIZE;i++){
        if(graph[nodeNum][i] && !accessed[i]){ // if nodeNum <-> i are connected
#ifdef VERBOSE
            for(int k = 0;k < pos;k++)printf(" ");
            printf("accessing %d -> %d, pos: %d\n", nodeNum + 1, i + 1, pos);
#endif
            accessed[i] = true;
            curRoute[pos] = i + 1;
            dfs(i, pos+1, goalNum);
            accessed[i] = false;
        }

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

    accessed[start - 1] = true;
    curRoute[0] = start;
    dfs(start - 1, 1, end - 1);
    getchar();
    return 0;
}
