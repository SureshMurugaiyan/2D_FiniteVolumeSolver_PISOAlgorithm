#include "mesh.h"

void meshGenerateBoundaryName(mesh_t *mesh){


	int fid;
	int idx,idy;
	int dimx,dimy;

	for (int cell = 0; cell < mesh->ncells; ++cell) {
		for (int face = 0; face < mesh->ncellFaces; ++face) {
			fid	=  face  + cell*mesh->ncellFaces;
			dimx = 0; // dim = 0 gives x component, dim = 1 gives y component
			dimy = 1;
			idx	= dimx+face*mesh->nmeshdimension+cell*mesh->ncellFaces*mesh->nmeshdimension;
			idy	= dimy+face*mesh->nmeshdimension+cell*mesh->ncellFaces*mesh->nmeshdimension;

			mesh->patchID[fid] = innerDomain;


			if (magnitude(mesh->Cf[idy]-2.0)<1e-14) {mesh->patchID[fid] = topBoundary;}
			if (magnitude(mesh->Cf[idy]+0.0)<1e-14) {mesh->patchID[fid] = bottomBoundary;}
			if (magnitude(mesh->Cf[idx]-2.0)<1e-14) {mesh->patchID[fid] = rightBoundary;}
			if (magnitude(mesh->Cf[idx]+0.0)<1e-14) {mesh->patchID[fid] = leftBoundary ;}


		}
	}

	int n = 50;
    char *variableName ;
    variableName	= (char*) calloc(n, sizeof(char));

	strcpy(variableName, "patchID");
	printMeshSurfaceScalar(mesh->patchID, variableName, mesh);

	free(variableName);
}
