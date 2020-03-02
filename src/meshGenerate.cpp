#include "mesh.h"

/******************************************************************************
                  Generates Mesh using Transfinite Interpolation
                   Author: Suresh Murugaiyan
*******************************************************************************/

void createBoundaryMesh(mesh_t *mesh);
void createSurfaceMesh(mesh_t *mesh);
void writeMesh(mesh_t *mesh);

void meshGenerate(mesh_t *mesh){

	printf("Generating Boundary Mesh  \n");
	createBoundaryMesh(mesh);

	printf("Generating Surface Mesh \n");
	createSurfaceMesh(mesh);

	printf("Writing Surface Mesh \n");
	writeMesh(mesh);

}

void createBoundaryMesh(mesh_t *mesh){


	double x1, y1, z1;   // (x1,y1,z1)--> north west corner
	double x2, y2, z2;   // (x2,y2,z2)--> north east corner
	double x3, y3, z3;   // (x3,y3,z3)--> south west corner
	double x4, y4, z4;   // (x4,y4,z4)--> south east corner

	x1 = 0.0; y1 = 2.0;
	x2 = 2.0; y2 = 2.0; // North Boundary
	x3 = 0.0; y3 = 0.0;
	x4 = 2.0; y4 = 0.0;// South Boundary

	/*index = column+ row*column_maximum; */
	// Linear index formula row major order

	/*index = dimension + column*dimension_max
	 *                  + row*dimension*column_maximum; */
	//Linear index for 2D vector variable formula row major order

	int northwest,southwest,southeast,northeast;
	int dimension,vertex,cell;
	int northwest_x,northwest_y,southwest_x,southwest_y;
	int southeast_x,southeast_y,northeast_x,northeast_y;

	northwest=0;
	southwest=(mesh->ncells-mesh->ncellsx);
	southeast=(mesh->ncells-1);
	northeast=(mesh->ncellsx-1);

	//========================================================================!

	dimension	=	0;
	vertex		=	0;
	cell		=	northwest;
	northwest_x = 	dimension + vertex*mesh->nmeshdimension
			+ cell*mesh->ncellVertices*mesh->nmeshdimension;

	dimension	=	1;
	vertex		=	0;
	cell		=	northwest;
	northwest_y = 	dimension + vertex*mesh->nmeshdimension
			+ cell*mesh->ncellVertices*mesh->nmeshdimension;

	//========================================================================!
	dimension	=	0;
	vertex		=	1;
	cell		=	southwest;
	southwest_x = 	dimension + vertex*mesh->nmeshdimension
			+ cell*mesh->ncellVertices*mesh->nmeshdimension;

	dimension	=	1;
	vertex		=	1;
	cell		=	southwest;
	southwest_y = 	dimension + vertex*mesh->nmeshdimension
			+ cell*mesh->ncellVertices*mesh->nmeshdimension;

	//========================================================================!
	dimension	=	0;
	vertex		=	2;
	cell		=	southeast;
	southeast_x = dimension + vertex*mesh->nmeshdimension
			+ cell*mesh->ncellVertices*mesh->nmeshdimension;

	dimension	=	1;
	vertex		=	2;
	cell		=	southeast;
	southeast_y = 	dimension + vertex*mesh->nmeshdimension
			+ cell*mesh->ncellVertices*mesh->nmeshdimension;

	//========================================================================!
	dimension	=	0;
	vertex		=	3;
	cell		=	northeast;
	northeast_x = 	dimension + vertex*mesh->nmeshdimension
			+ cell*mesh->ncellVertices*mesh->nmeshdimension;

	dimension	=	1;
	vertex		=	3;
	cell		=	northeast;
	northeast_y =	dimension + vertex*mesh->nmeshdimension
			+ cell*mesh->ncellVertices*mesh->nmeshdimension;
	//========================================================================!
	// Fix the corners vertices of the grid
	mesh->vertices[northwest_x] = x1;// North west Corner
	mesh->vertices[northwest_y] = y1;
	mesh->vertices[northeast_x] = x2;// North east Corner
	mesh->vertices[northeast_y] = y2;
	mesh->vertices[southwest_x] = x3;// South west Corner
	mesh->vertices[southwest_y] = y3;
	mesh->vertices[southeast_x] = x4;// South east Corner
	mesh->vertices[southeast_y] = y4;

	int count;
	int vertexid;
	int id1,id2;
	int cornervertex,cornercell;
	int NW,NE,SW,SE; // corner locations

	// Generate Boundary Mesh for  North Boundary
	count = 0;

	for( int cell = northwest; cell < (northeast+1);cell++){
		for(int dimension=0;dimension<mesh->nmeshdimension;dimension++){

			vertexid=0;
			id1 = dimension + vertexid*mesh->nmeshdimension
					+ cell*mesh->ncellVertices*mesh->nmeshdimension;

			vertexid=3;
			id2 = dimension + vertexid*mesh->nmeshdimension
					+ cell*mesh->ncellVertices*mesh->nmeshdimension;

			cornervertex	=	0;
			cornercell		=	northwest;
			NW				=	dimension + cornervertex*mesh->nmeshdimension
					+ cornercell*mesh->ncellVertices*mesh->nmeshdimension;
			// North West corner address

			cornervertex	=	3;
			cornercell		=	northeast;
			NE				=	dimension + cornervertex*mesh->nmeshdimension
					+ cornercell*mesh->ncellVertices*mesh->nmeshdimension;
			// North East corner address


			double minimum = mesh->vertices[NW];
			double maximum = mesh->vertices[NE];

			mesh->vertices[id1] =  minimum+(((maximum-minimum)/(mesh->ncellsx)))*count;
			mesh->vertices[id2] =  minimum+(((maximum-minimum)/(mesh->ncellsx)))*(count+1);

		}
		count++;
	}

	// Generate Boundary Mesh for  South Boundary
	count = 0;
	for( int cell = southwest; cell < (southeast+1);cell++){
		for(int dimension=0;dimension<mesh->nmeshdimension;dimension++){

			vertexid=1;
			id1 = dimension + vertexid*mesh->nmeshdimension +
					cell*mesh->ncellVertices*mesh->nmeshdimension;

			vertexid=2;
			id2 = dimension + vertexid*mesh->nmeshdimension +
					cell*mesh->ncellVertices*mesh->nmeshdimension;

			cornervertex	=	1;
			cornercell		=	southwest;
			SW				=	dimension + cornervertex*mesh->nmeshdimension
					+ cornercell*mesh->ncellVertices*mesh->nmeshdimension;
			// South west corner address

			cornervertex	=	2;
			cornercell		=	southeast;
			SE				=	dimension + cornervertex*mesh->nmeshdimension
					+ cornercell*mesh->ncellVertices*mesh->nmeshdimension;
			// South East corner address

			double minimum = mesh->vertices[SW];
			double maximum = mesh->vertices[SE];

			mesh->vertices[id1] =  minimum+(((maximum-minimum)/(mesh->ncellsx)))*count;
			mesh->vertices[id2] =  minimum+(((maximum-minimum)/(mesh->ncellsx)))*(count+1);

		}
		count++;
	}

	// Generate Boundary Mesh for  West Boundary
	count = 0;
	for( int cell = northwest; cell < (southwest+1);cell= (cell+mesh->ncellsx)){
		for(int dimension=0;dimension<mesh->nmeshdimension;dimension++){

			vertexid=0;
			id1 = dimension + vertexid*mesh->nmeshdimension
					+ cell*mesh->ncellVertices*mesh->nmeshdimension;

			vertexid=1;
			id2 = dimension + vertexid*mesh->nmeshdimension
					+ cell*mesh->ncellVertices*mesh->nmeshdimension;

			cornervertex	=	0;
			cornercell		=	0;
			NW				=	dimension + cornervertex*mesh->nmeshdimension
					+ cornercell*mesh->ncellVertices*mesh->nmeshdimension;
			// North West corner address

			cornervertex	=	1;
			cornercell		=	(mesh->ncells-mesh->ncellsx);
			SW				=	dimension + cornervertex*mesh->nmeshdimension
					+ cornercell*mesh->ncellVertices*mesh->nmeshdimension;
			// South west corner address


			double minimum = mesh->vertices[NW];
			double maximum = mesh->vertices[SW];

			mesh->vertices[id1] =  minimum+(((maximum-minimum)/(mesh->ncellsy)))*count;
			mesh->vertices[id2] =  minimum+(((maximum-minimum)/(mesh->ncellsy)))*(count+1);

		}
		count++;
	}

	// Generate Boundary Mesh for  East Boundary
	count = 0;
	for( int cell = northeast; cell < (southeast+1);cell= (cell+mesh->ncellsx)){
		for(int dimension=0;dimension<mesh->nmeshdimension;dimension++){

			vertexid=3;
			id1 = dimension + vertexid*mesh->nmeshdimension
					+ cell*mesh->ncellVertices*mesh->nmeshdimension;

			vertexid=2;
			id2 = dimension + vertexid*mesh->nmeshdimension
					+ cell*mesh->ncellVertices*mesh->nmeshdimension;

			cornervertex	=	2;
			cornercell		=	(mesh->ncells-1);
			SE				=	dimension + cornervertex*mesh->nmeshdimension
					+ cornercell*mesh->ncellVertices*mesh->nmeshdimension;
			// South East corner address

			cornervertex	=	3;
			cornercell		=	(mesh->ncellsx-1);
			NE				=	dimension + cornervertex*mesh->nmeshdimension
					+ cornercell*mesh->ncellVertices*mesh->nmeshdimension;
			// North East corner address


			double minimum = mesh->vertices[NE];
			double maximum = mesh->vertices[SE];

			mesh->vertices[id1] =  minimum+(((maximum-minimum)/(mesh->ncellsy)))*count;
			mesh->vertices[id2] =  minimum+(((maximum-minimum)/(mesh->ncellsy)))*(count+1);

		}
		count++;
	}

}

