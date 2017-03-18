// Dijkstra
// Language: C99

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE  6
#define MAX_DIST 999999

int graph[SIZE][SIZE];
int distance[SIZE];

void print_graph(){
    for(int i = 0;i < SIZE;i++){
        for(int j = 0;j < SIZE;j++){
            printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

void print_distance(){
    for(int i = 0;i < SIZE;i++){
        printf("%d ", distance[i]);
    }
    printf("\n");
}

void Dijkstra(int start_index){
    bool used[SIZE];
    memset(used, 0, sizeof(bool) * SIZE);

    for(int i = 0;i < SIZE;i++){
        if(graph[start_index][i] != MAX_DIST){
            distance[i] = graph[start_index][i];
        }
    }

    used[start_index] = true;

    while(true){
        // choose min index
        int min_dist = MAX_DIST;
        int min_index = -1;
        for(int i = 0;i < SIZE;i++){
            if(used[i]) continue;
            if(distance[i] < min_dist){
                min_index = i;
                min_dist = distance[min_index];
            }
        }
        if(min_index == -1) break; // all nodes have been used
        used[min_index] = true;
#ifdef VERBOSE
        printf("Closest node from %d is %d, distance %d\n", start_index + 1, min_index + 1, min_dist);
#endif

        // try to loose
        for(int i = 0;i < SIZE;i++){
            if(distance[i] > distance[min_index] + graph[min_index][i]){
#ifdef VERBOSE
                printf("Found a shorter way from %d to %d, whose distance is %d\n", min_index + 1, i + 1, distance[min_index] + graph[min_index][i]);
#endif
                distance[i] = distance[min_index] + graph[min_index][i];
            }
        }
#ifdef VERBOSE
        printf("After trying loosing with node %d:\n", min_index + 1);
        print_distance();
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

    for(int i = 0;i < SIZE;i++){
        distance[i] = MAX_DIST;
    }

    int start_index;
    scanf("%d", &start_index);

    Dijkstra(start_index - 1);
    print_graph();
    print_distance();
    getchar();

    return 0;
}
