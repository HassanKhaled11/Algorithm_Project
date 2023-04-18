/*
 ******************************Poisoned Wine Problem********************************
 *
 * @Solution Algorithm: Divide and conquer 
 * 
 * @Description: number all the 1000 barrels from 0 -> 999 in binary format, suppose that we have
 * 10 slaves, then slave#1 will drink from all the barrels that have the first digit equals to 1 
 * for ex. (0000000001, 0000000011, 0000000101, 0000000111, ...etc), and slave#2 will drink 
 * from barrels that have the second digit equals to 1 for ex. (0000000010, 0000000011, 0000000110, ...etc)
 * and so on. Then we can determine the poisoned barrel as follows: if only slave#1 dies, then
 * the poisoned barrel index in binary formate is 0000000001 which is barrel that has 1 in decimal.
 * 
 * @Algorithm steps: 
 *      1- ckecks the possibility to solve the problem based on the number of slaves entered, 
 *         and the index of the poisoned barrel
 *      2- divide the vector of "barrelNumber" that has 1000 string numbered from 0 -> 999 into
 *         to halves (0 -> 499 and 500 -> 999) then divide each one again into two halves ...etc
 *         until reaching the leaves which has one number
 *      3- check if this barrel is poisoned, then the slaves who drink from this barrel will be 
 *         marked to die (i.e. set the value one in "slavesLives" vector).
 *      4- convert the binary in slavesLives to decimal which is the decimal index of
 *         the poisoned barrel
 * 
 * * @Assumptions: 
 *      1- number of barrels is constant equals to 1000    
 *      2- numbering all the barrels as binary string is not considered a part of the algorithm,
 *         but it is considered as a precondition for the algorithm, and thus the time 
 *         taken to fill the vector of strings "barrelNumber" is not considered 
 *      3- storing the barrels from which each slave drinks is also not considered a part from 
 *         the algorithm, it is just for visualization
 *      4- All slaves drink from their barrels at the same time
*/

#include<iostream>
#include<vector>
#include<bitset>
#include<cmath>
using namespace std;

#define NUMBER_OF_DIGITS    10
#define NUMBER_OF_BARRELS   1000

//Global variables
int poisonedIndex;
vector<string>barrelNumber(NUMBER_OF_BARRELS);    


void divide_and_Conquer(int l, int r, vector<bool>&slavesLives, vector<vector<int>>&slavesBarrels)
{
    int m = (l + r) / 2;
    if(l >= r)
    {
        /*Fill slavesBarrels*/
        for (int i = NUMBER_OF_DIGITS - 1; i >= 0; i--)
        {
            if(barrelNumber[l][i] == '1')
                slavesBarrels[NUMBER_OF_DIGITS - i - 1].push_back(l);
        }                


        /*Fill slavesLives*/
        if(l == poisonedIndex)
        {            
            for (int i = 0; i < NUMBER_OF_DIGITS; i++)
            {
                if(barrelNumber[l][NUMBER_OF_DIGITS - i - 1] == '1')
                    slavesLives[i] = 1;
            }                                
        }
        return;
    }
    divide_and_Conquer(l, m, slavesLives, slavesBarrels);
    divide_and_Conquer(m + 1, r, slavesLives, slavesBarrels);
}




int main()
{   
    /*Take the input from the user*/
    int noSlaves;
    cout << "The index of the poisoned one (0 -> " << NUMBER_OF_BARRELS - 1 << "): ";
    cin >> poisonedIndex;
    cout << "Number of slaves: ";
    cin >> noSlaves;
    vector<bool>slavesLives(noSlaves, 0);        
    vector<vector<int>>slavesBarrels(noSlaves);
    

    /*Check whether the problem can be solved or not. this depends on the number of slaves*/
    if(noSlaves >= NUMBER_OF_DIGITS)
    {     
        //Fill the vector "barrelNumber" with the binary string for the index of each barrel   
        for (int i = 0; i < NUMBER_OF_BARRELS; i++)
        {
            bitset<10>binaryString{(unsigned int)i};   
            barrelNumber[i] = binaryString.to_string();                
        }


        //call the algorithm
        divide_and_Conquer(0, NUMBER_OF_BARRELS - 1, slavesLives, slavesBarrels);


        //print the barrels from which each slave drinks
        for (int i = 0; i < noSlaves; i++)
        {
            cout << "\n\n***Slave " << i + 1 << "***\n";
            for (int j = 0; j < slavesBarrels[i].size(); j++)
            {
                cout << slavesBarrels[i][j] << "  ";
            }  
            cout << "\n";          
        }


        //calculate the poisoned barrel number in decimal
        int poisonedBarrelIndexDecimal = 0;
        int j = 1;
        for (int i = 0; i < noSlaves; i++)
        {            
            poisonedBarrelIndexDecimal += (int)slavesLives[i] *  j;
            j *= 2;
        }
        cout << "\n\nThe poisoned barrel index is: " << poisonedBarrelIndexDecimal << "\n\n\n";
        
    }
    else
        cout << "Impossible to determine the poisoned barrel!!\n";
}