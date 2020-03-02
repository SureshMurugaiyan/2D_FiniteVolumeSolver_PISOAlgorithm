/******************************************************************************
                     2 Dimensional Finite Volume Numerical Solver.
                PISO Algorithm to solve Navier Stokes Equations.
*******************************************************************************/

// valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./main

#include "mesh.h"

int main(int argc, char **argv){


	clock_t t;
	t = clock();


	mesh_t *mesh = (mesh_t*) calloc(1, sizeof(mesh_t));

	mesh->ncellVertices	 = 4;
	mesh->ncellFaces  	 = 4;
	mesh->nfaceVertices  = 2;
	mesh->nmeshdimension = 2;



	mesh->ncellsx = 32;
	mesh->ncellsy = 32;
	mesh->ncells  = mesh->ncellsx*mesh->ncellsy;

	mesh->nvertices  = mesh->ncells*mesh->ncellVertices;


	meshConstructFields(mesh);

	meshGenerate(mesh);
	meshGenerateCellConnectivity(mesh);
	meshGenerateCellMetrics(mesh);

	meshGenerateBoundaryName(mesh);


	printf("\nStarting time marching loop \n");

	mesh->nsolutiondimension = 3; // Solves Ux, Uy, Uz

	solverConstructFields(mesh);

	mesh->timeStepMax		= 2000;
	mesh->finalTime  		= 2000*0.01;
	mesh->deltatime  		= 0.01;
	mesh->WriteFrequency	= 100;
	mesh->nCorrMax  		= 1;
	mesh->time  			= 0.0; // start time
	mesh->timeStep  		= 0; // start time step
	mesh->stopCriterion  	= false;

	insConstructSolutionFields(mesh);

	insSetInitialConditions(mesh);

	insWriteSolutionField(mesh);

	while (mesh->stopCriterion==false){

		copyVolumeVectorDataToFrom(mesh->U0,mesh->U,mesh);
		copyVolumeVectorDataToFrom(mesh->U00,mesh->U0,mesh);

		insConstructUEquation(mesh);

		mesh->lambda  	=	1.0;	// relaxation parameter
		mesh->maxNorm 	=	1e-9;	// max norm of solution
		mesh->maxitrEqn	=	500;	// max number of iterations

		solveVector(mesh->U,mesh);

		for (int ncorr = 0; ncorr < mesh->nCorrMax; ++ncorr){

			insConstructHbyAEqn(mesh);
			insConstructFlux(mesh->HbyA,mesh->phiHbyA,mesh);

			insConstructPEquation(mesh);


			int refCell  = 0;
			int refValue = 0;

			setReferenceValueScalar(mesh->p,refCell,refValue,mesh);


			mesh->lambda  	=	1.0;	// relaxation parameter
			mesh->maxNorm 	=	1e-9;	// max norm of solution
			mesh->maxitrEqn	=	2000;	// max number of iterations
			solveScalar(mesh->p,mesh);

			insCorrectU(mesh);

		}

		insCorrectVolumetricFlux(mesh);

		fvdDivergenceOfSurfaceScalar(mesh->phiU, mesh->divphiU, mesh);


		mesh->timeStep++;
		mesh->time = mesh->timeStep*mesh->deltatime;

		insWriteSolutionField(mesh);

		solverUpdateStoppingCriterion(mesh);
	}


	insDestructSolutionFields(mesh);
	solverDestructFields(mesh);
	meshDestructFields(mesh);
	free(mesh);

	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

	printf("Solver took %f seconds to execute \n", time_taken);

}

void setReferenceValueScalar(double* p,int refCell,double refValue, mesh_t *mesh){


	mesh->aP[refCell] = 1.00;

	for (int face = 0; face < mesh->ncellFaces; face++) {

		int fid = face+refCell*mesh->ncellFaces;

		mesh->aN[fid] = 0;

	}

	mesh->r[refCell]  = refValue;


}
