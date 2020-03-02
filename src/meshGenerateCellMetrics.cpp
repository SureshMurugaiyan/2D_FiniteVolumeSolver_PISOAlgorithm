#include "mesh.h"


void generateCellCenters(mesh_t *mesh);
void generateFaceCenters(mesh_t *mesh);
void generateFaceAreas(mesh_t *mesh);
void generateCellVolumes(mesh_t *mesh);
void generateCellFaceInterpolationFactor(mesh_t *mesh);
void generateCellFaceExtrapolationFactor(mesh_t *mesh);
void generateCellToCellDistanceVectors(mesh_t *mesh);
void writeMeshMetrics(mesh_t *mesh);


void meshGenerateCellMetrics(mesh_t *mesh){

	generateCellCenters(mesh);
	generateFaceCenters(mesh);
	generateFaceAreas(mesh);
	generateCellVolumes(mesh);

	generateCellFaceInterpolationFactor(mesh);
	generateCellFaceExtrapolationFactor(mesh);
	generateCellToCellDistanceVectors(mesh);

	writeMeshMetrics(mesh);
}

void generateCellCenters(mesh_t *mesh){


	for( int cell = 0; cell < mesh->ncells;cell++){

		double *sum;
		sum = (double*) calloc(mesh->nmeshdimension, sizeof(double));
		for (int i = 0; i < (mesh->nmeshdimension); i++) { sum[i] = 0;}

		for(int vertex=0;vertex<mesh->ncellVertices;vertex++){
			for(int dimension=0;dimension<mesh->nmeshdimension;dimension++){
				int vid = dimension + vertex*mesh->nmeshdimension
								    + cell*mesh->nmeshdimension*mesh->ncellVertices;
				sum[dimension] = sum[dimension] + mesh->vertices[vid];
			}
		}

		for(int dimension=0;dimension<mesh->nmeshdimension;dimension++){
			int cid = dimension+cell*mesh->nmeshdimension;
			mesh->C[cid] = sum[dimension]/mesh->ncellVertices;
		}
		free(sum);
	}

}


void generateFaceCenters(mesh_t *mesh){

	for( int cell = 0; cell < mesh->ncells;cell++){
		for (int face = 0; face < mesh->ncellFaces; ++face) {

			double *sum;
			sum = (double*) calloc(mesh->nmeshdimension, sizeof(double));
			for (int i = 0; i < (mesh->nmeshdimension); i++) { sum[i] = 0;}

			for (int facevertex = 0; facevertex < mesh->nfaceVertices; facevertex++){

				int vertex = mesh->faceToVertices[facevertex+face*mesh->nfaceVertices];

				for (int dimension = 0; dimension < mesh->nmeshdimension; dimension++) {
					int vid = dimension+vertex*mesh->nmeshdimension+ cell*mesh->ncellVertices*mesh->nmeshdimension;
					sum[dimension] = sum[dimension] + mesh->vertices[vid];
				}


			}

			for(int dimension=0;dimension<mesh->nmeshdimension;dimension++){
				int fid = dimension + face*mesh->nmeshdimension+
								    + cell*mesh->ncellFaces*mesh->nmeshdimension;
				mesh->Cf[fid] = sum[dimension]/mesh->nfaceVertices;
			}

			free(sum);

		}
	}

}

