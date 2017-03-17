// Disjoint Set
// Language: C99

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void joint(int arr[], int arr_size, int clue_left, int clue_right){
#ifdef VERBOSE
    printf("Before joint: ");
    print_array(arr, arr_size);

    printf("Clue: %d <- %d\n", clue_left, clue_right);
#endif

    int ancestor_left = search(arr, clue_left - 1);
    int ancestor_right = search(arr, clue_right - 1);

#ifdef VERBOSE
    printf("root: %d <- %d\n", ancestor_left, ancestor_right);
#endif

    arr[ancestor_right - 1] = ancestor_left;
#ifdef VERBOSE
    printf("After joint: ");
    print_array(arr, arr_size);
#endif
}

int calcGroupCount(int arr[], int arr_size){
    int count = 0;
    for(int i = 0;i < arr_size;i++){
        if(arr[i] == i + 1){
            count++;
        }
    }
    return count;
}

int main(){
    printf("Please input size of numbers: ");
    int size;
    scanf("%d", &size);

    int *nums = malloc(size * sizeof(int));

    for(int i = 0;i < size;i++){
        nums[i] = i + 1;
    }

    printf("Please input total amount of clues: ");
    int clue_count;
    scanf("%d", &clue_count);

    for(int i = 0;i < clue_count;i++){
        int clue_left, clue_right;
        scanf("%d %d", &clue_left, &clue_right);
        joint(nums, size, clue_left, clue_right);
    }

    print_array(nums, size);

    int group_count = calcGroupCount(nums, size);
    printf("Group count: %d\n", group_count);

    free(nums);

    return 0;
}
