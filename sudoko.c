#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


struct Move 
{
    int row;
    int col;
    int value;
};

void printGrid(int** grid, int gridSize)
{
    int i, j;

    for(i = 0; i < gridSize; i++)
    {
        for(j = 0; j < gridSize; j++)
        {
            printf("%d ",grid[i][j]);
        }
        putchar('\n');
    }
           
}

int solvedRegular(int **grid, int gridSize, int subgridSize)
{
    int i, j;
    int counter;
    char initialContainer[gridSize + 1];
    char checker[gridSize + 1];
    char container[gridSize + 1];
    for(i = 0; i < gridSize; i++)
    {
        checker[i] = '1';
        initialContainer[i] = '0';
    }
    checker[i] = '\0';
    initialContainer[i] = '\0';
    
    for(i = 0; i < gridSize; i++)
    {
        strcpy(container,initialContainer);
        for(j = 0; j < gridSize; j++)
        {
            container[grid[i][j] - 1] = '1';
        }
        container[gridSize] = '\0';
        if(strcmp(checker,container) != 0)
            return 0;
               
    }

    for(i = 0; i < gridSize; i++)
    {
        strcpy(container,initialContainer);
        for(j = 0; j < gridSize; j++)
        {
            container[grid[j][i] - 1] = '1';
        }
        container[gridSize] = '\0';
        if(strcmp(checker,container) != 0)
            return 0;
      
    }

    for(counter = 0 ; counter < gridSize; counter++)
    {
        strcpy(container,initialContainer);
        for(i = (counter / subgridSize) * subgridSize; i < ( ((counter / subgridSize) + 1) * subgridSize ); i++)
        {
            for(j = (counter % subgridSize) * subgridSize; j < ( (( counter % subgridSize) + 1) * subgridSize); j++)
            {
                container[grid[i][j] - 1] = '1';
            }
        }
        container[gridSize] = '\0';
        if(strcmp(checker,container) != 0)
        return 0;
       
       
    }


    return 1;
}
int solvedRegularX(int **grid, int gridSize, int subgridSize)
{

}
int solvedRegularY(int **grid, int gridSize, int subgridSize)
{


}
int solvedRegularXY(int **grid, int gridSize, int subgridSize)
{

}

int findUnassigned(int **grid, int gridSize, int *row, int *col)
{
    for(*row = 0; *row < gridSize; (*row)++)
        for(*col = 0; *col < gridSize; (*col)++)
            if(grid[*row][*col] == 0)
                return 1;
            
    return 0;
}
int isSafeRegular(int **grid, int gridSize, int row, int col, int value)
{

}

int main()
{
    FILE *fp = fopen("input.in","r");

    int puzzles;

    fscanf(fp,"%d",&puzzles);


    while(puzzles > 0)
    {
        int **grid;
        int gridSize;
        int subgridSize;
        int i,j,k;
        int row, col;
        fscanf(fp, "%d", &subgridSize);
        gridSize = subgridSize * subgridSize;


        grid = (int **)malloc(sizeof(int *) * gridSize );

        for(i = 0; i < gridSize; i++)
            grid[i] = (int *)malloc(sizeof(int) * gridSize);
        
        for(i = 0; i < gridSize; i++)
            for(j = 0; j < gridSize; j++)
                fscanf(fp, "%d ",&(grid[i][j]));
        
        
        if(solvedRegular(grid,gridSize,subgridSize))
                printGrid(grid,gridSize);
        
        /*while(findUnassigned(grid, gridSize, &row, &col))
        {
           printf("%d %d\n",row,col);

           
        }*/

        //printGrid(grid,gridSize);

        puzzles--;
    }
}