//#include <stdio.h>
#include "BintoDEC.h"
void input(int dec[], int bin[], int flag)
{
    int i;
    if (flag == 0)
    {
        for (i = 0; i < 4; i++)
        {
            do
            {
                printf("Inserisci la %d cifra dell'indirizzo ip in decimale: ", i + 1);
                scanf("%d", &dec[i]);
                if (dec[i] < 0 || dec[i] > 255)
                {
                    printf("La cifra %d non è contenuta tra 0 e 255, reinseriscila", dec[i]);
                }

            } while (dec[i] < 0 || dec[i] > 255);
        }
    }
    else
    {
        if (flag == 1)
        {
            for (i = 0; i < 32; i++)
            {
                do
                {
                    printf("Inserisci la %d cifra dell'indirizzo ip in binario: ", i + 1);
                    scanf("%d", &bin[i]);
                    if (bin[i] < 0 || bin[i] > 1)
                    {
                        printf("La cifra %d non è binaria, reinseriscila", bin[i]);
                    }
                    if (i == 7 || i == 15 || i == 23)
                    {
                        printf("\nOttetto inserito\n");
                    }
                } while (bin[i] < 0 || bin[i] > 1);
            }
            converti(bin, dec);
        }
        else
        {
            if (flag == 2)
            {
                for (i = 0; i < 4; i++)
                {
                    do
                    {
                        printf("Inserisci la %d cifra della subnet in decimale: ", i + 1);
                        scanf("%d", &dec[i]);
                        if (dec[i] < 0 || dec[i] > 255)
                        {
                            printf("La cifra %d non è contenuta tra 0 e 255, reinseriscila", dec[i]);
                        }
                    } while (dec[i] < 0 || dec[i] > 255);
                }
            }
            else
            {
                if (flag == 3)
                {
                    for (i = 0; i < 32; i++)
                    {
                        do
                        {
                            printf("Inserisci la %d cifra della subnet in binario: ", i + 1);
                            scanf("%d", &bin[i]);
                            if (bin[i] < 0 || bin[i] > 1)
                            {
                                printf("La cifra %d non è contenuta tra 0 e 1, reinseriscila", bin[i]);
                            }
                            if (i == 7 || i == 15 || i == 23)
                            {
                                printf("\nottetto inserito\n");
                            }
                        } while (bin[i] < 0 || bin[i] > 1);
                    }
                    converti(bin, dec);
                }
            }
        }
    }
}
