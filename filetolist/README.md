# File To List

Scrivere un programma C che dato un file testuale come argomento, inserisca tutte le parole del file in una lista ordinando le parole alfabeticamente. Ogni linea del file testuale puo' contenere piu' parole. Implementare la seguente interfaccia:
```
list_t *createList();                         // crea una lista vuota   
int     destroyList(list_t *L);               // libera tutta la memoria allocata dalla lista
int     insertList(list_t *L, const char *);  // inserisce una parola nella lista
void    printList(list_t *L);                 // stampa tutta la lista
```
Fornire i metodi di creazione e gestione della lista in una libreria statica (libList.a). Scrivere il Makefile per creare la libreria e generare l'eseguibile.