void createSurfaceMesh(mesh_t *mesh){

	// Transfinite Interpolation for creating inner points
	// https://en.wikipedia.org/wiki/Transfinite_interpolation
	double delr = 1.0/(mesh->ncellsx); // computational space unit length
	double dels = 1.0/(mesh->ncellsy); // computational space unit height
	double r=0.0,s=0.0;
	int cellRow,cellCol;
	int cornervertex,cornercell;
	int boundarycell, boundaryvertex;
	int NW,NE,SW,SE; // corner locations
	int N,S,W,E; // boundary locations

	for( int cell = 0; cell < mesh->ncells;cell++){
		for(int vertex=0;vertex<mesh->ncellVertices;vertex++){
			for(int dimension=0;dimension<mesh->nmeshdimension;dimension++){

				int id = dimension + vertex*mesh->nmeshdimension + cell*mesh->ncellVertices*mesh->nmeshdimension;

				cellRow = cell / mesh->ncellsx;
				cellCol = cell % mesh->ncellsx;

				r = cellCol*delr;
				s = 1.0-cellRow*dels;

				if(vertex==2){r = r+delr;}
				if(vertex==3){r = r+delr;}

				if(vertex==1){s = s-dels;}
				if(vertex==2){s = s-dels;}

				cornervertex	=	0;
				cornercell		=	0;
				NW				=	dimension + cornervertex*mesh->nmeshdimension
											  + cornercell*mesh->ncellVertices*mesh->nmeshdimension; // North West corner address


				cornervertex	=	1;
				cornercell		=	(mesh->ncells-mesh->ncellsx);
				SW				=	dimension + cornervertex*mesh->nmeshdimension
											  + cornercell*mesh->ncellVertices*mesh->nmeshdimension; // South west corner address

				cornervertex	=	2;
				cornercell		=	(mesh->ncells-1);
				SE				=	dimension + cornervertex*mesh->nmeshdimension
											  + cornercell*mesh->ncellVertices*mesh->nmeshdimension; // South East corner address

				cornervertex	=	3;
				cornercell		=	(mesh->ncellsx-1);
				NE				=	dimension + cornervertex*mesh->nmeshdimension
											  + cornercell*mesh->ncellVertices*mesh->nmeshdimension; // North East corner address


				boundarycell = cellCol + 0*mesh->ncellsx;  // boundarycell = cellCol + cellRow*mesh->ncellsx;
				if(vertex==0){ boundaryvertex = 0;}
				if(vertex==1){ boundaryvertex = 0;}
				if(vertex==2){ boundaryvertex = 3;}
				if(vertex==3){ boundaryvertex = 3;}

				N=dimension + boundaryvertex*mesh->nmeshdimension + boundarycell*mesh->ncellVertices*mesh->nmeshdimension; // North boundary cell


				boundarycell = cellCol + (mesh->ncellsy-1)*mesh->ncellsx;
				if(vertex==0){ boundaryvertex = 1;}
				if(vertex==1){ boundaryvertex = 1;}
				if(vertex==2){ boundaryvertex = 2;}
				if(vertex==3){ boundaryvertex = 2;}

				S=dimension + boundaryvertex*mesh->nmeshdimension + boundarycell*mesh->ncellVertices*mesh->nmeshdimension; // South boundary cell

				boundarycell = 0 + cellRow*mesh->ncellsx;
				if(vertex==0){ boundaryvertex = 0;}
				if(vertex==1){ boundaryvertex = 1;}
				if(vertex==2){ boundaryvertex = 1;}
				if(vertex==3){ boundaryvertex = 0;}
				W=dimension + boundaryvertex*mesh->nmeshdimension + boundarycell*mesh->ncellVertices*mesh->nmeshdimension; // West boundary cell

				boundarycell = (mesh->ncellsx-1) + cellRow*mesh->ncellsx;
				if(vertex==0){ boundaryvertex = 3;}
				if(vertex==1){ boundaryvertex = 2;}
				if(vertex==2){ boundaryvertex = 2;}
				if(vertex==3){ boundaryvertex = 3;}
				E=dimension + boundaryvertex*mesh->nmeshdimension + boundarycell*mesh->ncellVertices*mesh->nmeshdimension; // East boundary cell



				mesh->vertices[id] =     (1-s)*mesh->vertices[S]
										+ 	s*mesh->vertices[N]
										+ 	(1-s)*(mesh->vertices[W]-(1-s)*mesh->vertices[SW] - s*mesh->vertices[NW])
										+	r*(mesh->vertices[E]-(1-s)*mesh->vertices[SE]- s*mesh->vertices[NE]);


			}
		}
	}

}

void writeMesh(mesh_t *mesh){

	int n = 50;
    char *variableName ;
    variableName	= (char*) calloc(n, sizeof(char));

	int dimension;
	strcpy(variableName, "V");
	printMeshVertexVector(mesh->vertices, variableName, mesh);


	free(variableName);
}
