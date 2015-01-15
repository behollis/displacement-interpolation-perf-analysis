LIBS = ./libqhull/*.o -llapack -lrt -lgfortran

all: qInterpolate.o error.o mvndst.o interp.o
	g++ qInterpolate.o error.o mvndst.o interp.o ${LIBS} -o qInterpolate

qInterpolate.o: qInterpolate.cpp
	g++ -c qInterpolate.cpp

error.o: error.cpp
	g++ -c error.cpp

interp.o: interp.cpp
	g++ -c interp.cpp

mvndst.o: mvndst.f
	gfortran -c mvndst.f

clean: 
	- rm *.o