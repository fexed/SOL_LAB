# MyCp

Scrivere un programma, utilizzando chiamate di sistema, che implementi l'equivalente del comando Unix cp. Il programma deve accettare 3 argomenti come segue:

```
mycp_sc filein fileout [buffersize]
```

L'argomento 'buffersize' e' la dimensione del buffer da utilizzare per le letture e scritture con le SC read e write (se non specificato assegnare un valore di default, es. 256bytes): Realizzare quindi lo stesso programma, utilizzando le chiamate di libreria fread ed fwrite. Chiamiamo questa seconda versione 'mycp_std'. Confrontare le prestazioni (usando il comando time) del programma 'mycp_sc' e 'mycp_std' al variare del parametro 'buffersize' (provare un po' di casi: 1 4 8 16 32 ….. 8192). Che cosa si nota ?
Opzionale (homework) : scrivere uno script bash che lanciato da una regola del makefile esegue mycp_sc e mycp_std scrivendo i risultati in due file separati. Plottare i dati dello 'user' e 'sys' time con gnuplot.
