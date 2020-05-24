#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

pid_t pid_fiu;
int stare = 0, descSend[2], descRecv[2], bytes_read, received = 0, secunde = 5, send = 0;
char character = 'a', buffer;

//rutina de tratare a semnalelor
void handler(int sign) {
	if (sign == SIGALRM) {
		// daca evenimentul produs de alarma setata la 5 secunde a avut loc, o sa fie trimis semnalul SIGALRM
		// o sa fie schimbata starea pentru a putea iesii din bucla while din procesul parinte si
		// o sa se opreasca procesul fiu trimitand semnalul SIGINT
		stare = 1;
		kill(pid_fiu, SIGINT);
	} else if (sign == SIGUSR1) {
		// daca semnalul trimis este SIGUSR1, inseamna ca este apelat de procesul fiu, se trece variabila
		// received pe 1 pentru a se putea contoriza numarul de caractere in procesul fiu si variabila send se
		// trece pe 0 pentru a marca in procesul parinte faptul ca semnalul a fost trimis si receptionat cu succes
		printf("!!! Semnal SIGUSR1 receptionat !!!\n");
		received = 1;
		send = 0;
	} 
}

int main() {
	pipe(descSend);
	pipe(descRecv);
	pid_fiu = fork();

	if (pid_fiu == 0) {
		// cand evenimentul produs de alarma are loc la 5 secunde atunci procesul fiu
		// este oprit si nu o sa se ia in calcul si ultimul caracter trimis prin pipe
		// si pun contorApar sa inceapa de la 1 si nici al 5 -lea semnal nu o sa poata
		// fii receptionat
		int contorSig = 0, contorApar = 1;
		close(descSend[1]);
		close(descRecv[0]);

		// trimitem semnalul catre rutina de tratare
		signal(SIGUSR1, handler);

		while (1) {
			bytes_read = read(descSend[0], &buffer, 1);			
			if (bytes_read != 0) {
				if (buffer == character)						
					contorApar++;
				// daca caracterul primit prin pipe este a si semnalul SIGUSR1 a fost receptionat atunci contorizam
				if ((buffer == character) && (received == 1)) {
					contorSig++;
				}
				//trimitem prin pipe statistica
				write(descRecv[1], &contorSig, sizeof(contorSig));
				write(descRecv[1], &contorApar, sizeof(contorApar));
				contorSig = 0;
				received = 0;
			}
			sleep(1);
		}
		
	} else {
		
		close(descSend[0]);
		close(descRecv[1]);
		signal(SIGALRM, handler);
		alarm(secunde); 
		int cA, cS;
		int sig[secunde - 1];
		int i = 0, nr_semnale = 0;
		while (!stare) {
			sleep(1);
			printf("\nCaracter trimis: %c\n", character);	
			write(descSend[1], &character, 1);
			printf("Semnal SIGUSR1 trimis\n");
			send = 1;
			nr_semnale++;

			// trimitem semnalul SIGUSR1 catre procesul fiu
			kill(pid_fiu, SIGUSR1);
			int n1, n2;
			n1 = read(descRecv[0], &cS, sizeof(cS));
			n2 = read(descRecv[0], &cA, sizeof(cA));
			if (n1 != 0) {
				sig[i] = cS;
				i++;
			}
		}
		if (send == 1)
			printf("??? Semnalul SIGUSR1 nu a putut fi receptionat ???\n");

		//pe langa statistica din enunt am adaugat si numarul de semnale trimise si numarul de semnale receptionate
		printf("\n\nSemnale SIGUSR1 trimise: %d\n", nr_semnale);
		printf("Semnale SIGUSR1 receptionate: %d\n", i);
		printf("Numarul de caractere primite dupa fiecare semnal SIGUSR1: ");
		for (int j = 0; j < i; j++) {
			printf("%d ", sig[j]);
		}
		printf("\nNumarul total de caractere: %d\n\n", cA);
			
	}	
 return 0;
}
