LATEX = latex
BIBTEX = bibtex
DVIPS = dvips
RM = /bin/rm -f
RERUN = "Rerun to get"
BIBRERUN = "undefined citations"

all: kcorrection.ps

%.dvi: %.tex
	$(LATEX) $* ;
	egrep $(BIBRERUN) $*.log && ($(BIBTEX) $*) ; true
	egrep $(BIBRERUN) $*.log && ($(LATEX) $*) ; true
	egrep $(RERUN) $*.log && ($(LATEX) $*) ; true

%.ps: %.dvi
	dvips $< -o $@

clean:
	$(RM) *.aux *.log *.bbl *.blg *.dvi \
	kcorrection.ps cosmography.ps
