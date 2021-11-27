#include <stdio.h>
void decTobin(int ipdec[], int ipbin[])
{
    int n, con, mask, cont, i = 0; //variabili con assegnazioni per mask (128)
    int j,tmp=0;
    for (j = 0; j < 4; j++)
    {
        mask=128;
        n=ipdec[j];
        for (cont = 0; cont < 8; cont++) //ciclo for che termina quando i<8
        {
            con = n & mask; //operando and tra n e mask, il risultato va alla var. con
            if (con == 0)
                ipbin[i] = 0;
            else
                ipbin[i] = 1;
            mask = mask >> 1; //shift di una posizione della variabile mask
            i++;
        }
    }
}