// Lucas Castelani Gouveia
// RA: 168877

#include <stdio.h>
#include <stdlib.h>
typedef struct Tno {
  int valor;
  struct Tno *prox;
} Tno;
typedef struct Tno *Pno;
typedef struct Tfila {
  Pno ini;
  Pno fim;
} Tfila;
typedef Tfila *Pfila;

Pfila inicializa() {
  Pfila f = (Pfila)malloc(sizeof(Tfila));
  f->ini = f->fim = NULL;
  return (f);
}

Pfila insere(Pfila fila, int tempo) {
  Pno novo = (Pno)malloc(sizeof(Tno));
  novo->valor = tempo;
  novo->prox = NULL;
  if (fila->ini == NULL) {
    fila->ini = novo;
    fila->fim = novo;
    return (fila);
  }
  fila->fim->prox = novo;
  fila->fim = novo;
  novo->prox = NULL;
  return (fila);
}
Pfila remove_elemento(Pfila fila, int *valor) {
  Pno p;
  if (fila->ini == NULL) {
    return fila;
  }
  *valor = fila->ini->valor;
  p = fila->ini;
  fila->ini = p->prox;
  if (fila->ini == NULL) {
    fila->fim = NULL;
  }
  free(p);
  return fila;
}
void fila_vazia(Pno p) {
  if (p != NULL) {
    fila_vazia(p->prox);
    free(p);
  }
}


//Eu achei, que não precisava fazer fila para os caixas, somente uma fila geral e 
//depois falar quais cliente forame m cada caixa, mas vou fazer e iserir nas filas de cada caixa, 
//por não ter entendido direito o enunciado do exercício, mas vai ser linhas de codigos a mais que não vao fazer nada pra contribuir para o codigo...
//fazendo isso pra evitar descontar nota atoa
int main() {
  int **filas;
  Pfila fila_total;
  Pfila *fcaixas;
  fila_total = inicializa();
  int n_cliente, n_caixas, tempo, aux, i, j, id_cliente = 1, seleciona_caixa,tempo_total;
  scanf("%d %d", &n_cliente, &n_caixas);
  //cria vetor de filas dos caixas e inicializa
  fcaixas = (Pfila *) malloc(n_caixas * sizeof(Pfila));
  for (i = 0; i < n_caixas; i++)
  {
    fcaixas[i] = inicializa();
  }
  
  filas = (int **)malloc(n_caixas * sizeof(int *));
  for (j = 0; j < n_caixas; ++j) {
    filas[j] = (int *)malloc((n_cliente + 1) * sizeof(int));
  }
  aux = n_cliente;
  for (i = 0; i < n_caixas; i++) {
    for (j = 0; j <= n_cliente + 1; j++) {
      filas[i][j] = 0;
    }
  }

  for (i = 0; i < n_cliente; i++) {
    scanf("%d", &tempo);
    fila_total = insere(fila_total, tempo);
  }

  for (j = 1; j <= aux; j++) {
    if (j == 1) {
      for (i = 0; i < n_caixas; i++) {
          if (fila_total->ini != NULL){
          fila_total = remove_elemento(fila_total, &tempo);
          fcaixas[i] = insere(fcaixas[i], tempo);
          filas[i][j] = id_cliente++;
        }
        filas[i][0] += tempo;
      }

    } else {
      for (i = 0; i < n_caixas; i++) {
        if (i == 0) {
          tempo_total = filas[i][0];
          seleciona_caixa = i;
        } else if (tempo_total > filas[i][0]) {
          seleciona_caixa = i;
          tempo_total = filas[i][0];
        }
      }
      if (fila_total->ini != NULL) {
        fila_total = remove_elemento(fila_total, &tempo);
        fcaixas[seleciona_caixa] = insere(fcaixas[seleciona_caixa], tempo);
        filas[seleciona_caixa][0] += tempo;
        filas[seleciona_caixa][j] = id_cliente++;
      }
    }
  }

  for (i = 0; i < n_caixas; i++) {
    for (j = 0; j <= n_cliente + 1; j++) {
      if (filas[i][j] != 0) {
        if (j == 0) {
          printf("%d: ", i + 1);
        } else {
          printf("%d ", filas[i][j]);
        }
      }
    }
    printf("\n");
  }
  for (j = 0; j < n_caixas; j++) {
    free(filas[j]);
    fila_vazia(fcaixas[j]->ini);
    free(fcaixas[j]);
  }
  free(filas);
  fila_vazia(fila_total->ini);
  free(fila_total);
  free(fcaixas);
}