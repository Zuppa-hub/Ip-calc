//#include <stdio.h>
#include "BintoDEC.h"
int erroreStampa();
int input(int dec[], int bin[], int flag)
{
    int contP = 0; //contatore dei punti, se ne mettiamo meno o più di 3 restituisce un errore
    int i, j, k;
    if (flag == 0) //passata come paramentro, è il modo di inserimento quindi in bainario o decimale
    {
        char decimale[16];
        int moltiplica = 100;
        int m = 1;
        int somma;
        fflush(stdin);
        fgets(decimale, 15, stdin);
        decimale[strlen(decimale) - 1] = 46;
        fflush(stdin);
        fflush(stdout);
        for (i = 0; i < strlen(decimale) - 1; i++) //-1 perchè l'ultimo carattere è un . aggiunto manualmente per far terminare i controlli
            if (decimale[i] == 46)
                contP++;                                     //controllo se i punti siano 3
        if (strlen(decimale) >= 8 && strlen(decimale) <= 14) //lunghezza minima e massima della stringa contando i puntio es 1.1.1.1 || 255.255.255.255
        {
            i = 0;
            k = 0;
            for (j = 0; j < 4; j++) //192.168.1.1 = 4 blocchi 192 = un blocco
            {
                somma = 0;
                while (decimale[i] != 46) //vedo quante cifre ci sono in un blocco e moltiplico m per 10, m quindi puo essere variare da 10 a 1000
                {
                    m = m * 10;
                    i++;
                };
                m = m / 10; //m deve essere comreso tra 1 e 100, 1 = 1 cifra in un blocco, 100 = 3 cifre
                do
                {
                    somma = somma + (decimale[k] - 48) * m; //somma sarà la cifra del blocco moltiplicata per m, ES 192 = 1*100+9*10+2*1
                    m = m / 10;                             //divido m per 10 così e passo alla prossima cifra, ed da 1 per 100 a 9 per 10, 10 e 100 sono M.
                    k++;
                } while (k < i); //finche non giro tutte le cifre del blocco quindi k sarà maggiore di i;
                k++;
                //qui assegno la cifra intera e non più divisa al vettore, come se fosse un input di un intero.
                dec[j] = somma;
                m = 1; //faccio tornare m a 1
                i++;   //passo alla prossima cifra
            }
        }
        else                       //se non è compresa
            return erroreStampa(); //segnale d'errore -1 intpretato poi nel main
        if (contP != 3)
            contP = -1;
    }
    else
    {
        if (flag == 1) //input binario
        {
            char binario[36];
            fflush(stdin);
            fgets(binario, 36, stdin);
            i = 0;
            if (strlen(binario) == 35) //controllo la giusta lunghezza, 8 cifre a blocco *4 blocchi = 32 cifre + 3 punti
            {
                for (j = 0; j < 35; j++)
                {
                    if (binario[j] == 46) //se incontro i punti
                        contP++;
                    if (j == 8 || j == 17 || j == 26) //salto i punti andando alla cifra sucessiva
                        j++;
                    if (j < 35)                   //l'ultima volta sarà maggiore di 35 incrementando per saltare i punti
                        bin[i] = binario[j] - 48; //convero char in int
                    i++;
                    //printf("%d", bin[j]);
                }
                //for (j = 0; j < 32; j++)
                //sleep(100);
                //3 giusto
                if (contP != 3) // se ci sono più o meno punti di 3
                    contP = -1;
                /* for (i = 0; i < 32; i++)
                {
                    printf(" %d", bin[i]);
                    if (i == 7 || i == 15 || i == 23)
                        printf(".");
                    
                } */
                //sleep(100);
                converti(bin, dec); //porto il vettore ricavato da binario a decimale
            }
            else
                return erroreStampa();
        }
    }
    system("cls");
    printf("Controllo che l'indirizzo sia valido\n\n");
    j = 0;
    if (dec[0] >= 10 && dec[0] <= 255) // il primo blocco deve essere co preso tra 10 e 155 
        j++;
    for (i = 1; i < 4; i++)
        if (dec[i] >= 0 && dec[i] <= 255)   //gli altri tra 0 e 255 
            j++;
    if (j != i || contP == -1) //j è uguale a i se tutti i blocchi sono compresi tra 0 e 255
        return erroreStampa();
    printf("Indirizzo valido\n");
    sleep(1);
    system("cls");
    return 0;       //segnale di indirizzo valido poi intrepato nel main 
}
int erroreStampa()      //avviso 
{
    printf("Indirizzo non valido\n");
    sleep(3); //3 secondi per leggere l'avviso
    system("cls");
    return -1;
}
