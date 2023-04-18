#include<iostream>
#include<vector>
#include<bitset>
using namespace std;

#define NUMBER_OF_DIGITS    10
#define NUMBER_OF_BARRELS   1000

int poisonedIndex;
vector<string>barrelNumber(NUMBER_OF_BARRELS); 

void brute_force(vector<bool>&slavesLives, vector<vector<int>>&slavesBarrels)
{
    for (int i = 0; i < NUMBER_OF_BARRELS; i++)
    {

         /*Fill slavesBarrels*/
        for (int j = NUMBER_OF_DIGITS - 1; j >= 0; j--)
        {
            if(barrelNumber[i][j] == '1')
                slavesBarrels[NUMBER_OF_DIGITS - j - 1].push_back(i);
        }     

        if(i == poisonedIndex)
        {
            /*Fill slavesLives*/
            for (int j = 0; j < NUMBER_OF_DIGITS; j++)
            {
                if(barrelNumber[i][NUMBER_OF_DIGITS - j - 1] == '1')
                    slavesLives[j] = 1;
            } 
        }
    }
    
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
        brute_force(slavesLives, slavesBarrels);


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