#include "mesh.h"
double fvcDivergenceOfSurfaceScalar(dfloat alpha, dfloat* phiHbyA,mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {

		double sum = 0.0;

		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			sum = sum + phiHbyA[fid];

		}

		mesh->r[cell] = mesh->r[cell]+alpha*sum/mesh->V[cell];
	}

	return 0.0;
}
