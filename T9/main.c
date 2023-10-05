//
// Created by Des Caldnd on 10/2/2023.
//
#include "../functions.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void docs();
int get_rand_int_in_range(int a, int b);
void print_int_arr(int* arr, int length);
void fill_int_arr(int* arr, int length, int a, int b);
void swap_min_max_int_arr(int* arr, int length);
void quick_sort_int_arr(int arr[], int length);
int partition_int_array(int arr[], int length);
int find_closest_value(int* sorted_arr, int length, int target);
int get_closest(int val_1, int val_2, int target);

int main(int argc, char* argv[])
{
    srand(time(NULL));

    if (argc != 3)
    {
        incorrect_argc(&docs);
        return 0;
    }

    enum error_type first_error, second_error;

    int a = int_from_str(argv[1], &first_error), b = int_from_str(argv[2], &second_error);

    if (first_error == ERROR || second_error == ERROR)
    {
        printf("One of arguments is incorrect, please, check again");
        return 0;
    }

    printf("Executing first task:\n\n");

    int array[40];
    fill_int_arr(array, 40, a, b);

    print_int_arr(array, 40);

    swap_min_max_int_arr(array, 40);
    print_int_arr(array, 40);

    printf("Executing second task:\n\n");

    int *a_arr, *b_arr, *c_arr;
    int a_size, b_size;
    a_size = get_rand_int_in_range(10, 10000);
    b_size = get_rand_int_in_range(10, 10000);

    a_arr = (int*)(malloc(a_size * sizeof(int)));
    b_arr = (int*)(malloc(b_size * sizeof(int)));
    c_arr = (int*)(malloc(a_size * sizeof(int)));

    if(!(a_arr && b_arr && c_arr))
    {
        printf("Bad alloc\n");
        return 0;
    }

    fill_int_arr(a_arr, a_size, -1000, 1000);
    fill_int_arr(b_arr, b_size, -1000, 1000);
    quick_sort_int_arr(b_arr, b_size);

    for (int i = 0; i < a_size; ++i)
    {
        c_arr[i] = a_arr[i] + find_closest_value(b_arr, b_size, a_arr[i]);
    }

    print_int_arr(a_arr, a_size);
    print_int_arr(b_arr, b_size);
    print_int_arr(c_arr, a_size);

    free(a_arr);
    free(b_arr);
    free(c_arr);
}

int get_rand_int_in_range(int a, int b)
{
    if (a > b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    return (rand() % (b - a + 1)) + a;
}

void print_int_arr(int* arr, int length)
{
    for (int i = 0; i < length; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

void fill_int_arr(int* arr, int length, int a, int b)
{
    for (int i = 0; i < length; ++i)
    {
        arr[i] = get_rand_int_in_range(a, b);
    }
}

void swap_min_max_int_arr(int* arr, int length)
{
    int min_ind = 0, max_ind = 0;
    for (int i = 1; i < length; ++i)
    {
        if (arr[i] > arr[max_ind])
        {
            max_ind = i;
        } else if (arr[i] < arr[min_ind])
        {
            min_ind = i;
        }
    }

    int tmp = arr[min_ind];
    arr[min_ind] = arr[max_ind];
    arr[max_ind] = tmp;
}

void quick_sort_int_arr(int arr[], int length)
{
    if (length > 1)
    {
        int index = partition_int_array(arr, length);

        quick_sort_int_arr(arr, index);
        quick_sort_int_arr(&(arr[index + 1]), length - index - 1);
    }
}

int partition_int_array(int arr[], int length)
{
    int pivot = arr[length - 1];

    int i = -1;

    for (int j = 0; j <= length - 2; j++) {

        if (arr[j] < pivot) {

            i++;
            swap_int(&arr[i], &arr[j]);
        }
    }
    swap_int(&arr[i + 1], &arr[length - 1]);
    return (i + 1);
}

int find_closest_value(int* sorted_arr, int length, int target)
{
    if (target <= sorted_arr[0])
        return sorted_arr[0];

    if (target >= sorted_arr[length - 1])
        return sorted_arr[length - 1];

    int l = 0, r = length, mid = 0;
    while (l < r) {
        mid = (l + r) / 2;

        if (sorted_arr[mid] == target)
            return sorted_arr[mid];

        if (target < sorted_arr[mid]) {

            if (mid > 0 && target > sorted_arr[mid - 1])
                return get_closest(sorted_arr[mid - 1], sorted_arr[mid], target);
            r = mid;
        } else {
            if (mid < length - 1 && target < sorted_arr[mid + 1])
                return get_closest(sorted_arr[mid], sorted_arr[mid + 1], target);
            l = mid + 1;
        }
    }

    return sorted_arr[mid];
}

int get_closest(int val_1, int val_2, int target)
{
    if (target - val_1 >= val_2 - target)
        return val_2;
    else
        return val_1;
}

void docs()
{
    printf("You must enter two integer numbers as arguments - range of random generation");
}