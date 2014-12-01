.PHONY: all run doc doc-preview doc-spell srcdoc srcdoc-preview clean export

EXECS=app-server app-client
LIBS=util raii syscalls shared

EXECS_PATHS=$(addprefix build/exec/, $(EXECS))

CC=g++
CCFLAGS=-std=c++11 -Wall -Wextra -g -MP -MMD
INCLUDES=-I src -I libs

###############################################################################
# Helpers and administrative tasks
###############################################################################
all: $(EXECS_PATHS)

run: all
	build/exec/app-server -l 0

doc: build/doc/informe.pdf

doc-preview: doc
	evince build/doc/informe.pdf &

doc-spell: docs/informe.tex
	aspell -t check docs/informe.tex -d es

clean:
	rm -rf build
	rm -f app.log
	rm -f people.db

###############################################################################
# Executable building
###############################################################################
build:
	mkdir $@

build/objs: | build
	mkdir $@

build/exec: | build
	mkdir $@

define GENERATE_COMPILATION_RULES

$(1)_objs=$$(addsuffix .o,$$(basename $$(subst src/,build/objs/,$$(wildcard src/$(1)/*.cpp))))

$(1)_deps=$$(wildcard build/objs/$(1)/*.d)

-include $$($(1)_deps)

build/objs/$(1): | build/objs
	mkdir $$@

build/objs/$(1)/%.o: src/$(1)/%.cpp | build/objs/$(1)
	$$(CC) $$(CCFLAGS) $$(INCLUDES) -c $$< -o $$@

endef

define GENERATE_LINK_RUNLES

build/exec/$(1): $$($(1)_objs) $$(util_objs) $$(raii_objs) $$(syscalls_objs) $$(shared_objs) | build/exec
	$$(CC) $$^ -o $$@

endef

$(foreach compilable,$(EXECS),$(eval $(call GENERATE_COMPILATION_RULES,$(compilable))))
$(foreach compilable,$(LIBS),$(eval $(call GENERATE_COMPILATION_RULES,$(compilable))))
$(foreach executable,$(EXECS),$(eval $(call GENERATE_LINK_RUNLES,$(executable))))

###############################################################################
# Documentation building
###############################################################################
build/doc: | build
	mkdir build/doc

build/doc/informe.pdf: docs/informe.tex | build/doc
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex
	pdflatex --output-directory build/doc docs/informe.tex

