#include <stdio.h>

#define MAX_PROCESSES 10

struct Process 
{
    int id, arrival_time, burst_time, remaining_time, completion_time, waiting_time, turnaround_time;
};

void round_robin(struct Process p[], int n, int time_quantum) 
{
    int current_time = 0, completed = 0;
    int total_waiting_time = 0, total_turnaround_time = 0;
    
    while (completed != n) 
    {
        for (int i = 0; i < n; i++) 
        {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) 
            {
                if (p[i].remaining_time <= time_quantum) 
                {
                    current_time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    p[i].completion_time = current_time;
                    completed++;
                    
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

                    total_turnaround_time += p[i].turnaround_time;
                    total_waiting_time += p[i].waiting_time;
                } 
                else 
                {
                    p[i].remaining_time -= time_quantum;
                    current_time += time_quantum;
                }
            }
        }
    }

    printf("\nRound Robin Scheduling:\n");
    printf("ID  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++) 
    {
        printf("%2d  %2d  %2d  %2d  %3d  %2d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() 
{
    int n, time_quantum;
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

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    round_robin(p, n, time_quantum);

    return 0;
}

