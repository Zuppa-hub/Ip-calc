void supernet(int ipdec[], int ipbin[], int sottoreti)
{
    int broad;
    int host;
    int dec[4];
    int somma = 0;
    int i = 0;
    int es;
    int giri3ott;
    int subnetV;        //V = variabile non funzione
    int supermask;
    int sub3ott = 0;
    int bitwise;
    int classe;
    FILE *f;
    printf("Inserisci il numero di host");
    scanf("%d", &host);
    while (host >= somma)
    {
        somma = somma + 256;
        i++;
    };
    //printf("\nmi = %d\n", i);
    es = log2(i);
    giri3ott = i;
    i = 0;
    subnetV = 24 - es;
    //printf("\nsupernet mask CIDR= \\%d\n", subnet);
    if (subnetV < 8)
        classe = 1; // a
    else if (subnetV > 8 && subnetV < 16)
        classe = 2; // b
    else if (subnetV > 16)
        classe = 3; // c
    //printf("\nes = %d\n", es);
    for (i = 7; i >= es; i--)
        sub3ott = sub3ott + pow(2, i);
    //printf("\nsub3ott = %d\n", sub3ott);
    bitwise = ipdec[2] & sub3ott;
    //printf("\n&& = %d\n", bitwise);
    broad = pow(2, es) - 1;
    broad = broad + bitwise;
    i = 0;
    printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
    printf("\t%d\t%d.%d.%d.0\t\t%d.%d.%d.255", i, ipdec[0], ipdec[1], bitwise, ipdec[0], ipdec[1], broad); // net e broad
    printf("\t\t%d.%d.%d.1",ipdec[0], ipdec[1],bitwise);
    printf("\t\t%d.%d.%d.254\n",ipdec[0], ipdec[1],broad);
    subnet(subnetV,0,f);
}
