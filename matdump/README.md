# MatDump

Scrivere un programma che prende in ingresso un intero 'N' ('N' e' piccolo, es. <=512), alloca in memoria una matrice di NxN elementi float in modo che siano contigui in memoria. Inizializzare tale matrice (chiamata ad esempio M1) in modo arbitrario (ad esempio M1(i,j) = (i+j)/2.0). Fare quindi il salvataggio in un file della matrice sia in formato binario che in formato testuale in modo da ottenere due file separati 'mat_dump.dat' per il formato binario e 'mat_dump.txt' per quello testuale. Chiudere i file creati.

Scrivere un secondo programma (oppure estendere quello precedente) che prende in ingresso i nomi dei due file creati in precedenza e l'intero 'N', legge la matrice sia dal file 'mat_dump.dat' che dal file 'mat_dump.txt' memorizzandone il contenuto in due matrici distinte. Al termine dell'operazione di lettura, effettua il confronto delle due matrici con la funzione 'confronta' che deve essere implementata in modo “generico” cioe' deve prendere come argomenti un puntatore a funzione con tipo opportuno, i puntatori alle due matrici da confrontare e la size delle matrici. Il programma deve stampare l'esito del confronto. Testare il programma passando alla funzione 'confronta' la funzione di libreria memcmp (man 3 'memcmp').

Notare la differenza di size tra 'mat_dump.dat' e 'mat_dump.txt'.
