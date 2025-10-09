CC = gcc

CFLAGS = -O0 -g
LFLAGS = -lm

PROG = cgSolver
MODULES = utils gradiente_conjugado sislin matriz $(PROG)
OBJS = $(addsuffix .o,$(MODULES))
SRCS = $(addsuffix .c,$(MODULES)) $(addsuffix .h,$(MODULES))

# Nome do arquivo de código-fonte do teste
TEST_SRC = test_functions.c utils.c sislin.c
# Nome do programa executável de teste
TEST_PROG = run_tests

# Lista de arquivos para distribuição
DISTFILES = *.c *.h Makefile README.md
DISTDIR = ek24-sssaf24

# Adicionado 'test' à lista de alvos que não geram arquivos
.PHONY: clean purge dist all test

all: $(PROG)

# --- ALVO PARA COMPILAR E EXECUTAR O TESTE ---
# Este alvo compila o programa de teste
$(TEST_PROG): $(TEST_SRC)
	$(CC) $(CFLAGS) -o $(TEST_PROG) $(TEST_SRC) $(LFLAGS)

# Este alvo executa o teste (após garantir que ele foi compilado)
test: $(TEST_PROG)
	@echo "--- Executando os testes ---"
	./$(TEST_PROG)
	@echo "--- Testes finalizados ---"
# --- FIM DO ALVO DE TESTE ---

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