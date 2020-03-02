#include "mesh.h"

void solverConstructFields(mesh_t *mesh){

	createSolutionVolumeScalar(&mesh->aP,mesh);
	createSolutionSurfaceScalar(&mesh->aN,mesh);
	createSolutionVolumeVector(&mesh->R,mesh);
	createSolutionVolumeScalar(&mesh->r,mesh);

}

void solverDestructFields(mesh_t *mesh){

	free(mesh->aP);
	free(mesh->aN);
	free(mesh->R);
	free(mesh->r);


}
