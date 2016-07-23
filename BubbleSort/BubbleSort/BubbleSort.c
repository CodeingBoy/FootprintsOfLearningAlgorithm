#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define VERBOSE 1

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printNums(int n, int nums[])
{
    for (int i = 0; i < n; i++)
        printf("%d ", nums[i]);
    printf("\n");
}

void bubbleSort(int n, int nums[])
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (nums[j] > nums[j + 1]) {
                if (VERBOSE) {
                    printf("%d > %d, swapped.\n", nums[j], nums[j + 1]);
                }
                swap(&nums[j], &nums[j + 1]);
            }
        }
        if (VERBOSE) {
            printf("After %d sort: ", i);
            printNums(n, nums);
            printf("\n");
        }
    }
}

int main(void)
{
    printf("The size of numbers, please?");
    int numCount;
    scanf("%d", &numCount);

    int *nums = malloc(sizeof(int) * numCount);
    printf("Please input integers:");

    for (int i = 0; i < numCount; i++) {
        scanf("%d", &nums[i]);
    }
    printf("\n");

    printf("Before being sorted :");
    printNums(numCount, nums);

    bubbleSort(numCount, nums);

    printf("After being sorted :");
    printNums(numCount, nums);

    printf("Press any key to exit");
    getchar();
    getchar();
}