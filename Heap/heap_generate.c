// Generate Heap
// Language: C99

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define VERBOSE

void swap(int heap[], int index_a, int index_b){
    int temp = heap[index_a];
    heap[index_a] = heap[index_b];
    heap[index_b] = temp;
}

void print_heap(int heap[], int size){
    int level = 1;
    for(int i = 0;i < size;i++){
        printf("%d ", heap[i]);
        if(i == pow(2, level) - 2){
            printf("\n");
            level++;
        }
    }
    printf("\n");
}

void move_up(){
    int curindex = index;
    bool done = false;

    while((curindex + 1) / 2 - 1 < size && (curindex + 1) / 2 - 1 >= 0){
        int father_index = (curindex + 1) / 2 - 1;

        int swapindex = curindex;
        if(heap[curindex] < heap[father_index]){
            swapindex = father_index;
        }
        if(swapindex == curindex)break;
#ifdef verbose
        printf("swaping %d(%d) -> %d(%d)\n", heap[curindex], curindex, heap[swapindex], swapindex);
#endif
        swap(heap, swapindex, curindex);
#ifdef verbose
        printf("after swap: \n");
        print_heap(heap, size);
        printf("\n");
#endif
        curindex = swapindex;
    }
}

void move_down(int heap[], int index, int size){
    int curindex = index;
    bool done = false;

    while((curindex + 1) * 2 - 1 < size){
        int left_index = (curindex + 1) * 2 - 1;
        int right_index = left_index + 1;

        int swapindex = curindex;
        if(heap[curindex] > heap[left_index]){
            swapindex = left_index;
        }
        if(right_index < size && heap[swapindex] > heap[right_index]){
            swapindex = right_index;
        }
        if(swapindex == curindex)break;
#ifdef verbose
        printf("swaping %d(%d) -> %d(%d)\n", heap[curindex], curindex, heap[swapindex], swapindex);
#endif
        swap(heap, swapindex, curindex);
#ifdef verbose
        printf("after swap: \n");
        print_heap(heap, size);
        printf("\n");
#endif
        curindex = swapindex;
    }
}

int main(){
    int size;
    printf("Please input size of numbers: ");
    scanf("%d", &size);

    int *heap = malloc(size * sizeof(int));
    for(int i = 0;i < size;i++){
        scanf("%d", &heap[i]);
    }

    // generate heap
    for(int i = size / 2;i >= 0;i--){
        move_down(heap, i, size);
    }

    print_heap(heap, size);

    free(heap);

    getchar();

    return 0;
}
