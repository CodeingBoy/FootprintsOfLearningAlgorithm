// Floyd-Warshall
// Language: C99

#include <stdio.h>

#define SIZE  4
#define MAX_DIST 999999

int graph[SIZE][SIZE];

void print_graph(){
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

void Floyd_Warshall(){
    for(int middle_index = 0;middle_index < SIZE;middle_index++){
        for(int a_index = 0;a_index < SIZE;a_index++){
            for(int b_index = 0;b_index < SIZE;b_index++){
                if(graph[a_index][b_index] > graph[a_index][middle_index] + graph[middle_index][b_index]){
#ifdef VERBOSE
                    printf("Found %d -> %d -> %d has a shorter way, whose distance is %d\n", a_index + 1, middle_index + 1, b_index + 1, graph[a_index][middle_index] + graph[middle_index][b_index]);
#endif
                    graph[a_index][b_index] = graph[a_index][middle_index] + graph[middle_index][b_index];
                }
            }
        }
#ifdef VERBOSE
        printf("After %d:\n", middle_index + 1);
        print_graph();
        printf("\n");
#endif
    }
}

int main(){
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            scanf("%d", &graph[i][j]);
            if(graph[i][j] == -1){
                graph[i][j] = MAX_DIST;
            }
        }
    }

    Floyd_Warshall();
    print_graph();
    getchar();

    return 0;
}
