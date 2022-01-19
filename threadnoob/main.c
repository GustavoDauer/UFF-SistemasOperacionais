/******************************************************************************
* FILE: main.c
* Alunos: Gustavo Dauer
* 		  Pablo Moreira
*
* Resposta questão 1
*  A instrução de criação da thread é executada na ordem especificada pelo programa,
*  porém a execução das threads é assincrona e fica a cargo do sistema operacional,
*  assim, a saida visualizada confirma o fato de serem executadas na ordem escolhida
*  pelo S.O. onde algumas vezes pode estar na ordem de criação ou não.
******************************************************************************/


#include <pthread.h>
#include <stdio.h>

void *PrintHello(void *threadid)
{
   long tid;

   tid = (long)threadid;
   printf("Eu sou a thread #%ld e meu ID é %u \n", tid,pthread_self());
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	int total_threads = 0;
	printf("Digite o número de threads: ");
	scanf("%d",&total_threads);
	pthread_t threads[total_threads];
   int rc;
   long t;
   for(t=0; t<total_threads; t++){

	  //printf("Eu sou a thread %d: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   /* Last thing that main() should do */
   pthread_exit(NULL);
}
