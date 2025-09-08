# PROGRAMA
    PROG = resolveEDO
    PROG_LIKWID = $(PROG)-likwid
    OBJS = $(PROG).o edo.o utils.o fatoracao_lu.o
    VERIF = verificaEP02

# Compilador
    CC     = gcc

# Flags Padrão
    CFLAGS = -O0 -g
    LFLAGS = -lm

# LIKWID FLAGS
    CFLAGS-LIKWID = -O0 -g -DLIKWID -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
    LFLAGS-LIKWID = -lm -L${LIKWID_LIB} -llikwid

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile *.dat
DISTDIR = ${USER}

.PHONY: clean purge dist all lik-all

all: $(PROG) $(VERIF)

lik-all: $(PROG_LIKWID) $(VERIF)

%.o: %.c *.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)


$(PROG_LIKWID): CFLAGS = $(CFLAGS-LIKWID)
$(PROG_LIKWID): LFLAGS = $(LFLAGS-LIKWID)

$(PROG_LIKWID): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)


$(VERIF): $(VERIF).c
	$(CC) -Wno-format -o $@ $<

testeFormato: $(PROG) $(VERIF)
	@cat teste.dat | ./$(PROG) | ./$(VERIF)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak *.o

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f core a.out
	@rm -f $(PROG) $(PROG_LIKWID) $(VERIF) $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)