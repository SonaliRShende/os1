#include <stdio.h>

#define MAX_PROCESSES 10

struct Process 
{
    int id, arrival_time, burst_time, remaining_time, completion_time, waiting_time, turnaround_time;
};

void sjf_preemptive(struct Process p[], int n) 
{
    int completed = 0, current_time = 0, shortest = -1, min_time = 100;
    int total_waiting_time = 0, total_turnaround_time = 0;

    while (completed != n)
    {
        shortest = -1;
        min_time = 100;

        // Find the shortest job that has arrived
        for (int i = 0; i < n; i++) 
        {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].remaining_time < min_time) 
            {
                shortest = i;
                min_time = p[i].remaining_time;
            }
        }

        if (shortest == -1) 
        {
            current_time++;
            continue;
        }

        // Execute the shortest job for 1 time unit
        p[shortest].remaining_time--;
        current_time++;

        // If the process is finished
        if (p[shortest].remaining_time == 0) 
        {
            completed++;
            p[shortest].completion_time = current_time;
            p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;

            total_turnaround_time += p[shortest].turnaround_time;
            total_waiting_time += p[shortest].waiting_time;
        }
    }

    printf("\nSJF (Preemptive) Scheduling:\n");
    printf("ID  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%2d  %2d  %2d  %2d  %3d  %2d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time,          	p[i].waiting_time);
    }

    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() 
{
    int n;
    struct Process p[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) 
    {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }

    sjf_preemptive(p, n);

    return 0;
}



