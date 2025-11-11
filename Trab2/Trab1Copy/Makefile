CC = gcc

CFLAGS = -g -O3 -march=native -mavx -fopt-info-vec
LFLAGS = -lm

PROG = cgSolver
MODULES = utils gradiente_conjugado sislin matriz vetor $(PROG)
OBJS = $(addsuffix .o,$(MODULES))
SRCS = $(addsuffix .c,$(MODULES)) $(addsuffix .h,$(MODULES))

# Lista de arquivos para distribuição
DISTFILES = *.c *.h Makefile README.md
DISTDIR = ek24-sssaf24

.PHONY: clean purge dist all debug

all: $(PROG)

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

debug: CFLAGS += -D_DEBUG_
debug: $(PROG)

lik: CFLAGS += -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -DLIKWID_TEST -D_LIK_
lik: LFLAGS += -L${LIKWID_LIB} -llikwid
lik: $(PROG)


clean:
	@echo "Limpando sujeira ....."
	@rm -rf core *~ *.bak

purge: clean
	@echo "Fazendo a faxina ....."
	# Adicionado o executável de teste para ser removido na limpeza completa
	@rm -f a.out *.o $(PROG) $(TEST_PROG)


dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tgz) ..."
	@ln -s . $(DISTDIR)
	@tar -chzvf $(DISTDIR).tgz $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)