EXE=huffman
EXE_TESTS=testsHuffman
BINDIR=bin
SRCDIR=src
LATEXDIR=latex
INCLUDEDIR=incluvoid seDeplacerDansLArbre(int bit, ArbreDeHuffman *a);

	cd $(LATEXDIR); pdflatex main.tex
	rm -f ./$(LATEXDIR)/*.fls ./$(LATEXDIR)/*.fdb_latexmk ./$(LATEXDIR)/*.aux ./$(LATEXDIR)/*.log

clean :
	rm -rf ./$(TESTSDIR)/$(EXE_TESTS)
	rm -rf ./$(BINDIR)/$(EXE)
	rm -rf ./$(SRCDIR)/*.o
	rm -rf ./$(LATEXDIR)/*.pdf ./$(LATEXDIR)/*.fls ./$(LATEXDIR)/*.fdb_latexmk ./$(LATEXDIR)/*.aux ./$(LATEXDIR)/*.log