PATHS = -L/home/vagrant/libvtk/lib -I/home/vagrant/libvtk/include/vtk-6.1
LIBS = ./libqhull/*.o ./lapack/*.o\
       -lrt -lgfortran -pthread\
       -lvtkImagingSources-6.1 \
       -lvtkImagingCore-6.1 \
       -lvtkCommonExecutionModel-6.1 \
       -lvtkCommonDataModel-6.1 \
       -lvtkCommonMisc-6.1 \
       -lvtkCommonSystem-6.1 \
       -lvtkCommonTransforms-6.1 \
       -lvtkCommonMath-6.1 \
       -lvtkCommonComputationalGeometry-6.1 \
       -lvtkCommonCore-6.1 \
       -lvtksys-6.1 \
       -ldl

COMPILE = g++ -I/home/vagrant/libvtk/include/vtk-6.1

all: qInterpolate.o error.o mvndst.o interp.o
	g++ -static -rdynamic qInterpolate.o error.o mvndst.o interp.o ${PATHS} ${LIBS} -o qInterpolate

qInterpolate.o: qInterpolate.cpp
	${COMPILE} -c qInterpolate.cpp

error.o: error.cpp
	${COMPILE} -c error.cpp

interp.o: interp.cpp
	${COMPILE} -c interp.cpp

mvndst.o: mvndst.f
	gfortran -c mvndst.f

libqhull: 
	cd libqhull; g++ -c *.c

liblapack:
	cd lapack; gfortran -c *.f

clean: 
	- rm *.o