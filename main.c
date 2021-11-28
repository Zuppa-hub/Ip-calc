#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Header File contenenti le funzioni
#include "Input.h"
#include "ClassePvtPb.h"
#include "stessaRete.h"
#include "Varie.h"
#include "sottoreti.h"
//Costanti
#define maxbin 32
#define maxdec 12

int main()
{
    int ipDec[maxdec], ipDec2[maxdec];
    int ipBin[maxbin], ipBin2[maxbin];
    int smDec[maxdec], smBin[maxbin];
    int nId1[maxdec], nId2[maxdec];
    int classe, sottoreti;
    int scelta, scelta2, inserimentoDB;
    do
    {
        printf("\n1) Insisci ip e calcola classe indirizzo privato o pubblico\n2) Calcola se due indirizzi avendo una subnet mask appartengono alla stessa rete\n3) calcola le sottoreti avendo ip e numero sottoreti");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:;
            printf("\n Digita 0 se hai un indirizzo in decimale\n Digita 1 se hai un insirizzo in binario\n");
            inserimentoDB = inputscelta(1, 0);
            input(ipDec, ipBin, inserimentoDB);
            classe = classePrvPb(ipDec);
            break;
        case 2:;
            printf("\n Digita 0 se hai un indirizzo in decimale\n Digita 1 se hai un insirizzo in binario\n");
            inserimentoDB = inputscelta(1, 0);
            printf("\nInserisci il primo indirizzo ip\n");
            input(ipDec, ipBin, inserimentoDB);

            printf("\nInserisci il secondo ip\n");
            printf("\n Digita 0 se hai un indirizzo in decimale\n Digita 1 se hai un insirizzo in binario\n");
            inserimentoDB = inputscelta(1, 0);
            input(ipDec2, ipBin2, inserimentoDB);

            printf("\n Digita 0 se hai una subnet in decimale\n Digita 1 se hai una subnet in binario\n");
            inserimentoDB = inputscelta(1, 0);
            inserimentoDB = inserimentoDB + 2;
            input(smDec, smBin, inserimentoDB);
            netId(ipDec, smDec, nId1);
            netId(ipDec2, smDec, nId2);
            stessaRete(nId1, nId2);
            break;
        case 3:;
            printf("\n Digita 0 se hai un indirizzo ip in decimale\n Digita 1 se hai un insirizzo ip in binario\n");
            inserimentoDB = inputscelta(1, 0);
            input(ipDec, ipBin, inserimentoDB);
            printf("Digitare il numero di sottoreti");
            scanf("%d", &sottoreti);
            classe = classePrvPb(ipDec);
            CreaSottoreti(classe, ipDec, ipBin, sottoreti);
            break;
        case 5:;
            printf("\n Uscitza...");
            exit(0);
            break;
        default:
            printf("\nScelta non valida, riprova");
            break;
        }
    } while (scelta <6);
}
