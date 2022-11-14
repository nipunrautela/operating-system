#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
};

void swap_processes(struct Process *p1, struct Process *p2)
{
    struct Process temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_processes_arrival_time(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].arrival_time > processes[j].arrival_time)
                swap_processes(&processes[i], &processes[j]);
        }
    }
}

int main()
{
    int n = 5;
    struct Process processes[] = {
        {1, 1},
        {2, 3},
        {3, 4},
        {4, 2},
        {5, 5}};
    printf("Execution Order: ");
    sort_processes_arrival_time(processes, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", processes[i].id);
    }
    printf("\n");
    return 0;
}
