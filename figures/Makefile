# Build standalone figure sources into vector PDFs (included by main_spec.tex)
# and PNG previews. Regenerate after editing any fig-*.tex or preamble.tex:
#
#     make -C figures          # build all PDFs + PNGs
#     make -C figures clean     # remove generated artifacts
#
FIGURES  := fig-mem-domains fig-fence-quiet fig-put-signal-xdomain
PDFS     := $(addsuffix .pdf,$(FIGURES))
PNGS     := $(addsuffix .png,$(FIGURES))

LATEX    ?= pdflatex
PDFTOPPM ?= pdftoppm
RM       ?= rm -f

.PHONY: all clean
all: $(PDFS) $(PNGS)

# Each figure is a self-contained standalone document; the shared preamble is
# a dependency so edits to it trigger a rebuild.
%.pdf: %.tex preamble.tex
	$(LATEX) -interaction=nonstopmode -halt-on-error $<

# 300 dpi PNG preview (e.g. for web or issue trackers); not used by the spec.
%.png: %.pdf
	$(PDFTOPPM) -png -r 300 -singlefile $< $*

clean:
	$(RM) *.aux *.log $(PDFS) $(PNGS)
