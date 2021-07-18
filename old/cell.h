struct Cell
{
    int x;
    int y;
    struct Cell* next;
    int (*seed)(int count, int tablex, int tabley);
    int (*add)(int x, int y);
    int (*kill)(int x, int y);
    int (*find)(int x, int y);
    int (*print)();
    int (*destroy)();
};

int seed(int, int, int);
int add(int, int);
int kill(int, int);
int find(int, int);
int print();
int destroy();
void addMethods(struct Cell*);
