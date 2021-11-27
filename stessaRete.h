#include <stdio.h>

void netId(int ip[], int sm[], int nID[])
{
    int i;
    for (i = 0; i < 4; i++)
        nID[i] = ip[i] & sm[i]; 
}
int stessaRete(int nID[], int nID2[])
{
    int flag = 0;
    int i;
    for (i = 0; i < 4; i++)
    {
        if (nID[i]==nID2[i])
            flag ++;
    }
    if (flag == 4)
        printf("\nI due indirizzi appartengono alla stessa rete con Net Id %d.%d.%d.%d\n", nID[0], nID[1], nID[2], nID[3]);
    else
        printf("\nI due indirizzi non appartengono alla stessa rete");
}
