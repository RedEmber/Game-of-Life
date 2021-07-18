#include "Cell.h"

Cell::Cell(int x, int y)
{
    head = NULL;
    xlength = x;
    ylength = y;
}

int Cell::seed(int count)
{
    struct Unit* step;
    int x, y, i;

    if(count >= ((xlength*ylength)/2))
        return 0;
    
    destroy();
    head = new Unit();
    step = head;

    srand(time(0));
    for(i = 0; i < count; ++i)
    {
        x = rand() % xlength;
        y = rand() % ylength;
        if(findR(x, y, head))
            --i;
        else if(i < count - 1)
        {
            step->x = x;
            step->y = y;
            step->next = new Unit();
            step = step->next;
        }
        else
            step->next = NULL;
    }

    return 1;
}

int Cell::add(int x, int y)
{
    struct Unit* temp;

    if(head == NULL)
    {
        head = new Unit;
        head->x = x;
        head->y = y;
        head->next = NULL;
        return 2;
    }

    temp = new Unit;
    temp->x = x;
    temp->y = y;
    temp->next = head;
    head = temp;
    return 1;
}

int Cell::kill(int x, int y)
{
    if(head == NULL)
        return 0;
    else
        return killR(x, y, &head);
}

int Cell::killR(int x, int y, struct Unit** head)
{
    struct Unit* temp;

    if(*head == NULL)
        return 0;
    else if((*head)->x == x && (*head)->y == y)
    {
        temp = *head;
        *head = (*head)->next;
        temp->x = 0;
        temp->y = 0;
        temp->next = NULL;
        delete temp;
        return 1;
    }
    else
        return killR(x, y, &((*head)->next));
}

int Cell::find(int x, int y)
{
    return findR(x, y, head);
}

int Cell::findR(int x, int y, struct Unit* head)
{
    if(head == NULL)
        return 0;
    else if(head->x == x && head->y == y)
        return 1;
    else
        return findR(x, y, head->next);
}

int Cell::populate()
{
    short nextgen[xlength][ylength];
    int x, y, i, j, count;

    for(x = 0; x < xlength; ++x)
        for(y = 0; y < ylength; ++y)
        {
            nextgen[x][y] = 0;
            count = 0;
            for(i = -1; i < 2; ++i)
                for(j = -1; j < 2; ++j)
                    if(i == 0 && j == 0)
                        continue;
                    else if(findR(x + i, y + j, head))
                        ++count;

            if(findR(x, y, head) && (count < 2 || count > 3))
                nextgen[x][y] = 1;
            if(!findR(x, y, head) && count == 3)
                nextgen[x][y] = 2;
        }

    for(x = 0; x < xlength; ++x)
        for(y = 0; y < ylength; ++y)
            if(nextgen[x][y] == 1)
                kill(x, y);
            else if(nextgen[x][y] == 2)
                add(x, y);

    return 1;
}

int Cell::getXLen()
{
    return xlength;
}

int Cell::getYLen()
{
    return ylength;
}


int Cell::print()
{
    struct Unit* step = head;
    int count = 0;

    if(head == NULL)
        cout <<"Empty.";
    
    while(step != NULL)
    {
        ++count;
        cout <<"(" <<step->x <<"," <<step->y <<")";
        step = step->next;
        if(step != NULL)
            cout <<", ";
    }

    cout <<endl;
    return count;
}

int Cell::destroy()
{
    int ret;

    if(head == NULL)
        return 0;
    ret = destroyR(head);
    head = NULL;
    return ret;
}

int Cell::destroyR(struct Unit* head)
{
    int ret;

    if(head == NULL)
        return 0;

    ret = destroyR(head->next);
    head->x = 0;
    head->y = 0;
    head->next = NULL;
    delete head;
    head = NULL;
    return ret + 1;
}
