#include "mesh.h"

// Solution Fields

void createSolutionVertexScalar(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->ncellVertices;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createSolutionVertexVector(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->ncellVertices*mesh->nsolutiondimension;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createSolutionVolumeScalar(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createSolutionVolumeVector(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->nsolutiondimension;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createSolutionSurfaceScalar(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->ncellFaces;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}

void createSolutionSurfaceVector(dfloat** phi, mesh_t *mesh){

	int n = mesh->ncells*mesh->ncellFaces*mesh->nsolutiondimension;

	*phi = (dfloat*) calloc(n, sizeof(dfloat));

	for (size_t i = 0; i < n; i++) {
		(*phi)[i] = 0;
	}
}
