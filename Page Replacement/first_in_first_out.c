#include <stdio.h>
#include <stdlib.h>

int search_frame(int frames[], int frno, int page)
{
    for (int i = 0; i < frno; i++)
        if (frames[i] == page)
            return i;

    return -1;
}

void fifo_replacement(int pages[], int pgno, int frames[], int frno)
{
    int miss = 0;
    for (int i = 0; i < pgno; i++)
    {
        if (search_frame(frames, frno, pages[i]) == -1)
        {
            frames[miss % frno] = pages[i];
            miss++;
        }
    }

    printf("Hits: %d\n", pgno - miss);
    printf("Miss: %d\n", miss);
}

int main()
{
    int pgno = 13;
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};

    const int frame_size = 4;
    int *frames = malloc(frame_size * sizeof(int));
    for (int i = 0; i < frame_size; i++)
        frames[i] = -1;

    fifo_replacement(pages, pgno, frames, frame_size);

    return 0;
}
