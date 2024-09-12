#include <stdio.h>

// Function prototypes
void merge_sort(int arr[], int left, int right);
void merge(int arr[], int left, int middle, int right);

int main(void)
{
    int array[9] = {7, 2, 8, 3, 1, 0, 5, 4, 6};
    merge_sort(array, 0, 8);
    for (int i = 0; i < 9; i++) {
        printf("%i\n", array[i]);
    }
    return 0;
}

void merge(int arr[], int left, int middle, int right) {

    // Declare helper variables
    int i, j, k;

    // Define length of left and right halves
    int num_left = middle - left + 1;
    int num_right = right - middle;

    // Create helper arrays
    int l[num_left], r[num_right];


    // Populate helper arrays
    for (i = 0; i < num_left; i++) {
        l[i] = arr[left + i];
    }
    for (j = 0; j < num_right; j++) {
        r[j] = arr[middle + 1 + j];
    }

    // Redefine helper variables
    i = 0;
    j = 0;
    k = left;
    // Merge helper arrays int original array based on strength
    while (i < num_left && j < num_right) {
        if (l[i] <= r[j]) {
            arr[k] = l[i];
            i++;
        }
        else {
            arr[k] = r[j];
            j++;
        }
        k++;
    }

    // Add elements that were no iterated to original arr
    while (i < num_left) {
        arr[k] = l[i];
        i++;
        k++;
    }

    // Add elements that were no iterated to original arr
    while (j < num_right) {
        arr[k] = r[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {

        // Get middle index
        int middle = left + (right - left) / 2;

        // Sort both halves of the array
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);

        // Merge halves of the array
        merge(arr, left, middle, right);
    }
}

