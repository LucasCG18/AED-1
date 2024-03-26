// Lucas Castelani Gouveia
#include <stdio.h>
#include <stdlib.h>

struct Corredor
{
    int numero;
    char nome[20];
};

void adicionar_corredor(int i, struct Corredor **corredores)
{
    corredores[i] = (struct Corredor *)malloc(sizeof(struct Corredor));
    scanf("%d", &corredores[i]->numero);
    fgets(corredores[i]->nome, 20, stdin);
}

int main()
{
    int n_corredor = 0, i = 0,j = 0, *posicoes, ultrapassagem = 0, aux, n;
    struct Corredor **corredores;
    scanf("%d", &n_corredor);
    corredores = (struct Corredor **)malloc(n_corredor * (sizeof(struct Corredor *)));
    posicoes = (int *)malloc(n_corredor * (sizeof(int)));

    if (n_corredor >= 3 && n_corredor <= 1000)
    {
        while (i < n_corredor)
        {
            adicionar_corredor(i, corredores);
            i++;
        }
        i = 0;
        while (i < n_corredor)
        {
            scanf("%d", &posicoes[i]);
            i++;
        }
        do
        {
            scanf("%d", &ultrapassagem);
            if (ultrapassagem >= 0)
            {
                for (n = 1; n < n_corredor; n++)
                {
                    if (ultrapassagem == posicoes[n])
                    {
                        aux = posicoes[n];
                        posicoes[n] = posicoes[n - 1];
                        posicoes[n - 1] = aux;
                    }
                }
                
            }
        } while (ultrapassagem != -1);
        for (j = 0; j < 3; j++)
        {
            for (i = 0; i < n_corredor; i++)
            {
                if (posicoes[j] == corredores[i]->numero)
                {
                    printf("%d %s", corredores[i]->numero, corredores[i]->nome);
                }
            }
        }
    }

    free(posicoes);
    for (i = 0; i < n_corredor; i++)
    {
        free(corredores[i]);
    }
    free(corredores);
}