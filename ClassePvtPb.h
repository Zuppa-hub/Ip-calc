//#include <stdio.h>
int classePrvPb(int ipdec[])
{
    printf("L'indirizzo %d.%d.%d.%d e' di ", ipdec[0], ipdec[1], ipdec[2], ipdec[3]);
    if (ipdec[0] >= 0 && ipdec[0] <= 127)
    {
        printf("classe A ed e' un ");
        if (ipdec[0] == 10)
            printf("indirizzo privato");
        else
            printf("indirizzo pubblico");
        return 1;
    }
    else
    {
        if (ipdec[0] >= 128 && ipdec[0] <= 191)
        {
            printf("classe B ed e' un ");
            if (ipdec[0] == 172 && ipdec[1] >= 16 && ipdec[1] <= 31)
                printf("indirizzo privato");
            else
                printf("indirizzo pubblico");
            return 2;
        }
        else
        {
            if (ipdec[0] >= 192 && ipdec[0] <= 223)
            {
                printf("classe C ed e' un ");
                if (ipdec[0] == 192 && ipdec[1] == 168)
                    printf("indirizzo privato");
                else
                    printf("indirizzo pubblico");
                return 3;
            }
            else
            {
                if (ipdec[0] >= 224 && ipdec[0] <= 239)
                    printf("classe D");
                else if (ipdec[0] >= 240 && ipdec[0] <= 255)
                    printf("classe E");
                return 0;
            }
        }
    }
}
