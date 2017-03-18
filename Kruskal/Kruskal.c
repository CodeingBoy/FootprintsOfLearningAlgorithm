// Kruskal
// Language: C99

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

int start[SIZE];
int end[SIZE];
int dist[SIZE];
bool use[SIZE];

void print_array(int arr[], int size){
    for(int i = 0;i < size;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int search(int arr[], int index){
#ifdef VERBOSE
    printf("Searching ancestor of %d(group: %d)\n", index, arr[index]);
#endif
    if (arr[index] == index + 1){ // arr[index] is the ancestor
#ifdef VERBOSE
        printf("Returning ancestor %d\n", index + 1);
#endif
        return index + 1;
    }

    int father_index = arr[index] - 1;
    int ancestor_index = search(arr, father_index);
#ifdef VERBOSE
    printf("Modifing ancestor of %d from %d to %d\n", index, arr[index], ancestor_index);
#endif 
    arr[index] = ancestor_index; 
    return ancestor_index;
}

bool joint(int arr[], int arr_size, int clue_left, int clue_right){
#ifdef VERBOSE
    printf("Before joint: ");
    print_array(arr, arr_size);

    printf("Clue: %d <- %d\n", clue_left, clue_right);
#endif

    int ancestor_left = search(arr, clue_left - 1);
    int ancestor_right = search(arr, clue_right - 1);

    if(ancestor_left == ancestor_right) return false;
#ifdef VERBOSE
    printf("root: %d <- %d\n", ancestor_left, ancestor_right);
#endif

    arr[ancestor_right - 1] = ancestor_left;
#ifdef VERBOSE
    printf("After joint: ");
    print_array(arr, arr_size);
#endif
    return true;
}

void swap(int arr[], int index_a, int index_b){
    int temp = arr[index_a];
    arr[index_a] = arr[index_b];
    arr[index_b] = temp;
}

void quickSort(int index_start, int index_end){
    if(index_start >= index_end) return;
    int pivot = dist[index_start];
#ifdef VERBOSE
    printf("Try to sort %d <-> %d, pivot = %d\n", index_start, index_end, pivot);
#endif

    int left = index_start;
    int right = index_end - 1;
    while(left < right){
        while(left < right && dist[right] >= pivot) right--;
        while(left < right && dist[left] <= pivot) left++;

        if(left >= right) break;
#ifdef VERBOSE
        printf("left: %d, right: %d\n", left, right);
#endif
        swap(start, left, right);
        swap(end, left, right);
        swap(dist, left, right);
    }

    swap(start,index_start, left);
    swap(end, index_start, left);
    swap(dist, index_start, left);

    quickSort(index_start, left);
    quickSort(left+1, index_end);
}

int Kruskal(int node_count){
    quickSort(0, SIZE);

#ifdef VERBOSE
    for(int i = 0;i < SIZE;i++){
        printf("%d %d %d\n", start[i], end[i], dist[i]);
    }
    printf("\n");
#endif

    int *node_set = malloc(sizeof(int) * node_count);
    for(int i = 0;i < node_count;i++){
        node_set[i] = i + 1;
    }

    int total_distance = 0;
    int edges_count = 0;
    for(int i = 0;i < SIZE;i++){
        if(joint(node_set, node_count, start[i], end[i])){
#ifdef VERBOSE
            printf("Using edge %d, %d <- %d -> %d\n", i+1, start[i], dist[i], end[i]);
#endif
            use[i] = true;
            total_distance += dist[i];
            edges_count++;
        }
        if(edges_count >= node_count - 1) break;
    }

    free(node_set);

    return total_distance;
}


int main(){
    memset(use, 0, sizeof(bool) * SIZE);
    int node_count;
    scanf("%d", &node_count);
    for(int i = 0;i < SIZE;i++){
        scanf("%d %d %d", &start[i], &end[i], &dist[i]);
    }

    int distance = Kruskal(node_count);

    for(int i = 0;i < SIZE;i++){
        if(use[i]){
            printf("Use eged %d <- %d -> %d\n", start[i], dist[i], end[i]);
        }
    }
    printf("Total distance: %d\n", distance);

    return 0;

}
