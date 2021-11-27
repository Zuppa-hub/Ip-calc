#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DecToBin.h"

int CreaSottoretiA(int ipdec[], int ipbin[], int ns);
int CreaSottoretiB(int ipdec[], int ipbin[], int ns);
void CreaSottoretiC(int ipdec[], int ipbin[], int ns);
void subnet(int bit);

void CreaSottoreti(int classe, int ipdec[], int ipbin[], int ns)
{
    if (classe == 1)
    {
        if (ns >= pow(2, 21) || ns <= 0)
        {
            printf("Impossibile calcolare %d sottoreti con indirizzo %d.%d.%d.%d", ns, ipdec[0], ipdec[1], ipdec[2], ipdec[3]);
        }
        else
        {
            CreaSottoretiA(ipdec, ipbin, ns);
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
                CreaSottoretiB(ipdec, ipbin, ns);
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
                    CreaSottoretiC(ipdec, ipbin, ns);
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
void CreaSottoretiC(int ipdec[], int ipbin[], int ns)
{
    //decTobin(ipdec,ipbin);
    //massimo 64
    int *br, *nid;
    long dim = ns * sizeof(int);
    br = (int *)malloc(dim);
    nid = (int *)malloc(dim);
    int pot = 0, i = 0, j;
    int nidTMP = 0, brTMP = 0;
    int DC[4];
    while (ns >= pow(2, i))
        i++;
    int BitRete = i;
    pot = pow(2, i);
    pot = 256 / pot;
    for (int i = 0; i < ns; i++)
    {
        *(nid + i) = nidTMP;
        *(br + i) = nidTMP + pot - 1;
        nidTMP = nidTMP + pot;
    }
    printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
    printf("1) Decimale\n2) Binario");
    int scelta;
    scanf("%d", &scelta);
    switch (scelta)
    {
    case 1:
        printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
        for (i = 0; i < ns; i++)
            printf("\t%d)\t%d.%d.%d.%d\t%d.%d.%d.%d\t\t%d.%d.%d.%d\t%d.%d.%d.%d\t%d.%d.%d.%d\n", i + 1, ipdec[0], ipdec[1], ipdec[2], *(nid + i), ipdec[0], ipdec[1], ipdec[2], *(br + i), ipdec[0], ipdec[1], ipdec[2], *(nid + i) + 1, ipdec[0], ipdec[1], ipdec[2], *(nid + i) + 2, ipdec[0], ipdec[1], ipdec[2], *(br + i) - 1);
        subnet(BitRete + 24);
        break;
    case 2:
        printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
        DC[0] = ipdec[0];
        DC[1] = ipdec[1];
        DC[2] = ipdec[2];
        for (i = 0; i < ns; i++)
        {
            printf("%d) ", i + 1);
            DC[3] = *(nid + i);
            decTobin(DC, ipbin);
            for (j = 0; j < 32; j++)
            {
                printf("%d", ipbin[j]);
                if (j == 7 || j == 15 || j == 23)
                    printf(".");
            }
            printf("  ");
            DC[3] = *(br + i);
            decTobin(DC, ipbin);
            for (j = 0; j < 32; j++)
            {
                printf("%d", ipbin[j]);
                if (j == 7 || j == 15 || j == 23)
                    printf(".");
            }
            printf("  ");
            DC[3] = *(nid + i) + 1;
            decTobin(DC, ipbin);
            for (j = 0; j < 32; j++)
            {
                printf("%d", ipbin[j]);
                if (j == 7 || j == 15 || j == 23)
                    printf(".");
            }
            printf("  ");
            DC[3] = *(nid + i) + 2;
            decTobin(DC, ipbin);
            for (j = 0; j < 32; j++)
            {
                printf("%d", ipbin[j]);
                if (j == 7 || j == 15 || j == 23)
                    printf(".");
            }
            printf("  ");
            DC[3] = *(br + i) - 1;
            decTobin(DC, ipbin);
            for (j = 0; j < 32; j++)
            {
                printf("%d", ipbin[j]);
                if (j == 7 || j == 15 || j == 23)
                    printf(".");
            }
            printf("\n");
        }
        subnet(BitRete + 24);
        break;
    }
}
int CreaSottoretiA(int ipdec[], int ipbin[], int ns)
{
    int i = 0, j = 0, k = 0, cont = 0;
    int bit;
    int pot, intervallo;
    int ott2, ott3;
    int temp;
    int nidTMP = 0;
    int DC[4];
    int *br, *nid;
    long dim = ns * sizeof(int);
    br = (int *)malloc(dim);
    nid = (int *)malloc(dim);

    while (pow(2, i) <= ns)
        i++;
    bit = i;
    if (bit <= 8)
    {
        pot = pow(2, i);
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
        int scelta;
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
            for (i = 0; i < ns; i++)
            {
                printf("\t%d)", i + 1);
                printf("\t%d.%d.0.0", ipdec[0], *(nid + i));
                printf("\t%d.%d.255.255", ipdec[0], *(br + i));
                printf("\t%d.%d.0.1", ipdec[0], *(nid + i));
                printf("\t%d.%d.0.2", ipdec[0], *(nid + i));
                printf("\t%d.%d.255.254\n", ipdec[0], *(br + i));
            }
            subnet(bit + 8);
            break;
        case 2:
            printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
            DC[0] = ipdec[0];
            for (i = 0; i < ns; i++)
            {
                printf("%d) ", i + 1);
                DC[1] = *(nid + i);
                DC[2] = 0;
                DC[3] = 0;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("  ");
                DC[1] = *(br + i);
                DC[2] = 255;
                DC[3] = 255;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                DC[1] = *(nid + i);
                DC[2] = 0;
                DC[3] = 1;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("  ");
                DC[1] = *(nid + i);
                DC[2] = 0;
                DC[3] = 2;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("  ");
                DC[1] = *(br + i);
                DC[2] = 255;
                DC[3] = 254;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("\n");
            }
            subnet(bit + 8);
            break;
        }
    }
    else
    {
        if (bit <= 16)
        {
            ott3 = bit - 8;
            pot = pow(2, ott3);
            intervallo = 256 / pot;
            ;
            for (j = 0; j < ns / pot; j++)
            {
                nidTMP = 0;
                for (i = 0; i < pot; i++)
                {
                    *(nid + i) = nidTMP;
                    *(br + i) = nidTMP + intervallo - 1;
                    nidTMP = nidTMP + intervallo;
                }
            }
            printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
            printf("1) Decimale\n2) Binario");
            int scelta;
            scanf("%d", &scelta);
            switch (scelta)
            {
            case 1:
                for (j = 0; j < ns / pot; j++)
                {
                    printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
                    for (i = 0; i < pot; i++)
                    {
                        cont++;
                        printf("\t%d)", cont);
                        printf("\t%d.%d.%d.0", ipdec[0], j, *(nid + i));
                        printf("\t%d.%d.%d.255", ipdec[0], j, *(br + i));
                        printf("\t%d.%d.%d.1", ipdec[0], j, *(nid + i));
                        printf("\t%d.%d.%d.2", ipdec[0], j, *(nid + i));
                        printf("\t%d.%d.%d.254\n", ipdec[0], j, *(br + i));
                        if (cont == ns)
                        {
                            subnet(bit + 8);
                            return 0;
                        }
                    }
                }
                break;
            case 2:
                printf("\nRETE\t\t\tNET ID\t\t\tBROADCAST\t\t\t\tGATEWAY\t\t\t\tPRIMO HOST\t\t\t\tULTIMO HOST\n");
                DC[0] = ipdec[0];
                for (j = 0; j < ns / pot; j++)
                {
                    DC[1] = j;
                    for (i = 0; i < pot; i++)
                    {
                        cont++;
                        printf("\t%d)", cont);

                        DC[2] = *(nid + i);
                        DC[3] = 0;
                        decTobin(DC, ipbin);
                        for (j = 0; j < 32; j++)
                        {
                            printf("%d", ipbin[j]);
                            if (j == 7 || j == 15 || j == 23)
                                printf(".");
                        }
                        printf("  ");
                        DC[2] = *(br + i);
                        DC[3] = 255;
                        decTobin(DC, ipbin);
                        for (j = 0; j < 32; j++)
                        {
                            printf("%d", ipbin[j]);
                            if (j == 7 || j == 15 || j == 23)
                                printf(".");
                        }
                        printf("  ");
                        DC[2] = *(nid + i);
                        DC[3] = 1;
                        decTobin(DC, ipbin);
                        for (j = 0; j < 32; j++)
                        {
                            printf("%d", ipbin[j]);
                            if (j == 7 || j == 15 || j == 23)
                                printf(".");
                        }
                        printf("  ");
                        DC[3] = 2;
                        decTobin(DC, ipbin);
                        for (j = 0; j < 32; j++)
                        {
                            printf("%d", ipbin[j]);
                            if (j == 7 || j == 15 || j == 23)
                                printf(".");
                        }
                        printf("  ");
                        DC[2] = *(br + i);
                        DC[3] = 254;
                        decTobin(DC, ipbin);
                        for (j = 0; j < 32; j++)
                        {
                            printf("%d", ipbin[j]);
                            if (j == 7 || j == 15 || j == 23)
                                printf(".");
                        }
                        printf("\n");
                        if (cont == ns)
                        {
                            subnet(bit + 8);
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
            intervallo = 256 / pot;
            k = 0;

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
                        cont++;
                    }
                }
                k++;
            }
            printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
            printf("1) Decimale\n2) Binario");
            int scelta;
            scanf("%d", &scelta);
            switch (scelta)
            {
                printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
                while (k <= ((ns / 256) / pot))
                {
                    for (j = 0; j < 256; j++)
                    {
                        for (i = 0; i < pot; i++)
                        {
                            printf("\t%d)", cont);
                            printf("\t%d.%d.%d.%d", ipdec[0], k, j, *(nid + i));
                            printf("\t\t%d.%d.%d.%d", ipdec[0], k, j, *(br + i));
                            printf("\t%d.%d.%d.%d", ipdec[0], k, j, *(nid + i) + 1);
                            printf("\t%d.%d.%d.%d", ipdec[0], k, j, *(nid + i) + 2);
                            printf("\t%d.%d.%d.%d\n", ipdec[0], k, j, *(br + i) - 1);
                            if (cont == ns)
                            {
                                subnet(bit + 8);
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
                DC[0] = ipdec[0];
                while (k <= ((ns / 256) / pot))
                {
                    DC[1] = k;
                    for (j = 0; j < 256; j++)
                    {
                        DC[2] = j;
                        for (i = 0; i < pot; i++)
                        {
                            printf("\t%d)", cont);
                            DC[3] = *(nid + i);
                            decTobin(DC, ipbin);
                            for (j = 0; j < 32; j++)
                            {
                                printf("%d", ipbin[j]);
                                if (j == 7 || j == 15 || j == 23)
                                    printf(".");
                            }
                            printf("  ");
                            DC[3] = *(br + i);
                            decTobin(DC, ipbin);
                            for (j = 0; j < 32; j++)
                            {
                                printf("%d", ipbin[j]);
                                if (j == 7 || j == 15 || j == 23)
                                    printf(".");
                            }
                            printf("  ");
                            DC[3] = *(nid + i) + 1;
                            decTobin(DC, ipbin);
                            for (j = 0; j < 32; j++)
                            {
                                printf("%d", ipbin[j]);
                                if (j == 7 || j == 15 || j == 23)
                                    printf(".");
                            }
                            printf("  ");
                            DC[3] = *(nid + i) + 2;
                            decTobin(DC, ipbin);
                            for (j = 0; j < 32; j++)
                            {
                                printf("%d", ipbin[j]);
                                if (j == 7 || j == 15 || j == 23)
                                    printf(".");
                            }
                            printf("  ");
                            DC[3] = *(br + i) - 1;
                            decTobin(DC, ipbin);
                            for (j = 0; j < 32; j++)
                            {
                                printf("%d", ipbin[j]);
                                if (j == 7 || j == 15 || j == 23)
                                    printf(".");
                            }
                            printf("\n");

                            if (cont == ns)
                            {
                                subnet(bit + 8);
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
int CreaSottoretiB(int ipdec[], int ipbin[], int ns)
{
    int *br, *nid;
    long dim = ns * sizeof(int);
    br = (int *)malloc(dim);
    nid = (int *)malloc(dim);
    int pot = 0, i = 0, j = 0, cont = 0, ott3;
    int nidTMP = 0;
    int intervallo;
    int DC[4];
    while (ns >= pow(2, i))
    {
        i++;
    }
    pot = i;
    if (pot <= 8)
    {
        pot = pow(2, i);
        intervallo = 256 / pot;
        nidTMP = 0;
        printf("\n\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
        for (i = 0; i < ns; i++)
        {
            *(nid + i) = nidTMP;
            *(br + i) = nidTMP + intervallo - 1;
            nidTMP = nidTMP + intervallo;
        }
        printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
        printf("1) Decimale\n2) Binario");
        int scelta;
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            for (i = 0; i < ns; i++)
            {
                printf("\t%d)", i + 1);
                printf("\t%d.%d.%d.0", ipdec[0], ipdec[1], *(nid + i));
                printf("\t%d.%d.%d.255", ipdec[0], ipdec[1], *(br + i));
                printf("\t%d.%d.%d.1", ipdec[0], ipdec[1], *(nid + i));
                printf("\t%d.%d.%d.2", ipdec[0], ipdec[1], *(nid + i));
                printf("\t%d.%d.%d.254\n", ipdec[0], ipdec[1], *(br + i));
            }
            subnet(pot + 16);
            break;
        case 2:
            DC[0] = ipdec[0];
            DC[1] = ipdec[1];
            for (i = 0; i < ns; i++)
            {
                DC[2] = *(nid + i);
                DC[3] = 0;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("  ");
                DC[2] = *(br + i);
                DC[3] = 255;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("  ");
                DC[2] = *(nid + i);
                DC[3] = 1;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("  ");
                DC[2] = *(nid + i);
                DC[3] = 2;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("  ");
                DC[2] = *(br + i);
                DC[3] = 254;
                decTobin(DC, ipbin);
                for (j = 0; j < 32; j++)
                {
                    printf("%d", ipbin[j]);
                    if (j == 7 || j == 15 || j == 23)
                        printf(".");
                }
                printf("\n");
            }
            subnet(pot + 16);
            break;
        }
    }
    else
    {
        ott3 = pot - 8;
        pot = pow(2, ott3);
        intervallo = 256 / pot;
        printf("\tRETE\tNET ID\t\tBROADCAST\t\tGATEWAY\t\tPRIMO HOST\tULTIMO HOST\n");
        for (j = 0; j < ns / pot; j++)
        {
            nidTMP = 0;
            for (i = 0; i < pot; i++)
            {
                *(nid + i) = nidTMP;
                *(br + i) = nidTMP + intervallo - 1;
                nidTMP = nidTMP + intervallo;
            }
        }
        printf("\n\t\t\t\t**Sottoreti create**\nOra scelgi come visualizzarle\n");
        printf("1) Decimale\n2) Binario");
        int scelta;
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:
            for (j = 0; j < ns / pot; j++)
            {
                for (i = 0; i < pot; i++)
                {
                    cont++;
                    printf("\t%d)", cont);
                    printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], j, *(nid + i));
                    printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], j, *(br + i));
                    printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], j, *(nid + i) + 1);
                    printf("\t%d.%d.%d.%d", ipdec[0], ipdec[1], j, *(nid + i) + 2);
                    printf("\t%d.%d.%d.%d\n", ipdec[0], ipdec[1], j, *(br + i) - 1);
                    if (cont == ns)
                    {
                        subnet(pot + 16);
                        return 0;
                    }
                }
            }
            break;
        case 2:
            DC[0] = ipdec[0];
            DC[1] = ipdec[1];
            for (j = 0; j < ns / pot; j++)
            {
                DC[2] = j;
                for (i = 0; i < pot; i++)
                {
                    DC[3] = *(nid + i);
                    decTobin(DC, ipbin);
                    for (j = 0; j < 32; j++)
                    {
                        printf("%d", ipbin[j]);
                        if (j == 7 || j == 15 || j == 23)
                            printf(".");
                    }
                    printf("  ");
                    DC[3] = *(br + i);
                    decTobin(DC, ipbin);
                    for (j = 0; j < 32; j++)
                    {
                        printf("%d", ipbin[j]);
                        if (j == 7 || j == 15 || j == 23)
                            printf(".");
                    }
                    printf("  ");
                    DC[3] = *(nid + i) + 1;
                    decTobin(DC, ipbin);
                    for (j = 0; j < 32; j++)
                    {
                        printf("%d", ipbin[j]);
                        if (j == 7 || j == 15 || j == 23)
                            printf(".");
                    }
                    printf("  ");
                    DC[3] = *(nid + i) + 2;
                    decTobin(DC, ipbin);
                    for (j = 0; j < 32; j++)
                    {
                        printf("%d", ipbin[j]);
                        if (j == 7 || j == 15 || j == 23)
                            printf(".");
                    }
                    printf("  ");
                    DC[3] = *(br + 1) - 1;
                }
            }
            break;
        }
    }
}
void subnet(int bit)
{
    int sm[32], smD[4];
    int i;
    for (i = bit; i < 32; i++)
        sm[i] = 0;
    for (i = 0; i < bit; i++)
    {
        sm[i] = 1;
    }
    printf("Subnet mask in decimale = ");
    converti(sm, smD);
    printf("\n");
    for (i = 0; i < 3; i++)
    {
        printf("%d.", smD[i]);
    }
    printf("%d", smD[3]);
    printf("\nSubnet mask CIDR = /%d", bit);
}
