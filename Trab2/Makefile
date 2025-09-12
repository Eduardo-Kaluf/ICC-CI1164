# EDUARDO KALUF - GRR 20241770

# PROGRAMA
    PROG = resolveEDO
    OBJS = $(PROG).o edo.o utils.o gauss_seidel.o
    PROG-likwid = resolveEDO-likwid
    OBJS-likwid = $(PROG-likwid).o edo.o utils.o gauss_seidel.o
    VERIF = verificaEP02

# Compilador
    CC     = gcc

# Flags Padrão
    CFLAGS = -O0 -g -Wall -Wextra
    LFLAGS = -lm

# Flags LIKWID
    CFLAGS-likwid = -O0 -g -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -DLIKWID_TEST
    LFLAGS-likwid = -lm -L${LIKWID_LIB} -llikwid

# Lista de arquivos para distribuição
DISTFILES = *.c *.h README* Makefile *.dat teste.sh
DISTDIR = ${USER}

.PHONY: clean purge dist all lik-all

all: $(PROG) $(VERIF)

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

lik-all: $(PROG-likwid) $(VERIF)

$(PROG-likwid): $(OBJS-likwid)
	$(CC) -o $@ $^ $(LFLAGS-likwid)

# ----------------------------------- #

$(PROG-likwid).o: $(PROG).c
	$(CC) $(CFLAGS-likwid) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(VERIF): $(VERIF).c
	$(CC) -Wno-format -o $@ $<

# ----------------------------------- #

testeFormato: $(PROG) $(VERIF)
	@cat teste.dat | ./$(PROG) | ./$(VERIF)

clean:
	@rm -f *~ *.bak *.o

purge:  clean
	@rm -f core a.out
	@rm -f $(PROG) $(PROG-likwid) $(VERIF) $(DISTDIR) $(DISTDIR).tgz

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)