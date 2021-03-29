//Popis programu: program vyhleda nejkratsi cestu mezi dvema vrcholy grafu, vypise jeji hodnotu + vypise danou cestu
//Vstup: pocet vrcholu, startovni vrchol, cilovy vrchol, matice sousednosti
//Vystup: pokud existuje cesta - delka, cesta

#include <stdio.h>
#include <stdlib.h>

typedef int bool;
enum { false, true };

#define MAX 10000

int nactiPocetVrcholu(const char *filename)
{
    int N;
    FILE *file = fopen(filename, "r");
    fscanf(file, "%d", &N);
    fclose(file);

    return N;
}

int** inicializujMatici(int pocet_vrcholu)
{
    int **vzdal = malloc(pocet_vrcholu * sizeof(int*));
    int i;
    for (i = 0; i < pocet_vrcholu; ++i)
    {
        vzdal[i] = malloc(pocet_vrcholu * sizeof(int));
    }

    return vzdal;
}

void freeMatice(int **matice, int rozmer)
{
    int i;
    for (i = 0; i < rozmer; i++)
    {
        free(matice[i]);
    }
    free(matice);
}

void nactiData(const char *filename, int **vzdal, int *start, int *cil)
{
    FILE *file = fopen(filename, "r");
    int N;
    fscanf(file, "%d %d %d", &N, start, cil);

    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            fscanf(file, "%d", &vzdal[i][j]);
        }
    }

    close(file);
}

void inicializujPole(int N, int start, int *H, int *Docas)
{
    int i;
    for (i = 0; i < N; i++)
    {
        H[i] = MAX;
        Docas[i] = true;
    }

    H[start] = 0;
}

void pruchodGrafem(int **vzdal, int N, int cil, int *H, int *P, int *Docas)
{
    bool Pruchod = true;    //pokracovat v pruchodu
    int i, j;

    while ((Docas[cil] == true) && (Pruchod == true))
    {
        j = cil;
        for (i = 0; i < N; i++)
        {
            if ((Docas[i] == true) && (H[i] < H[j]))
            {
                j = i;
            }
        }
        if (H[j] == MAX)
        {
            Pruchod = false;
        }
        else
        {
            Docas[j] = false;
            for (i = 0; i < N; i++)
            {
                if (vzdal[j][i] < MAX)
                {
                    if ((H[j] + vzdal[j][i]) < H[i])
                    {
                        H[i] = H[j] + vzdal[j][i];
                        P[i] = j;
                    }
                }
            }
        }
    }
}

void vypisNejkratsiCestu(int *H, int *P, int *Docas, int start, int cil)
{
    if (Docas[cil] == true)
    {
        printf("Cilovy vrchol neni z pocatecniho dostupny.");
    }
    else
    {
        printf("Delka z %d do %d:\n%d\n", start, cil, H[cil]);

        printf("Cesta (v obracenem poradi vrcholu):\n");
        int i = cil;
        while (i != start)
        {
            printf("%d ", i);
            i = P[i];
        }
        printf("%d", start);
    }
}

testFun()
{

}

void vypis(int N, int **vzdal, int *H, int *P, int Start, int Cil)
{
    printf("N %d Start %d Cil %d\n", N, Start, Cil);

    printf("vzdal:\n");

    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", vzdal[i][j]);
        }
        printf("\n");
    }

    printf("H:\n");
    for (j = 0; j < N; j++)
    {
        printf("%d ", H[j]);
    }

    printf("\n");

    printf("P:\n");
    for (j = 0; j < N; j++)
    {
        printf("%d ", P[j]);
    }
}

void Dijkstra()
{
    int start, cil;
    int pocet_vrcholu = nactiPocetVrcholu("input.txt");
    int **vzdal = inicializujMatici(pocet_vrcholu);
    int *H = malloc(pocet_vrcholu);         //hodnoty vrcholu
    int *Docas = malloc(pocet_vrcholu);     //docasna hodnota
    int *P = malloc(pocet_vrcholu);         //predchudci vrcholu

    nactiData("input.txt", vzdal, &start, &cil);
    inicializujPole(pocet_vrcholu, start, H, Docas);
    pruchodGrafem(vzdal, pocet_vrcholu, cil, H, P, Docas);
    vypisNejkratsiCestu(H, P, Docas, start, cil);

    freeMatice(vzdal, pocet_vrcholu);
    free(H);
    free(Docas);
    free(P);
}

int main()
{
    Dijkstra();

    return 0;
}
