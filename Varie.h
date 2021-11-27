#include <stdio.h>
int inputscelta(int mass, int min)
{
    int scelta;
    do
    {
        scanf("%d", &scelta);
        if (scelta > mass || scelta < min)
        {
            printf("\nScelta non valida\n");
        }
    } while (scelta < min || scelta > mass);
    return scelta;
}