#include "mesh.h"


double ddteulerbackward(dfloat* rho, dfloat* U0, dfloat* U00,mesh_t *mesh){

// For First time step , use First Order Euler

	if (mesh->timeStep==0){

		for (int cell = 0; cell < mesh->ncells; cell++) {

			mesh->aP[cell] = mesh->aP[cell]+ rho[cell]/mesh->deltatime;
		}

		for (int cell = 0; cell < mesh->ncells; cell++) {
			for (int dimension = 0; dimension < mesh->nsolutiondimension; dimension++) {

				int cell_dim = dimension + cell*mesh->nsolutiondimension;
				mesh->R[cell_dim]  = mesh->R[cell_dim] - rho[cell]*U0[cell_dim]/mesh->deltatime;

			}
		}

	}

	// From second time step , use euler backward

	if (mesh->timeStep> 0){

		for (int cell = 0; cell < mesh->ncells; cell++) {

			mesh->aP[cell] = mesh->aP[cell]+ 3.0*rho[cell]/(2.0*mesh->deltatime);
		}


		for (int cell = 0; cell < mesh->ncells; cell++) {
			for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {

				int cell_dim = dim + cell*mesh->nsolutiondimension;

				mesh->R[cell_dim]  = mesh->R[cell_dim] - (4.0*rho[cell]*U0[cell_dim]-rho[cell]*U00[cell_dim])/(2.0*mesh->deltatime);
			}
		}

	}



	return 0.0;

}
