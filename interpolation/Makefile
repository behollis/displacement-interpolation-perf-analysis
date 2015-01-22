PATHS = -L./libvtk/lib -I./libvtk/include/vtk-6.1
LIBS = ./libqhull/*.o ./liblapack/*.o\
       -lrt -lgfortran -pthread\
       -lvtkFiltersCore-6.1 \
       -lvtkImagingHybrid-6.1 \
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

all: static

# static expects:
# libqhull/  <- not the latest version!
# libvtk/    <- version 6.1
# liblapack/ <- not sure what version
# These are excluded from the sourcetree to keep the size down
static: qInterpolate.o error.o mvndst.o interp.o
	# This produces some linker warnings about not using dlopen,
	# but those can be ignored.
	g++ -static -rdynamic qInterpolate.o error.o mvndst.o interp.o \
	    ${PATHS} ${LIBS} -o qInterpolate

# doesn't completely work, but it's closer than building static
shared: qInterpolate.o error.o mvndst.o interp.o
	g++ -rdynamic qInterpolate.o error.o mvndst.o interp.o ${LIBS} -o qInterpolate

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