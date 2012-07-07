docfiles = spp.tex spp_diagram_modulow.pdf

docfiles += spp.pdf
MANNAME = spp
MANTEXSRC = $(MANNAME).tex
MANAUX = $(MANNAME).aux
MANPDF = $(MANNAME).pdf

CLEANFILES = $(MANPDF) $(MANNAME).log $(MANNAME).idx $(MANNAME).out \
	$(MANNAME).toc $(MANAUX)

$(MANPDF): $(docdir)/$(MANTEXSRC)
	$(PDFLATEX) $<

dist_doc_DATA = $(docfiles)

