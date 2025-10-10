CC = gcc

CFLAGS = -O0 -g
LFLAGS = -lm

PROG = cgSolver
MODULES = utils gradiente_conjugado sislin matriz vetor $(PROG)
OBJS = $(addsuffix .o,$(MODULES))
SRCS = $(addsuffix .c,$(MODULES)) $(addsuffix .h,$(MODULES))

# Lista de arquivos para distribuição
DISTFILES = *.c *.h Makefile README.md
DISTDIR = ek24-sssaf24

# Adicionado 'test' à lista de alvos que não geram arquivos
.PHONY: clean purge dist all test

all: $(PROG)

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

debug:   CFLAGS+=-D__DEBUG__
debug: $(PROG)

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