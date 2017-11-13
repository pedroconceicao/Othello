#As minhas sources...
SRC=main.c othello.c pcolor.c

#Ficheiros de cabeçalho
HEADERS=othello.h

#O binário executável (nome do programa)
PROG=othello

#Ficheiro para o Doxygen
DOXYFILE=Doxyfile

AULA=TPC 7

################################

CC=gcc
CFLAGS=-Wall

OBJ=$(SRC:.c=.o)  #macro automática para gerar os OBJ a partir das SRC

INCLUDE=    #para as header files (cabeçalhos)
LIB=-lm     #bibliotecas específicas a usar

CFLAGS+=`pkg-config --cflags opencv`
LIB+=`pkg-config --libs opencv`
############################################
# Regras
############################################

###########################################
# Regras relativas à compilação e linkagem

$(PROG): prototypes.h $(OBJ)
	$(CC) $(OBJ) -o $(PROG) $(LIB)

.c.o:
	$(CC) $(CFLAGS) -c $(INCLUDE) $< -o $@

#########################################
# Regras relativas à gestão e organização

clean:
	rm -rf $(PROG) $(OBJ)

allclean: clean
	rm -rf html latex *.bak *~ tags prototypes.h

############################################
# Regras relativas à geração de documentação

#depende da $(DOXYFILE) e do ficheiro index.html
doc: $(DOXYFILE) html/index.html

#A $(DOXYFILE) só depende de si própria.
#Se não existir é criada e alguns defaults são ajustados:
$(DOXYFILE):
	doxygen -g $(DOXYFILE) ; \
	sed -i 's/^PROJECT_NAME.*$$/PROJECT_NAME      = "My project $(PROG)"/'       $(DOXYFILE) ;\
	sed -i 's/^GENERATE_LATEX.*$$/GENERATE_LATEX      = NO/'        $(DOXYFILE) ;\
	sed -i 's/^HAVE_DOT.*$$/HAVE_DOT      = YES/'                   $(DOXYFILE) ;\
	sed -i 's/^SOURCE_BROWSER.*$$/SOURCE_BROWSER      = YES/'       $(DOXYFILE) ;\
	sed -i 's/^PROJECT_LOGO.*$$/PROJECT_LOGO       = PARIlogo.png/' $(DOXYFILE) ;


#O ficheiro index.html depende obviamente da Doxyfile e das SRC, mas
#pode ter outras dependências adicionais...
html/index.html: $(DOXYFILE) $(SRC) mainpage.dox PARIlogo.png
	doxygen

#Forçar a geração de documentação mesmo que ela já exista (não depende de index.html)
forcedoc: $(DOXYFILE)
	doxygen

#Gera logotipo automaticamente
logo PARIlogo.png:
	convert pattern:circles \( +clone \) +append \( +clone \) -append \
		-fill grey -opaque black  -blur 0x0.5 -shade 120x45 \
		-gravity center -crop 50%  +repage    miff:- |\
		convert  -size 80x80 tile:- -fill blue \
		-draw "scale 2.5,3 text 2,12 PARI" \
		-draw "scale 2,2 text 2,32 'Aula $(AULA)'" PARIlogo.png

############################################
# Regra relativa à geração do ficheiro de protótipos
#
# Generate a list of functions (useful for prototypes)
#proto prototypes.h: $(SRC)
#	@echo "Rebuild prototypes.h"
#	@../genproto.sh   #script to generate the "prototypes.h" header file

###########################################
# targets que não são ficheiros e evita
# eventuais conflitos se porventura existirem
# ficheiros ou diretorios com estes nomes.
#
.PHONY: doc clean allclean forcedoc proto

############################################################
# regra para criar dependencias com as header files caso haja
# alguma alteração às header e não haja nas sources.
# Basta invocar este target quando houver inclusão de novas header.
# Gera automaticamente as dependências abaixo da linha "DO NOT DELETE"
dep depend:
	makedepend -Y $(SRC) 2> /dev/null

# DO NOT DELETE

main.o: othello.h
othello.o: othello.h
pcolor.o: pcolor.h
