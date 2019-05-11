CC	= gcc -std=c99   # quale compilatore usare per compilare il codice
CFLAGS	= -g -Wall -pthread # flags passati al compilatore per debugging e warning etc..
OPTFLAGS= -O3            # flags passati al compilatore per ottimizzazione del codice
INCLUDES= -I.            # path dove si trovano gli include (non di sistema)
LDFLAGS = -L.            # path dove so trovano le librerie
LIBS    =                # vanno messe qui le librerie da linkare

SOURCES=$(wildcard *.c)  # considera tutti i file .c nella directory 
BINS=$(SOURCES:.c=)      # rimuove il suffisso .c dalla lista SOURCES

.PHONY: all clean cleanall

# personalizziamo la generazione dell'eseguibile da un .c utilizzando una Pattern Rule
# Pattern Rules documentation:  
# https://www.gnu.org/software/make/manual/html_node/Pattern-Rules.html
%: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)

# prima regola contenente il target
all: $(BINS)

clean:
	\rm -f *~

cleanall: clean
	\rm -f $(BINS)