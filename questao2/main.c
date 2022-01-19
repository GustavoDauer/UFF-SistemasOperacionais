/******************************************************************************
* FILE: main.c
* Alunos: Gustavo Dauer
*
* Resposta questão 2
* O objetivo do "process scheduling" é manter a CPU ocupada o tempo inteiro e
* entregar respostas para todos os programas. A forma como isso é implementado
* é através de filas, o que fica evidente na saída do programa abaixo onde, é
* respeitada a ordem de criação dos processos.
*
******************************************************************************/

/*
ENUNCIADO

2 - Faça um programa em que o processo principal cria N processos (N é um dado de entrada lido do teclado).
Cada processo filho imprime "Eu sou o i-ésimo filho e meu PID é XX", onde 'i' expressa a ordem de criação.
O processo pai imprime "Eu sou o pai e meu PID é XX". Rode algumas vezes e compare as saídas.
Explique o resultado.

Dica: getpid() retorna o PID de um processo.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {

	int total = 0, child_status, i;
	pid_t child_pid;

	printf("Digite o número de processos: ");
	scanf("%d",&total);

	for (i = 1; i <= total; i++) {
		child_pid = fork();

		switch (child_pid) {
		case -1:
			perror("fork");
			exit(1);
		case 0:
			printf("Eu sou o %dº filho e meu PID é %ld\n", i,getpid());
			exit(0);

		default:

			wait(&child_status);
		}
	}
	printf("Eu sou o pai e meu PID é %ld \n",getpid());

}
