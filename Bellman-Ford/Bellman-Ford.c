// Bellman-Ford
// Language: C99

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE  5
#define MAX_DIST 999999

int start[SIZE];
int end[SIZE];
int dist[SIZE];
int distance[SIZE];

void print_distance(){
    for(int i = 0;i < SIZE;i++){
        printf("%d ", distance[i]);
    }
    printf("\n");
}

void Bellman_Ford(int node_count, int start_index){
    distance[start_index] = 0;

    for(int i = 0;i < node_count - 1;i++){
        bool hasChanged = false;
        for(int j = 0;j < SIZE;j++){
            int cur_start = start[j] - 1;
            int cur_end = end[j] - 1;
            int cur_dist = dist[j];

            if(distance[cur_end] > distance[cur_start] + cur_dist){
#ifdef VERBOSE
                printf("Loosing distance from %d to %d, new distance: %d\n", cur_start + 1, cur_end + 1, distance[cur_start] + cur_dist);
#endif
                distance[cur_end] = distance[cur_start] + cur_dist;
                hasChanged = true;
            }
        }
#ifdef VERBOSE
        printf("Loose process %d:\n", i);
        print_distance();
        printf("\n");
#endif
        if(!hasChanged){
#ifdef VERBOSE
            printf("Since distance had not been changed, search has completed\n");
#endif
            break;
        }
    }
}

int main(){
    int node_count;
    scanf("%d", &node_count);

    for(int i = 0;i < SIZE;i++){
        scanf("%d %d %d", &start[i], &end[i], &dist[i]);
    }


    for(int i = 0;i < SIZE;i++){
        distance[i] = MAX_DIST;
    }

    int start_index;
    scanf("%d", &start_index);

    Bellman_Ford(node_count, start_index - 1);
    print_distance();
    getchar();

    return 0;
}
