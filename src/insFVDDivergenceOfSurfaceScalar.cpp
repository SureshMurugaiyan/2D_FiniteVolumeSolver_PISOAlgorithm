#include "mesh.h"
void fvdDivergenceOfSurfaceScalar(double* phiU, double* divphiU, mesh_t *mesh){

		for (int cell = 0; cell < mesh->ncells; cell++) {

			double sum = 0.0;

			for (int face = 0; face < mesh->ncellFaces; face++) {

				int fid = face+cell*mesh->ncellFaces;
				sum = sum + phiU[fid];

			}

			mesh->divphiU[cell] = sum/mesh->V[cell];
		}

}