void generateFaceAreas(mesh_t *mesh){

	/* Face area in 2D = dl X k */
	/* compute component of length vector of each face, dl = dx i + dy j */
	/* Face area in 2D = dy i -dx j */

	for( int cell = 0; cell < mesh->ncells;cell++){
		for (int face = 0; face < mesh->ncellFaces; ++face) {

			double *dl;
			dl = (double*) calloc(mesh->nmeshdimension, sizeof(double));
			for (int i = 0; i < (mesh->nmeshdimension); i++) { dl[i] = 0;}

			int facevertex,vertex1,vertex2,vid1,vid2;
			facevertex = 0;
			vertex1 = mesh->faceToVertices[facevertex+face*mesh->nfaceVertices];
			facevertex = 1;
			vertex2 = mesh->faceToVertices[facevertex+face*mesh->nfaceVertices];

			for (int dimension = 0; dimension < mesh->nmeshdimension; dimension++) {
				vid1 = dimension+vertex1*mesh->nmeshdimension+ cell*mesh->ncellVertices*mesh->nmeshdimension;
				vid2 = dimension+vertex2*mesh->nmeshdimension+ cell*mesh->ncellVertices*mesh->nmeshdimension;

				dl[dimension] =  mesh->vertices[vid2]-mesh->vertices[vid1]; // calculate length vector, dx = x2-x1 , dy- y2-y1;
			}

			int dimension,fidx,fidy;
			dimension =0;
			fidx = dimension + face*mesh->nmeshdimension+cell*mesh->ncellFaces*mesh->nmeshdimension;
			dimension =1;
			fidy = dimension + face*mesh->nmeshdimension+cell*mesh->ncellFaces*mesh->nmeshdimension;

			mesh->Sf[fidx] =  dl[1];
			mesh->Sf[fidy] = -dl[0];

			free(dl);

		}
	}

	// Compute the magnitude of the face areas
	for( int cell = 0; cell < mesh->ncells;cell++){
		for (int face = 0; face < mesh->ncellFaces; ++face) {

			double *area;
			area = (double*) calloc(mesh->nmeshdimension, sizeof(double));

			for (int dimension = 0; dimension < mesh->nmeshdimension; dimension++) {

				int id = dimension + face*mesh->nmeshdimension+cell*mesh->ncellFaces*mesh->nmeshdimension;
				area[dimension] = mesh->Sf[id];
			}

			int fid		=  face  + cell*mesh->ncellFaces;
			mesh->magSf[fid] = sqrt(pow(area[0],2)+pow(area[1],2));
			free(area);
		}
	}


}

void generateCellVolumes(mesh_t *mesh){
	/* Cell area in 2D = one half of cross product of its diagonals */
	/* a->northwest , b->southwest , c->southeast , d->northeast  corners of cell*/
	/* area = 0.5* (r_bd X r_ca), where r is diagonal vector */

	double *a; a = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	double *b; b = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	double *c; c = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	double *d; d = (double*) calloc(mesh->nmeshdimension, sizeof(double));

	double *r_bd; r_bd = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	double *r_ca; r_ca = (double*) calloc(mesh->nmeshdimension, sizeof(double));

	for (int cell = 0; cell < mesh->ncells; cell++) {

		int vertex_a = 0 + cell * mesh->ncellVertices;
		int vertex_b = 1 + cell * mesh->ncellVertices;
		int vertex_c = 2 + cell * mesh->ncellVertices;
		int vertex_d = 3 + cell * mesh->ncellVertices;



		for (int dimension = 0; dimension < mesh->nmeshdimension; dimension++) {

			a[dimension] = mesh->vertices[dimension+vertex_a*mesh->nmeshdimension];
			b[dimension] = mesh->vertices[dimension+vertex_b*mesh->nmeshdimension];
			c[dimension] = mesh->vertices[dimension+vertex_c*mesh->nmeshdimension];
			d[dimension] = mesh->vertices[dimension+vertex_d*mesh->nmeshdimension];

			r_bd[dimension] = d[dimension]-b[dimension];
			r_ca[dimension] = a[dimension]-c[dimension];
		}

		mesh->V[cell] = 0.5*(r_bd[0]*r_ca[1]-r_bd[1]*r_ca[0]) ; // cross product of r_bd and r_ca


	}

	free(a);
	free(b);
	free(c);
	free(d);

	free(r_bd);
	free(r_ca);

}

void generateCellFaceInterpolationFactor(mesh_t *mesh){

	double *f;
	double *N;
	double *P;

	f = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	N = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	P = (double*) calloc(mesh->nmeshdimension, sizeof(double));

	for (size_t i = 0; i < mesh->nmeshdimension; i++) {
		f[i] = 0;
		N[i] = 0;
		P[i] = 0;
	}

	for (int cell = 0; cell < mesh->ncells; ++cell) {
		for (int face = 0; face < mesh->ncellFaces; ++face) {

			int fid		=  face  + cell*mesh->ncellFaces;
			int cell_n	=  mesh->cellToCells[fid];

			if (cell_n>(-1)) {

				for (int dim = 0; dim < mesh->nmeshdimension; dim++) {
					f[dim] = mesh->Cf[fid*mesh->nmeshdimension+dim];
					N[dim] = mesh->C[cell_n*mesh->nmeshdimension+dim];
					P[dim] = mesh->C[cell*mesh->nmeshdimension+dim];
				}

				double fN = distance(f,N);
				double PN = distance(P,N);

				mesh->fx[fid] = fN/PN;

			}

		}
	}

	free(f);
	free(N);
	free(P);

}


