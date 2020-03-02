#include "mesh.h"

void interpolateScalarCellToFace(dfloat* phiCell, dfloat* phiFace,mesh_t *mesh){

for(int cell=0;cell<mesh->ncells;cell++){
	for(int face=0;face<mesh->ncellFaces;face++){
		int fid = face+cell*mesh->ncellFaces;
		int cell_n	=  mesh->cellToCells[fid];

		if (cell_n>(-1)) {
			phiFace[fid] = mesh->fx[fid]*phiCell[cell]+(1-mesh->fx[fid])*phiCell[cell_n];
		}


	}
}

for(int cell=0;cell<mesh->ncells;cell++){
	for(int face=0;face<mesh->ncellFaces;face++){
		int fid = face+cell*mesh->ncellFaces;
		int cell_n	=  mesh->cellToCells[fid];
		int oface	=	mesh->faceToOppositeFaces[fid];
		int ofid	=	oface  + cell*mesh->ncellFaces;

		if (cell_n==(-1)) {

			phiFace[fid] = mesh->fx[fid]*phiCell[cell]+(1-mesh->fx[fid])*phiFace[ofid];
		}

	}
}

}
/*********************************************************************************/
void interpolateVectorCellToFace(dfloat* phiCell, dfloat* phiFace,mesh_t *mesh){

for(int cell=0;cell<mesh->ncells;cell++){
	for(int face=0;face<mesh->ncellFaces;face++){
		int fid = face+cell*mesh->ncellFaces;
		int cell_n	=  mesh->cellToCells[fid];


		if (cell_n>(-1)) {
			for(int dim=0;dim<mesh->nsolutiondimension;dim++){

				int fid_dim		= dim+fid*mesh->nsolutiondimension;
				int cell_dim	= dim+cell*mesh->nsolutiondimension;
				int cell_n_dim	= dim+cell_n*mesh->nsolutiondimension;

				phiFace[fid_dim] = mesh->fx[fid]*phiCell[cell_dim]+(1-mesh->fx[fid])*phiCell[cell_n_dim];
			}
		}


	}
}

for(int cell=0;cell<mesh->ncells;cell++){
	for(int face=0;face<mesh->ncellFaces;face++){
		int fid = face+cell*mesh->ncellFaces;
		int cell_n	=  mesh->cellToCells[fid];
		int oface	=	mesh->faceToOppositeFaces[fid];
		int ofid	=	oface  + cell*mesh->ncellFaces;

		if (cell_n==(-1)) {

			for(int dim=0;dim<mesh->nsolutiondimension;dim++){

				int fid_dim		= dim+fid*mesh->nsolutiondimension;
				int cell_dim	= dim+cell*mesh->nsolutiondimension;
				int ofid_dim	= dim+ofid*mesh->nsolutiondimension;

				phiFace[fid_dim] = mesh->fx[fid]*phiCell[cell_dim]+(1-mesh->fx[fid])*phiFace[ofid_dim];

			}

		}

	}
}

}
