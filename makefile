BINDIR=bin
SRCDIR=src
LATEXDIR=latex

all :

clean :
	rm -f $(BINDIR)/*
	rm -f $(SRCDIR)/*.o
	rm -f $(LATEXDIR)/*.pdf $(LATEXDIR)/*.fls $(LATEXDIR)/*.fdb_latexmk $(LATEXDIR)/*.aux $(LATEXDIR)/*.log
