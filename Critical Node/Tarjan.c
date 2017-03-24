// Tarjan
// Language: C99

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 6

int timestamp[SIZE];
int ancestor[SIZE];
bool isCriticalNode[SIZE];
int root_index = -1;

int min(int a, int b){
    return a > b ? b : a;
}

void print_timestamp(){
    for(int i = 0;i < SIZE;i++){
        printf("%d ", timestamp[i]);
    }
    printf("\n");
}

void print_ancestor(){
    for(int i = 0;i < SIZE;i++){
        printf("%d ", ancestor[i]);
    }
    printf("\n");
}

void dfs(int node_index, int father_index, int start[], int end[], int length){
    static int cur_timestamp = 1;
#ifdef VERBOSE
    printf("Timestamp of %d: %d\n", node_index, cur_timestamp);
#endif
    timestamp[node_index - 1] = cur_timestamp;
    cur_timestamp++;

    ancestor[node_index - 1] = node_index;

    int child_node_count = 0;
    for(int i = 0;i < length;i++){
        if(start[i] == node_index || end[i] == node_index){
            int begin_index = start[i] == node_index ? start[i] : end[i];
            int end_index = start[i] == node_index ? end[i] : start[i];
#ifdef VERBOSE
            printf("Accessing %d -> %d\n", begin_index, end_index);
#endif
            if(timestamp[end_index - 1] < 0){
#ifdef VERBOSE
                printf("Node %d has not been accessed\n", end_index);
#endif
                child_node_count++;
                dfs(end_index, begin_index, start, end, length);
#ifdef VERBOSE
                printf("Ancestor of %d = %d, ancestor of %d = %d\n", begin_index, ancestor[begin_index - 1], end_index, ancestor[end_index - 1]);
                printf("Setting ancestor of %d = %d\n", node_index, min(ancestor[node_index - 1], ancestor[end_index - 1]));
#endif
                ancestor[node_index - 1] = min(ancestor[node_index - 1], ancestor[end_index - 1]);
                if(node_index != root_index && ancestor[end_index] >= timestamp[node_index - 1]){
#ifdef VERBOSE
                    printf("Since ancestor of %d(%d) is greater than timestamp of %d(%d), node %d is a critical node\n", end_index, ancestor[end_index - 1], node_index, timestamp[node_index - 1], node_index);
#endif
                    isCriticalNode[node_index - 1] = true;
                }else if(node_index == root_index && child_node_count == 2){
#ifdef VERBOSE
                    printf("Since root node %d have two childs, node %d is a critical node\n", node_index, node_index);
#endif
                    isCriticalNode[node_index - 1] = true;
                }
            }else if(end_index != father_index){
#ifdef VERBOSE
                printf("Node %d had been accessed, timestamp = %d\n", end_index, timestamp[end_index - 1]);
                printf("Ancestor of %d = %d, timestamp of %d = %d\n", node_index, ancestor[node_index - 1], end_index, timestamp[end_index - 1]);
#endif
                ancestor[node_index - 1] = min(ancestor[node_index - 1], timestamp[end_index - 1]);
            }
#ifdef VERBOSE
            printf("Current timestamp:\n");
            print_timestamp();
            printf("\n");
            printf("Current ancestor:\n");
            print_ancestor();
            printf("\n");
#endif
        }
    }
}

void Tarjan(int node_start, int start[], int end[], int length){
    root_index = node_start;
    dfs(node_start, root_index, start, end, length);
}

int main(void){
    for(int i = 0;i < SIZE;i++){
        timestamp[i] = -1;
        ancestor[i] = -1;
    }

    int n;
    scanf("%d", &n);

    int *start = malloc(sizeof(int) * n);
    int *end = malloc(sizeof(int) * n);

    for(int i = 0;i < n;i++){
        scanf("%d %d", &start[i], &end[i]);
    }

    Tarjan(1, start, end, n);

    for(int i = 0;i < SIZE;i++){
        if(isCriticalNode[i]){
            printf("%d ", i + 1);
        }
    }

    free(start);
    free(end);

    return 0;
}
