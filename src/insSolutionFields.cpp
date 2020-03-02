#include "mesh.h"
void insConstructSolutionFields(mesh_t *mesh){

	createSolutionVolumeVector(&mesh->U,mesh);
	createSolutionVolumeScalar(&mesh->p,mesh);
	createSolutionVolumeScalar(&mesh->rho,mesh);
	createSolutionVolumeScalar(&mesh->mu,mesh);

	createSolutionSurfaceScalar(&mesh->phiU,mesh);
	createSolutionVolumeScalar(&mesh->divphiU,mesh);

	createSolutionVolumeVector(&mesh->U0,mesh);
	createSolutionVolumeVector(&mesh->U00,mesh);


	mesh->bcvalueScalar	= (dfloat*) calloc(1, sizeof(dfloat));
	mesh->bcvalueVector	= (dfloat*) calloc(mesh->nsolutiondimension, sizeof(dfloat));


	mesh->bcvalueScalar[0]=0.0;
	for (int i = 0; i < mesh->nsolutiondimension; i++) {
		mesh->bcvalueVector[i]=0.0;
	}

	createSolutionVolumeScalar(&mesh->rAU,mesh);

	createSolutionVolumeVector(&mesh->HbyA,mesh);
	createSolutionSurfaceScalar(&mesh->phiHbyA,mesh);

}

void insDestructSolutionFields(mesh_t *mesh){

	free(mesh->U);
	free(mesh->p);
	free(mesh->rho);
	free(mesh->mu);

	free(mesh->phiU);
	free(mesh->divphiU);

	free(mesh->U0);
	free(mesh->U00);

	free(mesh->bcvalueScalar);
	free(mesh->bcvalueVector);

	free(mesh->rAU);

	free(mesh->HbyA);
	free(mesh->phiHbyA);
}

