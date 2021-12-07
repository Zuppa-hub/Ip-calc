#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int CreaSottoretiA(int ipdec[], int ipbin[], int ns, FILE *f);
int CreaSottoretiB(int ipdec[], int ipbin[], int ns, FILE *f);
void CreaSottoretiC(int ipdec[], int ipbin[], int ns, FILE *f);
void subnet(int bit, int sceltaf, FILE *f);

void CreaSottoreti(int classe, int ipdec[], int ipbin[], int ns)
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
            CreaSottoretiA(ipdec, ipbin, ns, f);
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
                CreaSottoretiB(ipdec, ipbin, ns, f);
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
                    CreaSottoretiC(ipdec, ipbin, ns, f);
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
void CreaSottoretiC(int ipdec[], int ipbin[], int ns, FILE *f)
{
    //decTobin(ipdec,ipbin);
    //massimo 64
    int *br, *nid;
    int pot = 0, i = 0, j;
    while (ns >= pow(2, i))
        i++;
    int BitRete = i;
    pot = pow(2, i);
    pot = 256 / pot;
    long dim = pot * sizeof(int);
    br = (int *)malloc(dim);
    nid = (int *)malloc(dim);
    int nidTMP = 0, brTMP = 0;
    int DC[4];
    int scelta, sceltaf;
    printf("Vuoi salvare i risultati su file?\n0=no 1=si`");
    sceltaf = inputscelta(1, 0);
    if (sceltaf == 1)
    {
        if (errore(f) == 0)
        {
            f = fopen("SottoretiMFissa.txt", "w");
            fprintf(f, "Andrea Cazzato 4INA");
            printf("\nFile aperto in scrittura\n");
        }
        else
        {
            f = fopen("SottoretiMFissa.txt", "a");
            printf("\nFile già esistente, scrittura in coda\n");
        }

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(f, "Classe c %d sottoreti\n", ns);
        fprintf(f, "Sottoreti create in data: %d-%02d-%02d orario: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 1, tm.tm_min, tm.tm_sec);
    }
    else
        printf("Non salverò su file.");

    for (int i = 0; i < ns; i++)
    {
        *(nid + i) = nidTMP;
        *(br + i) = nidTMP + pot - 1;
        nidTMP = nidTMP + pot; //intervallo = pot
    }
    printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
    printf("1) Decimale\n2) Binario");
    scanf("%d", &scelta);
    switch (scelta)
    {
    case 1:
        printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
        if (sceltaf == 1)
            fprintf(f, "\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
        for (i = 0; i < ns; i++)
        {
            printf("\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\n", i + 1, ipdec[0], ipdec[1], ipdec[2], *(nid + i), ipdec[0], ipdec[1], ipdec[2], *(br + i), ipdec[0], ipdec[1], ipdec[2], *(nid + i) + 1, ipdec[0], ipdec[1], ipdec[2], *(nid + i) + 2, ipdec[0], ipdec[1], ipdec[2], *(br + i) - 1);
            if (sceltaf == 1)
                fprintf(f, "\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\n", i + 1, ipdec[0], ipdec[1], ipdec[2], *(nid + i), ipdec[0], ipdec[1], ipdec[2], *(br + i), ipdec[0], ipdec[1], ipdec[2], *(nid + i) + 1, ipdec[0], ipdec[1], ipdec[2], *(nid + i) + 2, ipdec[0], ipdec[1], ipdec[2], *(br + i) - 1);
        }
        if (sceltaf == 1)
        {
            fprintf(f, "\nNumero host per ogni sottorete = %d", pot - 3);
            fclose(f);
        }
        subnet(BitRete + 24, sceltaf, f);
        printf("\nNumero host per ogni sottorete = %d", pot - 3);
        break;
    case 2:
        printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
        if (sceltaf == 1)
            fprintf(f, "\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
        DC[0] = ipdec[0];
        DC[1] = ipdec[1];
        DC[2] = ipdec[2];
        for (i = 0; i < ns; i++)
        {
            printf("%d) ", i + 1);
            if (sceltaf == 1)
                fprintf(f, "%d) ", i + 1);
            DC[3] = *(nid + i);
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            DC[3] = *(br + i);
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            DC[3] = *(nid + i) + 1;
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            DC[3] = *(nid + i) + 2;
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            DC[3] = *(br + i) - 1;
            decTobin(DC, ipbin);
            stampa(ipbin, f, sceltaf);
            if (sceltaf == 1)
                fprintf(f, "\n");
            printf("\n");
        }
        subnet(BitRete + 24, sceltaf, f);
        printf("\nNumero host per ogni sottorete = %d", pot - 3);
        if (sceltaf == 1)
            fclose(f);
        break;
    }
}
int CreaSottoretiA(int ipdec[], int ipbin[], int ns, FILE *f)
{
    int i = 0, j = 0, k = 0, cont = 0;
    int bit;
    int pot, intervallo;
    int ott2, ott3;
    int temp;
    int nidTMP = 0;
    int DC[4];
    int *br, *nid;
    int scelta, sceltaf;
    printf("Vuoi salvare i risultati su file?\n0=no 1=si`");
    sceltaf = inputscelta(1, 0);
    if (sceltaf == 1)
    {
        if (errore(f) == 0)
        {
            f = fopen("SottoretiMFissa.txt", "w");
            fprintf(f, "Andrea Cazzato 4INA");
            printf("\nFile aperto in scrittura\n");
        }
        else
        {
            f = fopen("SottoretiMFissa.txt", "a");
            printf("\nFile già esistente, scrittura in coda\n");
        }
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(f, "Classe A %d sottoreti\n", ns);
        fprintf(f, "Sottoreti create in data: \n%d-%02d-%02d orario: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 1, tm.tm_min, tm.tm_sec);
    }
    else
        printf("Non salverò su file.");

    while (pow(2, i) <= ns)
        i++;
    bit = i;
    pot = pow(2, i);

    if (bit <= 8)
    {

        pot = pow(2, i);
        long dim = pot * sizeof(int);
        br = (int *)malloc(dim);
        nid = (int *)malloc(dim);
        intervallo = 256 / pot;
        nidTMP = 0;
        for (i = 0; i < ns; i++)
        {
            *(nid + i) = nidTMP;
            *(br + i) = nidTMP + intervallo - 1;
            nidTMP = nidTMP + intervallo;
        }
        printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
        printf("1) Decimale\n2) Binario");

        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
            if (sceltaf == 1)
                fprintf(f, "\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
            for (i = 0; i < ns; i++)
            {
                printf("\t%d) ", i + 1);
                printf("\t%d.%d.0.0", ipdec[0], *(nid + i));
                printf("\t%d.%d.255.255", ipdec[0], *(br + i));
                printf("\t%d.%d.0.1", ipdec[0], *(nid + i));
                printf("\t%d.%d.0.2", ipdec[0], *(nid + i));
                printf("\t%d.%d.255.254\n", ipdec[0], *(br + i));
                if (sceltaf == 1)
                    fprintf(f, "\t%d) \t%d.%d.0.0\t%d.%d.0.1\t%d.%d.0.1\t%d.%d.0.2\t%d.%d.255.254\n", i + 1, ipdec[0], *(nid + i), ipdec[0], *(br + i), ipdec[0], *(nid + i), ipdec[0], *(nid + i), ipdec[0], *(br + i));
            }
            if (sceltaf == 1)
                fclose(f);
            subnet(bit + 8, sceltaf, f);
            break;
        case 2:
            printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
            DC[0] = ipdec[0];
            if (sceltaf == 1)
                fprintf(f, "\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
            for (i = 0; i < ns; i++)
            {
                printf("%d) ", i + 1);
                if (sceltaf == 1)
                    fprintf(f, "%d) ", i + 1);
                DC[1] = *(nid + i);
                DC[2] = 0;
                DC[3] = 0;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                DC[1] = *(br + i);
                DC[2] = 255;
                DC[3] = 255;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                DC[1] = *(nid + i);
                DC[2] = 0;
                DC[3] = 1;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                DC[1] = *(nid + i);
                DC[2] = 0;
                DC[3] = 2;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                DC[1] = *(br + i);
                DC[2] = 255;
                DC[3] = 254;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                if (sceltaf == 1)
                    fprintf(f, "\n");
                printf("\n");
            }
            if (sceltaf == 1)
                fclose(f);
            subnet(bit + 8, sceltaf, f);
            break;
        }
    }
    else
    {
        if (bit <= 16)
        {
            ott3 = bit - 8;
            pot = pow(2, ott3);
            long dim = pot * sizeof(int);
            br = (int *)malloc(dim);
            nid = (int *)malloc(dim);
            intervallo = 256 / pot;
            printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
            printf("1) Decimale\n2) Binario");
            int scelta;
            scanf("%d", &scelta);
            switch (scelta)
            {
            case 1:
                printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
                if (sceltaf == 1)
                    if (sceltaf == 1)
                        fprintf(f, "\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
                for (j = 0; j < ns / pot; j++)
                {
                    nidTMP = 0;
                    for (i = 0; i < pot; i++)
                    {
                        *(nid + i) = nidTMP;
                        *(br + i) = nidTMP + intervallo - 1;
                        nidTMP = nidTMP + intervallo;
                        cont++;
                        printf("\t%d)", cont);
                        printf("\t%d.%d.%d.0", ipdec[0], j, *(nid + i));
                        printf("\t%d.%d.%d.255", ipdec[0], j, *(br + i));
                        printf("\t%d.%d.%d.1", ipdec[0], j, *(nid + i));
                        printf("\t%d.%d.%d.2", ipdec[0], j, *(nid + i));
                        printf("\t%d.%d.%d.254\n", ipdec[0], j, *(br + i));
                        if (sceltaf == 1)
                            fprintf(f, "\t%d)\t%d.%d.%d.0\t%d.%d.%d.255\t%d.%d.%d.1\t%d.%d.%d.2\t%d.%d.%d.254\n", cont, ipdec[0], j, *(nid + i), ipdec[0], j, *(br + i), ipdec[0], j, *(nid + i), ipdec[0], j, *(nid + i), ipdec[0], j, *(br + i));
                        if (cont == ns)
                        {
                            if (sceltaf == 1)
                                fclose(f);
                            subnet(bit + 8, sceltaf, f);
                            return 0;
                        }
                    }
                }
                break;
            case 2:
                printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
                DC[0] = ipdec[0];
                if (sceltaf == 1)
                    fprintf(f, "\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
                for (j = 0; j < ns / pot; j++)
                {
                    DC[1] = j;
                    nidTMP = 0;
                    for (i = 0; i < pot; i++)
                    {
                        *(nid + i) = nidTMP;
                        *(br + i) = nidTMP + intervallo - 1;
                        nidTMP = nidTMP + intervallo;
                        cont++;
                        printf("\t%d)", cont);
                        if (sceltaf == 1)
                            fprintf(f, "\t%d)", cont);
                        DC[2] = *(nid + i);
                        DC[3] = 0;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[2] = *(br + i);
                        DC[3] = 255;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[2] = *(nid + i);
                        DC[3] = 1;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[3] = 2;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        DC[2] = *(br + i);
                        DC[3] = 254;
                        decTobin(DC, ipbin);
                        stampa(ipbin, f, sceltaf);
                        printf("\n");
                        if (sceltaf == 1)
                            fprintf(f, "\n");
                        if (cont == ns)
                        {
                            if (sceltaf == 1)
                                fclose(f);
                            subnet(bit + 8, sceltaf, f);
                            return 0;
                        }
                    }
                }
                break;
            }
        }
        else
        {
            ott2 = bit - 16;
            pot = pow(2, ott2);
            long dim = pot * sizeof(int);
            br = (int *)malloc(dim);
            nid = (int *)malloc(dim);
            intervallo = 256 / pot;
            k = 0;
            printf("\nOra scelgi come visualizzarle\n");
            printf("1) Decimale\n2) Binario");
            int scelta;
            scanf("%d", &scelta);
            switch (scelta)
            {
            case 1:
                cont = 0;
                printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
                if (sceltaf == 1)
                    fprintf(f, "\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
                while (k <= ((ns / 256) / pot))
                {
                    for (j = 0; j < 256; j++)
                    {
                        nidTMP = 0;
                        for (i = 0; i < pot; i++)
                        {
                            *(nid + i) = nidTMP;
                            *(br + i) = nidTMP + intervallo - 1;
                            nidTMP = nidTMP + intervallo;
                            printf("\t%d)", cont);
                            printf("\t%d.%d.%d.%d", ipdec[0], k, j, *(nid + i));
                            printf("\t\t%d.%d.%d.%d", ipdec[0], k, j, *(br + i));
                            printf("\t%d.%d.%d.%d", ipdec[0], k, j, *(nid + i) + 1);
                            printf("\t%d.%d.%d.%d", ipdec[0], k, j, *(nid + i) + 2);
                            printf("\t%d.%d.%d.%d\n", ipdec[0], k, j, *(br + i) - 1);
                            if (sceltaf == 1)
                                fprintf(f, "\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\n", cont, ipdec[0], k, j, *(nid + i), ipdec[0], k, j, *(br + i), ipdec[0], k, j, *(nid + i) + 1, ipdec[0], k, j, *(nid + i) + 2, ipdec[0], k, j, *(br + i) - 1);
                            if (cont == ns)
                            {
                                if (sceltaf == 1)
                                    fclose(f);
                                subnet(bit + 8, 1, f);
                                return 0;
                            }
                            cont++;
                        }
                    }
                    k++;
                }
                break;
            case 2:
                printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
                cont = 0;
                DC[0] = ipdec[0];
                k = 0;
                int y;
                if (sceltaf == 1)
                    fprintf(f, "\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
                while (k <= ((ns / 256) / pot))
                {
                    DC[1] = k;
                    for (y = 0; y < 256; y++)
                    {
                        DC[2] = y;
                        nidTMP = 0;
                        for (i = 0; i < pot; i++)
                        {
                            *(nid + i) = nidTMP;
                            *(br + i) = nidTMP + intervallo - 1;
                            nidTMP = nidTMP + intervallo;

                            printf("%d) ", cont);
                            if (sceltaf == 1)
                                fprintf(f, " %d)", cont);
                            DC[3] = *(nid + i);
                            decTobin(DC, ipbin);
                            stampa(ipbin, f, sceltaf);
                            DC[3] = *(br + i);
                            decTobin(DC, ipbin);
                            stampa(ipbin, f, sceltaf);
                            DC[3] = *(nid + i) + 1;
                            decTobin(DC, ipbin);
                            stampa(ipbin, f, sceltaf);
                            DC[3] = *(nid + i) + 2;
                            decTobin(DC, ipbin);
                            stampa(ipbin, f, sceltaf);
                            DC[3] = *(br + i) - 1;
                            decTobin(DC, ipbin);
                            stampa(ipbin, f, sceltaf);
                            if (sceltaf == 1)
                                fprintf(f, "\n");
                            printf("\n");
                            if (cont == ns)
                            {
                                if (sceltaf == 1)
                                    fclose(f);
                                subnet(bit + 8, sceltaf, f);
                                return 0;
                            }
                            cont++;
                        }
                    }
                    k++;
                }
            }
        }
    }
}
int CreaSottoretiB(int ipdec[], int ipbin[], int ns, FILE *f)
{
    int *br, *nid;
    int pot = 0, i = 0, j = 0, cont = 0, ott3, k;
    int nidTMP = 0;
    int intervallo;
    int DC[4];
    int scelta, sceltaf;
    printf("Vuoi salvare i risultati su file?\n0=no 1=si`");
    sceltaf = inputscelta(1, 0);
    if (sceltaf == 1)
    {
        if (errore(f) == 0)
        {
            f = fopen("SottoretiMFissa.txt", "w");
            fprintf(f, "Andrea Cazzato 4INA");
            printf("\nFile aperto in scrittura\n");
        }
        else
        {
            f = fopen("SottoretiMFissa.txt", "a");
            printf("\nFile già esistente, scrittura in coda\n");
        }

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(f, "Classe B %d sottoreti\n", ns);
        fprintf(f, "Sottoreti create in data: \n%d-%02d-%02d orario: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour + 1, tm.tm_min, tm.tm_sec);
    }
    else
        printf("Non salverò su file.");
    while (ns >= pow(2, i))
    {
        i++;
    }
    pot = i;
    if (pot <= 8)
    {
        pot = pow(2, i);
        long dim = pot * sizeof(int);
        br = (int *)malloc(dim);
        nid = (int *)malloc(dim);
        intervallo = 256 / pot;
        nidTMP = 0;

        for (i = 0; i < ns; i++)
        {
            *(nid + i) = nidTMP;
            *(br + i) = nidTMP + intervallo - 1;
            nidTMP = nidTMP + intervallo;
        }
        printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
        printf("1) Decimale\n2) Binario");

        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
            if (sceltaf == 1)
                fprintf(f, "\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
            for (i = 0; i < ns; i++)
            {
                printf("\t%d)", i + 1);
                printf("\t%d.%d.%d.0", ipdec[0], ipdec[1], *(nid + i));
                printf("\t%d.%d.%d.255", ipdec[0], ipdec[1], *(br + i));
                printf("\t%d.%d.%d.1", ipdec[0], ipdec[1], *(nid + i));
                printf("\t%d.%d.%d.2", ipdec[0], ipdec[1], *(nid + i));
                printf("\t%d.%d.%d.254\n", ipdec[0], ipdec[1], *(br + i));
                if (sceltaf == 1)
                    fprintf(f, "\t%d)\t%d.%d.%d.0\t%d.%d.%d.255\t%d.%d.%d.1\t%d.%d.%d.2\t%d.%d.%d.254", i + 1, ipdec[0], ipdec[1], *(nid + i), ipdec[0], ipdec[1], *(br + i), ipdec[0], ipdec[1], *(nid + i), ipdec[0], ipdec[1], *(nid + i), ipdec[0], ipdec[1], *(br + i));
            }
            if (sceltaf == 1)
                fclose(f);
            subnet(pot + 16, sceltaf, f);
            break;
        case 2:
            printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
            DC[0] = ipdec[0];
            DC[1] = ipdec[1];
            if (sceltaf == 1)
                fprintf(f, "\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
            for (i = 0; i < ns; i++)
            {
                printf("%d) ", i + 1);
                if (sceltaf == 1)
                    fprintf(f, "%d) ", i + 1);
                DC[2] = *(nid + i);
                DC[3] = 0;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                DC[2] = *(br + i);
                DC[3] = 255;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                DC[2] = *(nid + i);
                DC[3] = 1;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                DC[2] = *(nid + i);
                DC[3] = 2;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                DC[2] = *(br + i);
                DC[3] = 254;
                decTobin(DC, ipbin);
                stampa(ipbin, f, sceltaf);
                if (sceltaf == 1)
                    fprintf(f, "\n");
                printf("\n");
            }
            if (sceltaf == 1)
                fclose(f);
            subnet(pot + 16, sceltaf, f);
            break;
        }
    }
    else
    {
        ott3 = pot - 8;
        pot = pow(2, ott3);
        long dim = pot * sizeof(int);
        br = (int *)malloc(dim);
        nid = (int *)malloc(dim);
        intervallo = 256 / pot;
        printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
        printf("1) Decimale\n2) Binario");
        int scelta;
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            printf("\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
            if (sceltaf == 1)
                fprintf(f, "\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
            for (j = 0; j < ns / pot; j++)
            {
                nidTMP = 0;
                for (i = 0; i < pot; i++)
                {
                    *(nid + i) = nidTMP;
                    *(br + i) = nidTMP + intervallo - 1;
                    nidTMP = nidTMP + intervallo;
                    cont++;
                    printf("\t%d)", cont);
                    printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], j, *(nid + i));
                    printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], j, *(br + i));
                    printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], j, *(nid + i) + 1);
                    printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], j, *(nid + i) + 2);
                    printf("\t%d.%d.%d.%d\n", ipdec[0], ipdec[1], j, *(br + i) - 1);
                    if (sceltaf == 1)
                        fprintf(f, "\t%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\n", cont, ipdec[0], ipdec[1], j, *(nid + i), ipdec[0], ipdec[1], j, *(br + i), ipdec[0], ipdec[1], j, *(nid + i), ipdec[0], ipdec[1], j, *(nid + i), ipdec[0], ipdec[1], j, *(br + i));
                    if (cont == ns)
                    {
                        if (sceltaf == 1)
                            fclose(f);
                        subnet(pot + 16, sceltaf, f);
                        return 0;
                    }
                }
            }
            break;
        case 2:
            printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
            DC[0] = ipdec[0];
            DC[1] = ipdec[1];
            cont = 0;
            if (sceltaf == 1)
                fprintf(f, "\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
            for (k = 0; k < ns / pot; k++)
            {
                DC[2] = k;
                nidTMP = 0;
                for (i = 0; i < pot; i++)
                {
                    *(nid + i) = nidTMP;
                    *(br + i) = nidTMP + intervallo - 1;
                    nidTMP = nidTMP + intervallo;
                    cont++;
                    printf("\t%d)", cont);
                    if (sceltaf == 1)
                        fprintf(f, "\t%d) ", cont);
                    DC[3] = *(nid + i);
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[3] = *(br + i);
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[3] = *(nid + i) + 1;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[3] = *(nid + i) + 2;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    DC[3] = *(br + 1) - 1;
                    decTobin(DC, ipbin);
                    stampa(ipbin, f, sceltaf);
                    printf("\n");
                    fprintf(f, "\n");
                    if (cont == ns)
                    {
                        if (sceltaf == 1)
                            fclose(f);
                        subnet(pot + 16, sceltaf, f);
                        return 0;
                    }
                }
            }
            break;
        }
    }
}
void subnet(int bit, int sceltaf, FILE *f)
{
    int sm[32], smD[4];
    int i;
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
