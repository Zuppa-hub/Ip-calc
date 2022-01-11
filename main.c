/*Andrea Cazzato 4 Ina 
Tutto il lavoro sugli indirizzi viene svolto in decimale, indirizzi inseriti in binario vengono convertiti.
1* Punto = controllo la classe dell'indirizzo inserito e se è pubblico o privato, tramite controlli sulle prime cifre del indirizzo
        fonte = https://it.wikipedia.org/wiki/Classi_di_indirizzi_IP
2* Punto = controllo l'appartenenza di due indirizzi ad una stessa rete avendo una subnet mask.
        faccio un operazione and Bit a bit tra indirizzo e subnet, il risultato sarà il net id. se il net id è uguale per entrambi gli indirizzi allora appartengono alla stessa rete.
3* Punto = In base all'indirizzo inserito la funzione principale indirizza alle funzioni specifiche per ogni classe facendo anche controlli se è possibile calcolare un determinato numero di sottoreti con un determinato indirizzo
            C   Per la clase C ad esempio si prende il la potneza minima per fare il numero di sottoreti richiesto e si eleva 2 alla potenza trovata. 
                L'intervallo poer la creazione delle sottreti sarà dato da 256 "2^8" / il 2^esponente trovato.
                Il primo net id è 0, il secondo la somma del primo più l'intervallo.
                Il broadcast sarà il prossimo net id -1.
                gateway = netid + 1.  
                primo host = netid + 2.
                ultimo host = broadcast - 1.
                host totali = potenza - 3.
            B   Per la classe b applichiamo lo stesso ragionamneto della classe C, ma dividiamo in due i casi. 
                    1* caso se la potenza  trovata è minore o ugualale di 8 allora metteremo il net id trovato con il ragionamento dell'intervallo al 3 ottetto e poi al 4 ottetto 0 per il net e 1 per il broad 
                    2* caso se la potenza è maggiore di 8 allora mettiamo net id e broad all'ultimo ottetto e al terzo mettiamo una variabile che da 0 si incrementa fino al numero di sottoreti / la potenza trovata, perchè l'esponente sarà il numero di intervalli per ogni sottorete.
            A   Per la classe a utlizziamo sempre lo stesso ragionamneto ma dividiamo in 3 casi
                    I primi due casi sono uguali alla classe b cambiando però che se i bitnecessari sono minoiri di 8 i calcoli si concerntrano sul secondo ottetto, se sono superiori a 8 e minori di 16 allora si concentrano sul 3.
                    3* caso se i bit necessari sono più di 16 allora si utlizzano due indici j che si incrementa ogni 255 volte, le sottoreti date dal 3 ottetto, e un indice k che si incrementa per il numero di sottoreti / 256.
4* Punto = 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

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
        fflush(stdout);
        fflush(stdin);
        printf("\n1) Insisci ip e calcola classe indirizzo privato o pubblico\n2) Calcola se due indirizzi avendo una subnet mask appartengono alla stessa rete\n3) Calcola le sottoreti avendo ip e numero sottoreti\n4) Calcola le sottoreti avendo ip e numero di host\n5)Uscita");
        scanf("%d", &scelta);
        switch (scelta)
        {
        case 1:; //controllo la classe dell'indirizzo inserito e se è pubblico o privato
            printf("\n Digita 0 se hai un indirizzo in decimale\n Digita 1 se hai un insirizzo in binario\n");
            inserimentoDB = inputscelta(1, 0); //inputscelta = funzione per avere il controllo dell'input passando il valore massimo e il minimo
            if (inserimentoDB == 0)
                printf("Esempio indirizzo ip in decimale 192.168.1.1\nInserisci l'indirizzo ip in decimale: ");
            else
                printf("Esempio indirizzo ip in binario 11000000.10101000.00000001.00000001\nInserisci l'indirizzo ip in binario: ");
            input(ipDec, ipBin, inserimentoDB); //input, in base al flag inserimentodb inseiriamo in decimnale o binario
            classe = classePrvPb(ipDec);
            break;
        case 2:; //inserendo due indirizzi e una subent mask tramite and bit bit verifichiamo se appartengono alla stessa rete
            printf("\n Digita 0 se hai un indirizzo in decimale\n Digita 1 se hai un insirizzo in binario\n");
            inserimentoDB = inputscelta(1, 0); //controllo input
            if (inserimentoDB == 0)
                printf("Esempio indirizzo ip in decimale 192.168.1.1\nInserisci l'indirizzo ip in decimale: ");
            else
                printf("Esempio indirizzo ip in binario 11000000.10101000.00000001.00000001\nInserisci il primo indirizzo ip in binario: ");
            input(ipDec, ipBin, inserimentoDB); //input primo infirizzo
            printf("\n Digita 0 se hai un indirizzo in decimale\n Digita 1 se hai un insirizzo in binario\n");
            inserimentoDB = inputscelta(1, 0);
            if (inserimentoDB == 0)
                printf("Esempio indirizzo ip in decimale 192.168.1.1\nInserisci l'indirizzo ip in decimale: ");
            else
                printf("Esempio indirizzo ip in binario 11000000.10101000.00000001.00000001\nInserisci il secondo indirizzo ip in binario: ");
            input(ipDec2, ipBin2, inserimentoDB); //secondo ind

            printf("\n Digita 0 se hai una subnet in decimale\n Digita 1 se hai una subnet in binario\n");
            inserimentoDB = inputscelta(1, 0);
            input(smDec, smBin, inserimentoDB); //sm
            netId(ipDec, smDec, nId1);          //calcolo net id tramite &&
            netId(ipDec2, smDec, nId2);         //secondo nid
            stessaRete(nId1, nId2);             //controllo se i net id sono uguali
            break;
        case 3:; //creazione sottoreti a maschera fissa, tutti i controlli sono nella funzione CreaSottoreti
            printf("\n Digita 0 se hai un indirizzo ip in decimale\n Digita 1 se hai un insirizzo ip in binario\n");
            inserimentoDB = inputscelta(1, 0);
           if (inserimentoDB == 0)
                printf("Esempio indirizzo ip in decimale 192.168.1.1\nInserisci l'indirizzo ip in decimale: ");
            else
                printf("Esempio indirizzo ip in binario 11000000.10101000.00000001.00000001\nInserisci l'indirizzo ip in binario: ");
            input(ipDec, ipBin, inserimentoDB); //input indirizzo
            printf("Digitare il numero di sottoreti");
            scanf("%d", &sottoreti);
            classe = classePrvPb(ipDec);                    //prendiamo la classe dell'indirizzo
            CreaSottoreti(classe, ipDec, ipBin, sottoreti); //richiamo funzione per la creazione delle sottoreti a maschera fissa
            break;
        case 4:; //creazione sottoreti a maschera variabile, tutti i controlli sono nella funzione CreaSottoretiVLSM e nelle relative sottofunzioni.
            printf("\n Digita 0 se hai un indirizzo ip in decimale\n Digita 1 se hai un insirizzo ip in binario\n");
            inserimentoDB = inputscelta(1, 0);
            input(ipDec, ipBin, inserimentoDB);
            printf("Digitare il numero di sottoreti");
            scanf("%d", &sottoreti);
            classe = classePrvPb(ipDec);
            CreaSottoretiVLSM(classe, ipDec, ipBin, sottoreti); //gli host vengono chiesti all interno della funzione.
            break;
        case 5:;
            printf("\n Uscita...");
            exit(0); //interrompo il processo e libero la memoria
            break;
        default:
            printf("\nScelta non valida, riprova");
            break;
        }
    } while (scelta < 6); // così da effettuare altre operazioni se non si esce dal programma.
}
