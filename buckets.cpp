/* Vick Ye
 * 45m 26s
 * 10/10
 * inputting grid
 */

#include<cstdio>

char grid[10][10];
int lake[2];
int rock[2];
int barn[2];

int abs(int a) {
	if(a < 0) {
		a *= -1;
	}
	return a;
}

bool contain(int r0, int r1, int b) {
	int min = r0 < r1 ? r0 : r1;
	int max = r0 > r1 ? r0 : r1;
	if(min < b && max > b) {
		return true;
	}
	return false;
}

int main() {
	//input
	FILE * in = fopen("buckets.in", "r");
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			fscanf(in, "%c", &grid[i][j]);
			//coordinates of lake, barn, rock with i = y, j = x
			//x stored in index 0 and y stored in index 1(for coordinate purposes)
			if(grid[i][j] == 'L') {
				lake[1] = i;
				lake[0] = j;
			} else if(grid[i][j] == 'R') {
				rock[1] = i;
				rock[0] = j;
			} else if(grid[i][j] == 'B') {
				barn[1] = i;
				barn[0] = j;
			}
		}
		fscanf(in, "\n");
	}
	fclose(in);



	//algorithm
	//if the distance(determined by change in x + change in y) between the barn and lake are alined with the rock in the way then its the dist + 1
	int steps = abs(barn[0] - lake[0]) + abs(barn[1] - lake[1]);


	//barn, lake, rock are alined by x and rock is between
	if(barn[0] == lake[0] && barn[0] == rock[0] && contain(barn[1], lake[1], rock[1])) {
		steps += 1;
	//barn, lake, rock are alined by y and rock is between
	} else if(barn[1] == lake[1] && barn[1] == rock[1] && contain(barn[0], lake[0], rock[0])) {
		steps += 1;
	} else {
	//if they aren't alined, then they have a corner
		steps -= 1;
	}
	


	//output
	FILE * out = fopen("buckets.out", "w");
	fprintf(out, "%d", steps);
	fclose(out);
}
