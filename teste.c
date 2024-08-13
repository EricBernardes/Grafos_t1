#include <stdio.h>
#include <stdlib.h>

//int N;

/* void BProfundidade(int conjuntoArestasConexas[N][N]) {
  int cont = 0;
  int visit[N];
  for(int i = 0; i < N; i++) {
    if(visit[i] == -1) {
      BP(conjuntoArestasConexas, i ,visit, cont);
    }
  }
}

BP(int conjuntoArestasConexas[N][N], int v, int visit[], int cont) {
  visit[v] = ++cont;
  printf("%d ", v);
  for(int i = 0; i < M; i++) {
  }
} */

int find(int x, int visited[]) {
    if (visited[x] != x) {
        visited[x] = find(visited[x], visited);  // Compressão de caminho
    }
    return visited[x];
}

int contarComponentes(int N, int vertices[][2], int M) {
    int visited[N];
    
    // Inicialmente, cada nó é seu próprio pai
    for (int i = 0; i < N; i++) {
        visited[i] = i;
    }

    // Itera sobre cada aresta
    for (int i = 0; i < M; i++) {
        int root1 = find(vertices[i][0], visited);
        int root2 = find(vertices[i][1], visited);
        if (root1 != root2) {
            visited[root1] = root2;  // Operação de união
            N--;  // Diminui a contagem de componentes
        }
    }
    
    return N;
}

int main(int argc, char *argv[]) {
  FILE *f = fopen(argv[1], "r");
  

  if (f == NULL) {
    printf("Error opening file!\n");
    exit(1);
  }

  int N = 0;
  int M = 0;

  fscanf(f, "%d", &N);
  fscanf(f, "%*[^\n]");
  fscanf(f, "%d", &M);
  fscanf(f, "%*[^\n]");

  if(M==0) {
    printf("FALTAM %d ESTRADAS\n", N-1);
    return 0;
  }


  /* int adjMatrix[N][N];

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      adjMatrix[i][j] = 0;
    }
  }

  for(int i = 0; i < M; i++) {
    int D, P;
    fscanf(f, "%d %d", &D, &P);
    adjMatrix[D-1][P-1] = 1;
    fscanf(f, "%*[^\n]");
  }

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      printf("%d ", adjMatrix[i][j]);
    }
    printf("\n");
  } */

  int vertices[M][2];
  for(int i = 0; i < M; i++) {
    int D, P;
    fscanf(f, "%d %d", &D, &P);
    vertices[i][0] = D;
    vertices[i][1] = P;
    fscanf(f, "%*[^\n]");
  }

  for(int i = 0; i < M; i++) {
    for(int j = 0; j < 2; j++) {
      printf("%d ", vertices[i][j]);
    }
    printf("\n");
  }


   int components = contarComponentes(N, vertices, M);

  if(components == 1) {
    printf("PROMESSA CUMPRIDA\n");
  } else {
    printf("FALTAM %d ESTRADAS\n", components-1);
  }

  /* printf("N = %d\n", N);
  printf("M = %d\n", M); */

  return 0;
}