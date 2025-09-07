# PROGRAMA
    PROG = main
    OBJS = utils.o gauss_seidel_edo.o main.o

# Compilador
    CC     = gcc

# Acrescentar onde apropriado as opções para incluir uso da biblioteca LIKWID
    CFLAGS = -O0 -g
    LFLAGS = -lm

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = ${USER}

.PHONY: all clean purge dist

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(PROG)

$(PROG): % : %.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

purge:  
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar
	@rm -f *~ *.bak

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)