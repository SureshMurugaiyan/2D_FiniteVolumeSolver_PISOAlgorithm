#include "mesh.h"

void insSetInitialConditions(mesh_t *mesh){



	int dimx = 0; // dim = 0 gives x component
	int dimy = 1; // dim = 1 gives y component
	int dimz = 2; // dim = 1 gives y component

	int idx,idy,idz;
	int idmx,idmy,idmz;

	for(int cell=0;cell<mesh->ncells;++cell){


		idx	= dimx+cell*mesh->nsolutiondimension;
		idy	= dimy+cell*mesh->nsolutiondimension;
		idz	= dimz+cell*mesh->nsolutiondimension;

		idmx	= dimx+cell*mesh->nmeshdimension;
		idmy	= dimy+cell*mesh->nmeshdimension;
		idmz	= dimz+cell*mesh->nmeshdimension;

		mesh->mu[cell]  =  1.0;
		mesh->rho[cell] =  1.0;

		mesh->U[idx]	= 0;
		mesh->U[idy]	= 0;
		mesh->U[idz]	= 0;

		mesh->p[cell]	= 0;


	}


}
