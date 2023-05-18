#include <bits/stdc++.h>
#include <iostream>

using namespace std;

#define N 8                                         // Size of the boarde


class Task2
{
private:
    // Move pattern on basis of the change of x coordinates and y coordinates respectively
    int coord_x[N] = {1,1,2,2,-1,-1,-2,-2};
    int coord_y[N] = {2,-2,1,-1,2,-2,1,-1};
    
public:
    Task2();
    bool findSolution();                            // Main Function to find the solution
    bool isValid(int a[], int x, int y);            // Checks whether a square is valid and empty or not
    int getDegree(int a[], int x, int y);           // Returns the number of valid motions adjacent to (x, y)
    bool nextMove(int a[], int *x, int *y);         // Picks next point using Warnsdorff's heuristic.
    bool closedTour(int x, int y, int xx, int yy);   // Check if tour is closed
    void printBoard(int a[]);                       // Print the board with the move number
};

Task2::Task2()
{
    // To make sure that different random initial positions
	srand(time(NULL));

    // While we don't get a solution
    while (!findSolution()){}
}

bool Task2::findSolution()
{
    // Filling up the chessboard matrix with -1's
    int a[N*N];
    for (int i = 0; i< N*N; ++i)
        a[i] = -1;
 
    // Random initial position
    int initial_x = rand()%N;
    int initial_y = rand()%N;
 
    // Current pposition
    int x = initial_x, y = initial_y;

    // Mark Start position by Zero
    a[y*N+x] = 0;
 
    // Use Warnsdorff's heuristic to pick up next move
    for (int i = 0; i < N*N-1; ++i)
        if (nextMove(a, &x, &y) == 0) // if no moves available return
            return false;
 
    // Check if tour is closed
    if (!closedTour(x, y, initial_x, initial_y))
        return false;
 
    printBoard(a);
    return true;
}
 
bool Task2::isValid(int a[], int x, int y){
    return ((x >= 0 && y >= 0) && (x < N && y < N)) && (a[y*N+x] < 0);
}

int Task2::getDegree(int a[], int x, int y){
    int count = 0;
    for (int i = 0; i < N; ++i)
        if (isValid(a, (x + coord_x[i]), (y + coord_y[i])))
            count++;
 
    return count;
}
 
bool Task2::nextMove(int a[], int *x, int *y){
    int min_deg_idx = -1, c, min_deg = (N+1), temp_x, temp_y;
 
    // Try all N adjacent of (*x, *y)
    int start = rand()%N;
    for (int count = 0; count < N; count++)
    {
        int i = (start + count)%N;
        temp_x = *x + coord_x[i];
        temp_y = *y + coord_y[i];
        if ((isValid(a, temp_x, temp_y)) && (c = getDegree(a, temp_x, temp_y)) < min_deg)
        {
            min_deg_idx = i;
            min_deg = c;
        }
    }
 
    // return False if no valid moves
    if (min_deg_idx == -1)
        return false;
 
    // Store next point
    temp_x = *x + coord_x[min_deg_idx];
    temp_y = *y + coord_y[min_deg_idx];
 
    // Increment number of Moves
    a[temp_y*N + temp_x] = a[(*y)*N + (*x)]+1;
 
    // Set new point
    *x = temp_x;
    *y = temp_y;
 
    return true;
} 

bool Task2::closedTour(int x, int y, int initial_x, int initial_y){
    for (int i = 0; i < N; ++i){
        if (((x+coord_x[i]) == initial_x)&&((y + coord_y[i]) == initial_y)){
          	printf("Total number of moves is 63\n");
            return true;
        }
    }
    return false;
}

void Task2::printBoard(int a[])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printf("%d\t",a[j*N+i]);
        printf("\n");
    }
}
 

 
// Driver code
int main()
{
    new Task2();

    return 0;
}