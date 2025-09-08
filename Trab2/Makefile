# AFTER COMPILING RUN WITH "likwid-perfctr -C 3 -g FLOPS_DP  -m ./perfSL < test.dat > test.log"

# PROGRAMA
    PROG = resolveEDO
    OBJS = $(PROG).o edo.o utils.o fatoracao_lu.o # mod1.o mod2.o
     VERIF = verificaEP02

# Compilador
    CC     = gcc

# Acrescentar onde apropriado as opções para incluir uso da biblioteca LIKWID
    CFLAGS = -O0 -g
    LFLAGS = -lm

# LIKWID FLAGS
    CFLAGS-LIKWID = -O0 -LIKWID -g -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
    LFLAGS-LIKWID = -lm -L${LIKWID_LIB} -llikwid

# Lista de arquivos para distribuição. Acrescentar mais arquivos se necessário.
DISTFILES = *.c *.h LEIAME* Makefile *.dat
DISTDIR = ${USER}

.PHONY: clean purge dist all

all: $(PROG) $(VERIF)

lik-all: $(PROG-LIKWID) $(VERIF)

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(PROG-LIKWID): $(OBJS)
	$(CC) $(CFLAGS-LIKWID) -o $@ $^ $(LFLAGS-LIKWID)

$(VERIF): $(VERIF).c
	$(CC) -Wno-format -o $@ $<

testeFormato: $(PROG) $(VERIF)
	@cat teste.dat | ./$(PROG) | ./$(VERIF)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f core a.out $(OBJS)
	@rm -f $(PROG) $(VERIF) $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
