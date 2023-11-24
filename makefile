BINDIR=bin
SRCDIR=src
LATEXDIR=latex

all :

pdf :
	cd $(LATEXDIR); pdflatex main.tex
	rm -f $(LATEXDIR)/*.fls $(LATEXDIR)/*.fdb_latexmk $(LATEXDIR)/*.aux $(LATEXDIR)/*.log
	open $(LATEXDIR)/main.pdf

clean :
	rm -f $(BINDIR)/*
	rm -f $(SRCDIR)/*.o
	rm -f $(LATEXDIR)/*.pdf $(LATEXDIR)/*.fls $(LATEXDIR)/*.fdb_latexmk $(LATEXDIR)/*.aux $(LATEXDIR)/*.log
