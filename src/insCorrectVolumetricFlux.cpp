#include "mesh.h"

void calculateSnGradientFlux(double* p, double* phigradP_f, int P_Name, mesh_t *mesh);

void insCorrectVolumetricFlux(mesh_t *mesh){

	/**********************Calculate the face of values ************************************/
	dfloat *rAU_f;
	createSolutionSurfaceScalar(&rAU_f,mesh);
	interpolateScalarCellToFace(mesh->rAU,rAU_f,mesh);

	dfloat *phigradP_f;
	createSolutionSurfaceScalar(&phigradP_f,mesh);
	calculateSnGradientFlux(mesh->p, phigradP_f, p, mesh);

	// correct the flux


	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;

			mesh->phiU[fid] = mesh->phiHbyA[fid]-rAU_f[fid]*phigradP_f[fid];


		}
	}


	for (int cell = 0; cell < mesh->ncells; cell++) {

		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];

			double sum = 0.0;

			if (cell_n==(-1)){

				for (int i = 0; i < (mesh->ncellFaces-1); i++){

					int idtemp = mesh->faceToLocalFaces[face+i+1];

					int fid_b = idtemp+cell*mesh->ncellFaces;

					sum  = sum+ mesh->phiU[fid_b];
				}
				mesh->phiU[fid] = -sum;
			}
		}

	}



	free(rAU_f);
	free(phigradP_f);


}

void calculateSnGradientFlux(double* p, double* phigradP_f, int P_name, mesh_t *mesh){


	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

				int fid = face+cell*mesh->ncellFaces;
				int cell_n = mesh->cellToCells[fid];


				/* Loop through internal faces */
				if (cell_n>(-1)){

					phigradP_f[fid]	=	mesh->magSf[fid]*(p[cell_n]-p[cell])/mesh->magd[fid];
				}

				/* Loop through Boundary faces */
				if (cell_n==(-1)){

					insGetBoundaryCondition(P_name,fid,mesh);

					if (mesh->bctype==fixedValue){

						phigradP_f[fid]	=	mesh->magSf[fid]*(mesh->bcvalueScalar[0]-p[cell])/mesh->magd[fid];
					}

					if (mesh->bctype==fixedNormalGradient){

						phigradP_f[fid]	=	0.0;

					}

				}

		}
	}



//
//	for (int cell = 0; cell < mesh->ncells; cell++) {
//		for (int face = 0; face < mesh->ncellFaces; face++) {
//
//			int fid = face+cell*mesh->ncellFaces;
//			int cell_n = mesh->cellToCells[fid];
//
//			if (cell_n>(-1)){
//
//				for (int dim = 0; dim < mesh->nmeshdimension; dim++) {
//
//					int fid_dim		= dim + fid*mesh->nsolutiondimension;
//					int cell_dim	= dim + cell*mesh->nmeshdimension;
//					int cell_n_dim	= dim + cell_n*mesh->nmeshdimension;
//
//					double den = magnitude ((mesh->C[cell_n_dim]-mesh->C[cell_dim]));
//
//					if (den > 0.0) {
//						gradP_f[fid_dim] = (p[cell_n]-p[cell])/(mesh->C[cell_n_dim]-mesh->C[cell_dim]);
//					}
//
//
//				}
//			}
//
//			if (cell_n==(-1)){
//
//				insGetBoundaryCondition(P_name,fid,mesh);
//
//				if (mesh->bctype==fixedValue){
//
//					for (int dim = 0; dim < mesh->nmeshdimension; dim++) {
//						int fid_dim		= dim + fid*mesh->nsolutiondimension;
//
//						int fid_mdim    = dim + fid*mesh->nmeshdimension;
//						int cell_dim	= dim + cell*mesh->nmeshdimension;
//						int cell_n_dim	= dim + cell_n*mesh->nmeshdimension;
//
//						double den = magnitude ((mesh->Cf[fid_mdim]-mesh->C[cell_dim]));
//
//						if (den > 0.0) {
//							gradP_f[fid_dim] = (mesh->bcvalueScalar[0]-p[cell])/(mesh->Cf[fid_mdim]-mesh->C[cell_dim]) ;
//						}
//
//					}
//
//				}
//
//				if (mesh->bctype==fixedNormalGradient){
//
//					for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
//						int fid_dim		= dim + fid*mesh->nsolutiondimension;
//						gradP_f[fid_dim] = 0.0;
//					}
//
//				}
//
//
//			}
//		}
//	}

}



