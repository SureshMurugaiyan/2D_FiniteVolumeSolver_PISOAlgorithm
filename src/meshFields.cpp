#include "mesh.h"

void meshConstructFields(mesh_t *mesh){

	createMeshVertexVector(&mesh->vertices,mesh);

	mesh->cellToCells 			= (int*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(int));
	mesh->cellToFaces 			= (int*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(int));
	mesh->faceToOppositeFaces	= (int*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(int));
	mesh->faceToVertices		= (int*) calloc(mesh->ncellFaces*mesh->nfaceVertices, sizeof(int));

	mesh->faceToLocalFaces		= (int*) calloc(mesh->ncellFaces*2, sizeof(int));


	for (int i = 0; i < (mesh->ncells*mesh->ncellFaces); i++) {
		mesh->cellToCells[i] = 0;
		mesh->cellToFaces[i] = 0;
		mesh->faceToOppositeFaces[i] = 0;
	}

	for (int i = 0; i < (mesh->ncellFaces*mesh->nfaceVertices); i++) {
		mesh->faceToVertices[i] = 0;
	}

	for (int i = 0; i < (mesh->ncellFaces*2); i++) {
		mesh->faceToLocalFaces[i] = 0;
	}

	createMeshVolumeVector(&mesh->C,mesh);
	createMeshSurfaceVector(&mesh->Cf,mesh);

	createMeshSurfaceVector(&mesh->Sf,mesh);
	createMeshSurfaceScalar(&mesh->magSf,mesh);

	createMeshVolumeScalar(&mesh->V,mesh);

	createMeshSurfaceScalar(&mesh->fx,mesh);

	createMeshSurfaceVector(&mesh->d,mesh);
	createMeshSurfaceScalar(&mesh->magd,mesh);

	mesh->patchID = (int*) calloc(mesh->ncells*mesh->ncellFaces, sizeof(int));

	for (int i = 0; i < (mesh->ncells*mesh->ncellFaces); i++) {
		mesh->patchID[i] = 0;
	}

}

void meshDestructFields(mesh_t *mesh){

	free(mesh->vertices);


	free(mesh->cellToCells);
	free(mesh->cellToFaces);
	free(mesh->faceToOppositeFaces);
	free(mesh->faceToVertices);
	free(mesh->faceToLocalFaces);

	free(mesh->C);
	free(mesh->Cf);
	free(mesh->Sf);
	free(mesh->magSf);

	free(mesh->V);
	free(mesh->fx);

	free(mesh->d);
	free(mesh->magd);

	free(mesh->patchID);
}
