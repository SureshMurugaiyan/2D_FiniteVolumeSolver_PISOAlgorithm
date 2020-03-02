#include "mesh.h"
double fvmLaplacianOfVector(double alpha, dfloat* mu, dfloat* U,int U_name,mesh_t *mesh){

	/**********************Calculate the face values ************************************/
	dfloat *mu_f;
	createSolutionSurfaceScalar(&mu_f,mesh);
	interpolateScalarCellToFace(mu,mu_f,mesh);



	/**********************Calculate the Coefficients of Matrix ************************************/

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

				int fid = face+cell*mesh->ncellFaces;
				int cell_n = mesh->cellToCells[fid];


				/* Loop through internal faces */
				if (cell_n>(-1)){

					mesh->aP[cell]	=	mesh->aP[cell] - (alpha/mesh->V[cell])*mu_f[fid]*mesh->magSf[fid]/mesh->magd[fid];
					mesh->aN[fid]	=	mesh->aN[fid]  + (alpha/mesh->V[cell])*mu_f[fid]*mesh->magSf[fid]/mesh->magd[fid];
				}

				/* Loop through Boundary faces */
				if (cell_n==(-1)){

					insGetBoundaryCondition(U_name,fid,mesh);

					if (mesh->bctype==fixedValue){

						mesh->aP[cell]	=	mesh->aP[cell] - (alpha/mesh->V[cell])*(mu_f[fid]*mesh->magSf[fid]/mesh->magd[fid]);

						for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
							int cell_dim = dim+cell*mesh->nsolutiondimension;
							mesh->R[cell_dim]	=	mesh->R[cell_dim]
															+ (alpha/mesh->V[cell])*(mu_f[fid]*mesh->magSf[fid]/mesh->magd[fid])*mesh->bcvalueVector[dim];

						}

					}

					if (mesh->bctype==fixedNormalGradient){


						for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
							int cell_dim = dim+cell*mesh->nsolutiondimension;
							mesh->R[cell_dim]	=	mesh->R[cell_dim]
															+ (alpha/mesh->V[cell])*(mu_f[fid]*mesh->bcvalueVector[dim]*mesh->magSf[fid]);
						}

					}

				}

		}
	}


	free(mu_f);
	return 0.0;
}
