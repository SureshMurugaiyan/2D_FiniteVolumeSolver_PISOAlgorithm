# define variables
HDRDIR  = ./include

# specify compilers to use

CC = g++
LD = g++

# compiler flags to be used (set to compile with debugging on)
CFLAGS = -I$(HDRDIR)  -O3 -std=c++11 -g3

# link flags to be used
LDFLAGS	= -I$(HDRDIR) 

# libraries to be linked in
LIBS = -lm

# types of files we are going to construct rules for
.SUFFIXES: .cpp

# rule for .cpp files
.cpp.o:
	$(CC) $(CFLAGS) -o $*.o -c $*.cpp

# list of objects to be compiled
OBJS = \
src/insMain.o\
src/meshCreateFields.o\
src/meshFields.o\
src/meshPrintFields.o\
src/meshGenerate.o\
src/meshGenerateCellConnectivity.o\
src/miscFunctions.o\
src/meshGenerateCellMetrics.o\
src/meshGenerateBoundaryName.o\
src/solverCreateFields.o\
src/solverFields.o\
src/insSolutionFields.o\
src/solverUpdateStoppingCriterion.o\
src/solveScalar.o\
src/solveVector.o\
src/solutionPrintFields.o\
src/insWriteSolutionField.o\
src/insSetInitialConditions.o\
src/insConstructUEquation.o\
src/insFVMddtSchemes.o\
src/interpolateCellToFace.o\
src/insGetBoundaryCondition.o\
src/insFVMlaplacianOfVectorSchemes.o\
src/insFVClaplacianOfVectorSchemes.o\
src/insFVMDivergenceOfVectorSchemes.o\
src/insFVCDivergenceOfVectorSchemes.o\
src/insFVDDivergenceOfSurfaceScalar.o\
src/insConstructFlux.o\
src/insConstrainByBoundaryField.o\
src/insConstructHbyAEqn.o\
src/insConstructPEquation.o\
src/insFVMlaplacianOfScalarSchemes.o\
src/insFVCdivergenceOfSurfaceScalar.o\
src/insFVDGradientOfScalar.o\
src/insCorrectU.o\
src/insCorrectVolumetricFlux.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\
#src/XXXXXXXXXXXXXXXXXXXXXX.o\


all:$(OBJS)
	$(LD)  $(LDFLAGS) -o main $(OBJS) $(LIBS)
	rm -r $(OBJS)

# what to do if user types "make clean"
clean :
	rm main

realclean :
	rm -r $(OBJS)
