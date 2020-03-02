#include "mesh.h"

void printSolutionVolumeScalar(double* phi, char *fileName,int timeStep,mesh_t *mesh){

	int n = 50;
    char *directory ;
    directory	= (char*) calloc(n, sizeof(char));

    char *subdirectory ;
    subdirectory	= (char*) calloc(n, sizeof(char));

	FILE * fptr;


	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
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

	//==========================================!
	free(subdirectory);
	free(directory);



}


void printSolutionVolumeVector(double* phi, char *fileName,int timeStep, mesh_t *mesh){

	int dimension;


	int n = 50;
    char *directory ;
    directory	= (char*) calloc(n, sizeof(char));

    char *subdirectory ;
    subdirectory	= (char*) calloc(n, sizeof(char));

	FILE * fptr;





	//==========================================!
	dimension = 0;

	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
	strcat(directory, fileName);
	strcat(directory, "X.txt");


	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

		int id = dimension + cell*mesh->nsolutiondimension;
		fprintf(fptr,"%6.10f \t",phi[id]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);



	//==========================================!
	dimension = 1;

	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
	strcat(directory, fileName);
	strcat(directory, "Y.txt");

	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

		int id = dimension + cell*mesh->nsolutiondimension;
		fprintf(fptr,"%6.10f \t",phi[id]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	//==========================================!
	dimension = 2;

	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
	strcat(directory, fileName);
	strcat(directory, "Z.txt");

	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

		int id = dimension + cell*mesh->nsolutiondimension;
		fprintf(fptr,"%6.10f \t",phi[id]);

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	//==========================================!
	free(subdirectory);
	free(directory);

}


void printSolutionSurfaceScalar(double* phi, char *fileName,int timeStep, mesh_t *mesh){

	int n = 50;
    char *directory ;
    directory	= (char*) calloc(n, sizeof(char));

    char *subdirectory ;
    subdirectory	= (char*) calloc(n, sizeof(char));

	FILE * fptr;


	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
	strcat(directory, fileName);
	strcat(directory, ".txt");

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
	free(subdirectory);
	free(directory);

}


void printSolutionSurfaceVector(double* phi, char *fileName,int timeStep, mesh_t *mesh){


	int dimension;


	int n = 50;
    char *directory ;
    directory	= (char*) calloc(n, sizeof(char));

    char *subdirectory ;
    subdirectory	= (char*) calloc(n, sizeof(char));

	FILE * fptr;





	//==========================================!
	dimension = 0;

	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
	strcat(directory, fileName);
	strcat(directory, "X.txt");


	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int face=0;face<mesh->ncellFaces;face++){

			int fid =  face + cell*mesh->ncellFaces;

			int id = dimension + fid*mesh->nsolutiondimension;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}


		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);



	//==========================================!
	dimension = 1;

	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
	strcat(directory, fileName);
	strcat(directory, "Y.txt");

	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

		for(int face=0;face<mesh->ncellFaces;face++){

			int fid =  face + cell*mesh->ncellFaces;

			int id = dimension + fid*mesh->nsolutiondimension;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	//==========================================!
	dimension = 2;

	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
	strcat(directory, fileName);
	strcat(directory, "Z.txt");

	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){

		for(int face=0;face<mesh->ncellFaces;face++){

			int fid =  face + cell*mesh->ncellFaces;

			int id = dimension + fid*mesh->nsolutiondimension;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}

		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);

	//==========================================!
	free(subdirectory);
	free(directory);

}


void printSolutionVertexScalar(double* phi, char *fileName,int timeStep, mesh_t *mesh){

	int n = 50;
    char *directory ;
    directory	= (char*) calloc(n, sizeof(char));

    char *subdirectory ;
    subdirectory	= (char*) calloc(n, sizeof(char));

	FILE * fptr;


	strcpy(directory, "testCase/");
	sprintf(subdirectory,"%d",timeStep);
	strcat(directory, subdirectory);
	mkdir(directory, 0777);


	strcat(directory, "/");
	strcat(directory, fileName);
	strcat(directory, ".txt");

	fptr = fopen (directory, "w");
	if(fptr == NULL) {
		printf("Could not create file.\n");
		exit(-1);
	}

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int cellVertex=(mesh->ncellVertices-1);cellVertex>(-1);cellVertex--){

			int id =  cellVertex + cell*mesh->ncellVertices;
			fprintf(fptr,"%6.10f \t",phi[id]);

		}
		int cellCol = cell % mesh->ncellsx;
		if (cellCol==(mesh->ncellsx-1)){fprintf(fptr,"\n");}
	}

	fclose(fptr);
	free(subdirectory);
	free(directory);

}
