#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
};

void input_process(struct Process *p)
{
    printf("Process ID: ");
    scanf("%d", &p->id);
    printf("Process Arrival Time: ");
    scanf("%d", &p->id);
    printf("Process Burst Time: ");
    scanf("%d", &p->id);
}

void print_process(struct Process p)
{
    printf("Process ID: %d", p.id);
    printf("Process Arrival Time: %d", p.arrival_time);
    printf("Process Execution Time: %d", p.burst_time);
}

struct Process *next_process(struct Process processes[], int n, char *executed, int *time_elapsed)
{
    int i = 0;
    // finding the first non-executed process
    while (i < n && executed[i] == 'y')
        i++;
    if (i == n)
        return NULL;

    // checking for gaps - no execution period
    int min_time = i;
    while (i < n && executed[i] == 'n' && processes[i].arrival_time > *time_elapsed)
        i++;
    if (i == n)
    {
        for (int i = min_time + 1; i < n; i++)
            if (executed[i] == 'n' && processes[i].arrival_time < processes[min_time].arrival_time)
                min_time = i;
    }
    *time_elapsed = processes[min_time].arrival_time;

    // finding the process with minimum burst time which hasn't executed and is in waiting queue(has arrived)
    int min_idx = i;
    for (i = i + 1; i < n; i++)
    {
        if (processes[i].arrival_time >= *time_elapsed && processes[i].burst_time < processes[min_idx].burst_time && executed[i] == 'n')
        {
            min_idx = i;
            // printf("%d ", i);
        }
    }
    // printf("m-%d ", min_idx);
    // printf("t-%d\n", *time_elapsed);
    *time_elapsed += processes[min_idx].burst_time;
    executed[min_idx] = 'y';

    return &processes[min_idx];
}

void print_order(struct Process *processes, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", processes[i].id);
}

int main()
{
    int n = 5;
    struct Process processes[] = {
        {1, 3, 1},
        {2, 1, 4},
        {3, 4, 2},
        {4, 0, 6},
        {5, 2, 3}};

    struct Process *execution_order = malloc(n * sizeof(struct Process));

    char *executed = malloc(n * sizeof(char));
    for (int i = 0; i < n; i++)
        executed[i] = 'n';

    int time_elapsed = INT_MAX;
    for (int i = 0; i < n; i++)
        if (processes[i].arrival_time < time_elapsed)
            time_elapsed = processes[i].arrival_time;

    for (int i = 0; i < n; i++)
    {
        execution_order[i] = *next_process(processes, n, executed, &time_elapsed);
    }

    printf("Order of Execution: ");
    print_order(execution_order, n);
    printf("\n");

    return 0;
}
