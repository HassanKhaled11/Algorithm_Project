/*
    Assumptions:
    1) The coordinates of the grid start from the top left (0, 0) and end in the bottom right with (n - 1, n - 1)
    2) x axis increase to the right, y axis increase to down ward
    3) We have only three colors RGB (RED_COLOR, GREEN_COLOR, BLUE_COLOR)
    4) GREEN_COLOR is used in the center, RED_COLOR is used in topRight, and bottomLeft, and BLUE_COLOR is used
       in the topLeft, and bottomRight
*/


#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define EMPTY_SYMBOL        '-'
#define MISSING_SYMBOL      '#'
#define RED_COLOR           'R'         // top right and bottom left
#define GREEN_COLOR         'G'         // the center
#define BLUE_COLOR          'B'         // top left and bottom right

bool firstIteration = true;

typedef enum
{
    topRight = 0,
    bottomRight,
    bottomLeft,
    topLeft,
    whole
}ESubGrid;



void print(vector<vector<char>>v, int n)
{
    for (int i = 0; i < pow(2, n); i++)
    {
        for (int j = 0; j < pow(2, n); j++)
        {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

void fill_center_first_time(vector<vector<char>>& v, vector<pair<int, int>>centerPoints, int xMiss, int yMiss, int xStart, int xEnd, int yStart, int yEnd)
{
    /*Check whether the missing square is in the top right sub grid*/
    if ((xMiss >= centerPoints[topRight].first && xMiss <= xEnd) &&
        (yMiss >= yStart && yMiss <= centerPoints[topRight].second))
    {         
        v[centerPoints[bottomRight].second][centerPoints[bottomRight].first] = GREEN_COLOR;
        v[centerPoints[bottomLeft].second][centerPoints[bottomLeft].first] = GREEN_COLOR;
        v[centerPoints[topLeft].second][centerPoints[topLeft].first] = GREEN_COLOR;
    }
    /*Check whether the missing square is in the bottom right sub grid*/
    else if ((xMiss >= centerPoints[bottomRight].first && xMiss <= xEnd) &&
            (yMiss >= centerPoints[bottomRight].second && yMiss <= yEnd))
    {
        v[centerPoints[bottomLeft].second][centerPoints[bottomLeft].first] = GREEN_COLOR;
        v[centerPoints[topLeft].second][centerPoints[topLeft].first] = GREEN_COLOR;
        v[centerPoints[topRight].second][centerPoints[topRight].first] = GREEN_COLOR;
    }
    /*Check whether the missing square is in the bottom left sub grid*/
    else if ((xMiss >= xStart && xMiss <= centerPoints[bottomLeft].first) &&
            (yMiss >= centerPoints[bottomLeft].second && yMiss <= yEnd))
    {
        v[centerPoints[bottomRight].second][centerPoints[bottomRight].first] = GREEN_COLOR;
        v[centerPoints[topRight].second][centerPoints[topRight].first] = GREEN_COLOR;
        v[centerPoints[topLeft].second][centerPoints[topLeft].first] = GREEN_COLOR;
    }
    /*Check whether the missing square is in the top right sub grid*/
    else
    {
        v[centerPoints[topRight].second][centerPoints[topRight].first] = GREEN_COLOR;
        v[centerPoints[bottomRight].second][centerPoints[bottomRight].first] = GREEN_COLOR;
        v[centerPoints[bottomLeft].second][centerPoints[bottomLeft].first] = GREEN_COLOR;
    }
}


void fill_center_with_missing(vector<vector<char>>&v, vector<pair<int, int>>centerPoints, int xMiss, int yMiss)
{
    /*Fill all the central points with GREEN_COLOR*/
    v[centerPoints[topLeft].second][centerPoints[topLeft].first] = GREEN_COLOR;
    v[centerPoints[topRight].second][centerPoints[topRight].first] = GREEN_COLOR;
    v[centerPoints[bottomLeft].second][centerPoints[bottomLeft].first] = GREEN_COLOR;
    v[centerPoints[bottomRight].second][centerPoints[bottomRight].first] = GREEN_COLOR;

    /*Reset the MISSING_SYMBOL in its positon*/
    if (xMiss == centerPoints[topLeft].first && yMiss == centerPoints[topLeft].second)
        v[centerPoints[topLeft].second][centerPoints[topLeft].first] = MISSING_SYMBOL;
    else if (xMiss == centerPoints[topRight].first && yMiss == centerPoints[topRight].second)
        v[centerPoints[topRight].second][centerPoints[topRight].first] = MISSING_SYMBOL;
    else if (xMiss == centerPoints[bottomLeft].first && yMiss == centerPoints[bottomLeft].second)
        v[centerPoints[bottomLeft].second][centerPoints[bottomLeft].first] = MISSING_SYMBOL;
    else
        v[centerPoints[bottomRight].second][centerPoints[bottomRight].first] = MISSING_SYMBOL;
}


void fill_center(vector<vector<char>>& v, ESubGrid subGrid, vector<pair<int, int>>centerPoints, int xMiss, int yMiss)
{
    switch (subGrid)
    {
    case topRight:
        /*Fill topRight sub grid center*/
        if (v[centerPoints[bottomLeft].second + 1][centerPoints[bottomLeft].first - 1] == GREEN_COLOR)
        {
            v[centerPoints[bottomRight].second][centerPoints[bottomRight].first] = GREEN_COLOR;
            v[centerPoints[topRight].second][centerPoints[topRight].first] = GREEN_COLOR;
            v[centerPoints[topLeft].second][centerPoints[topLeft].first] = GREEN_COLOR;
        }
        /*This subgrid has the missing square*/
        else
            fill_center_with_missing(v, centerPoints, xMiss, yMiss);
        break;
    case bottomRight:
        /*Fill bottomRight sub grid center*/
        if (v[centerPoints[topLeft].second - 1][centerPoints[topLeft].first - 1] == GREEN_COLOR)
        {
            v[centerPoints[bottomRight].second][centerPoints[bottomRight].first] = GREEN_COLOR;
            v[centerPoints[topRight].second][centerPoints[topRight].first] = GREEN_COLOR;
            v[centerPoints[bottomLeft].second][centerPoints[bottomLeft].first] = GREEN_COLOR;
        }
        /*This subgrid has the missing square*/
        else
            fill_center_with_missing(v, centerPoints, xMiss, yMiss);
        break;
    case bottomLeft:
        /*Fill bottomLeft sub grid center*/
        if (v[centerPoints[topRight].second - 1][centerPoints[topRight].first + 1] == GREEN_COLOR)
        {
            v[centerPoints[bottomRight].second][centerPoints[bottomRight].first] = GREEN_COLOR;
            v[centerPoints[topLeft].second][centerPoints[topLeft].first] = GREEN_COLOR;
            v[centerPoints[bottomLeft].second][centerPoints[bottomLeft].first] = GREEN_COLOR;
        }
        /*This subgrid has the missing square*/
        else
            fill_center_with_missing(v, centerPoints, xMiss, yMiss);
        break;
    case topLeft:
        /*Fill bottomLeft sub grid center*/
        if (v[centerPoints[bottomRight].second + 1][centerPoints[bottomRight].first + 1] == GREEN_COLOR)
        {
            v[centerPoints[topRight].second][centerPoints[topRight].first] = GREEN_COLOR;
            v[centerPoints[topLeft].second][centerPoints[topLeft].first] = GREEN_COLOR;
            v[centerPoints[bottomLeft].second][centerPoints[bottomLeft].first] = GREEN_COLOR;
        }
        /*This subgrid has the missing square*/
        else        
            fill_center_with_missing(v, centerPoints, xMiss, yMiss);        
        break;
    }

}


vector<pair<int, int>> fill(vector<vector<char>>& v, int xMiss, int yMiss, int xStart, int xEnd, int yStart, int yEnd, ESubGrid subGride)
{
    vector<pair<int, int>>centerPoints(4);
    vector<pair<int, int>>xyStart(1);
    xyStart[0] = { xStart, yStart };
    // store the center points starting from topRightCenterX and Y then store as clockwise direction    
    centerPoints[topRight] = {xyStart[0].first + ((xEnd - xStart) / 2) + 1, xyStart[0].second + ((yEnd - yStart) / 2) };
    centerPoints[bottomRight] = { xyStart[0].first + ((xEnd - xStart) / 2) + 1, xyStart[0].second + ((yEnd - yStart) / 2) + 1 };
    centerPoints[bottomLeft] = { xyStart[0].first + ((xEnd - xStart) / 2), xyStart[0].second + ((yEnd - yStart) / 2) + 1 };
    centerPoints[topLeft] = { xyStart[0].first + ((xEnd - xStart) / 2), xyStart[0].second + ((yEnd - yStart) / 2) };


    if (firstIteration)
    {
        firstIteration = false;
        fill_center_first_time(v, centerPoints, xMiss, yMiss, xStart, xEnd, yStart, yEnd);
    }
    else
    {
        fill_center(v, subGride, centerPoints, xMiss, yMiss);
        
    }

    if (xEnd - xStart <= 3)
    {                
        return xyStart;
    }
        

    /*Divide the grid into four sub grids*/
    //callTopRight grid

    xyStart = fill(v, xMiss, yMiss, centerPoints[topRight].first, xEnd, yStart, centerPoints[topRight].second, topRight);
    //callBottomRight grid
    xyStart = fill(v, xMiss, yMiss, centerPoints[bottomRight].first, xEnd, centerPoints[bottomRight].second, yEnd, bottomRight);
    //callBottomLeft grid
    xyStart = fill(v, xMiss, yMiss, xStart, centerPoints[bottomLeft].first, centerPoints[bottomLeft].second, yEnd, bottomLeft);
    //callTopLeft grid
    xyStart = fill(v, xMiss, yMiss, xStart, centerPoints[topLeft].first, yStart, centerPoints[topLeft].second, topLeft);    
    return xyStart;
}

int main()
{
    int n, xMiss, yMiss;
    vector<vector<char>>v;
    do
    {
        cout << "Size = (2^n * 2^n) -> n = ";
        cin >> n;
        if (n <= 1)
            cout << "**Invalid**\n";
    } while (n <= 1);

    /*Fill the vector with an EMPTY_SYMBOL*/
    for (int i = 0; i < pow(2, n); i++)
    {
        vector<char>temp(pow(2, n), EMPTY_SYMBOL);
        v.push_back(temp);
    }
    /*Take the coordinates of the missing square*/
    do
    {
        cout << "Missing square point x[1:n] = ";
        cin >> xMiss;
        if (xMiss < 1 || xMiss > pow(2, n))
            cout << "**Invalid**\n";
    } while (xMiss < 1 || xMiss > pow(2, n));

    do
    {
        cout << "Missing square point y[1:n] = ";
        cin >> yMiss;
        if (yMiss < 1 || yMiss > pow(2, n))
            cout << "**Invalid**\n";
    } while (yMiss < 1 || yMiss > pow(2, n));
    v[yMiss - 1][xMiss - 1] = MISSING_SYMBOL;
    vector<pair<int, int>>xyStart(1);
    fill(v, xMiss - 1, yMiss - 1, 0, pow(2, n) - 1, 0, pow(2, n) - 1, whole);
    print(v, n);
}