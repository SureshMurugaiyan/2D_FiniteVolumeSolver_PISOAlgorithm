#include "mesh.h"


void insWriteSolutionField(mesh_t *mesh){

	//---> to terminal monitoring
	printf("Time Step: %d\t"
			"Time: %.3e\t"
			"\n",
			mesh->timeStep,
			mesh->time);


	int n = 50;
    char *variableName ;
    variableName	= (char*) calloc(n, sizeof(char));




	if (mesh->timeStep % mesh->WriteFrequency == 0) {

		strcpy(variableName, "U");
		printSolutionVolumeVector(mesh->U, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "p");
		printSolutionVolumeScalar(mesh->p, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "rho");
		printSolutionVolumeScalar(mesh->rho, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "mu");
		printSolutionVolumeScalar(mesh->mu, variableName, mesh->timeStep, mesh);

		strcpy(variableName, "divphiU");
		printSolutionVolumeScalar(mesh->divphiU, variableName, mesh->timeStep, mesh);

	}

    free(variableName);
}



