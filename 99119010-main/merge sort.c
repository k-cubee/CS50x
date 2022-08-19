#include <stdio.h>
#include <cs50.h>

void merge_sort(int a[], int length);
void merge_sort_recursion(int a[], int l, int r);
void merge_sorted_arrays(int a[], int l, int m, int r);

int main(void)
{
    int array[] = {10, 8, 9, 4, 2, 3, 5, 7, 1, 6};
    int length = 10;
    merge_sort(array, length);

    for (int i = 0; i < length; i++)
    {
        printf("%i ", array[i]);
    }
}

int merge_sort(int a[], length)
{
    merge_sort_recursion(a, 0, length - 1);
}

void merge_sort_recursion(int a[], int l, int r)
{
    
}