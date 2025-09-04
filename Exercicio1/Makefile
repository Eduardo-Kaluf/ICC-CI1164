# AFTER COMPILING RUN WITH "likwid-perfctr -C 3 -g FLOPS_DP  -m ./perfSL < test.dat > test.log"

# PROGRAMA
    PROG = perfSL
    OBJS = utils.o sislin.o eliminacao_gauss.o gauss_seidel.o # acrescentar aqui outros módulos do programa

# Compilador
    CC     = gcc

# Acrescentar onde apropriado as opções para incluir uso da biblioteca LIKWID
    CFLAGS = -O0 -DLIKWID_PERFMON -I${LIKWID_INCLUDE}
    LFLAGS = -lm -L${LIKWID_LIB} -llikwid

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = ${USER}

.PHONY: all clean purge dist

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(PROG)

$(PROG): % : %.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak

purge:  clean
	@rm -f $(PROG) *.o core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
