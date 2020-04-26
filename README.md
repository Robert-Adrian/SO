# SO

Realizați un program C care primește 2 argumente din linia de comandă: un director sursă și un director destinație.

Se va parcurge recursiv structura de directoare din directorul sursă. Pentru fiecare intrare din directorul sursă, se vor executa următoarele operații, în funcție de tipul intrării:

 *  Pentru directoare, se va crea un director echivalent în directorul destinație, cu aceleași drepturi ca directorul original. Astfel, structura de directoare din directorul destinație va fi asemănătoare cu cea din sursă.
 *  Pentru fișierele obișnuite, în funcție de dimensiunea fișierului se va crea o copie sau o legătura simbolică:
       1. Pentru fișierele mai mari de 500 octeți, se va crea o copie a fișierului în directorul destinație (și, după caz, în subfolderul echivalent). Aceste fișiere vor avea aceleași drepturi de acces ca și fișierele originale.
       2. Pentru celelalte fișiere, se vor crea legături simbolice către fișierul original. Aceste linkuri vor avea doar aceleași drepturi de read ca și fișierele originale. (Ex: dacă fișierul original are –rwx-wxr-x, linkul nou va avea –r-----r--)
 *  Pentru (soft) linkuri, nu se va executa nici o operație.

Tema va fi însoțita de fișierul makefile corespunzător.

R:

Programul parcurge recursiv directorul radacina. Daca intalneste alte directoare noi le creaza si apoi le apeleaza pe acelea pentru a cauta in ele. Daca intalneste fisiere mai mari de 500 de octeti le copiaza cu aceleasi drepturi. Daca intalneste fisiere mai mici sau egale de 500 de octeti atunci le creaza un link simbolic avand doar aceleasi drepturi de citire cu fisierul catre care se face link. 
Construirea drepturilor pentru fisier/director se face cu variabila file_mask in care adun fiecare drept/mode de citire/scriere/executie , iar rezultatul este folosit pentru a atribuii aceste drepturi si pentru directoare/fisiere sau pentrua a realiza o masca pentru a ramane link-urile doar cu drepturi de citire