void generateCellFaceExtrapolationFactor(mesh_t *mesh){

	double *f;
	double *b;
	double *P;

	f = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	b = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	P = (double*) calloc(mesh->nmeshdimension, sizeof(double));

	for (size_t i = 0; i < mesh->nmeshdimension; i++) {
		f[i] = 0;
		b[i] = 0;
		P[i] = 0;
	}

	for (int cell = 0; cell < mesh->ncells; ++cell) {
		for (int face = 0; face < mesh->ncellFaces; ++face) {

			int fid		=  	face  + cell*mesh->ncellFaces;
			int cell_n	=  	mesh->cellToCells[fid];
			int oface	=	mesh->faceToOppositeFaces[fid];
			int ofid	=	oface  + cell*mesh->ncellFaces;

			if (cell_n==(-1)) {

				for (int dim = 0; dim < mesh->nmeshdimension; dim++) {
					f[dim] = mesh->Cf[ofid*mesh->nmeshdimension+dim];
					b[dim] = mesh->Cf[fid*mesh->nmeshdimension+dim];
					P[dim] = mesh->C[cell*mesh->nmeshdimension+dim];
				}

				double fb = distance(f,b);
				double fP = distance(f,P);

				mesh->fx[fid] = fb/fP;

			}

		}
	}

	free(f);
	free(b);
	free(P);
}


void generateCellToCellDistanceVectors(mesh_t *mesh){

	double *N;
	double *P;
	N = (double*) calloc(mesh->nmeshdimension, sizeof(double));
	P = (double*) calloc(mesh->nmeshdimension, sizeof(double));

	for (size_t i = 0; i < mesh->nmeshdimension; i++) {
		N[i] = 0;
		P[i] = 0;
	}

	for (int cell = 0; cell < mesh->ncells; ++cell) {
		for (int face = 0; face < mesh->ncellFaces; ++face) {
			int fid		=  face  + cell*mesh->ncellFaces;
			int cell_n	=  mesh->cellToCells[fid];

			if (cell_n>(-1)) {
				for (int dim = 0; dim < mesh->nmeshdimension; dim++) {
					N[dim] = mesh->C[cell_n*mesh->nmeshdimension+dim];
					P[dim] = mesh->C[cell*mesh->nmeshdimension+dim];
				}
			}

			if (cell_n==(-1)) {
				for (int dim = 0; dim < mesh->nmeshdimension; dim++) {
					N[dim] = mesh->Cf[fid*mesh->nmeshdimension+dim];
					P[dim] = mesh->C[cell*mesh->nmeshdimension+dim];
				}
			}


			for (int dim = 0; dim < mesh->nmeshdimension; dim++) {

				int id = dim + face*mesh->nmeshdimension
						     + cell*mesh->nmeshdimension*mesh->ncellFaces;

				mesh->d[id] = N[dim]-P[dim];

			}


		}
	}


	free(N);
	free(P);

	//===================================================
	double *dl;
	dl = (double*) calloc(mesh->nmeshdimension, sizeof(double));

	for (int cell = 0; cell < mesh->ncells; ++cell) {
		for (int face = 0; face < mesh->ncellFaces; ++face) {
			int fid		=  face  + cell*mesh->ncellFaces;

			for (int dim = 0; dim < mesh->nmeshdimension; dim++) {

				dl[dim] = mesh->d[fid*mesh->nmeshdimension+dim];
			}


			mesh->magd[fid] = sqrt(pow(dl[0],2)+pow(dl[1],2));
		}
	}

	free(dl);

}



void writeMeshMetrics(mesh_t *mesh){

	int n = 50;
    char *variableName ;
    variableName	= (char*) calloc(n, sizeof(char));


	strcpy(variableName, "C");
	printMeshVolumeVector(mesh->C, variableName, mesh);

	strcpy(variableName, "Cf");
	printMeshSurfaceVector(mesh->Cf, variableName, mesh);


	strcpy(variableName, "Sf");
	printMeshSurfaceVector(mesh->Sf, variableName, mesh);


	strcpy(variableName, "magSf");
	printMeshSurfaceScalar(mesh->magSf, variableName, mesh);

	strcpy(variableName, "V");
	printMeshVolumeScalar(mesh->V, variableName, mesh);

	strcpy(variableName, "fx");
	printMeshSurfaceScalar(mesh->fx, variableName, mesh);

	strcpy(variableName, "d");
	printMeshSurfaceVector(mesh->d, variableName, mesh);

	strcpy(variableName, "magd");
	printMeshSurfaceScalar(mesh->magd, variableName, mesh);

	free(variableName);

}


