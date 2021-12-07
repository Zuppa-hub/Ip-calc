/*Andrea Cazzato 4 Ina 
Tutto il lavoro sugli indirizzi viene svolto in decimale, indirizzi inseriti in binario vengono convertiti.
1* Punto = controllo la classe dell'indirizzo inserito e se è pubblico o privato, tramite controlli sulle prime cifre del indirizzo
        fonte = https://it.wikipedia.org/wiki/Classi_di_indirizzi_IP
2* Punto = controllo l'appartenenza di due indirizzi ad una stessa rete avendo una subnet mask.
        faccio un operazione and Bit a bit tra indirizzo e subnet, il risultato sarà il net id. se il net id è uguale per entrambi gli indirizzi allora appartengono alla stessa rete.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Header File contenenti le funzioni
#include "Input.h"
#include "ClassePvtPb.h"
#include "DecToBin.h"
#include "stessaRete.h"
#include "Varie.h"
#include "sottoreti.h"
#include "Vlsm.h"
//Costanti
#define maxbin 32 //cifre binarie
#define maxdec 12 //cifre decimali

int main()
{
    //dichiarazione vettori contententi indirizzi e subnet
    int ipDec[maxdec], ipDec2[maxdec];
    int ipBin[maxbin], ipBin2[maxbin];
    int smDec[maxdec], smBin[maxbin];
    int nId1[maxdec], nId2[maxdec];
    int classe, sottoreti; //classe verrà restituita dalla funzione classe in un numero
    int scelta;            //scelta = variabile per switch
    int inserimentoDB;     // inserimentoDB = flag per il metodo di input. 0 = decimale. 1 = binario
    do
    {
        printf("\n1) Insisci ip e calcola classe indirizzo privato o pubblico\n2) Calcola se due indirizzi avendo una subnet mask appartengono alla stessa rete\n3) Calcola le sottoreti avendo ip e numero sottoreti\n4) Calcola le sottoreti avendo ip e numero di host\n5)Uscita");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:; //controllo la classe dell'indirizzo inserito e se è pubblico o privato
            printf("\n Digita 0 se hai un indirizzo in decimale\n Digita 1 se hai un insirizzo in binario\n");
            inserimentoDB = inputscelta(1, 0);  //inputscelta = funzione per avere il controllo dell'input passando il valore massimo e il minimo
            input(ipDec, ipBin, inserimentoDB); //input, in base al flag inserimentodb inseiriamo in decimnale o binario
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
        case 4:;
            printf("\n Digita 0 se hai un indirizzo ip in decimale\n Digita 1 se hai un insirizzo ip in binario\n");
            inserimentoDB = inputscelta(1, 0);
            input(ipDec, ipBin, inserimentoDB);
            printf("Digitare il numero di sottoreti");
            scanf("%d", &sottoreti);
            classe = classePrvPb(ipDec);
            CreaSottoretiVLSM(classe,ipDec,ipBin,sottoreti);
            break;
        case 5:;
            printf("\n Uscita...");
            exit(0);
            break;
        default:
            printf("\nScelta non valida, riprova");
            break;
        }
    } while (scelta < 6);
}
