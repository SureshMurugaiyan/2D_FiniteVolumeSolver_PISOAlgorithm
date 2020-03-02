#include "mesh.h"

void createMeshVertexScalar(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->ncellVertices;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createMeshVertexVector(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->ncellVertices*mesh->nmeshdimension;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createMeshVolumeScalar(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createMeshVolumeVector(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->nmeshdimension;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createMeshSurfaceScalar(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->ncellFaces;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createMeshSurfaceVector(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->ncellFaces*mesh->nmeshdimension;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}
