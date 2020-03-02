
#include "mesh.h"

void meshCellToCellsConnectivity(mesh_t *mesh);
void meshCellToFacesConnectivity(mesh_t *mesh);
void meshFaceToOppositeFacesConnectivity(mesh_t *mesh);
void meshFaceToVerticesConnectivity(mesh_t *mesh);
void meshFaceToLocalFaceConnectivity(mesh_t *mesh);

void meshGenerateCellConnectivity(mesh_t *mesh){

	meshCellToCellsConnectivity(mesh);
	meshCellToFacesConnectivity(mesh);
	meshFaceToOppositeFacesConnectivity(mesh);
	meshFaceToVerticesConnectivity(mesh);

	meshFaceToLocalFaceConnectivity(mesh);

}

void meshCellToCellsConnectivity(mesh_t *mesh){

	int COLMAX = mesh->ncellsx;
	int ROWMAX = mesh->ncellsy;


	// This is Hard Coded for 2D
	if (mesh->ncellFaces !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellFaces should be set to %i!\n", 4 );
		exit ( 1 );
	}

	int *cells;
	cells	= (int*) calloc(mesh->ncellFaces, sizeof(int));


		for (int row = 0; row < ROWMAX; row++) {
			for (int col = 0; col < COLMAX; col++) {

				cells[0] =  (col-1) + (row+0)*COLMAX;
				cells[1] =  (col+0) + (row+1)*COLMAX;
				cells[2] =  (col+1) + (row+0)*COLMAX;
				cells[3] =  (col+0) + (row-1)*COLMAX;

				for (int f = 0; f < mesh->ncellFaces; f++) {

					int index = f 	+ col*mesh->ncellFaces
									+ row*mesh->ncellFaces*COLMAX;
					mesh->cellToCells[index] = cells[f];


					// Correct for north boundary
					if ((row ==0) && (f==3)){
						mesh->cellToCells[index] = -1;
					}

					// Correct for south boundary
					if ((row ==(ROWMAX-1)) && (f==1)){
						mesh->cellToCells[index] = -1;
					}


		            // Correct for West boundary
					if ((col==0) && (f==0)){
						mesh->cellToCells[index] = -1;
					}


		            // Correct for East boundary
					if ((col==(COLMAX-1)) && (f==2)){
						mesh->cellToCells[index] = -1;
					}

				}
			}
		}


		free(cells);


}

void meshCellToFacesConnectivity(mesh_t *mesh){

	int COLMAX = mesh->ncellsx;
	int ROWMAX = mesh->ncellsy;

	// This is Hard Coded for 2D
	if (mesh->ncellFaces !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellFaces should be set to %i!\n", 4 );
		exit ( 1 );
	}

	int *cells;
	cells	= (int*) calloc(mesh->ncellFaces, sizeof(int));

		for (size_t row = 0; row < ROWMAX; row++) {
			for (size_t col = 0; col < COLMAX; col++) {

				cells[0] =  2;
				cells[1] =  3;
				cells[2] =  0;
				cells[3] =  1;


				for (size_t f = 0; f < mesh->ncellFaces; f++) {
					int index = f 	+ col*mesh->ncellFaces
									+ row*mesh->ncellFaces*COLMAX;
					mesh->cellToFaces[index] = cells[f];

					// Correct for north boundary
					if ((row ==0) && (f==3)){
						mesh->cellToFaces[index] = -1;
					}

					// Correct for south boundary
					if ((row ==(ROWMAX-1)) && (f==1)){
						mesh->cellToFaces[index] = -1;
					}


		            // Correct for West boundary
					if ((col==0) && (f==0)){
						mesh->cellToFaces[index] = -1;
					}


		            // Correct for East boundary
					if ((col==(COLMAX-1)) && (f==2)){
						mesh->cellToFaces[index] = -1;
					}
				}

			}

		}


	free(cells);

}


void meshFaceToVerticesConnectivity(mesh_t *mesh){

	mesh->faceToVertices[0] = 0;
	mesh->faceToVertices[1] = 1;
	mesh->faceToVertices[2] = 1;
	mesh->faceToVertices[3] = 2;
	mesh->faceToVertices[4] = 2;
	mesh->faceToVertices[5] = 3;
	mesh->faceToVertices[6] = 3;
	mesh->faceToVertices[7] = 0;

}



void meshFaceToOppositeFacesConnectivity(mesh_t *mesh){

	int COLMAX = mesh->ncellsx;
	int ROWMAX = mesh->ncellsy;

	// This is Hard Coded for 2D
	if (mesh->ncellFaces !=4) {
		printf ( "\n" );
		printf ( "Fatal error!\n" );
		printf ( "  mesh->ncellFaces should be set to %i!\n", 4 );
		exit ( 1 );
	}

	int *cells;
	cells	= (int*) calloc(mesh->ncellFaces, sizeof(int));

		for (size_t row = 0; row < ROWMAX; row++) {
			for (size_t col = 0; col < COLMAX; col++) {

				cells[0] =  2;
				cells[1] =  3;
				cells[2] =  0;
				cells[3] =  1;


				for (size_t f = 0; f < mesh->ncellFaces; f++) {
					int index = f 	+ col*mesh->ncellFaces
									+ row*mesh->ncellFaces*COLMAX;
					mesh->faceToOppositeFaces[index] = cells[f];

				}

			}

		}


	free(cells);

}

void meshFaceToLocalFaceConnectivity(mesh_t *mesh){

	mesh->faceToLocalFaces[0] = 0;
	mesh->faceToLocalFaces[1] = 1;
	mesh->faceToLocalFaces[2] = 2;
	mesh->faceToLocalFaces[3] = 3;
	mesh->faceToLocalFaces[4] = 0;
	mesh->faceToLocalFaces[5] = 1;
	mesh->faceToLocalFaces[6] = 2;
	mesh->faceToLocalFaces[7] = 3;

}
