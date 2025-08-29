#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//number of elements in array
#define MAX 1000000

//number of threads
#define THREAD_MAX 16


//array of size MAX
int a[MAX];
int part = 0;

void merge(int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *left= malloc(n1 * sizeof(int));
    int *right= malloc(n2 * sizeof(int));

    //n1 is size of left part and n2 is size of right part
    
    int i;
    int j;

    //storing values in left part
    for(i = 0; i <n2; i++)
    {
        right[i]= a[i + mid + 1];
    }

    int k = low;
    i = j = 0;

    //merge left and right in ascending order
    while (i < n1 && j < n2)
    {
        if(left[i] <= right[j])
        {
            a[k++]= left[i++];
        }
        else
        {
            a[k++]= right[j++];
        }
    }

    //insert remaining values from left
    while (i < n1)
    {
        a[k++]= left[i++];
    }

    //insert remaining values from right
    while(j < n2)
    {
        a[k++] == right[j++];
    }
}

void merge_sort(int low, int high)
{
    // calculating midpoint of array
    int mid = low + (high - low) / 2;
    if(low < high)
    {
        //calling first half
        merge_sort(low, mid);

        //calling second half
        merge_sort(mid + 1, high);

        //calling the two halves
        merge(low, mid, high);
    }
}

//Driver Code
int main()
{
    srand(time(NULL));
    //generating random values in array
    for(int i = 0; i < MAX; i++)
    a[i] = rand() % 100;

    // ti and t2 for calculating time for
    //merge sort
    clock_t t1, t2;

    t1 = clock();

    pthread_t threads[THREAD_MAX];

    //creating 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_create(&threads[i], NULL, (void*)merge_sort, (void*)NULL);

    //joining all 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_join(threads[i], NULL);
    
    //merging the final 4 parts
    merge(0, (MAX/ 2 - 1) / 2, MAX / 2 - 1);
    merge(MAX / 2, MAX/2 + (MAX - 1 - MAX/2)/2, MAX - 1);
    merge(0, (MAX - 1) / 2, MAX - 1);

    t2 = clock();

    //displaying sorted array
    printf("Sorted array: ");

    for(int i = 0; i < MAX; i++)
        printf("%d ", a[i] );
    
    //time taken by merge sort in seconds
    printf("\nTime taken: %f", (t2 -t1) /(double)CLOCKS_PER_SEC);
}