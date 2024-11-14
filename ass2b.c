#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX 30

void bubble_sort_asc(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_desc(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void print(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n, arr[MAX], pid;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid = fork();
    if (pid == 0) {
        // Child process (Orphan state demonstration)
        sleep(5); // Delay to allow parent to terminate first
        printf("\n***** ORPHAN STATE *****\n");
        printf("Child Process (Orphan) PID: %d\n", getpid());
        printf("Parent Process PPID (should be init or another system process): %d\n", getppid());
        bubble_sort_asc(arr, n);
        printf("Array in Ascending Order (Child Process): ");
        print(arr, n);
    } 
    else if (pid > 0) {
        // Parent process (Zombie state demonstration)
        printf("\n***** PARENT PROCESS *****\n");
        printf("Parent Process PID: %d\n", getpid());

        sleep(5); // Allow child to become a zombie temporarily
        printf("\nChild process is now in ZOMBIE STATE (before wait is called by parent).\n");

        wait(NULL); // Reap the child process
        printf("Child process reaped by parent, no longer in zombie state.\n");

        bubble_sort_desc(arr, n);
        printf("Array in Descending Order (Parent Process): ");
        print(arr, n);
    } 
    else {
        printf("Error in fork.\n");
    }

    return 0;
}
