//Lucas Castelani Gouveia 168877 Noturno
 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct arvore
{
    char tipo;
    float area;
    struct arvore *esq;
    struct arvore *dir;
}TArv;

typedef TArv *PArv;

PArv busca(PArv arv, float area){
    if (arv == NULL) return NULL;
    if (arv->area == area)return arv;
    if(arv->area > area) return busca(arv->esq, area);
    if(arv->area < area) return busca(arv->dir, area);
    return arv;
}
PArv insere(PArv arv, char tipo, float area){
    if (arv == NULL) {
        arv = (PArv)malloc(sizeof(TArv));
        arv->tipo=tolower(tipo);
        arv->area=area;
        arv->esq=NULL;
        arv->dir=NULL;
        return arv;
    }else if(busca(arv,area) == NULL){
        if(arv->area > area){
            arv->esq = insere(arv->esq, tipo, area);
        }else{
            arv->dir = insere(arv->dir, tipo, area);
        }
    }
    return arv;
}

int busca_tipo(PArv arv, char c, int qntd){
    if (arv == NULL) return qntd;
    if(arv->tipo == c) qntd = 1;
    qntd = busca_tipo(arv->esq,c,qntd);
    qntd = busca_tipo(arv->dir,c,qntd);
    return qntd;
}
void mostrar_arv(PArv arv, char tipo){
    if(arv == NULL)return;
    mostrar_arv(arv->esq, tipo);
    if (arv->tipo == tipo)
    {
        printf("%.1f ",arv->area);
    }
    mostrar_arv(arv->dir, tipo);
    
}
PArv remover (PArv arv,char tipo, float area) {
	PArv a = arv,ant, p;
	if (a == NULL) return NULL; 
    a->esq = remover(a->esq,tipo, area); 
    a->dir = remover(a->dir,tipo, area); 
    if (tipo == a->tipo && a->area < area)
    {
        if (a->esq == NULL && a->dir == NULL) { 
            free(a);
            return NULL;
        } else if (a->dir == NULL) {
            p = a->esq;
            free(a);
            return p;
        } else if (a->esq == NULL) { 
            p = a->dir;
            free (a);
            return p;
        } else {
            for (ant = a, p = a->esq; p->dir != NULL; ant = p, p = p->dir);
            a->area = p->area;
            a->tipo = p->tipo;
            if (ant == a) a->esq = p->esq;
            else ant->dir = p->esq;
            free(p);
        }
        
	}
	return arv;
}
void libera(PArv a){
    if(a == NULL) return;
    libera(a->esq);
    libera(a->dir);
    free(a);
}
int main(){
    char resposta, tipo;
    float raio,base,altura,area_ex;
    int count_c = 0, count_r = 0, count_t = 0;
    PArv arv = NULL;
    do
    {
        scanf("%c", &resposta);
        resposta = tolower(resposta);
        if (resposta == 'c')
        {
            scanf("%f", &raio);
            area_ex = raio * raio * 3.14159;
            arv = insere(arv, resposta, area_ex);
        }else if (resposta == 'r')
        {
            scanf("%f %f", &base, &altura);
            arv = insere(arv, resposta, base * altura);
        }else if (resposta == 't')
        {
            scanf("%f %f", &base, &altura);
            arv = insere(arv, resposta, (base * altura)/ 2);
        }else if (resposta == 'i')
        {
            
            count_c = busca_tipo(arv,'c',count_c);
            count_r = busca_tipo(arv,'r',count_r);
            count_t = busca_tipo(arv,'t',count_t);
            if (count_c > 0)
            {
                printf("circulo\n");
                mostrar_arv(arv,'c');
                printf("\n");
                count_c = 0;
            }
            if (count_r > 0)
            {
                printf("retangulo\n");
                mostrar_arv(arv,'r');
                printf("\n");
                count_r = 0;
            }if (count_t > 0){
                printf("triangulo\n");
                mostrar_arv(arv,'t');
                printf("\n");
                count_t = 0;
            }
        }else if (resposta == 'e')
        {
            scanf(" %c",&tipo);
            scanf("%f", &area_ex);
            arv = remover(arv, tipo, area_ex);
        }
    } while (resposta != 70 && resposta != 102);
    libera(arv);
}
