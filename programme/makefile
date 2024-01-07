EXE=huffman
EXE_TESTS_TADS=testsTADs
EXE_TESTS_FONCTIONS_METIER=testsFonctionsMetier

LATEX_MAIN=main.tex
DOXYFILE_NAME=doxyfile

BINDIR=bin
SRCDIR=src
INCLUDEDIR=include
RAPPORTDIR=../rapport
LATEXDIR=$(RAPPORTDIR)/latex
DOCDIR=doc
TESTSDIR=tests

CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -O3 -I$(INCLUDEDIR)
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
	cd $(LATEXDIR); pdflatex --shell-escape $(LATEX_MAIN); cd ..
	cd $(LATEXDIR); pdflatex --shell-escape $(LATEX_MAIN); cd ..
	rm -rf ./$(LATEXDIR)/_minted-main ./$(LATEXDIR)/*.aux ./$(LATEXDIR)/*.log ./$(LATEXDIR)/*.toc ./$(LATEXDIR)/*.out
	mv $(LATEXDIR)/$(LATEX_MAIN:.tex=.pdf) $(RAPPORTDIR)

doc:
	doxygen $(DOXYFILE_NAME)
	cd $(DOCDIR)/latex; make; cd ../../

clean :
	rm -rf ./$(TESTSDIR)/*
	rm -rf ./$(BINDIR)/*
	rm -rf ./$(SRCDIR)/*.o
	rm -rf ./$(LATEXDIR)/*.pdf ./$(LATEXDIR)/_minted-main ./$(LATEXDIR)/*.aux ./$(LATEXDIR)/*.log ./$(LATEXDIR)/*.toc ./$(LATEXDIR)/*.out
	rm -rf ./$(DOCDIR)
