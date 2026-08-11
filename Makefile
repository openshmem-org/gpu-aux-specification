TARGET   = main_spec
SOURCES  = $(shell find . -name '*.tex' -print)
FIGURES  = $(shell find figures -name '*.pdf' -print 2>/dev/null)
EXAMPLES = $(shell find example_code -name '*.[c,f]*' -print 2>/dev/null)

.PHONY: all figures
all: figures ${TARGET}.pdf

# Build the standalone figure PDFs/PNGs (see figures/Makefile) before the main
# document, which includes the generated PDFs via \includegraphics.
figures:
	$(MAKE) -C figures

${TARGET}.pdf: ${SOURCES} ${FIGURES} ${EXAMPLES}
	pdflatex $(LATEXOPT) ${TARGET}
	makeindex ${TARGET}
	pdflatex $(LATEXOPT) ${TARGET}
	makeindex ${TARGET}
	pdflatex $(LATEXOPT) ${TARGET}

RM ?= rm -f
CLEAN_EXTENSIONS = aux idx ilg ind log out pdf toc
.PHONY: clean
clean:
	for e in ${CLEAN_EXTENSIONS}; do $(RM) ${TARGET}.$$e; done
