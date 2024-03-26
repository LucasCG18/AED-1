//Lucas Castelani Gouveia 168877 Noturno
#include <stdio.h>
#include <stdlib.h>
struct lista
{
    int valor;
    int coluna;
    struct lista *prox;
};
typedef struct lista Tlista;
typedef Tlista *Plista;
 
Plista insere (Plista lista, int valor, int coluna) {
    Plista novo = (Plista) malloc (sizeof(Tlista));
    Plista ant = NULL, paux, aux;
    novo->valor = valor; 
    novo->coluna = coluna;
    novo->prox = NULL; 
    //insere de forma ordenada
    if (lista != NULL){
        for (ant = NULL, paux = lista; paux != NULL && paux->coluna < coluna; paux = paux->prox) ant = paux;
        if (ant == NULL){
            novo->prox = lista;
            lista = novo;
        }
        else{
            aux = ant->prox;
            ant->prox = novo; 
            novo->prox = aux; 
        }
    }else{
        lista = novo;
    }
    return lista;
}
 
void insere_em_torno (Plista *lista, int Lt, int Ct, int Lb, int Cb){
    int valor, i, j;
    for (i = Lb-1; i <= Lb+1; i++){
        for (j = Cb - 1; j <= Cb + 1; j++){
            if ((j >=0 && i >=0) && (i < Lt && j < Ct)){
                valor = pValor(lista[i], j);
                if (valor != -1) valor++;
                lista[i] = insere(lista[i], valor, j);
            }
        }
    }
}
int pValor (Plista lista, int coluna){
    int valor = 0;
    Plista aux;
    if (lista != NULL){
        for (aux = lista; aux->coluna < coluna && aux->prox != NULL; aux = aux->prox);
        if (aux != NULL && aux->coluna == coluna){
            valor = aux->valor;
        }
    }
    return valor;
}
 
Plista libera (Plista lista) {
    Plista aux; 
    for (aux = lista; aux != NULL; aux = lista) { 
        lista = lista->prox; 
        free(aux);
    }
    return NULL;
}
void mostrar(Plista *lista, int l, int c){
    int i,j;
    for (i = 0; i < l; i++){
        for (j = 0; j < c; j++){
            if (pValor(lista[i], j) == -1){
                printf("X ");
            }else{
                printf("%d ", pValor(lista[i], j));
            }
        }
        printf("\n");
    }
}
 
int main(){
    int L,C,B,Lb,Cb,i,j;
    Plista *vetorLista, p;
    scanf("%d %d", &L, &C);
    vetorLista=(Plista *)malloc(L*sizeof(Plista));
    for (i = 0; i < L; i++){
        vetorLista[i] = NULL;
    }
    scanf("%d", &B);
    if (L < 101 && C<101 && B<61){
        while (B != 0){
            scanf("%d %d", &Lb, &Cb);
            if(Lb < L && Cb < C){
                if (pValor(vetorLista[Lb], Cb) != -1){
                    vetorLista[Lb] = insere(vetorLista[Lb], -1, Cb);
                    insere_em_torno(vetorLista, L,C,Lb,Cb);
                }
            }
            B--;
        }
        mostrar(vetorLista, L, C);
    }
}