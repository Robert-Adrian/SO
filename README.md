# SO Tema 3

Se consideră un program C ce conţine două procese (părinte + fiu). Procesul părinte va trimite, printr-un pipe, timp de 5s caracterul “a” către procesul fiu, în plus la fiecare secundă o să trimită semnalul SIGUSR1. Procesul fiu va citi caracterele din pipe şi va realiza o statistică ce va conţine numărul total de caractere, precum şi numărul de caractere primite după fiecare semnal SIGUSR1. La final statistica va fi trimisă printr-un pipe procesului părinte ce o va afişa.

