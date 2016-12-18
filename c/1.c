#include <stdio.h>
#include <string.h>

char a1[10005],a2[10005];

int main(int argc, char const *argv[]) {

    scanf("%s\n",a1);
    // gets(a1);
    // gets(a2);
    scanf("%s\n",a2);
    printf("%s\n%s\n",a1,a2);
    // char * t1 = a1, * t2 = a2;
    int l1 = strlen(a1),l2 = strlen(a2);


    int ttt ;
    int eq = 1;
    for (int i = 0; i < l1; i++) {
        ttt = i;
        eq = 1;
        for (int j = 0; j < l2; j++)
        {

            if(a1[ttt] != a2[j] || ttt >=l1)
            {
                eq = 0;
                break;
            }

            ++ ttt;
            // ++ j;
        }

        if(eq)
        {
            printf("%d",i);
        }
    }

    printf("\n");

    return 0;
}
