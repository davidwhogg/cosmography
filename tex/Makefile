# makefile for latex+bibtex+dvips
#
# bugs:
#  - doesn't always re-run bibtex if only the .bib file has changed
#  - harsh "clean"
#
# revision history:
# 2002-07-25  written - Hogg (NYU)

all: kcorrection.ps

kcorrection.ps: kcorrection.tex
	latex kcorrection; bibtex kcorrection; latex kcorrection; latex kcorrection; dvips kcorrection

clean:
	$(RM) *.aux *.log *.bbl *.blg *.dvi *.eps \
	kcorrection.ps cosmography.ps
