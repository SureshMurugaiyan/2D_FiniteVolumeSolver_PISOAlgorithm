#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <sys/stat.h>

#include "math.h"

#define dfloat double



typedef enum {
	topBoundary=0, bottomBoundary=1, leftBoundary=2,	rightBoundary=3,	innerDomain=4
} patchID;


typedef enum {
	fixedValue=5,	fixedNormalGradient=6, none=7
} boundarycondition_type;



typedef enum {
	U=8,	p=9,	rho=10, mu=11
} variable_name;




typedef struct{

	/*************************************************************/
	/* Mesh Field                                                */
	/*************************************************************/
	int ncellVertices; /* number of vertices per cell */
	int ncellFaces; /* number of faces per cell */
	int nfaceVertices; /* number of vertices per Face */
	int nmeshdimension; /* nmeshdimension = x,y stored for 2D Mesh */

	int ncellsx; /* number of cells along each row = colmax*/
	int ncellsy; /* number of cells along each col = rowmax */
	int ncells; /* number of cells in mesh */

	int nvertices; /* number of vertices in mesh */

	int *cellToCells; /* cell to cell connectivity */
	int *cellToFaces; /* cell to Local Face connectivity */
	int *faceToVertices; /* local face to Local vertices connectivity */
	int *faceToOppositeFaces; /* Face to Opposite Intersecting Face connectivity */
	int *faceToLocalFaces; /* Face to Opposite Local Face connectivity */


	dfloat *vertices; /* coordinates of vertices */
	dfloat *C; /* coordinates of cell centers */
	dfloat *Cf; /* coordinates of cell face centers */

	dfloat *Sf; /* vector values of outward cell normal face Areas */
	dfloat *magSf; /* Magnitude of Face areas */

	dfloat *V; /* cell volumes (in 2D Cell Area) */

	dfloat *fx; /* Cell Face interpolation Factor */

	dfloat *d; /* Vector from from cell P to cell N  */
	dfloat *magd; /* distance from P to N */

	int *patchID; /* Name the patches inlet, outlet, top wall, bottom wall */

	/*************************************************************/
	/* Solver Fields                                             */
	/*************************************************************/
	int nsolutiondimension; /* nsolutiondimension=3 for Ux,Uy,Uz */
	dfloat *aP;
	dfloat *aN;
	dfloat *R;
	dfloat *r;

	/*************************************************************/
	/* Solver Control                                			 */
	/*************************************************************/
	int timeStepMax;
	double finalTime;
	double deltatime;
	int WriteFrequency;
	int nCorrMax; // number of corrector loops in predictor corrector
	double time;
	int timeStep;
	bool stopCriterion;

	double lambda; // relaxation parameter
	double maxNorm; // max norm of solution
	int maxitrEqn; // max number of iterations

	/*************************************************************/
	/* Solution Field                                            */
	/*************************************************************/

	dfloat *U;
	dfloat *p;
	dfloat *rho;
	dfloat *mu;

	dfloat *phiU;
	dfloat *divphiU;

	dfloat *rAU;

	dfloat *HbyA;
	dfloat *phiHbyA;
	/*************************************************************/
	/* Boundary condition type and value                         */
	/*************************************************************/
	int bctype;
	dfloat* bcvalueScalar;
	dfloat* bcvalueVector;

	dfloat *U0;
	dfloat *U00;


}mesh_t;


void createMeshVertexScalar(dfloat** phi, mesh_t *mesh);
void createMeshVertexVector(dfloat** phi, mesh_t *mesh);
void createMeshVolumeScalar(dfloat** phi, mesh_t *mesh);
void createMeshVolumeVector(dfloat** phi, mesh_t *mesh);
void createMeshSurfaceScalar(dfloat** phi, mesh_t *mesh);
void createMeshSurfaceVector(dfloat** phi, mesh_t *mesh);


void meshConstructFields(mesh_t *mesh);
void meshDestructFields(mesh_t *mesh);

void printMeshVertexVector(double* phi, char *fileName,mesh_t *mesh);
void printMeshVolumeVector(double* phi, char *fileName,mesh_t *mesh);
void printMeshSurfaceVector(double* phi, char *fileName,mesh_t *mesh);
void printMeshSurfaceScalar(double* phi, char *fileName, mesh_t *mesh);
void printMeshSurfaceScalar(int* phi, char *fileName, mesh_t *mesh);

