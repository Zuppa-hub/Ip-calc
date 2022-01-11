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
int errore(FILE *fp) //funzione per verificvare se un file esiste oppure no
{
    if (fopen("SottoretiMFissa.txt", "r") == NULL)
    {
        printf("\nFile vuoto o non esistente");
        return 0;
    }
    return 1;
}
int erroreVar(FILE *fp) //funzione per verificvare se un file esiste oppure no
{
    if (fopen("SottoretiVLSM.txt", "r") == NULL)
    {
        printf("\nFile vuoto o non esistente");
        fclose(fp);
        return 0;
    }
    else
        fclose(fp);
    return 1;
}
void stampa(int *ipbin, FILE *f, int flag)
{
    int i, j;
    if (flag == 1)
    {
        for (j = 0; j < 32; j++)
        {
            fprintf(f, "%d", ipbin[j]);
            printf("%d", ipbin[j]);
            if (j == 7 || j == 15 || j == 23)
            {
                printf(".");
                fprintf(f, ".");
            }
        }
        fprintf(f, "  ");
        printf("  ");
    }
    else
    {
        for (j = 0; j < 32; j++)
        {
            printf("%d", ipbin[j]);
            if (j == 7 || j == 15 || j == 23)
                printf(".");
        }
        printf("  ");
    }
}