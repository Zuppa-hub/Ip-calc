//#include <stdio.h>
int classePrvPb(int ipdec[])
{
   // printf("\n%d",ipdec[0]);
    if (ipdec[0] >= 0 && ipdec[0] <= 127)
    {
        printf("Classe A");
        if (ipdec[0] == 10)
        {
            printf("insirizzo privato");
        }
        else
        {
            printf("insirizzo pubblico");
        }
        return 1;
    }
    else
    {
        if (ipdec[0] >= 128 && ipdec[0] <= 191)
        {
            printf("Classe B");
            if (ipdec[0] == 172 && ipdec[1]>=16 && ipdec[1]<=31)
                printf("insirizzo privato");
            else
            printf("insirizzo pubblico");
            return 2;
        }
        else
        {
            if(ipdec[0] >= 192 && ipdec[0] <=223)
            {
                printf("Classe C");
                if (ipdec[0] == 192 && ipdec[1]==168)
                printf("indirizzo privato");
                else
                printf("indirizzo pubblico");
                return 3;
            }
            else
            {
                if(ipdec[0] >= 224 && ipdec[0] <=239)
                {
                    printf("Classe D");
                    return 0;
                }
                else
                {
                    if(ipdec[0] >= 240 && ipdec[0] <=255)
                        printf("Classe E");
                        return 0;
                }
            }
        }
    }
}
