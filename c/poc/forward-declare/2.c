#include <stdio.h>

typedef struct L * L;


struct L{
    char c;
};



int main(int argc, char const *argv[])
{
    L a;
    struct L c;
    printf("%d %d\n",sizeof(a),sizeof(c));
    return 0;
}


