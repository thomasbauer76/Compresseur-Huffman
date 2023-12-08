EXE=huffman
EXE_TESTS=testsHuffman
BINDIR=bin
SRCDIR=src
LATEXDIR=latex
INCLUDEDIR=include
TESTSDIR=tests
CFLAGS=-Wall -pedantic -std=c99 -I$(INCLUDEDIR)
LDFLAGS=-lcunit

all :

tests: $(SRCDIR)/tests.o $(SRCDIR)/statistiques.o $(SRCDIR)/octet.o
	gcc -o $(TESTSDIR)/$(EXE_TESTS) $(SRCDIR)/tests.o $(SRCDIR)/statistiques.o $(SRCDIR)/octet.o $(LDFLAGS)

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