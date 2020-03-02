#include "mesh.h"
double fvmLaplacianOfScalar(double alpha, dfloat* rAU, dfloat* p,int P_name,mesh_t *mesh){

	/**********************Calculate the face values ************************************/
	dfloat *rAU_f;
	createSolutionSurfaceScalar(&rAU_f,mesh);
	interpolateScalarCellToFace(rAU,rAU_f,mesh);



	/**********************Calculate the Coefficients of Matrix ************************************/

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

				int fid = face+cell*mesh->ncellFaces;
				int cell_n = mesh->cellToCells[fid];


				/* Loop through internal faces */
				if (cell_n>(-1)){

					mesh->aP[cell]	=	mesh->aP[cell] - (alpha/mesh->V[cell])*rAU_f[fid]*mesh->magSf[fid]/mesh->magd[fid];
					mesh->aN[fid]	=	mesh->aN[fid]  + (alpha/mesh->V[cell])*rAU_f[fid]*mesh->magSf[fid]/mesh->magd[fid];
				}

				/* Loop through Boundary faces */
				if (cell_n==(-1)){

					insGetBoundaryCondition(P_name,fid,mesh);

					if (mesh->bctype==fixedValue){

						mesh->aP[cell]	=	mesh->aP[cell] - (alpha/mesh->V[cell])*(rAU_f[fid]*mesh->magSf[fid]/mesh->magd[fid]);
						mesh->r[cell]	=	mesh->r[cell]  + (alpha/mesh->V[cell])*(rAU_f[fid]*mesh->magSf[fid]/mesh->magd[fid])*mesh->bcvalueScalar[0];
					}

					if (mesh->bctype==fixedNormalGradient){

						double g_b = mesh->bcvalueScalar[0];
						mesh->r[cell]	=	mesh->r[cell]  + (alpha/mesh->V[cell])*(rAU_f[fid]*g_b*mesh->magSf[fid]);

					}

				}

		}
	}


	free(rAU_f);
	return 0.0;
}
