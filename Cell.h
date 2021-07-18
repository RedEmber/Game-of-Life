#include <iostream>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <fstream>
using namespace std;

class Cell
{
    public:
        Cell(int, int);
        int seed(int);
        int add(int, int);
        int kill(int, int);
        int find(int, int);
        int populate();
        int getXLen();
        int getYLen();
        int print();
        int destroy();
    private:
        int killR(int, int, struct Unit**);
        int destroyR(struct Unit*);
        int findR(int, int, struct Unit*);
        struct Unit* head;
        int xlength;
        int ylength;
};

struct Unit
{
    int x;
    int y;
    struct Unit* next;
};

class Patterns
{
    public:
        Patterns();
        int add(Cell, char*);
        int addFile(char*);
        int addToCell(Cell&, char*, int, int);
        int rem(char*);
        int display();
        int destroy();
    private:
        int remR(char*, struct Pattern**);
        int destroyR(struct Pattern*);
        struct Pattern* head;
};

struct Pattern
{
    char** grid;
    char* name;
    int xlength;
    int ylength;
    struct Pattern* next;
};
