# PC Threads

Scrivere un programma C con due threads, un produttore (P) ed un consumatore (C). Il thread P genera, uno alla volta, una sequenza di numeri inserendoli in un buffer di una sola posizione condiviso con il thread C. Il thread consumatore estrae i numeri dal buffer e li stampa sullo standard output. Se il buffer e' pieno P attende che C consumi il dato, analogamente se il buffer e' vuoto C attende che P produca un valore da consumare.
