#include "mesh.h"
void insConstructHbyAEqn(mesh_t *mesh){

//	insConstructUEquation(mesh);

	double *sum;
	sum		= (dfloat*) calloc(mesh->nsolutiondimension, sizeof(dfloat));

	for (int i = 0; i < mesh->nsolutiondimension; i++) {
		sum[i]=0.0;
	}



	for (int cell = 0; cell < mesh->ncells; cell++) {

		for (int i = 0; i < mesh->nsolutiondimension; i++) {
			sum[i]=0.0;
		}


		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];


			if (cell_n>(-1)){

				for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {

					int cell_dim 	=	dim	+ cell*mesh->nsolutiondimension;
					int cell_n_dim 	=	dim	+ cell_n*mesh->nsolutiondimension;

					sum[dim] = sum[dim] + mesh->aN[fid]*mesh->U[cell_n_dim];
				}

			}

		}


		for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
			int cell_dim = dim+cell*mesh->nsolutiondimension;
			mesh->HbyA[cell_dim] = (-sum[dim]-mesh->R[cell_dim])*mesh->rAU[cell];
		}


	}


	free(sum);

}



