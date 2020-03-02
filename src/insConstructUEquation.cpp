#include "mesh.h"
void insConstructUEquation(mesh_t *mesh){

	for(int i=0;i<mesh->ncells;++i){
		mesh->aP[i] = 0.0;
		mesh->r[i] 	= 0.0;
	}

	for(int i=0;i<mesh->ncells*mesh->ncellFaces;++i){
		mesh->aN[i] = 0.0;
	}


	for(int i=0;i<mesh->ncells*mesh->nsolutiondimension;++i){
		mesh->R[i]  = 0.0;
	}

	double Ueqn=0.0;




	Ueqn =	ddteulerbackward(mesh->rho,mesh->U0, mesh->U00, mesh)
		+ fvmLaplacianOfVector (-1.0, mesh->mu, mesh->U,U,mesh)
		+ fvmDivergenceOfVector (1.0, mesh->rho, mesh->U,U,mesh->phiU,mesh);

//	Ueqn =	ddteulerbackward(mesh->rho,mesh->U0, mesh->U00, mesh)
//		+ fvcLaplacianOfVector (-1.0, mesh->mu, mesh->U,U,mesh)
//		+fvcDivergenceOfVector (1.0, mesh->rho, mesh->U,U,mesh->phiU,mesh);


	for (int cell = 0; cell < mesh->ncells; cell++) {
		mesh->rAU[cell]=1.0/mesh->aP[cell];
	}
}
