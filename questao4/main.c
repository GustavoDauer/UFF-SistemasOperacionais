/******************************************************************************
  FILE: main.c
  Alunos: Gustavo Dauer
 *
  O linux não faz distinção entre processos e threads, ele usa um conceito mais
  genérico que é o de tarefas (tasks).
  pthread_self retorna a identificação da thread criada em relação pthread(identificao interna),
  enquanto gettid retorna um id da task correspondente a thread.
  Para efeito de curiosidade, tambem usei a funcao getpid(), que retorna o mesmo valor para todas threads,
  conforme esperado, pois esta retorna o ID do processo de onde partem as threads.

  ENUNCIADO

 4 - Tanto pthread_self() quanto gettid() retornam o ID da thread.
 Altere o programa do exercício 1 para imprimir a ID da thread usando ambas funções.
 Elas retornam o mesmo valor?
 Se não, pesquise qual a diferença entre elas.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdlib.h>

typedef struct thread_data {
	int num_thread; // Armazena o numero da nossa thread! O ID pegaremos atraves da funcao pthread_self()
} THREAD_DATA;

void *PrintHello(void *threadarg) {
	THREAD_DATA *my_data;
	my_data = (THREAD_DATA*) threadarg;
	int tid = my_data->num_thread;
	printf("Eu sou a thread #%d e meu ID (pthread_self) é %u | meu ID (syscall(SYS_gettid)) é %ld | meu ID (getpid) é %ld \n", tid, pthread_self(), syscall(SYS_gettid), getpid());
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	int total_threads = 0, rc = 0, t = 0;

	printf("Digite o numero de threads: ");
	scanf("%d", &total_threads);

	THREAD_DATA thread_data_array[total_threads];
	pthread_t threads[total_threads];

	for (t = 0; t < total_threads; t++) {
		thread_data_array[t].num_thread = t;

		rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &thread_data_array[t]);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc); // Problema na criacao da thread - exibe o codigo do erro
			exit(-1);
		}
	}

	pthread_exit(NULL);
}
