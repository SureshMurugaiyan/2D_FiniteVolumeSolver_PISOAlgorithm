#include "mesh.h"
void printMeshVertexVector(double* phi, char *fileName,mesh_t *mesh){

	int dimension;


	int n = 50;
    char *directory ;
	FILE * fptr;

	//==========================================!
	dimension = 0;
    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, "X.txt");


	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=(mesh->ncellVertices-1);vertex>(-1);vertex--){

			int id = dimension + vertex*mesh->nmeshdimension
							   + cell*mesh->ncellFaces*mesh->nmeshdimension;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);


	//==========================================!
	dimension = 1;

    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, "Y.txt");

	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=(mesh->ncellVertices-1);vertex>(-1);vertex--){

			int id = dimension + vertex*mesh->nmeshdimension
							   + cell*mesh->ncellFaces*mesh->nmeshdimension;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);

}

void printMeshVolumeVector(double* phi, char *fileName,mesh_t *mesh){

	int dimension;


	int n = 50;
    char *directory ;
	FILE * fptr;

	//==========================================!
	dimension = 0;
    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, "X.txt");


	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

		int id = dimension + cell*mesh->nmeshdimension;
		fprintf(fptr,"%6.10f \t",phi[id]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);


	//==========================================!
	dimension = 1;

    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, "Y.txt");

	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

		int id = dimension + cell*mesh->nmeshdimension;
		fprintf(fptr,"%6.10f \t",phi[id]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);

}

void printMeshSurfaceVector(double* phi, char *fileName,mesh_t *mesh){

	int dimension;


	int n = 50;
    char *directory ;
	FILE * fptr;

	//==========================================!
	dimension = 0;
    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, "X.txt");


	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int face=0;face<mesh->ncellFaces;face++){

			int id = dimension + face*mesh->nmeshdimension
							   + cell*mesh->ncellFaces*mesh->nmeshdimension;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);


	//==========================================!
	dimension = 1;

    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, "Y.txt");

	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int face=0;face<mesh->ncellFaces;face++){

			int id = dimension + face*mesh->nmeshdimension
							   + cell*mesh->ncellFaces*mesh->nmeshdimension;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);

}

//===============================================================+!
void printMeshSurfaceScalar(double* phi, char *fileName, mesh_t *mesh){

	int n = 50;
    char *directory ;
    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, ".txt");

	FILE * fptr;
	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int face=0;face<mesh->ncellFaces;face++){

			int id =  face + cell*mesh->ncellFaces;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);

}


//===============================================================+!
void printMeshSurfaceScalar(int* phi, char *fileName, mesh_t *mesh){

	int n = 50;
    char *directory ;
    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, ".txt");

	FILE * fptr;
	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int face=0;face<mesh->ncellFaces;face++){

			int id =  face + cell*mesh->ncellFaces;
			fprintf(fptr,"%d \t",phi[id]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);

}
//===============================================================+!
void printMeshVolumeScalar(double* phi, char *fileName,mesh_t *mesh){

	int n = 50;
    char *directory ;
	FILE * fptr;

    directory	= (char*) calloc(n, sizeof(char));

    strcpy(directory, "testCase/");
    mkdir(directory, 0777);

	strcpy(directory, "testCase/Mesh/");
	mkdir(directory, 0777);


	strcat(directory, fileName);
	strcat(directory, ".txt");


	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

		fprintf(fptr,"%6.10f \t",phi[cell]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	free(directory);



}
