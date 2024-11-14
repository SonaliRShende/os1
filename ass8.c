#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Function to calculate absolute value
int absolute(int x) { return x > 0 ? x : -x; }

// SSTF Disk Scheduling
void sstf(int request[], int head, int n) {
  int visited[n], seek_count = 0, seek_sequence[n + 1];
  for (int i = 0; i < n; i++)
    visited[i] = 0; // Mark all requests as unvisited

  seek_sequence[0] = head;

  for (int i = 0; i < n; i++) {
    int min_distance = INT_MAX, index = -1;

    // Find the nearest unvisited request
    for (int j = 0; j < n; j++) {
      if (!visited[j] && absolute(head - request[j]) < min_distance) {
        min_distance = absolute(head - request[j]);
        index = j;
      }
    }

    // Process the nearest request
    if (index != -1) {
      visited[index] = 1;
      seek_count += min_distance;
      head = request[index];
      seek_sequence[i + 1] = head;
    }
  }

  printf("SSTF Total Seek Operations: %d\n", seek_count);
  printf("SSTF Seek Sequence: ");
  for (int i = 0; i <= n; i++)
    printf("%d ", seek_sequence[i]);
  printf("\n");
}

// SCAN Disk Scheduling
void scan(int request[], int head, int n, int disk_size, int direction) {
  int seek_count = 0, seek_sequence[n + 2];
  request[n] = 0;                 // Add lower boundary
  request[n + 1] = disk_size - 1; // Add upper boundary
  n += 2;

  // Sort the requests
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (request[i] > request[j]) {
        int temp = request[i];
        request[i] = request[j];
        request[j] = temp;
      }
    }
  }

  int index = 0;
  while (index < n && request[index] < head)
    index++;

  int seq_index = 0;

  if (direction == 1) {
    // Move towards the higher tracks
    for (int i = index; i < n; i++)
      seek_sequence[seq_index++] = request[i];
    // Move towards the lower tracks
    for (int i = index - 1; i >= 0; i--)
      seek_sequence[seq_index++] = request[i];
  } else {
    // Move towards the lower tracks
    for (int i = index - 1; i >= 0; i--)
      seek_sequence[seq_index++] = request[i];
    // Move towards the higher tracks
    for (int i = index; i < n; i++)
      seek_sequence[seq_index++] = request[i];
  }

  seek_count = absolute(head - seek_sequence[0]);
  for (int i = 1; i < seq_index; i++)
    seek_count += absolute(seek_sequence[i] - seek_sequence[i - 1]);

  printf("SCAN Total Seek Operations: %d\n", seek_count);
  printf("SCAN Seek Sequence: ");
  for (int i = 0; i < seq_index; i++)
    printf("%d ", seek_sequence[i]);
  printf("\n");
}

// C-LOOK Disk Scheduling
void clook(int request[], int head, int n) {
  int seek_count = 0, seek_sequence[n];
  // Sort the requests
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (request[i] > request[j]) {
        int temp = request[i];
        request[i] = request[j];
        request[j] = temp;
      }
    }
  }

  int index = 0;
  while (index < n && request[index] < head)
    index++;

  int seq_index = 0;
  // Move towards higher tracks
  for (int i = index; i < n; i++)
    seek_sequence[seq_index++] = request[i];
  // Wrap around to the lowest track
  for (int i = 0; i < index; i++)
    seek_sequence[seq_index++] = request[i];

  seek_count = absolute(head - seek_sequence[0]);
  for (int i = 1; i < seq_index; i++)
    seek_count += absolute(seek_sequence[i] - seek_sequence[i - 1]);

  printf("C-LOOK Total Seek Operations: %d\n", seek_count);
  printf("C-LOOK Seek Sequence: ");
  for (int i = 0; i < seq_index; i++)
    printf("%d ", seek_sequence[i]);
  printf("\n");
}

// Main Function
int main() {
  int n, head, disk_size, direction;

  // Get the number of disk requests
  printf("Enter number of requests: ");
  scanf("%d", &n);

  int request[n + 2]; // Extra space for SCAN boundaries
  printf("Enter the request array:\n");
  for (int i = 0; i < n; i++)
    scanf("%d", &request[i]);

  // Get the initial head position and disk size
  printf("Enter initial head position: ");
  scanf("%d", &head);

  printf("Enter disk size: ");
  scanf("%d", &disk_size);

  // Call SSTF
  printf("\nSSTF Disk Scheduling:\n");
  sstf(request, head, n);

  // Call SCAN
  printf("\nSCAN Disk Scheduling:\n");
  printf("Enter direction for SCAN (1 for high, 0 for low): ");
  scanf("%d", &direction);
  scan(request, head, n, disk_size, direction);

  // Call C-LOOK
  printf("\nC-LOOK Disk Scheduling:\n");
  clook(request, head, n);

  return 0;
}
