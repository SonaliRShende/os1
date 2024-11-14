#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void FCFS(int pages[], int n, int frames);
void LRU(int pages[], int n, int frames);
void Optimal(int pages[], int n, int frames);

int main() {
  int choice, n, frames;

  // Input: number of pages
  printf("Enter the number of pages: ");
  scanf("%d", &n);

  int pages[n];
  printf("Enter the page reference string:\n");
  for (int i = 0; i < n; i++) {
    scanf("%d", &pages[i]);
  }

  // Input: number of frames (minimum 3)
  do { 
    printf("Enter the number of frames (minimum 3): ");
    scanf("%d", &frames);
  } while (frames < 3);

  // Menu-driven interface
  while (1) {
    printf("\n--- Page Replacement Algorithms ---\n");
    printf("1. FCFS (First-Come, First-Served)\n");
    printf("2. LRU (Least Recently Used)\n");
    printf("3. Optimal Page Replacement\n");
    printf("4. Exit\n");
    printf("Select an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      printf("\nFCFS Page Replacement:\n");
      FCFS(pages, n, frames);
      break;
    case 2:
      printf("\nLRU Page Replacement:\n");
      LRU(pages, n, frames);
      break;
    case 3:
      printf("\nOptimal Page Replacement:\n");
      Optimal(pages, n, frames);
      break;
    case 4:
      printf("Exiting...\n");
      exit(0);
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
   
  return 0;
}

// Function to implement FCFS Page Replacement
void FCFS(int pages[], int n, int frames) {
  int frame[frames], page_faults = 0;
  for (int i = 0; i < frames; i++)
    frame[i] = -1;

  int index = 0;
  for (int i = 0; i < n; i++) {
    int found = 0;
    // Check if page is already in the frame
    for (int j = 0; j < frames; j++) {
      if (frame[j] == pages[i]) {
        found = 1;
        break;
      }
    }

    // If page is not in the frame, replace using FCFS
    if (!found) {
      frame[index] = pages[i];
      index = (index + 1) % frames;
      page_faults++;
    }

    // Display current state of frames
    printf("Page %d: ", pages[i]);
    for (int j = 0; j < frames; j++) {
      if (frame[j] != -1)
        printf("%d ", frame[j]);
      else
        printf("- ");
    }
    printf("\n");
  }

  printf("Total Page Faults (FCFS): %d\n", page_faults);
}

// Function to implement LRU Page Replacement
void LRU(int pages[], int n, int frames) {
  int frame[frames], page_faults = 0;
  int time[frames]; // To keep track of the last used time of each frame

  // Initialize frames with -1 (indicating they are empty)
  for (int i = 0; i < frames; i++) {
    frame[i] = -1;
    time[i] = -1;
  }

  for (int i = 0; i < n; i++) {
    int found = 0;

    // Check if the current page is already in one of the frames
    for (int j = 0; j < frames; j++) {
      if (frame[j] == pages[i]) {
        found = 1;
        time[j] = i; // Update the time of this frame as it was recently used
        break;
      }
    }

    // If the page is not found in the frame, we have a page fault
    if (!found) {
      int lru_index = 0;

      // Find the frame with the least recent use (smallest timestamp)
      for (int j = 1; j < frames; j++) {
        if (time[j] < time[lru_index]) {
          lru_index = j;
        }
      }

      // Replace the least recently used page with the new one
      frame[lru_index] = pages[i];
      time[lru_index] =
          i; // Update the time of this frame with the current index
      page_faults++;
    }

    // Display the current state of the frames
    printf("Page %d: ", pages[i]);
    for (int j = 0; j < frames; j++) {
      if (frame[j] != -1) {
        printf("%d ", frame[j]);
      } else {
        printf("- ");
      }
    }
    printf("\n");
  }

  printf("\nTotal Page Faults (LRU): %d\n", page_faults);
}

// Function to implement Optimal Page Replacement
void Optimal(int pages[], int n, int frames) {
  int frame[frames], page_faults = 0;
  for (int i = 0; i < frames; i++)
    frame[i] = -1; // Initialize frames to -1

  for (int i = 0; i < n; i++) {
    int found = 0;

    // Check if the page is already in one of the frames
    for (int j = 0; j < frames; j++) {
      if (frame[j] == pages[i]) {
        found = 1;
        break;
      }
    }

    // If page not found, replace using Optimal strategy
    if (!found) {
      int replace_index = -1, furthest = i;
      for (int j = 0; j < frames; j++) {
        if (frame[j] == -1) {
          replace_index = j;
          break;
        }
        int next_use = n;
        for (int k = i + 1; k < n; k++) {
          if (pages[k] == frame[j]) {
            next_use = k;
            break;
          }
        }
        if (next_use > furthest) {
          furthest = next_use;
          replace_index = j;
        }
      }
      if (replace_index == -1)
        replace_index = 0;
      frame[replace_index] = pages[i];
      page_faults++;
    }

    // Print the current state of the frames
    printf("Page %d: ", pages[i]);
    for (int j = 0; j < frames; j++) {
      if (frame[j] != -1)
        printf("%d ", frame[j]);
      else
        printf("- ");
    }
    printf("\n");
  }
  printf("Total Page Faults (Optimal): %d\n", page_faults);
}
