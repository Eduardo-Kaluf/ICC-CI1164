# PROGRAMA
    PROG = resolveEDO
    OBJS = $(PROG).o edo.o utils.o fatoracao_lu.o
    VERIF = verificaEP02

# Compilador
    CC     = gcc

# Flags Padrão
    CFLAGS = -O0 -g -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
    LFLAGS = -lm -L${LIKWID_LIB} -llikwid

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile *.dat
DISTDIR = ${USER}

.PHONY: clean purge dist all

all: $(PROG) $(VERIF)

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

# ----------------------------------- #

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(VERIF): $(VERIF).c
	$(CC) -Wno-format -o $@ $<

# ----------------------------------- #

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