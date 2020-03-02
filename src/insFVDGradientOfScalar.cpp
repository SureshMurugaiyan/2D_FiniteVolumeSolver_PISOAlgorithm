#include "mesh.h"
void fvdGradientOfScalar(dfloat* gradCell,dfloat *phiCell, int P_Name, mesh_t *mesh){

	dfloat *pf;
	createSolutionSurfaceScalar(&pf,mesh);

	interpolateScalarCellToFace(mesh->p,pf,mesh);

	insConstrainByBoundaryFieldScalar(pf,mesh->p,p,mesh);


	double *sum;
	sum		= (dfloat*) calloc(mesh->nsolutiondimension, sizeof(dfloat));


	for (int cell = 0; cell < mesh->ncells; cell++) {

		for (int i = 0; i < mesh->nsolutiondimension; i++) {
			sum[i]=0.0;
		}


		for (int face = 0; face < mesh->ncellFaces; face++) {
			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];



			for (int dim = 0; dim < mesh->nmeshdimension; dim++) {
				int fid_dim = dim+ fid*mesh->nmeshdimension;
				sum[dim]	=	sum[dim]+pf[fid]*mesh->Sf[fid_dim];
			}

		}

		for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {
			int cell_dim = dim+ cell*mesh->nsolutiondimension;
			gradCell[cell_dim]  = sum[dim]/mesh->V[cell];
		}


	}



	free(pf);
	free(sum);
}
