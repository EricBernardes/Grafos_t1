#include <stdio.h>
#include <stdlib.h>

int **iniciaMatriz(int M) {
  int **vertices = (int **)malloc(M * sizeof(int *));
  if (vertices == NULL) {
    printf("Erro ao alocar memória\n");
    exit(1);
  }

  for (int i = 0; i < M; i++) {
    vertices[i] = (int *)malloc(2 * sizeof(int));
    if (vertices[i] == NULL) {
      printf("Erro ao alocar memória\n");
      exit(1);
    }
  }

  for(int i = 0; i < M; i++) {
    for(int j = 0; j < 2; j++) {
      vertices[i][j] = 0;
    }
  }

  return vertices;
}

int *iniciaEPreencheVetorVisit(int N) {
  int *visited = (int *)malloc(N * sizeof(int));

  if (visited == NULL) {
    printf("Erro ao Alocar Memória\n");
    exit(1);
  }

  for (int i = 1; i <= N; i++) {
    visited[i] = i;
  }

  return visited;
}

void liberaMatriz(int **vertices, int M) {
  for (int i = 0; i < M; i++) {
    free(vertices[i]);
  }
  free(vertices);
}

int find(int x, int *visited) {
  if (visited[x] != x) {
    printf("Visited[%d] - %d\n", x, visited[x]);
    printf("X - %d\n", x);
    visited[x] = find(visited[x], visited);
  }
  return visited[x];
}

int contarComponentes(int N, int **vertices, int M) {
  int *visited = iniciaEPreencheVetorVisit(N);

  for (int i = 0; i < M; i++) {
    int root1 = find(vertices[i][0], visited);
    int root2 = find(vertices[i][1], visited);
    if (root1 != root2) {
      visited[root1] = root2;
      N--;
    }
  }

  free(visited);

  return N;
}

int **leArquivo(char *arg, int *N, int* M) {
  FILE *f = fopen(arg, "r");

  if (f == NULL) {
    printf("Erro ao Abrir Arquivo\n");
    exit(1);
  }

  fscanf(f, "%d", N);
  fscanf(f, "%*[^\n]");
  fscanf(f, "%d", M);
  fscanf(f, "%*[^\n]");

  int **vertices = iniciaMatriz(*M);

  for (int i = 0; i < *M; i++) {
    int D, P;
    fscanf(f, "%d %d", &D, &P);
    vertices[i][0] = D;
    vertices[i][1] = P;
    fscanf(f, "%*[^\n]");
  }

  fclose(f);
  return vertices;
}



int main(int argc, char *argv[]) {
  int N = 0;
  int M = 0;

  int **vertices = leArquivo(argv[1], &N, &M);

  if (M == 0) {
    printf("FALTAM %d ESTRADAS\n", N - 1);
    return 0;
  }

  printf("*************\n");
  
  int componentes = contarComponentes(N, vertices, M);

  liberaMatriz(vertices, M);

  if (componentes == 1) {
    printf("PROMESSA CUMPRIDA\n");
  } else {
      printf("FALTAM %d ESTRADAS\n", componentes - 1);
  }


  return 0;
}