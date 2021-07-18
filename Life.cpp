#include "Cell.h"
#include "termcolor.hpp"
#define COUNT 10
#define TABLEX 50
#define TABLEY 20

void step(Cell&, char[40]);
void run(Cell&, char[40], char[40]);
void edit(Cell&, Patterns&, char[40], char[40]);
void dis(Patterns, char[40]);
void rem(Patterns&, char[40], char[40]);
void add(Cell&, Patterns&, char[40], char[40]);
void kill(Cell&, char[40]);
void seed(Cell&, char[40], char[40], int, int);
void help(char[40]);
void clear();
int interpret(char[40]);
void printWorld(Cell, int = TABLEX, int = TABLEY);
int ctoi(char[40], int, char);
int numlength(int);
int stoc(char[40], char*&, int, char);

int main()
{
    Patterns patterns;
    Cell cells(TABLEX, TABLEY);
    char file[40] = {"oscillators.txt\0"};
    char input[40];
    char nextshell[40] = {'\0'};
    int command;
    bool running = true;
    int i;

    patterns.addFile(file);
    strncpy(file, "spaceships.txt\0", 15);
    patterns.addFile(file);
    do
    {
        clear();
        printWorld(cells);

        command = 0;
        if(nextshell[0] != '\0')
            cout <<nextshell <<endl;
        else
            cout <<"~~~Life~~~" <<endl;
        cout <<"$ ";
        cin.getline(input, sizeof(input));
        command = interpret(input);

        for(i = 0; i < 40; ++i)
            nextshell[i] = '\0';

        if(command == 0)
            strncpy(nextshell, "Bad command.\0", 13);
        if(command == 1)
            step(cells, nextshell);
        else if(command == 2)
            run(cells, nextshell, input);
        else if(command == 3)
            edit(cells, patterns, nextshell, input);
        else if(command == 4)
            dis(patterns, nextshell);
        else if(command == 5)
            rem(patterns, nextshell, input);
        else if(command == 6)
            add(cells, patterns, nextshell, input);
        else if(command == 7)
            kill(cells, nextshell);
        else if(command == 8)
            seed(cells, nextshell, input, TABLEX, TABLEY);
        else if(command == 9)
            help(nextshell);
        else if(command == -1)
            running = false;
    } while(running);

    cout <<"Goodbye!" <<endl;
    cells.destroy();
    patterns.destroy();
}

void step(Cell &cells, char nextshell[40])
{
    cells.populate();
    strncpy(nextshell, "Step.\0", 6);
}

void run(Cell &cells, char nextshell[40], char input[40])
{
    int sleep;
    int length;
    int i;

    strncpy(nextshell, "Run\0", 4);

    if(input[1] == ' ')
    {
        sleep = ctoi(input, 2, ' ');
        length = ctoi(input, 3 + numlength(sleep), '\0');
    }
    else
    {
        sleep = ctoi(input, 4, ' ');
        length = ctoi(input, 5 + numlength(sleep), '\0');
    }

    if(sleep == -1 || length == -1)
    {
        strncpy(nextshell, "Could not parse args.\0", 22);
        return;
    }

    for(i = 0; i < length; ++i)
    {
        clear();
        cells.populate();
        printWorld(cells);
        cout <<"~~~Life~~~" <<endl <<"Gen " <<i+1 <<flush;
        usleep(sleep * 1000);
    }
}

void edit(Cell &cells, Patterns& patterns, char nextshell[40], char input[40])
{
    Cell* pattern;
    char name[40];
    bool running = true;
    int xlength, ylength, x, y;

    if(input[1] == ' ')
    {
        xlength = ctoi(input, 2, ' ');
        ylength = ctoi(input, 3 + numlength(xlength), '\0');
    }
    else
    {
        xlength = ctoi(input, 5, ' ');
        ylength = ctoi(input, 6 + numlength(xlength), '\0');
    }

    if(xlength == -1 || ylength == -1)
    {
        strncpy(nextshell, "Could not parse args.\0", 22);
        return;
    }

    pattern = new Cell(xlength, ylength);
    strncpy(nextshell, "~~~Life~~~\0", 11);
    while(running)
    {
        clear();
        printWorld(*pattern, xlength, ylength);
        cout <<nextshell <<endl <<"X: ";
        cin >> x;

        clear();
        printWorld(*pattern, xlength, ylength);
        cout <<nextshell <<endl <<"Y: ";
        cin >> y;

        if(x == -1 || y == -1)
            running = false;
        else if(pattern->find(x, y))
            pattern->kill(x, y);
        else
            pattern->add(x, y);
    }

    cin.ignore(100, '\n');

    cout <<"Enter pattern name: ";
    cin.getline(name, sizeof(name));
    cout <<"Press Enter to add pattern.";
    cin.ignore(100, '\n');
    patterns.add(*pattern, name);
    
    pattern->destroy();
    delete pattern;
    strncpy(nextshell, "~~~Life~~~\0", 11);
}

void dis(Patterns patterns, char nextshell[40])
{
    clear();
    if(patterns.display() == 0)
        strncpy(nextshell, "Empty.\0", 7);
    else
        strncpy(nextshell, "~~~Life~~~\0", 11);
}

