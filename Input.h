//#include <stdio.h>
#include "BintoDEC.h"
int input(int dec[], int bin[], int flag)
{
    int i, j, k;
    if (flag == 0)
    {
        char decimale[16];
        char decAppoggio[4];
        int moltiplica = 100;
        int m = 1;
        int somma;
        fflush(stdin);
        fgets(decimale, 15, stdin);
        decimale[strlen(decimale) - 1] = 46;
        i = 0;
        k = 0;
        for (j = 0; j < 4; j++)
        {
            somma = 0;
            while (decimale[i] != 46)
            {
                m = m * 10;
                i++;
            };
            m = m / 10;
            do
            {
                somma = somma + (decimale[k] - 48) * m;
                m = m / 10;
                k++;
            } while (k < i);
            k++;
            dec[j] = somma;
            m = 1;
            i++;
        }
    }
    else
    {
        if (flag == 1)
        {
            char binario[35];
            fflush(stdin);
            fgets(binario, 35, stdin);
            for (j = 0; j < 35; j++)
            {
                bin[j] = binario[j] - 48;
                if (j == 8 || j == 17 || j == 26)
                    j++;
            }
            converti(bin, dec);
            free(bin);
        }
    }
    system("cls");
    printf("Controllo che l'indirizzo sia valido\n\n");
    j = 0;
    for (i = 0; i < 4; i++)
        if (dec[i] >= 0 && dec[i] <= 255)
            j++;
    if (j != i)
    {
        char passa[1];
        printf("Indirizzo non valido\nPremere un tasto per continuare");
        fgets(passa,1,stdin);
        system("cls");
        return -1;
    }
    printf("Indirizzo valido\n");
    sleep(1);
    system("cls");
    return 0;
}
