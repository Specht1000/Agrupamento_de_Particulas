// Guilherme Specht e Matheus Santos
// Código que simula um agrupamento de partículas, trabalho da
// cadeira Linguagem C para Engenharia da UFRGS.
// Última atualização: 22/02/2024

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimi(int **matriz, int tamanho_matriz);
int gerar_particula(int **matriz, int tamanho_matriz);
int** build_matrix(int tamanho_matriz);
void move_particula(int **matriz, int tamanho_matriz, int numero_particula);


void imprimi(int **matriz, int tamanho_matriz) {
  for (int i = 0; i < tamanho_matriz; i++) {
        for (int j = 0; j < tamanho_matriz; j++) {
            printf("%d", matriz[i][j]);
        }
        printf("\n");
  } 
}

int gerar_particula(int **matriz, int tamanho_matriz) {
  int i, j;
   
  do{
     i = rand() % tamanho_matriz;
     j = rand() % tamanho_matriz;
  }while(matriz[i][j] == 1);
  matriz[i][j] = 1;
  // Convertendo coordenadas 2D para 1D.
  return i * tamanho_matriz + j;
}

int** build_matrix(int tamanho_matriz) {
    int **mat, i, j;

    // Alocação dinâmica para a matriz
    mat = malloc(tamanho_matriz * sizeof(int*));
    for (i = 0; i < tamanho_matriz; i++) {
        mat[i] = malloc(tamanho_matriz * sizeof(int));
    }

    // Atribuir valor zero para a matriz
    for (i = 0; i < tamanho_matriz; i++) {
        for (j = 0; j < tamanho_matriz; j++) {
            mat[i][j] = 0;
        }
    }

    // Definir o valor 1 em uma posição aleatória da matriz
    srand(time(NULL));
    int i_aleatorio = rand() % tamanho_matriz;
    int j_aleatorio = rand() % tamanho_matriz;
    mat[i_aleatorio][j_aleatorio] = 1;

    // Imprimir a matriz
    imprimi(mat, tamanho_matriz);

    return mat;
}

void move_particula(int **matriz, int tamanho_matriz, int numero_particulas) {
  int direcao; 
  int particulas = 0; 
  
  while(particulas < numero_particulas-1) {
    int nova_posicao = gerar_particula(matriz, tamanho_matriz);
    // Convertendo coordenadas 1D para 2D.
    int i_nova = nova_posicao / tamanho_matriz;
    int j_nova = nova_posicao % tamanho_matriz;
    matriz[i_nova][j_nova] = 1;

    printf("\n");
    imprimi(matriz, tamanho_matriz);

    while(1){
      direcao = rand() % 4;

      // Se os vizinhos forem 1
      if(((i_nova > 0) && (matriz[i_nova - 1][j_nova] == 1)) ||
          ((i_nova < tamanho_matriz - 1) && (matriz[i_nova + 1][j_nova] == 1)) ||
          ((j_nova > 0) && (matriz[i_nova][j_nova - 1] == 1)) ||
          ((j_nova < tamanho_matriz - 1) && (matriz[i_nova][j_nova + 1] == 1))) {
        break;
      }
      
        
         // Move para cima
          if((direcao==0) && (i_nova > 0)) {
            matriz[i_nova][j_nova] = 0;
            i_nova--;
            matriz[i_nova][j_nova] = 1;
            printf("\n");
            imprimi(matriz, tamanho_matriz);
          }
          
        
        // Move para baixo
          if((direcao==1) && (i_nova < tamanho_matriz - 1)) {
            matriz[i_nova][j_nova] = 0;
            i_nova++;
            matriz[i_nova][j_nova] = 1; 
            printf("\n");
            imprimi(matriz, tamanho_matriz);
          }     
        
        // Move para esquerda
          if((direcao==2) && (j_nova > 0)) {
            matriz[i_nova][j_nova] = 0;
            j_nova--;
            matriz[i_nova][j_nova] = 1; 
            printf("\n");
            imprimi(matriz, tamanho_matriz);
          }
        
        // Move para direita
          if((direcao==3) && (j_nova < tamanho_matriz - 1)) {
            matriz[i_nova][j_nova] = 0;
            j_nova++;
            matriz[i_nova][j_nova] = 1; 
            printf("\n");
            imprimi(matriz, tamanho_matriz);
          }
        
  }

    particulas++;
 }
}

int main() {
    // Definir o tamanho da matriz
    int tamanho_matriz;
    int numero_particulas; 
  
  do {
    printf("Defina o tamanho 'n' da matriz (n>3): ");
    scanf("%d", &tamanho_matriz);
    if(tamanho_matriz<=3) {
      printf("!Erro digite o valor novamente!\n\n");
    }
  }
    while(tamanho_matriz<=3);

    printf("\n");

    do {
    printf("Digite o numero de particulas 'N' ao qual deseja ver no programa ('N' precisa ser maior que 1 e menor que 'n'): ");
    scanf("%d", &numero_particulas);
      if((numero_particulas<=1)||(numero_particulas>tamanho_matriz)) {
        printf("!Erro digite o valor novamente!\n\n");
      }
      }
      while((numero_particulas<=1)||(numero_particulas>tamanho_matriz));

    printf("\n");
  
    int **matriz = build_matrix(tamanho_matriz);
    move_particula(matriz, tamanho_matriz, numero_particulas);

    // Desalocar memória da matriz na função main
    for (int i = 0; i < tamanho_matriz; i++) {
        free(matriz[i]);
    }
    free(matriz);

    printf("\n\n\n\n");

    return 0;
}
