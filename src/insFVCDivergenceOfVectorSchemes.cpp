#include "mesh.h"
double fvcDivergenceOfVector(double alpha, dfloat* rho, dfloat* U,int U_name,
		dfloat* phiU, mesh_t *mesh){

	/**********************Calculate the face values ************************************/
	dfloat *rho_f;
	createSolutionSurfaceScalar(&rho_f,mesh);
	interpolateScalarCellToFace(rho,rho_f,mesh);


	/**********************Calculate the Coefficients of Matrix ************************************/

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];


			/* Loop through internal faces */
			if (cell_n>(-1)){

				for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
					int cell_dim = dim+cell*mesh->nsolutiondimension;
					int cell_ndim = dim+cell_n*mesh->nsolutiondimension;

					mesh->R[cell_dim]	= mesh->R[cell_dim]
												  + (alpha/mesh->V[cell])*rho_f[fid]*mesh->phiU[fid]*(mesh->fx[fid]*U[cell_dim] + (1.0-mesh->fx[fid])*U[cell_ndim] );
				}


			}

			/* Loop through Boundary faces */
			if (cell_n==(-1)){

				insGetBoundaryCondition(U_name,fid,mesh);


				if (mesh->bctype==fixedValue){

					for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
						int cell_dim = dim+cell*mesh->nsolutiondimension;
						mesh->R[cell_dim]	= mesh->R[cell_dim] + (alpha/mesh->V[cell])*rho_f[fid]*mesh->phiU[fid]*mesh->bcvalueVector[dim];
					}
				}

				if (mesh->bctype==fixedNormalGradient){

					for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
						int cell_dim = dim+cell*mesh->nsolutiondimension;
						mesh->R[cell_dim]	= mesh->R[cell_dim] + (alpha/mesh->V[cell])*rho_f[fid]*mesh->phiU[fid]*U[cell_dim];
					}

				}

			}
		}
	}

	free(rho_f);
	return 0.0;
}
