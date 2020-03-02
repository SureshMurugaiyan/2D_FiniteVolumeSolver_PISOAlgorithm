#include "mesh.h"
void insCorrectU(mesh_t *mesh){

	dfloat *gradP; // cell center Pressure gradient
	createSolutionVolumeVector(&gradP,mesh);
	fvdGradientOfScalar(gradP,mesh->p,p,mesh);

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
			int cell_dim = dim+ cell*mesh->nsolutiondimension;

			mesh->U[cell_dim]=mesh->HbyA[cell_dim]-mesh->rAU[cell]*gradP[cell_dim];
		}

	}


	free(gradP);


}
