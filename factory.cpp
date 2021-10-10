/* Vick Ye
 * 2h 13m 30s
 * 10/10
 * I wanted to not make the function recursive and just add on discovered paths as they are discovered so the end will be pushed but segmentation fault so I had to make it recursively check itself until no paths of discovered
 */
#include<cstdio>
#include<vector>
#include <algorithm>

int N;
int pathAmt;
int a[100];
int b[100];
// path[factory][entrances] (store factory and what paths lead to it)
std::vector<int> path[99];

void addIndirectPath(int f) {
	//loop through entrances and added entrances
	std::vector<int> newPath;
	for(auto iterator = path[f].begin(); iterator != path[f].end(); iterator++) {
		int entranceFactory = *iterator;
		//test what leads into the entrances
		for(auto newEntrance = path[entranceFactory].begin(); newEntrance != path[entranceFactory].end(); newEntrance++) {
			//if potentialEntrance not in path list, add to vector for adding later
			int potential = *newEntrance;
			if(std::count(path[f].begin(), path[f].end(), potential) == 0) {
				newPath.push_back(potential);
			}
		}
	}
	if(newPath.size() != 0) {
		//add discovered indirect path
		for(auto iterator = newPath.begin(); iterator != newPath.end(); iterator++) {
			path[f].push_back(*iterator);
		}

		//if added path, test for more indirect paths
		addIndirectPath(f);
	}
}

int main() {
	//input
	FILE * in = fopen("factory.in", "r");
	fscanf(in, "%d", &N);
	
	pathAmt = N - 1;
	
	for(int i = 0; i < pathAmt; i++) {
		fscanf(in, "%d %d", &a[i], &b[i]);
	};
	fclose(in);
	
	//convert factory num to index
	for(int i = 0; i < pathAmt; i++) {
		a[i] -= 1;
		b[i] -= 1;
	}




	//algorithm
	int walkways = -1;

	//store direct path based on destination
	//paths = N - 1
	for(int i = 0; i < pathAmt; i++) {
		int pathStart = a[i];
		int pathEnd = b[i];
		//path[destination][entrance]
		path[pathEnd].push_back(pathStart);
	}
	
	//add indirect destinations
	
	for(int i = 0; i < N; i++) {
		addIndirectPath(i);
	}
	
	//check paths
	for(int i = 0; i < N; i++) {
		if(path[i].size() == pathAmt) {
			walkways = i;
			break;
		}
	}




	//output
	
	//shift back to factory num
	if(walkways != -1) {
		walkways += 1;
	}
	
	FILE * out = fopen("factory.out", "w");
	fprintf(out, "%d", walkways);
	fclose(out);
}
