# Macro
Dato il seguente codice C

```
#define dimN 16
#define dimM  8
int main() {
    long *M = malloc(dimN*dimM*sizeof(long));
    CHECK_PTR(M, "malloc"); 
    for(size_t i=0;i<dimN;++i)
	for(size_t j=0;j<dimM;++j)			
	    ELEM(M,i,j) = i+j;    
    
    PRINTMAT(M, dimN, dimM);
    return 0;
}
```
scrivere le 3 macros CHECK_PTR, ELEM e PRINTMAT. 'CHECK_PTR' prende due argomenti, un puntatore ed una stringa. La macro controlla che il primo argomento sia 'NULL' ed in tal caso stampa utilizzando la funzione di librerie perror (man 3 'perror') la stringa passata come secondo argomento prima di uscire dal programma con EXIT_FAILURE (man 3 'exit'). 'PRINTMAT' stampa la matrice passata come primo argomento. Al suo interno PRINTMAT usa la macro ELEM per accedere agli elementi della matrice.

Esempio di output richiesto:

```
Stampo la matrice M:
   0    1    2    3    4    5    6    7 
   1    2    3    4    5    6    7    8 
   2    3 ....
```
