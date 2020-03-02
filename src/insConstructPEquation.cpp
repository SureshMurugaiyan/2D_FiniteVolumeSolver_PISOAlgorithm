#include "mesh.h"

void insConstructPEquation(mesh_t *mesh){

		for(int i=0;i<mesh->ncells;++i){
			mesh->aP[i] = 0.0;
			mesh->r[i] 	= 0.0;
		}



		for(int i=0;i<mesh->ncells*mesh->nsolutiondimension;++i){
			mesh->R[i]  = 0.0;
		}

		for(int i=0;i<mesh->ncells*mesh->ncellFaces;++i){
			mesh->aN[i] = 0.0;
		}

	double Peqn=0.0;
	double alpha1 = 1.0;
	double alpha2 =-1.0;



	Peqn = fvmLaplacianOfScalar (alpha1, mesh->rAU, mesh->p,p,mesh)+ fvcDivergenceOfSurfaceScalar (alpha2,mesh->phiHbyA,mesh);


}
