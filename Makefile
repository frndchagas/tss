################################

SYSTEM     = x86-64_linux
LIBFORMAT  = static_pic
CPLEXDIR   = /opt/ibm/ILOG/CPLEX_Studio221/cplex
CONCERTDIR = /opt/ibm/ILOG/CPLEX_Studio221/concert

################

# Compilador 
CCC = g++ -O3

# Opcoes de compilacao
# CCOPT = -m64 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD -Wno-ignored-attributes
CCOPT = -m64 -std=c++11 -O -fPIC -fno-strict-aliasing -fexceptions -DNDEBUG -DIL_STD -Wno-ignored-attributes

# Bibliotecas e includes
CPLEXBINDIR   = $(CPLEXDIR)/bin/$(BINDIST)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(SYSTEM)
CPLEXLIB      = cplex$(dynamic:yes=2010)

CCLNDIRS  = -L$(CPLEXLIBDIR) -L$(CONCERTLIBDIR) $(dynamic:yes=-L$(CPLEXBINDIR))
CCLNFLAGS = -lconcert -lilocplex -l$(CPLEXLIB) -lm -lpthread -ldl

CONCERTINCDIR = $(CONCERTDIR)/include
CPLEXINCDIR   = $(CPLEXDIR)/include

CCFLAGS = $(CCOPT) -I$(CPLEXINCDIR) -I$(CONCERTINCDIR) 

all : main

main: main.o data.o
	$(CCC) $(CCFLAGS) $(CCLNDIRS) main.o data.o -o main $(CCLNFLAGS)

main.o: main.cpp
	$(CCC) -c $(CCFLAGS) main.cpp -o main.o

data.o: data.cpp
	$(CCC) -c $(CCFLAGS) data.cpp -o data.o

clean:
	rm --force main main.o data.o
