


//Conways game of life, need to create a [5][5] 2D array and generate live or dead cells
/* The rules are summarized as follows:
1. A live cell with fewer than two live neighbors dies.    2 == alive
2. A live cell with more than three live neighbors also dies. ** Greater than 3, is alive
3. A live cell with exactly two or three live neighbors lives. 
4. A dead cell with exactly three live neighbors becomes alive.  */



/* The program that you will write needs two arguments:
 	-the number of generations
	-a filename of the file that contains the initial matrix.
The format of the file is a 5x5 matrix of integers. Cells at each row are separated by a space. An
alive cell is presented by a 1, while a dead one is presented by a 0.  */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> //need the string library for the file i/o

//mains takes 2 arguments, 1 is the amount of generations and 2 is the actual matrix itself

//1. TopLeft = 1
//2. TopRight = 2
//3. BottomLeft = 3
//4. BottomRight = 4
//5. Left Border = Q
//6. Right Border = P
//7. TopBorder = T
//8. BottomBorder = B
//9. middle cell = O

//This function is telling me where my cell is 
char getposition(int x, int y){
	if(x == 0){
		if(y == 0) { return '1';}

		else if (y == 4) { return '3';}

		else { return 'Q';}
	}
	else if( x == 4){
		if( y == 4) { return '4';}

		else if (y == 0 ) { return '2';}

		else { return 'P';}

	}
	else {
		if(y == 0){ return 'T';}

		else if( y == 4) { return 'B';}

		else { return 'O';}
	}
}
//ALL THE FUNCTIONS BELOW ARE TO CHECK HOW MANY LIVING NEIGHBORS EACH CELL HAS
//Checks my 4 corners
int CornerChecker(int x, int y, int matrix[5][5]){
	int neighbors = 0;
	if(x==0 && y ==0){ //TopLeft [0][0]
		if(matrix[1][1] == 1){ neighbors++; }
		if(matrix[0][1] == 1){ neighbors++; }
		if(matrix[1][0] == 1){ neighbors++; }
	}
	//Bottom Right [4][4]
	else if(x == 4 && y == 4){ //for nxn matrixes we would do it x==n and y ==n , but we are limited to a fixed 5x5
		if(matrix[3][3] == 1){ neighbors++; }
		if(matrix[3][4] == 1){ neighbors++; }
		if(matrix[4][3] == 1){ neighbors++; }

		}
	
	else if(x==4 && y == 0){//Top Right [4][0]
		if(matrix[3][0] == 1){ neighbors++; }
		if(matrix[4][1] == 1){ neighbors++; }
		if(matrix[3][1] == 1){ neighbors++; }
	}
	else{ //x==0 && y == 4. [0][4], bottom left
		if(matrix[0][3] == 1){ neighbors++; }
		if(matrix[4][1] == 1){ neighbors++; }
		if(matrix[1][3] == 1){ neighbors++; }
	}
	return neighbors;
}
//Checks the TopBorder
int TopChecker(int x, int y, int matrix[5][5]){
	int neighbors = 0;
	if(matrix[x-1][y] == 1){ neighbors++; }
	if(matrix[x+1][y] == 1){ neighbors++; }
	if(matrix[x][y+1] == 1){ neighbors++; }
	if(matrix[x-1][y+1] == 1){ neighbors++; }
	if(matrix[x+1][y+1] == 1){ neighbors++; }
	return neighbors;
}
//Checks the Bottom Border
int BottomChecker(int x, int y, int matrix[5][5]){
	int neighbors = 0;
	if(matrix[x+1][y] == 1){ neighbors++; }
	if(matrix[x-1][y] == 1){ neighbors++; }
	if(matrix[x-1][y-1] == 1){ neighbors++; }
	if(matrix[x][y-1] == 1){ neighbors++; }
	if(matrix[x+1][y-1] == 1){ neighbors++; }
	return neighbors;
}
//Checks the Left and rightside Borders
int SideChecker(int x, int y, int matrix[5][5]){
	int neighbors = 0;
	if(x == 0){
		if(matrix[x+1][y] == 1){ neighbors++; }
		if(matrix[x][y+1] == 1){ neighbors++; }
		if(matrix[x][y-1] == 1){ neighbors++; }
		if(matrix[x+1][y+1] == 1){ neighbors++; }
		if(matrix[x+1][y-1] == 1){ neighbors++; }

	}
	else if(x == 4){
		if(matrix[x-1][y] == 1){ neighbors++; }
		if(matrix[x][y+1] == 1){ neighbors++; }
		if(matrix[x][y-1] == 1){ neighbors++; }
		if(matrix[x-1][y+1] == 1){ neighbors++; }
		if(matrix[x-1][y-1] == 1){ neighbors++; }

	}
	return neighbors;
}
//Checks all values in the center
int CenterChecker(int x, int y, int matrix[5][5]){
	int neighbors = 0;
	if(matrix[x+1][y] == 1){ neighbors++; }
	if(matrix[x-1][y] == 1){ neighbors++; }
	if(matrix[x][y+1] == 1){ neighbors++; }
	if(matrix[x][y-1] == 1){ neighbors++; }
	if(matrix[x+1][y+1] == 1){ neighbors++; }
	if(matrix[x-1][y-1] == 1){ neighbors++; }
	if(matrix[x+1][y-1] == 1){ neighbors++; }
	if(matrix[x-1][y+1] == 1){ neighbors++; }
	return neighbors;
}


