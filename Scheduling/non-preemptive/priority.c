#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
};

void swap_processes(struct Process *p1, struct Process *p2)
{
    struct Process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_priority(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (processes[i].priority < processes[j].priority)
                swap_processes(&processes[i], &processes[j]);
}

void priority_scheduling(struct Process processes[], int n, struct Process order[])
{
    sort_priority(processes, n);
    int execution_count = 0;
    bool *executed = (bool *)malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++)
        executed[i] = false;
    int c = 0;

    int time_elapsed = INT_MAX;
    // find the first process arrival time
    for (int i = 0; i < n; i++)
        if (time_elapsed > processes[i].arrival_time)
            time_elapsed = processes[i].arrival_time;

    while (execution_count < n)
    {
        int to_execute = 0;

        // find the first non executed process
        while (executed[to_execute])
            to_execute++;

        // check if there's at least one process arrived
        int k = to_execute;
        int min_time = to_execute;
        for (k = 0; k < n; k++)
            if (executed[k] == false && processes[k].arrival_time <= time_elapsed)
                break;
            else if (executed[k] == false && processes[k].arrival_time < processes[min_time].arrival_time)
                min_time = k;
        // if no process arrived then set time to next process arrival time
        if (k == n)
            time_elapsed = processes[min_time].arrival_time;

        // first arrived non executed process
        while (executed[to_execute] || processes[to_execute].arrival_time > time_elapsed)
            to_execute++;

        // finding process to execute
        for (int i = 0; i < n; i++)
        {
            if (!executed[i] && processes[i].arrival_time < time_elapsed && processes[i].priority > processes[to_execute].priority)
                to_execute = i;
        }

        executed[to_execute] = true;
        order[c++] = processes[to_execute];
        time_elapsed += processes[to_execute].burst_time;
        execution_count++;
    }
}

int main()
{
    int n = 5;
    struct Process processes[] = {
        {1, 0, 4, 2},
        {2, 1, 3, 3},
        {3, 2, 1, 4},
        {4, 3, 5, 5},
        {5, 4, 2, 5},
    };

    struct Process *execution_order = malloc(n * sizeof(struct Process));
    priority_scheduling(processes, n, execution_order);
    for (int i = 0; i < n; i++)
        printf("%d ", execution_order[i].id);
    printf("\n");

    return 0;
}
