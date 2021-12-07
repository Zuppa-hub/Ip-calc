#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
void VariabileClasseC(int ipdec[], int ipbin[], int ns, FILE *f);
void VariabileClasseB(int ipdec[], int ipbin[], int ns, FILE *f);
void CreaSottoretiVLSM(int classe, int ipdec[], int ipbin[], int ns)
{
    FILE *f;
    if (classe == 1)
    {
        if (ns >= pow(2, 21) || ns <= 0)
        {
            printf("Impossibile calcolare %d sottoreti con indirizzo %d.%d.%d.%d", ns, ipdec[0], ipdec[1], ipdec[2], ipdec[3]);
        }
        else
        {
            //CreaSottoretiA(ipdec, ipbin, ns, f);
        }
    }
    else
    {
        if (classe == 2)
        {
            if (ns >= pow(2, 14) || ns < 0)
            {
                printf("Impossibile calcolare %d sottoreti con indirizzo %d.%d.%d.%d", ns, ipdec[0], ipdec[1], ipdec[2], ipdec[3]);
            }
            else
            {
                VariabileClasseB(ipdec, ipbin, ns, f);
            }
        }
        else
        {
            if (classe == 3)
            {
                if (ns > pow(2, 6) || ns <= 0)
                {
                    printf("Impossibile calcolare %d sottoreti con indirizzo %d.%d.%d.%d", ns, ipdec[0], ipdec[1], ipdec[2], ipdec[3]);
                }
                else
                {
                    VariabileClasseC(ipdec, ipbin, ns, f);
                }
            }
        }
    }
    if (classe != 1 && classe != 2 && classe != 3)
    {
        printf("\nErrore\n");
        printf("%d\n", classe);
    }
}
void VariabileClasseC(int ipdec[], int ipbin[], int ns, FILE *f)
{
    int *host, *pot;
    int *netID, *broad;
    long dim = ns * sizeof(int);
    host = (int *)malloc(dim);
    pot = (int *)malloc(dim);
    netID = (int *)malloc(dim);
    broad = (int *)malloc(dim);
    int i, j, k;
    int tmp;
    int DC[4];
    int bithost, bitrete;
    int potenza, intervallo, intervalloP = 0;
    int scelta, sceltaf;
    for (i = 0; i < ns; i++)
    {
        printf("Inserisci il numero di Host per la %d sottorete", i + 1);
        scanf("%d", &tmp);
        tmp = tmp + 3;
        *(host + i) = tmp;
    }
    for (i = 0; i < ns; i++)
    {
        for (j = i + 1; j < ns; j++)
        {
            if (*(host + j) > *(host + i))
            {
                tmp = *(host + i);
                *(host + i) = *(host + j);
                *(host + j) = tmp;
            }
        }
    }
    for (i = 0; i < ns; i++)
    {
        j = 0;
        while (*(host + i) > pow(2, j))
            j++;
        *(pot + i) = j;
    }
    printf("Vuoi salvare i risultati su file?\n0=no 1=si`");
    sceltaf = inputscelta(1, 0);
    if (sceltaf == 1)
    {
        if (erroreVar(f) == 0)
        {
            f = fopen("SottoretiVLSM.txt", "w");
            fprintf(f, "Andrea Cazzato 4INA");
            printf("\nFile aperto in scrittura\n");
        }
        else
        {
            f = fopen("SottoretiVLSM.txt", "a");
            printf("\nFile già esistente, scrittura in coda\n");
        }

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(f, "Classe C %d sottoreti a maschera variabile \n", ns);
        fprintf(f, "Sottoreti create in data: \n%d-%02d-%02d orario: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 1, tm.tm_min, tm.tm_sec);
    }
    else
        printf("Non salverò su file.");

    for (i = 0; i < ns; i++)
        printf("\nPotenza per l' host %d = %d", *(host + i), *(pot + i));
    printf("\nOra scelgi come visualizzarle\n");
    printf("1) Decimale\n2) Binario");
    scanf("%d", &scelta);
    if (sceltaf == 1 && scelta == 1)
        fprintf(f, "\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
    else if (sceltaf == 1 && scelta == 2)
        fprintf(f, "\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
    for (i = 0; i < ns; i++)
    {
        bitrete = 8 - *(pot + i);
        potenza = pow(2, bitrete);
        intervallo = 256 / potenza;

        *(netID + i) = intervalloP;
        *(broad + i) = intervallo + intervalloP - 1;
        intervalloP = intervallo + intervalloP;
    }

    switch (scelta)
    {
    case 1:
        printf("\n\tRETE\tNET ID\t\tBROADCAST\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\tNUMERO HOST\n");
        for (k = 0; k < ns; k++)
        {
            printf("\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\n", k + 1, ipdec[0], ipdec[1], ipdec[2], *(netID + k), ipdec[0], ipdec[1], ipdec[2], *(broad + k), ipdec[0], ipdec[1], ipdec[2], *(netID + k) + 1, ipdec[0], ipdec[1], ipdec[2], *(netID + k) + 2, ipdec[0], ipdec[1], ipdec[2], *(broad + k) - 1);
            printf("%d\n", *(broad + k) - *(netID + k) - 2);
            if (sceltaf == 1)
            {
                fprintf(f, "\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d", k + 1, ipdec[0], ipdec[1], ipdec[2], *(netID + k), ipdec[0], ipdec[1], ipdec[2], *(broad + k), ipdec[0], ipdec[1], ipdec[2], *(netID + k) + 1, ipdec[0], ipdec[1], ipdec[2], *(netID + k) + 2, ipdec[0], ipdec[1], ipdec[2], *(broad + k) - 1);
                fprintf(f, "\t%d\n", *(broad + k) - *(netID + k) - 2);
            }
        }
        break;
    case 2:
        DC[0] = ipdec[0];
        DC[1] = ipdec[1];
        DC[2] = ipdec[2];
        printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
        for (i = 0; i < ns; i++)
        {
            printf("%d) ", i + 1);
            if (sceltaf == 1)
                fprintf(f, "%d) ", i + 1);
            DC[3] = *(netID + i);
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            DC[3] = *(broad + i);
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            DC[3] = *(netID + i) + 1;
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            DC[3] = *(netID + i) + 2;
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            DC[3] = *(broad + i) - 1;
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            if (sceltaf == 1)
                fprintf(f, "\n");
            printf("\n");
        }
    }
    if (sceltaf == 1)
        fclose(f);
}
void VariabileClasseB(int ipdec[], int ipbin[], int ns, FILE *f)
{
    int *host, *pot;
    int *netID, *broad;
    int *nHost;
    long dim = ns * sizeof(int);
    host = (int *)malloc(dim);
    pot = (int *)malloc(dim);
    netID = (int *)malloc(dim);
    broad = (int *)malloc(dim);
    nHost = (int *)malloc(dim);
    int i, j, k;
    int tmp;
    int bithost, bitrete;
    int potenza, intervallo[2];
    int inter3ott = 0;
    int inter4ott = 0;

    for (i = 0; i < ns; i++)
    {
        printf("Inserisci il numero di Host per la %d sottorete", i + 1);
        scanf("%d", &tmp);
        tmp = tmp + 3;
        *(host + i) = tmp;
    }
    for (i = 0; i < ns; i++)
    {
        for (j = i + 1; j < ns; j++)
        {
            if (*(host + j) > *(host + i))
            {
                tmp = *(host + i);
                *(host + i) = *(host + j);
                *(host + j) = tmp;
            }
        }
    }
    for (i = 0; i < ns; i++)
    {
        j = 0;
        while (*(host + i) > pow(2, j))
            j++;
        *(pot + i) = j;
    }
    for (i = 0; i < ns; i++)
        printf("\nPotenza per l' host %d = %d", *(host + i), *(pot + i));
    printf("\n\tRETE\tNET ID\t\tBROADCAST\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\tNUMERO HOST");
    //calcolo
    for (k = 0; k < ns; k++)
    {
        if (*(pot + k) >= 8)
        {
            bitrete = 16 - *(pot + k);
            potenza = pow(2, bitrete);
            intervallo[0] = 256 / potenza;

            *(netID + k) = inter3ott;
            *(broad + k) = inter3ott + intervallo[0] - 1;

            *(nHost + k) = ((*(broad + k) + 1 - *(netID + k)) * 256) - 2; //Nel caso net[k] sia 0, diventerebbe -1 e invece di sottrarre sommerebbe. Perciò aumento il broadcast.
            if (*(nHost + k) == -2)
            {
                *(nHost + k) = 253;
            }
            printf("\t%d)", k + 1);
            printf("\t%d.%d.%d.0", ipdec[0], ipdec[1], *(netID + k));
            printf("\t%d.%d.%d.255", ipdec[0], ipdec[1], *(broad + k));
            printf("\t%d.%d.%d.1", ipdec[0], ipdec[1], *(netID + k));
            printf("\t%d.%d.%d.2", ipdec[0], ipdec[1], *(netID + k));
            printf("\t%d.%d.%d.254\n", ipdec[0], ipdec[1], *(broad + k));
        }
        else
        {
            intervallo[0] = 0;
            bitrete = 8 - *(pot + k);
            potenza = pow(2, bitrete);
            intervallo[1] = 256 / potenza;

            *(netID + k) = inter4ott;
            *(broad + k) = inter4ott + intervallo[1] - 1;

            printf("\t%d)", k + 1);
            printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], inter3ott, *(netID + k));
            printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], inter3ott, *(broad + k));
            printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], inter3ott, *(netID + k) + 1);
            printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], *(netID + k) + 2);
            printf("\t%d.%d.%d.%d\n", ipdec[0], ipdec[1], *(broad + k) - 1);
            printf("   %d\n", *(broad + k) - *(netID + k) - 2);
            inter4ott = inter4ott + intervallo[1];
        }
        inter3ott = inter3ott + intervallo[0];
    }
}