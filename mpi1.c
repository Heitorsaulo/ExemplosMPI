#include <stdio.h>
#include <string.h>  
#include <mpi.h>     
#include <math.h>

int main(void) {
   int        comm_sz;               /* Número de processos    */
   int        my_rank;               /* Rank   do processo     */

   /* Inicia MPI */
   MPI_Init(NULL, NULL); 

   /* Obter número de processos */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* Obter rank (id) do processo */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
   
   int x = 4;
   
   if(my_rank == 0){
      x = sqrt(x);
      printf("sou jão: %d, valor: %d\n", my_rank, x);
   } else{
      x = x*x;
      printf("sou pedrão : %d, valor: %d\n", my_rank, x);
   }
   //printf("Número de processos: %d Rank do processos corrente: %d \n", comm_sz, my_rank);

   /* Encerra MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */
