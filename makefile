EXE=huffman
EXE_TESTS=testsHuffman
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

MAIN_OBJS=$(filter-out $(SRCDIR)/testsHuffman.o, $(OBJS))
TESTS_OBJS=$(filter-out $(SRCDIR)/main.o $(SRCDIR)/compression.o $(SRCDIR)/decompression.o, $(OBJS))

all :

tests: $(TESTS_OBJS)
	$(CC) -o $(TESTSDIR)/$(EXE_TESTS) $(TESTS_OBJS) $(LDFLAGS)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

pdf :
	cd $(LATEXDIR); pdflatex main.tex
	rm -f ./$(LATEXDIR)/*.fls ./$(LATEXDIR)/*.fdb_latexmk ./$(LATEXDIR)/*.aux ./$(LATEXDIR)/*.log

clean :
	rm -rf ./$(TESTSDIR)/$(EXE_TESTS)
	rm -rf ./$(BINDIR)/$(EXE)
	rm -rf ./$(SRCDIR)/*.o
	rm -rf ./$(LATEXDIR)/*.pdf ./$(LATEXDIR)/*.fls ./$(LATEXDIR)/*.fdb_latexmk ./$(LATEXDIR)/*.aux ./$(LATEXDIR)/*.log