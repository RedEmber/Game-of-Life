#include "cell.h"

int seed(int count, int tablex, int tabley)
{
    struct Cell* step;
    int i;
    
    head = (struct Cell*) malloc(sizeof(struct Cell));
    step = head;

    srand(time(0));
    for(i = 0; i < count; ++i)
    {
        step->x = rand() % TABLEX;
        step->y = rand() % TABLEY;
        addMethods(&step);
        if(i < count - 1)
        {
            step->next = (struct Cell*) malloc(sizeof(struct Cell));
            step = step->next;
        }
        else
            step->next = NULL;
    }

    return 1;
}

int add(int x, int y)
{
    struct Cell* temp = (struct Cell*) malloc(sizeof(struct Cell));

    temp->x = x;
    temp->y = y;
    addMethods(&temp);

    if(head == NULL)
    {
        temp->next = NULL;
        head = temp;
        return 2;
    }

    temp->next = head;
    head = temp;
    return 1;
}

int kill(int x, int y)
{
    struct Cell* temp = head;
    struct Cell* temp2;

    if(head == NULL)
        return 0;
    else if(head->x == x && head->y == y)
    {
        temp = head;
        head = head->next;
        temp->x = 0;
        temp->y = 0;
        temp->next = NULL;
        free(temp);
        return 1;
    }
    
    while(temp->next != NULL)
    {
        if(temp->next->x == x && temp->next->y == y)
        {
            temp2 = temp->next;
            temp->next = temp2->next;
            temp2->x = 0;
            temp2->y = 0;
            temp2->next = NULL;
            free(temp2);
            return 1;
        }
        
        temp = temp->next;        
    }

    return 0;
}

int find(int x, int y)
{
    struct Cell* step = head;

    if(head == NULL)
        return 0;
    
    while(step != NULL)
        if(step->x == x && step->y == y)
            return 1;
        else
            step = step->next;

    return 0;
}

int print()
{ 
    struct Cell* step = head;

    if(head == NULL)
        printf("Empty.\n");

    while(step != NULL)
    {
        printf("(%d,%d)", step->x, step->y);
        if(step->next != NULL)
            printf(", ");
        else print("\n");

        step = step->next;
    }

    return 1;
}

int destroy()
{
    struct Cell* temp;
    int count = 0;

    while(head != NULL)
    {
        head->x = 0;
        head->y = 0;
        temp = head->next;
        free(head);
        head = temp;
        ++count;
    }

    return count;
}

void addMethods(struct Cell* cell)
{
    cell->seed = seed;
    cell->add = add;
    cell->kill = kill;
    cell->find = find;
    cell->print = print;
    cell->destroy = destroy;
}
