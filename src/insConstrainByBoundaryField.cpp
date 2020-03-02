
#include "mesh.h"

void insConstrainByBoundaryFieldVector(double* Uf, double* U, int U_name,mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

				int fid = face+cell*mesh->ncellFaces;
				int cell_n = mesh->cellToCells[fid];

				if (cell_n == (-1)){

					insGetBoundaryCondition(U_name,fid,mesh);

					if (mesh->bctype==fixedValue){
						for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {

							int fid_dim = dim+ fid*mesh->nsolutiondimension;

							Uf[fid_dim] = mesh->bcvalueVector[dim];
						}
					}

					if (mesh->bctype==fixedNormalGradient){
						for (int dim = 0; dim < mesh->nsolutiondimension; dim++) {

							int fid_dim = dim+ fid*mesh->nsolutiondimension;

							Uf[fid_dim] = U[cell];
						}
					}

				}

		}
	}
}


void insConstrainByBoundaryFieldScalar(double* pf,double* pcell,int p_name,mesh_t *mesh){

	for (int cell = 0; cell < mesh->ncells; cell++) {
		for (int face = 0; face < mesh->ncellFaces; face++) {

			int fid = face+cell*mesh->ncellFaces;
			int cell_n = mesh->cellToCells[fid];

			if (cell_n == (-1)){

				insGetBoundaryCondition(p_name,fid,mesh);

				if (mesh->bctype==fixedValue){
					pf[fid] = mesh->bcvalueScalar[0];
				}

				if (mesh->bctype==fixedNormalGradient){
					pf[fid] = pcell[cell];
				}

			}

		}
	}
}
