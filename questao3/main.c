/******************************************************************************
 * FILE: main.c
 * Alunos: Gustavo Dauer
 *
 * Resposta questão 3
 * A funcao wait() espera um child terminar retornando seu id para o processo pai.
 * Porem como, na concepcao da questao 2, utilizei a funcao wait conforme exemplificado no manual Unix Process,
 * nos levando a uma execucao sequencial dos processos, modifiquei o switch de forma a nao haver espera do termino do child.
 * Assim, fazendo o wait dentro de uma iteracao de N processos, pude notar uma execucao assincrona dos processos, uma vez que,
 * eles sao executados com a condicao de esperar que um child termina (qualquer child), levando a saidas nao sequenciais.
 * Desse modo, usando o comando break no default do switch (area onde ja estariamos no processo pai) para nao "sequenciar" os processos,
 * podemos observar esse efeito.
 ******************************************************************************/

/*
 ENUNCIADO

 3 - Repita o exercício 2, desta vez chamando a função wait() N vezes no processo pai antes de imprimir
 "Eu sou o pai e meu PID é XX".
 Rode algumas vezes e compare as saídas.
 Explique o resultado.
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {

	int total = 0, child_status, i;
	pid_t child_pid;

	printf("Digite o número de processos: ");
	scanf("%d", &total);

	for (i = 1; i <= total; i++) {

		child_pid = fork();

		switch (child_pid) {
		case -1:
			perror("fork");
			exit(1);
		case 0:
			printf("Eu sou o %dº filho e meu PID é %ld\n", i, getpid());
			exit(0);

		default:
			break;
			//wait(&child_status);
		}
	}

	for (i = 1; i <= total; i++) {
		wait(); // Espera um child terminar, porem como ja foi chamada no switch, a saida ficara identica a da questao 2!
				// Desse modo, usando o comando break para nao "sequenciar" os processos, podemos observar o efeito explicado acima
	}

	printf("Eu sou o pai e meu PID é %ld \n", getpid());
}
