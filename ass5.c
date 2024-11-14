#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

struct Process {
  int max[MAX_RESOURCES], allocated[MAX_RESOURCES], need[MAX_RESOURCES];
} processes[MAX_PROCESSES];

int n, m;

// Function prototypes
void input(int available[]);
void display();
int isSafeState(int available[], int safeSequence[]);

int main() {
  int available[MAX_RESOURCES], safeSequence[MAX_PROCESSES];

  // Input number of processes and resources
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  printf("Enter the number of resources: ");
  scanf("%d", &m);

  // Input process details and available resources
  input(available);

  // Display the entered details
  display();

  // Check if the system is in a safe state
  if (isSafeState(available, safeSequence)) {
    printf("\nSYSTEM IS IN A SAFE STATE.\nSafe sequence: ");
    for (int i = 0; i < n; i++) {
      printf("P%d ", safeSequence[i]);
      if (i < n - 1)
        printf("-> ");
    }
    printf("\n");
  } else {
    printf("\nSYSTEM IS IN AN UNSAFE STATE.\n");
  }

  return 0;
}

// Function to input process details and available resources
void input(int available[]) {
  printf("\nEnter details for each process:\n");
  for (int i = 0; i < n; i++) {
    printf("Process P%d:\n", i);
    printf("  Allocated resources: ");
    for (int j = 0; j < m; j++) {
      scanf("%d", &processes[i].allocated[j]);
    }
    printf("  Maximum resources: ");
    for (int j = 0; j < m; j++) {
      scanf("%d", &processes[i].max[j]);
      processes[i].need[j] = processes[i].max[j] - processes[i].allocated[j];
    }
  }

  printf("Enter the available resources: ");
  for (int j = 0; j < m; j++) {
    scanf("%d", &available[j]);
  }
}

// Function to display the process table
void display() {
  printf("\nProcess\tAllocated\tMax\t\tNeed\n");
  for (int i = 0; i < n; i++) {
    printf("P%d\t", i);
    for (int j = 0; j < m; j++)
      printf("%d ", processes[i].allocated[j]);
    printf("\t\t");
    for (int j = 0; j < m; j++)
      printf("%d ", processes[i].max[j]);
    printf("\t\t");
    for (int j = 0; j < m; j++)
      printf("%d ", processes[i].need[j]);
    printf("\n");
  }
}

// Function to check if the system is in a safe state
int isSafeState(int available[], int safeSequence[]) {
  int work[MAX_RESOURCES], finish[MAX_PROCESSES] = {0};
  int index = 0;

  // Initialize the work array with available resources
  for (int j = 0; j < m; j++) {
    work[j] = available[j];
  }

  // Attempt to find a safe sequence
  for (int count = 0; count < n; count++) {
    int found = 0;
    for (int i = 0; i < n; i++) {
      if (!finish[i]) {
        int canAllocate = 1;
        for (int j = 0; j < m; j++) {
          if (processes[i].need[j] > work[j]) {
            canAllocate = 0;
            break;
          }
        }
        if (canAllocate) {
          for (int j = 0; j < m; j++) {
            work[j] += processes[i].allocated[j];
          }
          safeSequence[index++] = i;
          finish[i] = 1;
          found = 1;
          break;
        }
      }
    }
    if (!found) {
      return 0; // No safe sequence found
    }
  }

  return 1; // Safe sequence found
}
