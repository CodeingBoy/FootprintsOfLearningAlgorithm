#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define VERBOSE 1

void BucketSort(int n, int nums[])
{
    // find max numbers
    int max = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (nums[i] > max)
            max = nums[i];
    }

    // create buckets
    int *buckets = malloc(sizeof(int) * (max + 1));
    if (VERBOSE)
        printf("Created %d buckets.\n", max + 1);

    // initialize buckets
    for (int i = 0; i < max + 1; i++)
        buckets[i] = 0;
    if (VERBOSE)
        printf("Initialize buckets completed.\n");

    // fill buckets
    for (int i = 0; i < n; i++) {
        buckets[nums[i]]++;
        if (VERBOSE) {
            printf("Number %d hitted bucket %d. ", nums[i], nums[i]);
            printf("The value of bucket %d : %d\n", nums[i], buckets[nums[i]]);
        }
    }

    // fill numbers
    int i = 0, j = 0;
    while (i < n) {
        while (buckets[j] == 0) { // skip empty buckets
            j++;
        }
        if (VERBOSE)
            printf("Skipped empty buckets to %d\n", j);

        for (int k = 0; k < buckets[j]; k++) {
            if (VERBOSE)
                printf("Output num %d to pos %d.\n", j, i);

            nums[i] = j;
            i++;
        }
        j++;
    }
}

void printNums(int n, int nums[])
{
    for (int i = 0; i < n; i++)
        printf("%d ", nums[i]);
    printf("\n");
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

    BucketSort(numCount, nums);

    printf("After being sorted :");
    printNums(numCount, nums);

    printf("Please press any key to exit");
    getchar();
    getchar();
}