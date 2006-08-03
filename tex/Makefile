# makefile for latex+bibtex+dvips
#
# bugs:
#  - doesn't always re-run bibtex if only the .bib file has changed
#  - harsh "clean"
#
# revision history:
# 2002-07-25  written - Hogg (NYU)

all: kcorrection.ps cosmography.ps

kcorrection.ps: kcorrection.tex kcorrection.bbl
	latex kcorrection; latex kcorrection; latex kcorrection; dvips kcorrection -o

cosmography.ps: cosmography.tex
	latex cosmography; latex cosmography; latex cosmography; dvips cosmography -o

clean:
	$(RM) *.aux *.log *.bbl *.blg *.dvi *.eps
