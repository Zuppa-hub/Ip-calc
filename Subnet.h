int sm[32], smD[4];
int i;
void subnet(int bit, int sceltaf, FILE *f)
{

    for (i = bit; i < 32; i++)
        sm[i] = 0;
    for (i = 0; i < bit; i++)
    {
        sm[i] = 1;
    }
    printf("\nSubnet mask in decimale = ");
    converti(sm, smD);
    printf("\n");
    for (i = 0; i < 3; i++)
        printf("%d.", smD[i]);
    printf("%d", smD[3]);
    printf("\nSubnet mask CIDR = /%d", bit);
    if (sceltaf == 1)
    {
        if (errore(f) == 1)
        {
            f = fopen("SottoretiMFissa.txt", "a");
            fprintf(f, "\n");
            for (i = 0; i < 3; i++)
                fprintf(f, "%d.", smD[i]);
            fprintf(f, "%d", smD[3]);
            fprintf(f, "\nSubnet mask CIDR = /%d", bit);
            fclose(f);
        }
        else
        {
            printf("Errore nella scrittura della subnet nel file");
        }
    }
}
int subvar(int bit, int sceltaf, FILE *f)
{
    for (i = bit; i < 32; i++)
        sm[i] = 0;
    for (i = 0; i < bit; i++)
        sm[i] = 1;
    converti(sm, smD);
    for (i = 0; i < 3; i++)
        printf("%d.", smD[i]);
    printf("%d", smD[3]);
    if (sceltaf == 1)
    {
        if (erroreVar(f) == 1)
        {
            f = fopen("SottoretiVLSM.txt", "a");
            fprintf(f, "\n");
            for (i = 0; i < 3; i++)
                fprintf(f, "%d.", smD[i]);
            fprintf(f, "%d", smD[3]);
            //fprintf(f, "\nSubnet mask CIDR = /%d", bit);
            fclose(f);
        }
        else
        {
            printf("Errore nella scrittura della subnet nel file");
        }
    }
}