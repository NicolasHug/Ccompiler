# colorize outputs
HASCOLOR = $(shell if test `which colorgcc`; then echo true; else echo false; fi)
ifneq ($(HASCOLOR), true)
          export CC=@printf "\033[34m   CC\t$$@\033[0m\n" && gcc 
	else
	        export CC=@printf "\033[34m   CC\t$$@\033[0m\n" && colorgcc
	      endif
export CXX=@printf "\033[34m   CPPC\t$$@\033[0m\n" && g++ 
export AR=@printf "\033[34m   AR\t$$@\033[0m\n" && ar
export LD=@printf "\033[35m   LD\t$$@\033[0m\n" && ld



SUBDIRS = compilateur interpreteur
CURRENTDIR=$(realpath .)

all: projet

projet:
	@for i in $(SUBDIRS); do \
	  printf "\033[1m>>> [$$i]\033[0m\n"; \
	  $(MAKE) -C $$i; \
	  if [ $$? = 0 ]; then printf "\033[1m<<< [$$i] [\033[32mOK\033[0m\033[1m]\033[0m\n"; else printf "\033[31m\033[1m<<< [$$i] [FAIL]\033[0m\n"; exit 1; fi; \
	  done;
	mv compilateur/compilo build
	mv interpreteur/interpreteur build

clean:
	@ for i in $(SUBDIRS); do \
	  cd $$i; make clean; cd $(CURRENTDIR);\
	  done;
	rm -f build/asm build/compilo build/asmPremierePasse build/interpreteur
