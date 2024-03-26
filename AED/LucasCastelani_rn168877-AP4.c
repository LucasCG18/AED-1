// Lucas Castelani Gouveia
// RA: 168877
#include <stdlib.h>
#include <stdio.h>
 
struct Tpilha
{
    int valor;
    struct Tpilha *prox;
};
typedef struct Tpilha *Ppilha;
 
Ppilha inicializacao_pilha(){
    return NULL;
}
 
Ppilha push(Ppilha p, int valor){
    Ppilha novo = (Ppilha)malloc(sizeof(struct Tpilha));
    novo->valor = valor;
    novo->prox = p;
    return novo;
}
 
Ppilha pop(Ppilha p, int *valor){
    Ppilha l = p;
    if (p = NULL) return p;
    *valor = l->valor;
    l = l->prox;
    free(p);
    return l;
}
void pilha_vazia(Ppilha p){
    if (p!= NULL){
        pilha_vazia(p->prox);
        free(p);
    }
}
 
int main(){
    int valor, i, item1, item2, condicao = 0;
    char resposta[1025], c;
    Ppilha p = inicializacao_pilha();
    scanf("%s", resposta);
    for (i = 0, c = resposta[0]; c != '\0' && condicao == 0; i++, c = resposta[i]){
        if (c <= 57 && c >= 48)
        {
            valor = c - 48;
            p = push(p,valor);
            
        }else
        {
            if (p != NULL && p->prox != NULL){
                switch (c)
                {
                case 42:
                    p = pop(p, &item1);
                    p = pop(p, &item2);
                    p = push(p, item2 * item1);
                    break;
                
                case 43:
                    p = pop(p, &item1);
                    p = pop(p, &item2);
                    p = push(p, item2 + item1);
                    break;
                case 45:
                    p = pop(p, &item1);
                    p = pop(p, &item2);
                    p = push(p, item2 - item1); 
                    break;
                case 47:
                    p = pop(p, &item1);
                    p = pop(p, &item2);
                    p = push(p, item2 / item1);
                    break;
                default:
                    condicao = 1;
                    break;
                }
            }else
                condicao = 1;
        }
    }
    if (condicao == 0)
    {
        p = pop(p, &valor);
        if (p == NULL)
        {
            printf("%d", valor);
        }else
            printf("Invalid Expression");
    }else
        printf("Invalid Expression");
    
    pilha_vazia(p);
}