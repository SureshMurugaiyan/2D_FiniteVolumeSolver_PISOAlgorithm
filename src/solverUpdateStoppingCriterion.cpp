#include "mesh.h"

void solverUpdateStoppingCriterion(mesh_t *mesh){

	  if (mesh->timeStep > mesh->timeStepMax) {
		  mesh->stopCriterion=true;
	  }

	  if (mesh->time > mesh->finalTime) {
		  mesh->stopCriterion=true;
	  }

}