//C does Columns and Rows NOT ROWS AND COLUMNS, things need to be flip flopped

//What is our main line of logic here?  first --> we read in the matrix 
// 										secondly --> we need to determine each position of the cell, based off the positions we can determine its neighbors
//										third --> create a new matrix because old matrix values cannot affect old matrix values, so have 'generations'
// amount of matrices or we could just have 2 and juggle them back and forth? Reposting the rules down here
int main(int argc, char **argv){
	FILE *initial;
	int gens = atoi(argv[1]);
	//printf("%d\n",gens);
	char c;
	initial = fopen(argv[2], "r");
	int matrix[5][5];
	int TempMatrix[5][5];
	//int t;
	int i,j;
	int res;
	//int neighbors = 0;
	for(i=0; i<5; i++){ //Scanning in my initial Matrix
		for(j=0; j<5; j++){

			fscanf(initial, "%d", &matrix[i][j]);
			//printf("%d \t", matrix[i][j]);
			//fscanf(initial, "%d", &TempMatrix[i][j]);   //ok so when i put this line in, my code does not print out the right values
			//fscanf(initial, "%d");
			//printf("%c \t", getposition(j,i));
		}
		//printf("\n");
	}
	//printf("\n");
	//need an intial copy of the matrix in the event they ask for 0 generations;
	for(i=0; i<5; i++){
			for(j=0; j<5; j++){
				TempMatrix[i][j] = matrix[i][j];
			}
		}

	for(int count = 0; count < gens; count++){ //loop through however many generations needed

		for(i=0; i<5; i++){ //recopying the matrix
			for(j=0; j<5; j++){
				matrix[i][j] = TempMatrix[i][j];
			}
		}
		for(int i = 0; i <5; i++){
			for(int j = 0; j < 5; j++){	
				//printf("%d \t", matrix[i][j]);
				res = 0;
				c = getposition(i,j);
				switch(c) {
					case('1'): //check right, bottom and diagonal down left [0][0]
						res = CornerChecker(i, j, matrix);
						//printf("%s\n", "Top Left");
						break;

					case('2'): //check left, bottom, and diagonal down right  [4][0]
						res = CornerChecker(i, j, matrix);
						//printf("%s\n", "Top Right");
						break;

					case('3'): // check right, up and diagonal up right. [0][4]
						res = CornerChecker(i, j, matrix);
						//printf("%s\n", "Bottom Left");
						break;

					case('4'): // check left, up and diagonal up left  [4][4]
						res = CornerChecker(i, j, matrix);
						//printf("%s\n", "Bottom Right");
						break;

					case('T'):  //all except above
						res = TopChecker(i, j, matrix);
						//printf("%s\n", "Top Border");
						break;

					case('B'):	//all except below
						res = BottomChecker(i, j, matrix);
						//printf("%s\n", "Bottom Border");
						break;

					case('Q'): //all except left
						res = SideChecker(i, j, matrix);
						//printf("%s\n", "Left Border");
						break;

					case('P'): //all except right
						res = SideChecker(i, j, matrix);
						//printf("%s\n", "Right Border");
						break;

					default: //check everything
						res = CenterChecker(i, j, matrix);
						//printf("%s\n", "Center Piece");
						break;
					}
					//printf("%d", res);
					if(matrix[i][j] == 1){
							if(res < 2){
								TempMatrix[i][j]^=1;
							}
							else if(res > 3){
								TempMatrix[i][j]^=1;
							}
						}
					else if(matrix[i][j] == 0){
						if(res == 3){
							TempMatrix[i][j]^=1;
						}
					} ///End of my IF STATEMENT AT THE END
				}
			}
		}
	//Creation of new file
	char* str = strcat(argv[2], ".out"); //Using the string library here to concatenate rather than allocating memory
	FILE* outputfile; //creating my new output file
	outputfile = fopen(str, "w");
	//printing the final generation
	for(int row=0; row < 5; row++){ //Scanning in my initial Matrix
		for(int column =0; column < 5; column++){ 
			fprintf(outputfile, "%d \t", TempMatrix[row][column]);
		}
		fprintf(outputfile, "\n");
	}
	fprintf(outputfile, "\n");

	
	//printf("%s\n", str); //This is keeping track of the file name;
	fclose(initial);
	return 0;
//is_corner and is_border function 

}
