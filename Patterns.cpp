#include "Cell.h"

Patterns::Patterns()
{
    head = NULL;
}

int Patterns::add(Cell toadd, char* name)
{
    struct Pattern* temp;
    int x, y;

    temp = new Pattern;
    temp->name = new char[strlen(name)+1];
    strncpy(temp->name, name, strlen(name)+1);
    temp->xlength = toadd.getXLen();
    temp->ylength = toadd.getYLen();
    temp->grid = new char*[temp->xlength];

    for(x = 0; x < temp->xlength; ++x)
    {
        temp->grid[x] = new char[temp->ylength];
        for(y = 0; y < temp->ylength; ++y)
            if(toadd.find(x, y))
                temp->grid[x][y] = '#';
            else
                temp->grid[x][y] = ' ';
    }

    temp->next = head;
    head = temp;

    return 1;
}

int Patterns::addFile(char* filename)
{
    ifstream file(filename);
    Pattern* temp;
    char line[100];
    int count = 0;
    int i, j;

    if(file.is_open())
    {
        file.getline(line, 100, '\n');
        while(!file.eof())
        {
            ++count;
            temp = new Pattern;

            temp->xlength = stoi(line, NULL);
            file.getline(line, 100, '\n');
            temp->ylength = stoi(line, NULL);

            file.getline(line, 100, '\n');
            temp->name = new char[strlen(line) + 1];
            strncpy(temp->name, line, strlen(line) + 1);

            temp->grid = new char*[temp->xlength];
            for(i = 0; i < temp->xlength; ++i)
                temp->grid[i] = new char[temp->ylength];

            for(i = 0; i < temp->ylength; ++i)
            {
                file.getline(line, 100, '\n');
                for(j = 0; j < temp->xlength; ++j)
                    if(line[j] == '-')
                        temp->grid[j][i] = ' ';
                    else
                        temp->grid[j][i] = '#';
            }

            temp->next = head;
            head = temp;
            temp = NULL;
            file.getline(line, 100, '\n');
        }
    }
    else
        return 0;
    return count;
}

int Patterns::addToCell(Cell& cells, char* name, int x, int y)
{
    struct Pattern* toadd = head;
    int count = 0;
    int i, j;

    while(toadd != NULL)
    {
        if(strncmp(toadd->name, name, strlen(toadd->name)) == 0)
        {
            if(x + toadd->xlength > cells.getXLen() || y + toadd->ylength > cells.getYLen())
                return -1;

            for(i = 0; i < toadd->xlength; ++i)
                for(j = 0; j < toadd->ylength; ++j)
                    if(toadd->grid[i][j] == '#')
                    {
                        cells.add(x + i, y + j);
                        ++count;
                    }
            return count;
        }
        toadd = toadd->next;
    }

    return 0;
}

int Patterns::rem(char* name)
{
    if(head == NULL)
        return 0;
    return remR(name, &head);
}

int Patterns::remR(char* name, struct Pattern** head)
{
    struct Pattern* temp;
    int i;

    if(*head == NULL)
        return 0;
    else if(strncmp((*head)->name, name, strlen((*head)->name)) == 0)
    {
        temp = *head;
        *head = (*head)->next;

        delete temp->name;
        temp->name = NULL;

        for(i = temp->xlength - 1; i >= 0; --i)
        {
            delete temp->grid[i];
            temp->grid[i] = NULL;
        }
        temp->grid = NULL;

        temp->xlength = 0;
        temp->ylength = 0;

        delete temp;
        temp = NULL;
        return 1;
    }
    else
        return remR(name, &((*head)->next));
}

int Patterns::display()
{
    struct Pattern* step = head;
    int count = 0;
    int i, j;

    if(head == NULL)
    {
        cout <<"Empty." <<endl;
        return 0;
    }

    while(step != NULL)
    {
        ++count;
        for(i = 0; i < step->xlength + 2; ++i)
            cout <<"-";
        cout <<endl;

        for(i = 0; i < step->ylength; ++i)
        {
            cout <<"|";
            for(j = 0; j < step->xlength; ++j)
                cout <<step->grid[j][i];
            cout <<"|" <<endl;
        }

        for(i = 0; i < step->xlength + 2; ++i)
            cout <<"-";
        cout <<endl <<step->name <<endl <<"Press Enter.";
        cin.ignore(1);
        cout <<endl;

        step = step->next;
    }

    return count;
}

int Patterns::destroy()
{
    int ret;

    if(head == NULL)
        return 0;

    ret = destroyR(head);
    head = NULL;
    return ret;
}

int Patterns::destroyR(struct Pattern* head)
{
    int ret, i;

    if(head == NULL)
        return 0;

    ret = destroyR(head->next);
    for(i = head->xlength - 1; i >= 0; --i)
    {
        delete head->grid[i];
        head->grid[i] = NULL;
    }
    delete head->grid;
    head->grid = NULL;

    delete head->name;
    head->name = NULL;

    head->xlength = 0;
    head->ylength = 0;

    delete head;
    head = NULL;
    return ret + 1;
}
