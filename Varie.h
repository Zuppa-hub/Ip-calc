#include <stdio.h>
int inputscelta(int mass, int min)//invece di scrivere ad ogni input un controllo questa funzione passadno il valore minimo e massimo lo restituisce appena viene insierito valido
{
    char scelta[1];
    int sceltaI;
    do
    {
        fflush(stdin);
        scanf("%c",&scelta[0]);     //per evitare che vengano inserite lettere e blochino il programma con una variabile int
        sceltaI = scelta[0] - 48;   //converto la stringa in intero 
        //printf("%d\n", sceltaI);
        if (sceltaI > mass || sceltaI < min)
        {
            printf("\nScelta non valida, riprova\n");
        }
    } while (sceltaI < min || sceltaI > mass);
    return sceltaI;
}
int errore(FILE *fp) //funzione per verificvare se un file esiste oppure no
{
    if (access("SottoretiMFissa.txt", F_OK) == 0)
        return 1;
    else
        return 0;
}
int erroreVar(FILE *fp) //funzione per verificvare se un file esiste oppure no
{
    if (access("SottoretiVLSM.txt", F_OK) == 0)
        return 1;
    else
        return 0;
}
void stampa(int *ipbin, FILE *f, int flag)      //stampa gli indirizi 
{
    int i, j;
    if (flag == 1)      //file
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