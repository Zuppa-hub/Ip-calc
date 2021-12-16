//#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>
void converti(int bin[], int dec[])     //conversione di 4 ottetti da binario a decimale 
{
    int cifra, somma, pot, esp, i, j;
    i = 0;
    for (j = 0; j < 4; j++)             //4 ottetti 
    {
        esp = 7;   //7 perchè è l'esponente massimo per un otetto
        somma = 0; //variabile che conterrà il numero convertito
        do
        {
            pot = pow(2, esp); //2^esp
            cifra = bin[i];
            cifra = cifra * pot; // se 1 allora 1 * pot = pot sennò 0*pot = 0
            somma = somma + cifra;  //sommiamo tute le cifre 
            esp--;                      //decrementiamo l'esponente  
            i++;                  
        } while (esp >= 0);             //fino a che diventa 0 
        dec[j] = somma; // restituiamo il valore convertito 
    }
}