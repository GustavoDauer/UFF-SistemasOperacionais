/******************************************************************************
 FILE: main.c
 Alunos: Gustavo Dauer

 Resposta questão 1
  A instrução de criação da thread é executada na ordem especificada pelo programa,
  porém a execução das threads é assincrona e fica a cargo do sistema operacional estabalecer uma ordem de execução.
  Assim, a saida visualizada confirma o fato de serem executadas na ordem escolhida
  pelo S.O. onde algumas vezes pode estar na ordem de criação ou não.


 ENUNCIADO

 1 - Faça um programa que crie N threads (N é um dado de entrada lido do teclado).
 A primeira thread criada é a "thread01", a segunda é a "thread02", e assim por diante.
 Cada thread, quando executar, deverá imprimir na tela "Eu sou a threadXX e meu ID é YY",
 onde YY é o ID que o sistema operacional dá para a thread (tipo pthread_t, primeiro campo
 da função pthread_create). Explique as saídas do programa quando este é executado.
 NÃO USE VARIÁVEIS GLOBAIS!!!
 */

#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct thread_data {
	int num_thread; // Armazena o numero da nossa thread! O ID pegaremos atraves da funcao pthread_self()
} THREAD_DATA;

void *PrintHello(void *threadarg) {
	THREAD_DATA *my_data;
	my_data = (THREAD_DATA*) threadarg;
	int tid = my_data->num_thread;
	printf("Eu sou a thread #%d e meu ID é %u \n", tid, pthread_self());
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
