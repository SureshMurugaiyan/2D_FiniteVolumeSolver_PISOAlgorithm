#include "mesh.h"
void insConstructFlux(double* HbyA, double* phiHbyA, mesh_t *mesh){

	dfloat *HbyAf;
	createSolutionSurfaceVector(&HbyAf,mesh);

	interpolateVectorCellToFace(HbyA,HbyAf,mesh);


	insConstructFluxofSurfaceVector(HbyAf,phiHbyA,mesh);


	free(HbyAf);
}


void insConstructFluxofSurfaceVector(double* HbyAf, double* phiHbyA, mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;

			double sum=0.0;

			for (int dim = 0; dim < mesh->nmeshdimension; dim++) {

				int fidm_dim = dim+ fid*mesh->nmeshdimension;
				int fids_dim = dim+ fid*mesh->nsolutiondimension;

				sum	=	sum+HbyAf[fids_dim]*mesh->Sf[fidm_dim];

			}

			phiHbyA[fid] = sum;
		}
	}

}
