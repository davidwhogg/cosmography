# makefile for latex+bibtex+dvips
#
# bugs:
#  - doesn't always re-run bibtex if only the .bib file has changed
#  - harsh "clean"
#
# revision history:
# 2002-07-25  written - Hogg (NYU)

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
	$(RM) *.aux *.log *.bbl *.blg *.dvi *.eps \
	kcorrection.ps cosmography.ps
