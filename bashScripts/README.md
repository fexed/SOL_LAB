# Bash Scripts

Vari script bash

## SortedUsers
Estrarre dal file /etc/passwd la lista di tutti gli utenti della macchina utilizzando il comando cut (vedere slide su introduzione bash e manuale di cut). Ordinare alfabeticamente la lista ottenuta utilizzando il comando sort (vedere man 1 sort).
NB: fare attenzione al seguente messaggio di warning contenuto nel manuale del comando sort:
“The locale specified by the environment affects sort order. Set LC_ALL=C to get the traditional sort order that uses native byte values.”

## TarIfDir
Scrivere uno script bash che prende come argomento un nome di directory, esegue il controllo che la directory esista e sia leggibile (opzione '-d' e '-r' del comando 'if') e restituisce un file in formato 'nodedirectory.tar.gz' contenente l'archivio compresso della directory passata come argomento.

## DirWordMins
Scrivere uno script bash che dati come argomenti un nome di directory una parola ed un numero N, stampa la lista di tutti i nomi di file contenuti nella directory che sono stati modificati negli ultimi N minuti e che contengono la parola passata come secondo argomento. Per cercare nella directory passata come argomento usare il comando find, per trovare i file modificati meno di N minuti fa utilizzare l'opzione '-mmin' di find – leggere il manuale man 1 find.
