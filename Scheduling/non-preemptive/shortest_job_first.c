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

    // find the first non-executed and arrived process
    while (i < n && (executed[i] == 'y' || processes[i].arrival_time > *time_elapsed))
        i++;

    // if there is no process arrived
    if (i == n)
    {
        printf("no process arrived\n");
        int min_time = 0;
        for (int j = 0; j < n; j++)
            if (executed[j] == 'n')
            {
                min_time = j;
                break;
            }
        for (int j = 0; j < n; j++)
        {
            if (executed[j] == 'n' && processes[i].arrival_time < processes[min_time].arrival_time)
                min_time = j;
        }

        if (processes[min_time].arrival_time > *time_elapsed)
            *time_elapsed = processes[min_time].arrival_time;
    }

    // finding the process with minimum burst time which hasn't executed and is in waiting queue(has arrived)
    int min_idx = 0;
    for (i = 1; i < n; i++)
        if (processes[i].arrival_time <= *time_elapsed && executed[i] == 'n')
        {
            min_idx = i;
            break;
        }
    // printf("%d ", min_idx);
    for (i = 0; i < n; i++)
    {
        // printf("%d ", i);
        if (processes[i].arrival_time <= *time_elapsed && processes[i].burst_time < processes[min_idx].burst_time && executed[i] == 'n')
        {
            min_idx = i;
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
        {1, 2, 6},
        {2, 5, 2},
        {3, 1, 8},
        {4, 0, 3},
        {5, 4, 4}};

    struct Process *execution_order = malloc(n * sizeof(struct Process));

    char *executed = malloc(n * sizeof(char));
    for (int i = 0; i < n; i++)
        executed[i] = 'n';

    int time_elapsed = INT_MAX;
    for (int i = 0; i < n; i++)
        if (processes[i].arrival_time < time_elapsed)
            time_elapsed = processes[i].arrival_time;
    // printf("te-%d\n", time_elapsed);

    for (int i = 0; i < n; i++)
    {
        execution_order[i] = *next_process(processes, n, executed, &time_elapsed);
    }

    printf("Order of Execution: ");
    print_order(execution_order, n);
    printf("\n");

    return 0;
}
