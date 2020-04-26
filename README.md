# SO
Să se realizeaze un script ce colectează şi afişează informaţii despre sistemul de operare.

Scriptul va afişa un meniu cu următoarele opţiuni:

1. Ieşire

2. Afişează informaţii masina (numele serverului, tipul masinii-procesorului, tipul sistemului de operare) şi calea curentă (vezi $HOSTNAME, $HOSTTYPE, $OSTYPE)

3. Afișați data în format UTC (vezi date) 

4. Afişarea primelor 2 shell-urilor instalate în sistem (vezi /etc/shells) 

5. Afişarea pentru toţi utilizatorii din sistem a numelui de login şi a directorului de home (vezi /etc/passwd)

6. Afişare ultimele linii incepand cu linia 9 din fisierul /etc/protocols (vezi tail)

7. Afişare tip procesor şi frecvenţa de rulare (vezi /proc/cpuinfo)

8. Scrieți comanda ls care afișeaza toate numele de directoare din directorul /proc ce reprezintă imaginea unui proces pe disc (numele directorului conține doar cifre)

9. Afişare şi căutare în log-uri:

1. Se vor afişa fişierele de log (vezi /var/log) arhivate (nu şi cele curente)

2. Sa se afiseze toate fisierele de log. Utilizatorul va introduce un nume de fişier de log (ori curent ori arhivat) şi se va căuta un text introdus de la tastatură de catre utilizator.

Pentru căutarea în fişierele arhivate ale logului vezi gunzip -c
