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
    if (fopen("SottoretiMFissa.txt","r") == NULL)
    {
        printf("\nFile vuoto o non esistente");
        fclose(fp);
        return 0;
    }
    else
        fclose(fp);
    return 1;
}