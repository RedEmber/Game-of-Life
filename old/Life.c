#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "Life.h"
#include "cell.h"

int main()
{
    struct Cell cells = (struct Cell) malloc(sizeof(struct Cell));
    int i;
    /*char input[40];
    char* ret;
    int running = 1;
    int command = 1;

    do
    {
        clear();
        printf("Table goes here.\n");
        do
        {
            printf("Life$ ");
            ret = fgets(input, 40, stdin);
            fflush(stdin);
            if((command = interpret(input)) == 0)
                printf("Bad command.\n");
        } while(command == 0);

        if(command == 1) // Step
            printf("Step.\n\n");
        else if(command == 2) // Run for Time
            printf("Run.\n\n");
        else if(command == 3) // Quit
            running = 0;
    } while(running);

    printf("Goodbye!\n");
    if(ret)
        ret = ret;*/
    cells.x = 0;
    cells.y = 0;
    cells.next = NULL;
    addMethods(&cells);
    cells.seed(COUNT, TABLEX, TABLEY);
    cells.print();
    cells.add(4, 3);
    cells.print();
    cells.destroy();
}

void clear()
{
    int i;
    
    for(i = 0; i < 100; ++i)
        printf("\n");
}

int interpret(char input[40])
{
    if(input[0] == '\n')
        return 0;
    else if(strncmp(input, "step", 4) == 0 || strncmp(input, "s\n", 2) == 0)
        return 1;
    else if(strncmp(input, "run", 3) == 0 || strncmp(input, "r\n", 2) == 0)
        return 2;
    else if(strncmp(input, "quit", 4) == 0 || strncmp(input, "q\n", 2) == 0)
        return 3;
    else 
        return 0;
}

/*int populate(struct Cell* head)
{
    int x, y, i, j, count;

    if(head == NULL)
        return 0;

    for(x = 0; x < TABLEX; ++x)
        for(y = 0; y < TABLEY; ++y)
        {
            count = 0;
            for(i = -1; i < 2; ++i)
                for(j = -1; j < 2; ++j)
                    if(i == 0 && j == 0)
                        continue;
                    else if(find(x + i, y + j, head))
                        ++count;

            if(find(x, y, head) && (count < 2 || count > 3))
                kill(x, y, &head);
            else if(count == 3)
                add(x, y, head);
        }

    return 1;
}*/

/*void printWorld(struct Cell* cells)
{
    int i, j;

    for(i = 0; i < TABLEX + 2; ++i)
        printf("-");
    printf("\n");

    for(i = 0; i < TABLEY; ++i)
    {
        printf("|");
        for(j = 0; j < TABLEX; ++j)
            if(find(j, i, cells))
                printf("#");
            else
                printf(" ");
        printf("|\n");
    }

    for(i = 0; i < TABLEX + 2; ++i)
        printf("-");
    printf("\n");
}*/
