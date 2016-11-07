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

struct Cell
{
    int value;
    int active;
};

void printGrid(struct Cell** grid, int gridSize)
{
    int i, j;

    for(i = 0; i < gridSize; i++)
    {
        for(j = 0; j < gridSize; j++)
        {
            printf("%d ",grid[i][j].value);
        }
        putchar('\n');
    }
           
}
int boardFilled(struct Cell** grid, int gridSize)
{
    int i,j;

    for(i = 0; i < gridSize; i++)
        for(j = 0; j < gridSize; j++)
            if(grid[i][j].value == 0)
                return 0;

    return 1;
}
int solvedRegular(struct Cell **grid, int gridSize, int subgridSize)
{
    if(!boardFilled(grid,gridSize))
        return 0;
    
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
            container[grid[i][j].value - 1] = '1';
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
            container[grid[j][i].value - 1] = '1';
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
                container[grid[i][j].value - 1] = '1';
            }
        }
        container[gridSize] = '\0';
        if(strcmp(checker,container) != 0)
        return 0;
       
       
    }

     printf("SOLVED!\n");
    return 1;
}
int solvedRegularX(struct Cell **grid, int gridSize, int subgridSize)
{

}
int solvedRegularY(struct Cell **grid, int gridSize, int subgridSize)
{


}
int solvedRegularXY(struct Cell **grid, int gridSize, int subgridSize)
{
    
}

int isSafeRegular(struct Cell **grid, int gridSize, int subgridSize, int row, int col, int candidate, int move)
{
    int i, j;
    
    for(j = 0; j < gridSize; j++)
        if(grid[row][j].value == candidate)
            return 0;

    for(j = 0; j < gridSize; j++)
        if(grid[j][col].value == candidate)
            return 0;
    
    for(i = (row / subgridSize) * subgridSize; i < ((row / subgridSize) + 1) * subgridSize; i++)
        for(j = (col / subgridSize) * subgridSize; j < ((col / subgridSize) + 1) * subgridSize; j++)
            if(grid[i][j].value == candidate)
                return 0;
    
        /*for(i = (move / subgridSize) * subgridSize; i < ( ((move / subgridSize) + 1) * subgridSize ); i++)
            for(j = (move % subgridSize) * subgridSize; j < ( (( move % subgridSize) + 1) * subgridSize); j++)
                if(grid[i][j].value == candidate)
                    return 0;*/

      

       return 1;
       
    
}

int isActiveCell(struct Cell **grid, int gridSize, int move)
{
    move = move - 1;

    int row = move / gridSize;
    int col = move % gridSize;
    
    if(grid[row][col].active)
        return 1;
    
    else
        return 0;
}
int isValidMove(struct Cell **grid, int gridSize, int subgridSize, int move, int candidate)
{
    move = move - 1;

    int row = move / gridSize;
    int col = move % gridSize;

    if(isSafeRegular(grid, gridSize, subgridSize, row, col, candidate, move))
        return 1;
    
    else
        return 0;
}
void pushStack(struct Move *moveStack, struct Move *move, int *stackCounter)
{
    moveStack[++*stackCounter] = *move;
}
struct Move popStack(struct Move *moveStack, int *stackCounter)
{
    struct Move retVal = moveStack[*stackCounter--];

    printf("%d %d %d\n",retVal.row,retVal.col,retVal.value);
    return retVal;
}
void executeMove(struct Cell **grid, struct Move move)
{
    grid[move.row][move.col].value = move.value; 
}
struct Move createNewMove(int move, int candidate, int gridSize)
{
    move = move - 1;

    int row = move / gridSize;
    int col = move % gridSize;

    struct Move newMove={row,col,candidate};
    return newMove;
}
void printNopts(int *nopts, int gridSize)
{
    int i;
     for(i = 0; i < gridSize*gridSize + 1; i++)
        printf("%d ",i);
    
    putchar('\n');

    for(i = 0; i < gridSize*gridSize + 1; i++)
        printf("%d ",nopts[i]);

    putchar('\n');
}
int main()
{
    FILE *fp = fopen("input.in","r");

    int puzzles;

    fscanf(fp,"%d",&puzzles);


    while(puzzles > 0)
    {
        struct Cell **grid;
        int gridSize;
        int subgridSize;
        int i,j,k;
        int row, col;
        int start, move;
        int candidate;
        int stackCounter = 0;
        int forward;
        int index;
        fscanf(fp, "%d", &subgridSize);
        gridSize = subgridSize * subgridSize;

        int nopts[((gridSize*gridSize) + 2)];
        struct Move moveStack[gridSize*gridSize*gridSize];
        struct Move options[gridSize*gridSize+2][gridSize];
        struct Move *newMove;
        grid = (struct Cell **)malloc(sizeof(struct Cell *) * gridSize );

        for(i = 0; i < gridSize; i++)
            grid[i] = (struct Cell *)malloc(sizeof(struct Cell) * gridSize);
        
        for(i = 0; i < gridSize; i++)
            for(j = 0; j < gridSize; j++)
            {
                fscanf(fp, "%d ",&(grid[i][j].value));
                if(grid[i][j].value == 0)
                    grid[i][j].active = 1;
                else
                    grid[i][j].active = 0;
            }
       
        
        if(solvedRegular(grid,gridSize,subgridSize))
                printGrid(grid,gridSize);
        
        start = move = 0;
        nopts[start] = 1;
        while(nopts[start] > 0)
        {   
            if(nopts[move] > 0 || !isActiveCell(grid,gridSize,move))
            {
                printf("%d\n\n",move);
                move++;

                while(!isActiveCell(grid,gridSize,move) && move < gridSize*gridSize+1)
                    move++;
                nopts[move] = 0;
   
                if(solvedRegular(grid,gridSize,subgridSize))
                {
                    printGrid(grid,gridSize);
                    break;
                }
                else if(isActiveCell(grid, gridSize, move))
                {
                    for(candidate = gridSize; candidate > 0; candidate--)
                    {
                        if(isValidMove(grid, gridSize, subgridSize, move, candidate))
                            options[move][++nopts[move]] = createNewMove(move, candidate, gridSize);
                    }
                    if(nopts[move] > 0)
                        executeMove(grid,options[move][nopts[move]]);
                    printGrid(grid,gridSize);
                    //sleep(1);
                }
            }
            else
            {
                move--;
                while(!isActiveCell(grid,gridSize,move))
                move--;

                if(nopts[move] > 1)
                    executeMove(grid,options[move][--nopts[move]]);
                else
                {
                    executeMove(grid,createNewMove(move,0,gridSize));
                    nopts[move]--;
                }
               // printGrid(grid,gridSize);
               
            }
        }

        puzzles--;
    }
}