void rem(Patterns& patterns, char nextshell[40], char input[40])
{
    char* torem;
    int i;

    if(input[2] == ' ')
        i = 3;
    else
        i = 7;

    if(!stoc(input, torem, i, '\0') || !patterns.rem(torem))
        strncpy(nextshell, "Not found.\0", 11);
    else
        strncpy(nextshell, "Removed.\0", 9);
}

void add(Cell& cells, Patterns& patterns, char nextshell[40], char input[40])
{
    char* toadd;
    int x, y, i;

    if(input[1] == ' ')
        i = 2;
    else
        i = 4;

    x = ctoi(input, i, ' ');
    y = ctoi(input, i + numlength(x) + 1, ' ');

    if(x == -1 || y == -1 || !stoc(input, toadd, i + numlength(x) + numlength(y) + 2, '\0'))
        strncpy(nextshell, "Could not parse args.\0", 22);
    else if(!patterns.addToCell(cells, toadd, x, y))
            strncpy(nextshell, "Pattern not found.\0", 19);
    else
            strncpy(nextshell, "Added.\0", 7);
}

void kill(Cell& cells, char nextshell[40])
{
    cells.destroy();
    strncpy(nextshell, "Killed.\0", 8);
}

void seed(Cell& cells, char nextshell[40], char input[40], int xmax, int ymax)
{
    int count;

    count = ctoi(input, 5, '\0');
    
    if(count == -1)
        strncpy(nextshell, "Could not parse args.\0", 22);
    else
    {
        if(!cells.seed(count))
            strncpy(nextshell, "Too many cells.\0", 16);
        else
            strncpy(nextshell, "Seeded.\0", 8);
    }
}

void help(char nextshell[40])
{
    clear();
    cout <<"step (or s):        run one generation" <<endl;
    cout <<"run (or r) X Y:     run for Y generations with X milliseconds between each" <<endl;
    cout <<"edit (or e):        enter editor and create pattern of size X and Y" <<endl;
    cout <<"display (or d):     display all saved patterns" <<endl;
    cout <<"remove (or rm) X:   remove pattern X" <<endl;
    cout <<"add (or a) X Y Z:   place pattern Z at coordinates (X, Y)" <<endl;
    cout <<"kill (or k):        clean entire board" <<endl;
    cout <<"seed X:             clean board and generate X random cells" <<endl;

    cout <<"ENTER";
    cin.ignore(100, '\n');
    strncpy(nextshell, "~~~Life~~~\0", 11);
}

void clear()
{
    int i;
    
    for(i = 0; i < 100; ++i)
        cout <<endl;
}

int interpret(char input[40])
{
    if(input[0] == '\n')
        return 0;
    else if(strncmp(input, "step", 4) == 0 || strncmp(input, "s\0", 2) == 0)
        return 1;
    else if(strncmp(input, "run", 3) == 0 || strncmp(input, "r ", 2) == 0)
        return 2;
    else if(strncmp(input, "edit", 4) == 0 || strncmp(input, "e ", 2) == 0)
        return 3;
    else if(strncmp(input, "display", 7) == 0 || strncmp(input, "d\0", 2) == 0)
        return 4;
    else if(strncmp(input, "remove", 6) == 0 || strncmp(input, "rm ", 3) == 0)
        return 5;
    else if(strncmp(input, "add", 3) == 0 || strncmp(input, "a ", 2) == 0)
        return 6;
    else if(strncmp(input, "kill", 4) == 0 || strncmp(input, "k\0", 2) == 0)
        return 7;
    else if(strncmp(input, "seed", 4) == 0)
        return 8;
    else if(strncmp(input, "help", 4) == 0 || strncmp(input, "h\0", 2) == 0)
        return 9;
    else if(strncmp(input, "quit", 4) == 0 || strncmp(input, "q\0", 2) == 0)
        return -1;
    else 
        return 0;
}

void printWorld(Cell cells, int xlength, int ylength)
{
    int i, j;

    for(i = 0; i < xlength + 2; ++i)
        cout <<"-";
    cout <<endl;

    for(i = 0; i < ylength; ++i)
    {
        cout <<"|";
        for(j = 0; j < xlength; ++j)
            if(cells.find(j, i))
                cout <<termcolor::on_green <<" " <<termcolor::reset;
            else
                cout <<" ";
        cout <<"|" <<endl;
    }

    for(i = 0; i < xlength + 2; ++i)
        cout <<"-";
    cout <<endl;
}

int ctoi(char input[40], int start, char stop)
{
    int count = 0;
    int ret = 0;
    int i;

    if(input[start] < '0' || input[start] > '9')
        return -1;

    for(i = 0; input[start+i] != stop; ++i)
        ++count;

    for(i = count - 1; i >= 0; --i)
        ret += (input[start+count-i-1] - '0') * pow(10, i);

    return ret;
}

int numlength(int n)
{
    int count = 0;

    do
    {
        ++count;
        n /= 10;
    } while(n);

    return count;
}

int stoc(char input[40], char*& torem, int start, char stop)
{
    int count = 1;
    int i = start;

    while(input[i] != stop)
    {
        ++count;
        ++i;
    }

    if(count == 1)
        return 0;

    torem = new char[count];
    for(i = 0; i < count; ++i)
        torem[i] = input[i + start];

    return count;
}
