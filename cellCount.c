/* PLEASE DO NOT MODIFY A SINGLE STATEMENT IN THE TEXT BELOW.
READ THE FOLLOWING CAREFULLY AND FILL IN THE GAPS

I hereby declare that all the work that was required to 
solve the following problem including designing the algorithms
and writing the code below, is solely my own and that I received
no help in creating this solution and I have not discussed my solution 
with anybody. I affirm that I have read and understood
the Senate Policy on Academic honesty at 
https://secretariat-policies.info.yorku.ca/policies/academic-honesty-senate-policy-on/
and I am well aware of the seriousness of the matter and the penalties that I will face as a 
result of committing plagiarism in this assignment.

BY FILLING THE GAPS,YOU ARE SIGNING THE ABOVE STATEMENTS.

Full Name: Diego Santosuosso
Student Number: 217339987
Course Section: M
*/

#include<stdio.h>
#include<stdlib.h>

#include <stdbool.h> 
#include <string.h> 

#define IMAGE_SIZE 10


// this function prints the array
void printImgArray(int array[IMAGE_SIZE][IMAGE_SIZE])
{
  
    printf("------ Image Contents -------\n");
    for (int i=0; i<IMAGE_SIZE; i++)
    {
    for (int j=0; j<IMAGE_SIZE; j++)
        printf("%02d, ",array[i][j]);
    printf("\n");
    }
    printf("-----------------------------\n");
}

// Traverses the array
void traverse(int image[IMAGE_SIZE][IMAGE_SIZE], bool passed[IMAGE_SIZE][IMAGE_SIZE], int i, int j) 
{ 
    passed[i][j] = true; //cell is passed
    static int column_index[] = { -1, 0, 1, -1, 1, -1, 0, 1 }; 
    static int row_index[] = { -1, -1, -1, 0, 0, 1, 1, 1 }; 
    int neighbours = 8; //each element has 8 neighbours (up, down, left, right, top-right, top-left, low-right, low-left)
    
  
    for (int k = 0; k < neighbours; k++) {
    	int i_index = row_index[k] + i;
    	int j_index = column_index[k] + j;
        // ensures that no Index out of Bounds occur
        if ((i_index >= 0))
            if (IMAGE_SIZE > i_index)
                if (j_index >= 0)
                    if (IMAGE_SIZE > j_index)
                        if (image[i_index][j_index] && !passed[i_index][j_index]){
                            traverse(image, passed, i_index, j_index);
                        }
    }
} 

/**
 * This function counts the number of distinct 
 * number (i.e. the number of cells)
 **/
int cellCount(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task1.1 here
    // you may want to change the return value. 


    bool passed[IMAGE_SIZE][IMAGE_SIZE]; //keeps track of occupied matrix entries
    memset(passed, 0, sizeof(passed)); 
  

    int sum = 11; 
    //loop through columns (vertical)
    for (int j = 0; j < IMAGE_SIZE; ++j)
        //loop through rows (horizontal)
        for (int i = 0; i < IMAGE_SIZE; ++i) 
            //if value of 1 is found
            if (image[i][j] == 1){
                //if cell where value of 1 was found is not passed
                if (!passed[i][j]){
                    //visit every subcell
                    image[i][j] = sum;
                    sum = sum + 11;
                    traverse(image, passed, i, j);
                }
            }
    
    int max = 0;
    //loop through rows (horizontal)
    for (int i = 0; i < IMAGE_SIZE ; i++){
        //loop through columns (vertical)
        for (int j = 0; j < IMAGE_SIZE; j++){
            if (image[i][j] > max){
                max = image[i][j];
            }
        }
    }
    return (max/11);
}

int getMaxNeighbour(int image[IMAGE_SIZE][IMAGE_SIZE], int i, int j){
    int neighbours[8] = {0,0,0,0,0,0,0,0};
    int max = 0;

    int top = image[i-1][j];
    int bottom = image[i+1][j];
    int left = image[i][j-1];
    int right = image[i][j+1];
    int top_left = image[i-1][j-1];
    int top_right = image[i-1][j+1];
    int bottom_left = image[i+1][j-1];
    int bottom_right = image[i+1][j+1];

    //left top corner
    if (i == 0 && j == 0){
        neighbours[0] = right;
        neighbours[1] = bottom;
        neighbours[2] = bottom_right;
    }

    //right top corner
    if (i == 0 && j == 9){
        neighbours[0] = left;
        neighbours[1] = bottom;
        neighbours[2] = bottom_left;
    }

    //left bottom corner
    if (i == 9 && j == 0){
        neighbours[0] = top;
        neighbours[1] = right;
        neighbours[2] = top_right;
    }

    //right bottom corner
    if (i == 9 && j == 9){
        neighbours[0] = top;
        neighbours[1] = left;
        neighbours[2] = top_left;
    }

    //top edge
    if (i == 0 && j <= 8 && j >= 1){
        neighbours[0] = bottom;
        neighbours[1] = bottom_left;
        neighbours[2] = bottom_right;
        neighbours[3] = right;
        neighbours[4] = left;
    }

    //bottom edge
    if (i == 9 && j <= 8 && j >= 1){
        neighbours[0] = top;
        neighbours[1] = top_left;
        neighbours[2] = top_right;
        neighbours[3] = left;
        neighbours[4] = right;
    }

    //left edge
    if (j == 0 && i <= 8 && i >= 1){
        neighbours[0] = right;
        neighbours[1] = top_right;
        neighbours[2] = bottom_right;
        neighbours[3] = top;
        neighbours[4] = bottom;
    }

    //right edge
    if (j == 9 && i <= 8 && i >= 1){
        neighbours[0] = left;
        neighbours[1] = top_left;
        neighbours[2] = bottom_left;
        neighbours[3] = top;
        neighbours[4] = bottom;
    }

    if (j >= 1 && j <= 8 && i >= 1 && i <= 8){
        neighbours[0] = top;
        neighbours[1] = bottom;
        neighbours[2] = left;
        neighbours[3] = right;
        neighbours[4] = top_left;
        neighbours[5] = top_right;
        neighbours[6] = bottom_left;
        neighbours[7] = bottom_right;
    }

    for (int k = 0; k < 8; k++){
        if (neighbours[k] > max){
            max = neighbours[k];
        }
    }
    return max;  

}

