#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
void VariabileClasseC(int ipdec[], int ipbin[], int ns, FILE *f);
void VariabileClasseB(int ipdec[], int ipbin[], int ns, FILE *f);
void VariabileClasseA(int ipdec[], int ipbin[], int ns, FILE *f);
void CreaSottoretiVLSM(int classe, int ipdec[], int ipbin[], int ns)
{
    FILE *f;
    if (classe == 1)
    {
        if (ns >= pow(2, 22) || ns <= 0)
            printf("Impossibile calcolare %d sottoreti con indirizzo %d.%d.%d.%d", ns, ipdec[0], ipdec[1], ipdec[2], ipdec[3]);
        else
            VariabileClasseA(ipdec, ipbin, ns, f);
    }
    else
    {
        if (classe == 2)
        {
            if (ns >= pow(2, 15) || ns < 0)
                printf("Impossibile calcolare %d sottoreti con indirizzo %d.%d.%d.%d", ns, ipdec[0], ipdec[1], ipdec[2], ipdec[3]);
            else
                VariabileClasseB(ipdec, ipbin, ns, f);
        }
        else
        {
            if (classe == 3)
            {
                if (ns > pow(2, 7) || ns <= 0)
                    printf("Impossibile calcolare %d sottoreti con indirizzo %d.%d.%d.%d", ns, ipdec[0], ipdec[1], ipdec[2], ipdec[3]);
                else
                    VariabileClasseC(ipdec, ipbin, ns, f);
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
    int somma = 0;
    for (i = 0; i < ns; i++) //prendo il numero host
    {
        printf("Inserisci il numero di Host per la %d sottorete", i + 1);
        scanf("%d", &tmp);
        tmp = tmp + 3;
        *(host + i) = tmp;           //calcolo numero host effettivo sommando 3
        somma = somma + *(host + i); //sommo tutti gli host per controllare che le sottoreti siano fattibili
    }
    if (somma > 255) //controllo che per la classe c siano fattibili x sottoreti
        printf("Impossibile calcolare le sottoreti, troppi host per la classe C");
    else
    {
        for (i = 0; i < ns; i++) //ordinamento degli host in modo decrescente
        {
            for (j = i + 1; j < ns; j++) //selection sort semplificato
            {
                if (*(host + j) > *(host + i))
                {
                    tmp = *(host + i);
                    *(host + i) = *(host + j);
                    *(host + j) = tmp;
                }
            }
        }
        for (i = 0; i < ns; i++) //assegno la potenza da utilizzare agli host per ogni sottorete
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
            fprintf(f, "Sottoreti create in data: %d-%02d-%02d orario: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 1, tm.tm_min, tm.tm_sec); //file
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
            bitrete = 8 - *(pot + i);  //calcolo i bit da dare alla rete, agendo su un solo ottetto faccio -8
            potenza = pow(2, bitrete); //se i bit alla rete sono 2 avremo potenza = 4, l'intervallo per le sottoreti sarà 64
            intervallo = 256 / potenza;

            *(netID + i) = intervalloP;                  //primo = 0
            *(broad + i) = intervallo + intervalloP - 1; //secondo net -1
            intervalloP = intervallo + intervalloP;
        }
        switch (scelta)
        {
        case 1:
            printf("\n\tRETE\tNET ID\t\tBROADCAST\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\tNUMERO HOST\tSUBNET\nn");
            for (k = 0; k < ns; k++)
            {
                printf("\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d\n", k + 1, ipdec[0], ipdec[1], ipdec[2], *(netID + k), ipdec[0], ipdec[1], ipdec[2], *(broad + k), ipdec[0], ipdec[1], ipdec[2], *(netID + k) + 1, ipdec[0], ipdec[1], ipdec[2], *(netID + k) + 2, ipdec[0], ipdec[1], ipdec[2], *(broad + k) - 1, );
                printf("%d\n", *(broad + k) - *(netID + k) - 2);
                if (sceltaf == 1)
                {
                    fprintf(f, "\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d", k + 1, ipdec[0], ipdec[1], ipdec[2], *(netID + k), ipdec[0], ipdec[1], ipdec[2], *(broad + k), ipdec[0], ipdec[1], ipdec[2], *(netID + k) + 1, ipdec[0], ipdec[1], ipdec[2], *(netID + k) + 2, ipdec[0], ipdec[1], ipdec[2], *(broad + k) - 1);
                    fprintf(f, "\t%d\n", *(broad + k) - *(netID + k) - 2); // host per ogni sottorete
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
}
void VariabileClasseB(int ipdec[], int ipbin[], int ns, FILE *f) // stesso ragionamneto della classe c ma divindendo in due i casi e
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
    int tmp = 0, somma = 0, sceltaf = -1, scelta = -1;
    int bithost = 0, bitrete = 0;
    int potenza, intervallo[2] = {0, 0};
    int inter3ott = 0;
    int inter4ott = 0;
    int Hdisp = 0;
    int DC[4] = {0, 0, 0, 0};
    //come classe c
    for (i = 0; i < ns; i++)
    {
        printf("Inserisci il numero di Host per la %d sottorete", i + 1);
        scanf("%d", &tmp);
        tmp = tmp + 3;
        *(host + i) = tmp;
        somma = somma + *(host + i);
    }
    if (somma > 65536)
        printf("Impossibile calcolare le sottoreti, troppi host per la classe B");
    else
    {
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
            fprintf(f, "Classe B %d sottoreti a maschera variabile \n", ns);
            fprintf(f, "Sottoreti create in data: %d-%02d-%02d orario: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 1, tm.tm_min, tm.tm_sec);
        }
        else
            printf("Non salverò su file.");
        printf("\nOra scelgi come visualizzarle\n");
        printf("1) Decimale\n2) Binario");
        scanf("%d", &scelta);
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
        if (scelta == 1)
        {
            printf("\n\tRETE\tNET ID\t\tBROADCAST\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\tNUMERO HOST\n");
            if (sceltaf == 1)
                fprintf(f, "\n\tRETE\tNET ID\t\tBROADCAST\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\tNUMERO HOST\n");
        }
        else
        {
            printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
            if (sceltaf == 1)
                fprintf(f, "\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
        }
        //calcolo
        DC[0] = ipdec[0];
        DC[1] = ipdec[1];
        for (k = 0; k < ns; k++)
        {
            if (*(pot + k) >= 8)
            {
                inter3ott = inter3ott + intervallo[0];
                bitrete = 16 - *(pot + k);
                potenza = pow(2, bitrete);
                intervallo[0] = 256 / potenza;

                *(netID + k) = inter3ott;
                *(broad + k) = inter3ott + intervallo[0] - 1;

                *(nHost + k) = ((*(broad + k) + 1 - *(netID + k)) * 256) - 2; //Nel caso net[k] sia 0, diventerebbe -1 e invece di sottrarre sommerebbe. Perciò aumento il broadcast.
                if (*(nHost + k) == -2)
                    *(nHost + k) = 253;
                if (scelta == 1)
                {
                    printf("\t%d)\t%d.%d.%d.0\t%d.%d.%d.255\t%d.%d.%d.1\t%d.%d.%d.2\t%d.%d.%d.254\t", k + 1, ipdec[0], ipdec[1], *(netID + k), ipdec[0], ipdec[1], *(broad + k), ipdec[0], ipdec[1], *(netID + k), ipdec[0], ipdec[1], *(netID + k), ipdec[0], ipdec[1], *(broad + k));
                    printf("%d\n", (intervallo[0] * 256) - 3); //host disponibili per ogni sottorete
                    if (sceltaf == 1)
                    {
                        fprintf(f, "\t%d)\t%d.%d.%d.0\t%d.%d.%d.255\t%d.%d.%d.1\t%d.%d.%d.2\t%d.%d.%d.254\t", k + 1, ipdec[0], ipdec[1], *(netID + k), ipdec[0], ipdec[1], *(broad + k), ipdec[0], ipdec[1], *(netID + k), ipdec[0], ipdec[1], *(netID + k), ipdec[0], ipdec[1], *(broad + k));
                        fprintf(f, "%d\n", (intervallo[0] * 256) - 3);
                    }
                }
                else
                {
                    printf("\t%d)", k + 1);
                    if (sceltaf == 1)
                        fprintf(f, "%d) ", i + 1);
                    DC[2] = *(netID + k);
                    DC[3] = 0;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[2] = *(broad + k);
                    DC[3] = 255;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[2] = *(netID + k);
                    DC[3] = 1;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[2] = *(netID + k);
                    DC[3] = 2;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[2] = *(broad + k);
                    DC[3] = 254;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    if (sceltaf == 1)
                        fprintf(f, "\n");
                    printf("\n");
                }
            }
            else
            {
                inter3ott = inter3ott + intervallo[0];
                intervallo[0] = 0;
                bitrete = 8 - *(pot + k);
                potenza = pow(2, bitrete);
                intervallo[1] = 256 / potenza;

                *(netID + k) = inter4ott;
                *(broad + k) = inter4ott + intervallo[1] - 1;
                if (scelta == 1)
                {
                    printf("\n\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d", k + 1, ipdec[0], ipdec[1], inter3ott, *(netID + k), ipdec[0], ipdec[1], inter3ott, *(broad + k), ipdec[0], ipdec[1], inter3ott, *(netID + k) + 1, ipdec[0], ipdec[1], inter3ott, *(netID + k) + 2, ipdec[0], ipdec[1], inter3ott, *(broad + k) - 1, *(broad + k) - *(netID + k) - 2);
                    if (sceltaf == 1)
                        fprintf(f, "\n\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d", k + 1, ipdec[0], ipdec[1], inter3ott, *(netID + k), ipdec[0], ipdec[1], inter3ott, *(broad + k), ipdec[0], ipdec[1], inter3ott, *(netID + k) + 1, ipdec[0], ipdec[1], inter3ott, *(netID + k) + 2, ipdec[0], ipdec[1], inter3ott, *(broad + k) - 1, *(broad + k) - *(netID + k) - 2);
                }
                else
                {
                    printf("\t%d)", k + 1);
                    if (sceltaf == 1)
                        fprintf(f, "%d) ", i + 1);
                    DC[2] = inter3ott;
                    DC[3] = *(netID + k);
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[2] = inter3ott;
                    DC[3] = *(broad + k);
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[2] = inter3ott;
                    DC[3] = *(netID + k) + 1;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[2] = inter3ott;
                    DC[3] = *(netID + k) + 2;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[2] = inter3ott;
                    DC[3] = *(broad + k) - 1;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    if (sceltaf == 1)
                        fprintf(f, "\n");
                    printf("\n");
                }
                inter4ott = inter4ott + intervallo[1];
            }
            if (inter4ott > 255)
            {
                inter4ott = 0;
                inter3ott++;
            }
        }
        if (sceltaf == 1)
            fclose(f);
    }
}
void VariabileClasseA(int ipdec[], int ipbin[], int ns, FILE *f)
{
    fflush(stdin);
    fflush(stdout);
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
    int tmp = 0, somma = 0, sceltaf = -1, scelta = -1;
    int bithost = 0, bitrete = 0;
    int potenza, intervallo[3] = {0, 0, 0};
    int inter3ott = 0;
    int inter4ott = 0;
    int inter2ott = 0;
    int Hdisp = 0;
    int DC[4] = {0, 0, 0, 0};
    for (i = 0; i < ns; i++)
    {
        printf("Inserisci il numero di Host per la %d sottorete", i + 1);
        scanf("%d", &tmp);
        tmp = tmp + 3;
        *(host + i) = tmp;
        somma = somma + *(host + i);
    }
    if (somma > pow(2, 24) - 2)
        printf("Impossibile calcolare le sottoreti, troppi host per la classe A");
    else
    {
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
            fprintf(f, "Classe A %d sottoreti a maschera variabile \n", ns);
            fprintf(f, "Sottoreti create in data: \n%d-%02d-%02d orario: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 1, tm.tm_min, tm.tm_sec);
        }
        else
            printf("Non salverò su file.");
        printf("\nOra scelgi come visualizzarle\n");
        printf("1) Decimale\n2) Binario");
        scanf("%d", &scelta);
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
        //calcolo da fare
        printf("\n\nNet ID\t\tBroadcast\tGateway\t\tRange\t\t\t\t   N.Host\n");

        for (k = 0; k < ns; k++)
        {
            if (*(pot + k) >= 16)
            {
                //2 ottetto
                DC[0] = ipdec[0];
                inter2ott = inter2ott + intervallo[2];
                bitrete = 24 - *(pot + k);
                potenza = pow(2, bitrete);
                intervallo[2] = 256 / potenza;

                *(netID + k) = inter2ott;
                *(broad + k) = inter2ott + intervallo[2] - 1;
                Hdisp = (intervallo[2] * 256 * 256) - 3;

                if (scelta == 1)
                {
                    printf("\n\t%d)\t%d.%d.0.0\t%d.%d.255.255\t%d.%d.0.1\t%d.%d.0.2\t%d.%d.255.254\t%d", k + 1, ipdec[0], *(netID + k), ipdec[0], *(broad + k), ipdec[0], *(netID + k), ipdec[0], *(netID + k) + 2, ipdec[0], *(broad + k) - 1, Hdisp);
                    if (sceltaf == 1)
                    {
                        fprintf(f, "\n\t%d)\t%d.%d.0.0\t%d.%d.255.255\t%d.%d.0.1\t%d.%d.0.2\t%d.%d.255.254\t%d", k + 1, ipdec[0], *(netID + k), ipdec[0], *(broad + k), ipdec[0], *(netID + k), ipdec[0], *(netID + k) + 2, ipdec[0], *(broad + k) - 1, Hdisp);
                    }
                }
                else
                {
                    printf("\t%d)", k + 1);
                    if (sceltaf == 1)
                        fprintf(f, "%d) ", i + 1);
                    DC[1] = *(netID + k);
                    DC[2] = 0;
                    DC[3] = 0;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[1] = *(broad + k);
                    DC[2] = 255;
                    DC[3] = 255;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[1] = *(netID + k);
                    DC[2] = 0;
                    DC[3] = 1;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[1] = *(netID + k);
                    DC[2] = 0;
                    DC[3] = 1;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[1] = *(broad + k);
                    DC[2] = 255;
                    DC[3] = 254;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    if (sceltaf == 1)
                        fprintf(f, "\n");
                    printf("\n");
                }
            }
            else
            {
                inter2ott = inter2ott + intervallo[2];
                intervallo[2] = 0;
                if (*(pot + k) >= 8)
                {
                    //3o ottetto
                    inter3ott = inter3ott + intervallo[0];

                    if (inter3ott > 255)
                    {
                        inter3ott = 0;
                        inter2ott++;
                    }

                    bitrete = 16 - *(pot + k);
                    potenza = pow(2, bitrete);
                    intervallo[0] = 256 / potenza;

                    *(netID + k) = inter3ott;
                    *(broad + k) = inter3ott + intervallo[0] - 1;
                    Hdisp = (intervallo[0] * 256) - 3;

                    if (scelta == 1)
                    {
                        printf("\n\t%d)\t%d.%d.%d.0\t%d.%d.%d.255\t%d.%d.%d.1\t%d.%d.%d.2\t%d.%d.%d.254\t%d", k + 1, ipdec[0], inter2ott, *(netID + k), ipdec[0], inter2ott, *(broad + k), ipdec[0], inter2ott, *(netID + k), ipdec[0], inter2ott, *(netID + k), ipdec[0], inter2ott, *(broad + k), Hdisp);
                        if (sceltaf == 1)
                            fprintf(f, "\n\t%d)\t%d.%d.%d.0\t%d.%d.%d.255\t%d.%d.%d.1\t%d.%d.%d.2\t%d.%d.%d.254\t%d", k + 1, ipdec[0], inter2ott, *(netID + k), ipdec[0], inter2ott, *(broad + k), ipdec[0], inter2ott, *(netID + k), ipdec[0], inter2ott, *(netID + k), ipdec[0], inter2ott, *(broad + k), Hdisp);
                    }
                    else
                    {
                        printf("\t%d)", k + 1);
                        if (sceltaf == 1)
                            fprintf(f, "%d) ", i + 1);
                        DC[1] = inter2ott;
                        DC[2] = *(netID + k);
                        DC[3] = 0;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[1] = inter2ott;
                        DC[2] = *(broad + k);
                        DC[3] = 255;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[1] = inter2ott;
                        DC[2] = *(netID + k);
                        DC[3] = 1;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[1] = inter2ott;
                        DC[2] = *(netID + k);
                        DC[3] = 2;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[1] = inter2ott;
                        DC[2] = *(broad + k);
                        DC[3] = 254;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        if (sceltaf == 1)
                            fprintf(f, "\n");
                        printf("\n");
                    }
                }
                else
                {
                    //4o ottetto
                    inter3ott = inter3ott + intervallo[0];
                    intervallo[0] = 0;

                    if (inter3ott > 255)
                    {
                        inter3ott = 0;
                        inter2ott++;
                    }

                    bitrete = 8 - *(pot + k);
                    potenza = pow(2, bitrete);
                    intervallo[1] = 256 / potenza;

                    *(netID + k) = inter4ott;
                    *(broad + k) = inter4ott + intervallo[1] - 1;
                    if (scelta == 1)
                    {
                        printf("\n\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d", k + 1, ipdec[0], inter2ott, inter3ott, *(netID + k), ipdec[0], inter2ott, inter3ott, *(broad + k), ipdec[0], inter2ott, inter3ott, *(netID + k) + 1, ipdec[0], inter2ott, inter3ott, *(netID + k) + 2, ipdec[0], inter2ott, inter3ott, *(broad + k) - 1, intervallo[1] - 3);
                        if (sceltaf == 1)
                            fprintf(f, "\n\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d", k + 1, ipdec[0], inter2ott, inter3ott, *(netID + k), ipdec[0], inter2ott, inter3ott, *(broad + k), ipdec[0], inter2ott, inter3ott, *(netID + k) + 1, ipdec[0], inter2ott, inter3ott, *(netID + k) + 2, ipdec[0], inter2ott, inter3ott, *(broad + k) - 1, intervallo[1] - 3);
                    }
                    else
                    {
                        printf("\t%d)", k + 1);
                        if (sceltaf == 1)
                            fprintf(f, "%d) ", i + 1);
                        DC[1] = inter2ott;
                        DC[2] = inter3ott;
                        DC[3] = *(netID + k);
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[1] = inter2ott;
                        DC[2] = inter3ott;
                        DC[3] = *(broad + k);
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[1] = inter2ott;
                        DC[2] = inter3ott;
                        DC[3] = *(netID + k) + 1;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[1] = inter2ott;
                        DC[2] = inter3ott;
                        DC[3] = *(netID + k) + 2;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[1] = inter2ott;
                        DC[2] = inter3ott;
                        DC[3] = *(broad + k) - 1;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        if (sceltaf == 1)
                            fprintf(f, "\n");
                        printf("\n");
                    }
                    inter4ott = inter4ott + intervallo[1];
                }
                if (inter4ott > 255)
                {
                    inter4ott = 0;
                    inter3ott++;
                }
                if (inter3ott > 255)
                {
                    inter3ott = 0;
                    inter2ott++;
                }
            }
        }
    }
    if (sceltaf == 1)
        fclose(f);
}
