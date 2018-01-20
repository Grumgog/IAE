object = iaemath.o iaesys.o utility.o
platform = iaesys.cpp

all: iaeMAIN.lib iaesys.lib iaemath.lib
	echo it is ready

iaeMAIN.lib : $(object)
	ar crs iaeMAIN.lib $(object)

iaesys.lib : iaesys.o
	ar crs iaesys.lib iaesys.o

iaemath.lib : iaemath.o
	ar crs iaemath.lib iaemath.o

iaemath.o : iaemath.cpp iaemath.h iaetypes.h
	mingw32-g++ -c iaemath.cpp -o iaemath.o

iaesys.o : $(platform)
	mingw32-g++ -c $(platform) -o iaesys.o

utility.o : utility.h utility.cpp iaetypes.h
	mingw32-g++ -c utility.cpp -o utility.o
