#include "mesh.h"
void solveScalar(double* P, mesh_t *mesh){

	double maxNorm 	=	mesh->maxNorm;
	double lambda 	=	mesh->lambda;
	int	maxitrEqn	=	mesh->maxitrEqn;

	int itrEqn = 0;
	bool stopCriterionUEqn=false;

	double sum =0.0;
	double delPhi=0.0;

	while (stopCriterionUEqn==false){

		for (int cell = 0; cell < mesh->ncells; cell++) {
			sum =0.0;
			delPhi=0.0;
			for (int face = 0; face < mesh->ncellFaces; face++) {

				int fid = face+cell*mesh->ncellFaces;
				int cell_n = mesh->cellToCells[fid];


				if (cell_n>(-1)){

				sum = sum + mesh->aN[fid]*P[cell_n];
				}

			}

			sum = sum+ mesh->r[cell]+mesh->aP[cell]*P[cell];
			delPhi = -sum/mesh->aP[cell];
			P[cell] = P[cell]+lambda*delPhi;

		}

		itrEqn++;
		if (itrEqn==maxitrEqn) {stopCriterionUEqn=true;}

	}




}
