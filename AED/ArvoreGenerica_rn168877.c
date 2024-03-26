//Lucas Castelani Gouveia 168877 Noturno
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct Arvore
{
    char nome[20];
    int dia,mes,ano;
    struct Arvore *irmao;
    struct Arvore *filho;
}Tarv;
typedef Tarv* PArv;
 
PArv busca(PArv arv, char *contratador, PArv pai) {
    if (arv == NULL)
        return NULL;
 
    if (strcmp(arv->nome, contratador) == 0)
        return arv;
 
    PArv resultado = busca(arv->filho, contratador, arv);
 
    if (resultado != NULL)
        return resultado;
 
    return busca(arv->irmao, contratador, pai);
}
PArv busca_Pai(PArv arv, char *filho) {
    PArv resultado = arv->filho, no_inicial = arv->filho, pai = arv;
    if (arv == NULL)return NULL;
    while (resultado != NULL && strcmp(resultado->nome, filho) != 0)
    {
        resultado = resultado->irmao;
        if (resultado == NULL)
        {
            resultado = no_inicial->filho;
            no_inicial = resultado;
            if(no_inicial != NULL) pai = pai->filho;
        }
    }
    if (resultado == NULL)return NULL;
    return pai;
}
PArv cria_no(PArv arv,char *nome,int dia,int mes,int ano, char *contratador){
    PArv pai, aux1, aux2, aux3, novo, repetido;
    if (strcmp(contratador, "fundador") == 0)
    {
        arv = (PArv)malloc(sizeof(Tarv));
        strcpy(arv->nome, nome);
        arv->dia=dia;
        arv->mes=mes;
        arv->ano=ano;
        arv->filho = NULL;
        arv->irmao = NULL;
        return arv;
    }
    if (arv != NULL)
    {
       repetido = busca(arv, nome, arv);
        pai = busca(arv, contratador, arv);
        if (pai!= NULL && repetido == NULL)
        {
            novo = (PArv) malloc(sizeof(Tarv));
            novo->ano = ano;
            novo->mes = mes;
            novo->dia = dia;
            strcpy(novo->nome, nome);
            novo->filho = NULL;
            aux3 = pai->filho;
            if (aux3 != NULL && aux3->irmao != NULL)
            {
            for (aux1 = aux3, aux2 = aux3->irmao; aux2 != NULL && ano > aux2->ano || (ano == aux2->ano && (mes > aux2->mes || (mes == aux2->mes && dia > aux2->dia))); aux1 = aux2, aux2 = aux1->irmao);
                    if (aux2 != NULL &&(aux1->dia == aux2->dia && aux1 ->mes == aux2->mes && aux1->ano == aux2->ano))
                    {
                        novo->irmao = aux2->irmao;
                        aux2->irmao = novo;
                    }else{
                        novo->irmao = aux1->irmao;
                        aux1->irmao = novo;        
                    }
                    if (aux1->irmao == aux2)
                    {
                        pai->filho = novo;
                    }
                
            }else if(aux3 != NULL){
                if (ano > aux3->ano || (ano == aux3->ano && (mes > aux3->mes || (mes == aux3->mes && dia > aux3->dia))))
                {
                    novo->irmao = aux3->irmao;
                    aux3->irmao = novo;
                    
                }else if(aux3->dia == dia && aux3 ->mes == mes && aux3->ano == ano){
                    novo->irmao = aux3->irmao;
                    aux3->irmao = novo;
                }else{
                    novo->irmao = aux3;
                    pai->filho = novo;
                }
            }else{
                pai->filho = novo;
                novo->irmao = NULL;
            }
        }
    }
    return arv;
}
void liberar_arvore(PArv arv) {
    if (arv == NULL || arv->filho == NULL)
        return;
    liberar_arvore(arv->filho);
    liberar_arvore(arv->filho->irmao);
 
    free(arv->filho);
}
 
void remove_no(PArv arv, char *nome){
    PArv aux, irmao_anterior;
    aux = busca_Pai(arv, nome);
    if (aux == NULL) return;
    irmao_anterior = aux->filho;
    if (strcmp(irmao_anterior->nome,nome) == 0)
    {
        aux->filho = aux->filho->irmao;
        liberar_arvore(irmao_anterior);
    }else{
        while (irmao_anterior->irmao != NULL && strcmp(irmao_anterior->irmao->nome, nome) != 0)
        {
            irmao_anterior = irmao_anterior->irmao;
        }
        aux = irmao_anterior->irmao;
        irmao_anterior->irmao = irmao_anterior->irmao->irmao;
        liberar_arvore(aux);
    }
    
}
 
 
 
void mostrar_nomes(PArv arv){
    if(arv == NULL)return;
    printf("%s\n",arv->nome);
    mostrar_nomes(arv->filho);
    mostrar_nomes(arv->irmao);
}
 
 
 
int main (){
    int resposta, dia, mes, ano;
    char nome[20], contratador[20];
    PArv arv = NULL;
    do
    {
        scanf("%d", &resposta);
        switch (resposta)
        {
        case 1:
            scanf("%s %d %d %d %s", nome, &dia, &mes, &ano, contratador);
            arv = cria_no(arv,nome,dia,mes,ano,contratador);
            break;
        case 2:
            scanf("%s", nome);
            remove_no(arv, nome);
            break;
 
        case 3:
            mostrar_nomes(arv);
            break;
        }
    } while (resposta != 4);
    
 
}