#include <stdio.h>
#include <string.h>  
#include <math.h>
#include <mpi.h>     

const int MAX_STRING = 100;

int main(void) {
   int      resultado = 0;  
   int      comm_size;               
   int      my_rank;               
   int      soma = 1;
   
   MPI_Init(NULL, NULL); 
   MPI_Comm_size(MPI_COMM_WORLD, &comm_size); 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 


   if (my_rank != 0) { 
      /* Criação da mensagem */
      resultado = pow(2,my_rank);
      
      /* Envio da mensagem para o processo 0 */
      MPI_Send(&resultado, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
   } else {  
      /* Impressão da mensagem do processo centralizador */
      printf("Processo centralizador em execução: %d of %d!\n", my_rank, comm_size);
      
      for (int q = 1; q < comm_size; q++) {
         /* Recepção da mensagem do processo q */
         MPI_Recv(&resultado, 1, MPI_INT, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
         
         soma += resultado;
         /* Impressão da mensagem do processo q */
         printf("O processo %d recebeu a seguinte mensagem: 2^%d = %d e a soma acumulada é: %d\n", my_rank, q, resultado, soma);
         if(q == comm_size - 1){
             printf("%d\n",soma);
         }
         
      }
   }

   /* Finaliza MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