/**
 * This function colors each cell with a unique color
 * (i.e. unique number)
 **/
void colorhelper(int image[IMAGE_SIZE][IMAGE_SIZE]){
    // insert your code for task 1.2 here
    bool passed[IMAGE_SIZE][IMAGE_SIZE]; 
    memset(passed, 0, sizeof(passed)); 
    
    int sum = 11;
    //loop through columns (vertical)
    for (int j = 0; j < IMAGE_SIZE; ++j)
        //loop through rows (horizontal)
        for (int i = 0; i < IMAGE_SIZE; ++i) 
            //if value of 1 is found
            if (image[i][j] == 1){
                //if cell where value of 1 was found is not passed
                if (!passed[i][j]){
                    image[i][j] = sum;
                    sum = sum + 11;
                    //visit every subcell
                    traverse(image, passed, i, j);
                }
            }
}

void colorloop(int image[IMAGE_SIZE][IMAGE_SIZE]){
    //loop through columns (vertical)
    for (int j = 0; j < IMAGE_SIZE; j++)
    {
        //loop through rows (horizontal)
        for (int i = 0; i < IMAGE_SIZE; i++)
        {
            if (image[i][j] == 1)
            {
                int max = getMaxNeighbour(image, i, j);
                if (max > image[i][j])
                {
                    image[i][j] = max;
                }
            }
        }
    }
}

void color(int image[IMAGE_SIZE][IMAGE_SIZE])
{
    colorhelper(image);
    //Run Color loop many times to ensure proper functioning
    for (int k = 0; k < IMAGE_SIZE; k++){
        colorloop(image);
    }
}

/**
 * This function colors each cell with a unique color
 * (i.e., unique number). This function works with 
 * pointers
 * currentRow: shows the current row that is processed
 * currentCol: shows the current column that is process
 * currentIndex: show the index that is processed
 * color: is an integer that represents a color
 **/

int colorRecursively(int image[IMAGE_SIZE][IMAGE_SIZE], int currentRow, int currentCol, int currentIndex, int color) {
    // insert your code for task 2.1 here, in case you decided to complete this task
    // you may want to change the return value
    return 0;
 
}

void colorPtr(int* image)
{
    // insert your code for task 2.2 here
    int n = IMAGE_SIZE;
    int array[IMAGE_SIZE][IMAGE_SIZE];

    for (int i = 0; i < IMAGE_SIZE; i++){
        for (int j = 0; j < IMAGE_SIZE; j++){
            int entry = *(image + (i * n) + j);
            array[i][j] = entry;
        }
    }

    colorhelper(array);
    //Run Color loop many times to ensure proper functioning
    for (int k = 0; k < IMAGE_SIZE; k++){
        colorloop(array);
    }

    for (int i = 0; i < IMAGE_SIZE; i++){
        for (int j = 0; j < IMAGE_SIZE; j++){  
            *(image + (i * n) + j) = array[i][j];
        }
    }
}
    

#ifndef __testing
int main(){

    // DO not change anything in main(), it will confuse the
    // auto-checker.  
    puts("testing the code with color() function");
    int count = 0;
    int cellImg[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};

    printImgArray(cellImg);
    color(cellImg);
    printImgArray(cellImg);
    count=cellCount(cellImg);
    printf("Total number of cells in the image: %d\n",count);
 

    puts("Testing the code with colorPtr");
    int cellImg_[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};

    int* ptr = cellImg_;
    printImgArray(ptr);
    colorPtr(ptr);
    printImgArray(ptr);
    count=cellCount(ptr);
    printf("Total number of cells in the image: %d\n",count); 
    puts("Testing the code with colorRecursively");
    int cellImg__[IMAGE_SIZE][IMAGE_SIZE]={{0,0,1,1,0,0,1,0,0,1},\
		               {1,0,1,1,0,0,1,1,0,1},\
		               {1,0,0,1,1,0,1,1,0,1},\
		               {1,1,0,0,0,0,0,0,0,0},\
		               {1,0,0,1,1,1,0,0,1,0},\
		               {0,0,0,0,1,0,0,1,1,0},\
		               {0,0,1,0,0,1,0,1,0,0},\
		               {0,0,1,1,0,0,1,0,0,0},\
		               {0,0,1,0,0,0,0,0,1,1},
		               {0,1,1,0,0,0,1,1,1,1}};
    printImgArray(cellImg__);
    colorRecursively(cellImg__, 0, 0, 1, 0);
    printImgArray(cellImg__);
    count=cellCount(cellImg__);
    printf("Total number of cells in the image: %d\n",count);
    return 0;
}
#endif