//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
void converti(int bin[],int dec[])
{
    int cifra, somma, pot, esp, i, j;       
    i = 0;
    for (j = 0; j < 4; j++)
    {
        esp = 7;
        somma = 0;
        do
        {
            pot = pow(2, esp);
            cifra = bin[i];
            cifra = cifra * pot;
            somma = somma + cifra;
            esp--;
            i++;
        } while (esp >= 0);
        dec[j]=somma;
    }
}