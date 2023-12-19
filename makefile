EXE=huffman
EXE_TESTS_TADS=testsTADs
EXE_TESTS_FONCTIONS_METIER=testsFonctionsMetier
BINDIR=bin
SRCDIR=src
LATEXDIR=latex
INCLUDEDIR=include
TESTSDIR=tests
CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -I$(INCLUDEDIR)
LDFLAGS=-lcunit

SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:.c=.o)

MAIN_OBJS=$(filter-out $(SRCDIR)/testsTADs.o $(SRCDIR)/testsFonctionsMetier.o, $(OBJS))
TESTS_OBJS=$(filter-out $(SRCDIR)/main.o, $(OBJS))
TESTS_TADS_OBJS=$(filter-out $(SRCDIR)/testsFonctionsMetier.o $(SRCDIR)/compression.o $(SRCDIR)/decompression.o, $(TESTS_OBJS))
TESTS_FONCTIONS_METIER_OBJS=$(filter-out $(SRCDIR)/testsTADs.o $(SRCDIR)/compression.o $(SRCDIR)/decompression.o, $(TESTS_OBJS))

all : $(MAIN_OBJS)
	$(CC) -o $(BINDIR)/$(EXE) $(MAIN_OBJS) $(LDFLAGS)

tests: $(TESTS_OBJS)
	$(CC) -o $(TESTSDIR)/$(EXE_TESTS_TADS) $(TESTS_TADS_OBJS) $(LDFLAGS)
	$(CC) -o $(TESTSDIR)/$(EXE_TESTS_FONCTIONS_METIER) $(TESTS_FONCTIONS_METIER_OBJS) $(LDFLAGS)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

pdf :
	cd $(LATEXDIR); pdflatex main.tex
	rm -f ./$(LATEXDIR)/*.fls ./$(LATEXDIR)/*.fdb_latexmk ./$(LATEXDIR)/*.aux ./$(LATEXDIR)/*.log

clean :
	rm -rf ./$(TESTSDIR)/$(EXE_TESTS_TADS) ./$(TESTSDIR)/$(EXE_TESTS_FONCTIONS_METIER)
	rm -rf ./$(BINDIR)/$(EXE)
	rm -rf ./$(SRCDIR)/*.o
	rm -rf ./$(LATEXDIR)/*.pdf ./$(LATEXDIR)/*.fls ./$(LATEXDIR)/*.fdb_latexmk ./$(LATEXDIR)/*.aux ./$(LATEXDIR)/*.log