#include <stdio.h>
#include <string.h>  
#include <math.h>
#include <mpi.h>     

float calculoAreaRetangulo(float base, float altura){
        return base*altura;
    }
    
float calculoAltura(float valorX){
        //para ver outra função basta alterar aqui, a função para exemplo é f(x) = x^2+3x+5
        return pow(valorX,2)+valorX*3+5;
    }
    
int main(void) {
   float    resultado = 0;  
   int      comm_size;               
   int      my_rank;               
   float    soma = 0;
   int      limiteEsquerda = 0;
   int      limiteDireita = 50;
   
   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_size); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
    
    
    
    float valorBase = (limiteDireita - limiteEsquerda)/comm_size;
    printf("%.2f\n", valorBase);
   if (my_rank != 0) { 
      /* Criação da mensagem */
      
      float x = limiteEsquerda + my_rank * valorBase;
      float altura = calculoAltura(x);
      resultado = calculoAreaRetangulo(valorBase, altura);
      
      /* Envio da mensagem para o processo 0 */
      MPI_Send(&resultado, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
   } else {  
      /* Impressão da mensagem do processo centralizador */
      printf("Processo centralizador em execução: %d of %d!\n", my_rank, comm_size);
      
      for (int q = 1; q < comm_size; q++) {
         /* Recepção da mensagem do processo q */
         MPI_Recv(&resultado, 1, MPI_FLOAT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         
         soma += resultado;
         /* Impressão da mensagem do processo q */
         printf("O processo %d calculou uma area de: %.2f\n", q, resultado);
         if(q == comm_size - 1){
            soma+=calculoAreaRetangulo(valorBase,calculoAltura(0));
            printf("area total da forma: %.2f\n",soma);
         }
         
      }
   }

   /* Finaliza MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
