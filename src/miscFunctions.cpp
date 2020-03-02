#include "mesh.h"

double distance(double *X1,double *X2){

	double Distance = 0.0;

	double a = X2[0]-X1[0];
	double b = X2[1]-X1[1];

	Distance = sqrt(pow(a,2)+pow(b,2));



	return Distance;
}


double magnitude(double a){
double c = 0;
	if(a>0){c= a;}
	if(a<0){c=-a;}

	return c;
}

void copyVolumeVectorDataToFrom(double* copyTo, double* copyFrom,mesh_t *mesh){

	int n = mesh->ncells*mesh->nsolutiondimension;

	for (int i = 0; i< n; i++){
		copyTo[i]= copyFrom[i];
	}
}
