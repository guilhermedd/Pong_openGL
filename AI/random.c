#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("%d, %d\n", rand(), rand());
    }
    return 0;
}