void printMeshVolumeScalar(double* phi, char *fileName,mesh_t *mesh);

double distance(double *X1,double *X2);
double magnitude(double a);

void meshGenerate(mesh_t *mesh);
void meshGenerateCellConnectivity(mesh_t *mesh);
void meshGenerateCellMetrics(mesh_t *mesh);
void meshGenerateBoundaryName(mesh_t *mesh);


void createSolutionVertexScalar(dfloat** phi, mesh_t *mesh);
void createSolutionVertexVector(dfloat** phi, mesh_t *mesh);
void createSolutionVolumeScalar(dfloat** phi, mesh_t *mesh);
void createSolutionVolumeVector(dfloat** phi, mesh_t *mesh);
void createSolutionSurfaceScalar(dfloat** phi, mesh_t *mesh);
void createSolutionSurfaceVector(dfloat** phi, mesh_t *mesh);

void solverConstructFields(mesh_t *mesh);
void solverDestructFields(mesh_t *mesh);


void insConstructSolutionFields(mesh_t *mesh);
void insDestructSolutionFields(mesh_t *mesh);

void solverUpdateStoppingCriterion(mesh_t *mesh);

void solveVector(double* U, mesh_t *mesh);
void solveScalar(double* P, mesh_t *mesh);


void printSolutionVolumeScalar(double* phi, char *fileName,int timeStep,mesh_t *mesh);
void printSolutionVolumeVector(double* phi, char *fileName,int timeStep, mesh_t *mesh);
void printSolutionSurfaceScalar(double* phi, char *fileName, int timestep, mesh_t *mesh);
void printSolutionSurfaceVector(double* phi, char *fileName,int timeStep, mesh_t *mesh);
void printSolutionVertexScalar(double* phi, char *fileName,int timeStep, mesh_t *mesh);

void insWriteSolutionField(mesh_t *mesh);
void insSetInitialConditions(mesh_t *mesh);

void copyVolumeVectorDataToFrom(double* copyTo, double* copyFrom,mesh_t *mesh);

void insConstructUEquation(mesh_t *mesh);
double ddteulerbackward(dfloat* rho, dfloat* U0, dfloat* U00,mesh_t *mesh);

void interpolateScalarCellToFace(dfloat* phiCell, dfloat* phiFace,mesh_t *mesh);
void interpolateVectorCellToFace(dfloat* phiCell, dfloat* phiFace,mesh_t *mesh);

void insGetBoundaryCondition( int variable_name, int fid, mesh_t *mesh);

void insConstructFlux(double* HbyA, double* phiHbyA, mesh_t *mesh);
void insConstructFluxofSurfaceVector(double* HbyAf, double* phiHbyA, mesh_t *mesh);

void insConstrainByBoundaryFieldVector(double* Uf, double* U, int U_name,mesh_t *mesh);
void insConstrainByBoundaryFieldScalar(double* pf,double* pcell,int p_name,mesh_t *mesh);

void insConstructHbyAEqn(mesh_t *mesh);
void insConstructPEquation(mesh_t *mesh);

double fvmLaplacianOfVector(double alpha, dfloat* rAU, dfloat* p,int P_name,mesh_t *mesh);
double fvcLaplacianOfVector(double alpha, dfloat* mu, dfloat* U,int U_name,mesh_t *mesh);
double fvmDivergenceOfVector(double alpha, dfloat* rho, dfloat* U,int U_name,
		dfloat* phiU, mesh_t *mesh);
double fvcDivergenceOfVector(double alpha, dfloat* rho, dfloat* U,int U_name,
		dfloat* phiU, mesh_t *mesh);

void fvdDivergenceOfSurfaceScalar(double* phiU, double* divphiU, mesh_t *mesh);
double fvmLaplacianOfScalar(double alpha, dfloat* rAU, dfloat* p,int P_name,mesh_t *mesh);
double fvcDivergenceOfSurfaceScalar(dfloat alpha, dfloat* phiHbyA,mesh_t *mesh);
void fvdGradientOfScalar(dfloat* gradCell,dfloat *phiCell, int P_Name, mesh_t *mesh);

void insCorrectU(mesh_t *mesh);
void insCorrectVolumetricFlux(mesh_t *mesh);

void setReferenceValueScalar(double* p,int refCell,double refValue, mesh_t *mesh);
