#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX 30
#define MAX_ARGS 100

// Function to perform bubble sort on an array
void sortArray(int arr[], int size) 
{
    int temp;
    for (int i = 0; i < size - 1; i++) 
    {
        for (int j = 0; j < size - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() 
{
  
    int i,n,arr[MAX];
    printf("\nEnter the no.of elements you want in an array: ");
    scanf("%d",&n);
    printf("Enter the array elements : ");
    for(i=0;i<n;i++)
    {
       	scanf("%d",&arr[i]);
    }
    //int n1 = sizeof(arr) / sizeof(arr[0]);

    // Sort the array
    sortArray(arr, n);

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Prepare arguments for the child process
    char *args[MAX_ARGS];
    args[0] = "./child";  // Child program name
    for (int i = 0; i < n; i++) {
        args[i + 1] = malloc(12); // Allocating memory for each number
        snprintf(args[i + 1], 12, "%d", arr[i]);
    }
    args[n + 1] = NULL; // Null-terminate the arguments array

    // Fork a child process
    pid_t pid = fork();
    if (pid == 0) {
        // In the child process
        execve("./child", args, NULL);
        perror("execve failed");
        exit(1); // Exit if execve fails
    } else if (pid > 0) {
        // In the parent process
        wait(NULL); // Wait for the child process to complete

        // Free allocated memory
        for (int i = 1; i <= n; i++) {
            free(args[i]);
        }
    } else {
        // Forking failed
        perror("fork failed");
        return 1;
    }

    return 0;
}



