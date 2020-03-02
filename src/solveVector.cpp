#include "mesh.h"
void solveVector(double* U, mesh_t *mesh){

	double maxNorm 	=	mesh->maxNorm;
	double lambda 	=	mesh->lambda;
	int	maxitrEqn	=	mesh->maxitrEqn;

	int itrEqn =0;
	bool stopCriterionUEqn=false;


	double *sum;
	double *delPhi;

	sum		= (dfloat*) calloc(mesh->nsolutiondimension, sizeof(dfloat));
	delPhi	= (dfloat*) calloc(mesh->nsolutiondimension, sizeof(dfloat));


	for (int i = 0; i < mesh->nsolutiondimension; i++) {
		sum[i]=0.0;
		delPhi[i]=0.0;
	}


	while (stopCriterionUEqn == false){

		for (int cell = 0; cell < mesh->ncells; cell++) {

			for (int i = 0; i < mesh->nsolutiondimension; i++) {
				sum[i]=0.0;
				delPhi[i]=0.0;
			}

			for (int face = 0; face < mesh->ncellFaces; face++) {


					int fid = face+cell*mesh->ncellFaces;
					int cell_n = mesh->cellToCells[fid];


					if (cell_n>(-1)){

						for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {

							int cell_n_dim =dim+ cell_n*mesh->nsolutiondimension;
							sum[dim] = sum[dim] + mesh->aN[fid]*U[cell_n_dim];
						}
					}

			}


			for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {

				int cell_dim = dim+cell*mesh->nsolutiondimension;

				sum[dim]    =  sum[dim]+ mesh->R[cell_dim] + mesh->aP[cell]*U[cell_dim];
				delPhi[dim] =  -sum[dim]/mesh->aP[cell];
				U[cell_dim] = U[cell_dim]+lambda*delPhi[dim];
			}




		}

		itrEqn++;
		if (itrEqn==maxitrEqn) {stopCriterionUEqn=true;}

	}


	free(sum);
	free(delPhi);

}
