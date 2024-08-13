#include <stdio.h>
#include <stdlib.h>

int find(int x, int visited[]) {
    if (visited[x] != x) {
        visited[x] = find(visited[x], visited);
    }
    return visited[x];
}

int contarComponentes(int N, int vertices[][2], int M) {
    int visited[N];
    
    for (int i = 0; i < N; i++) {
        visited[i] = i;
    }

    for (int i = 0; i < M; i++) {
        int root1 = find(vertices[i][0], visited);
        int root2 = find(vertices[i][1], visited);
        if (root1 != root2) {
            visited[root1] = root2;
            N--;
        }
    }
    
    return N;
}

int main(int argc, char *argv[]) {
  FILE *f = fopen(argv[1], "r");

  if (f == NULL) {
    printf("Erro ao Abrir Arquivo\n");
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

  int componentes = contarComponentes(N, vertices, M);

  if(componentes == 1) {
    printf("PROMESSA CUMPRIDA\n");
  } else {
    printf("FALTAM %d ESTRADAS\n", componentes-1);
  }

  return 0;
}