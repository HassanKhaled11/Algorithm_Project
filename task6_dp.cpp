#include <iostream>
#include <cstring>
int coins[12]={1,1,1,1,1,1,1,1,1,1,1,1};

const int ROWS = 4;
const int COLS = 12;
int memo[ROWS][COLS];

int weighingMemoHelper(int arr[], int s, int e) {
    if (s == e) {
        return 0;
    }
    else {
        int result = arr[e-1] + weighingMemoHelper(arr, s, e-1);
        memo[s][e] = result;
        return result;
    }
}
int weighing(int arr[], int s, int e) {
    memset(memo, -1, sizeof(memo));
    return weighingMemoHelper(arr, s, e);
}


int main(){

if(weighing(coins,0,4)==weighing(coins,4,8)){ //8genuine

 if((coins[0]+coins[8])==(coins[9]+coins[10])){
     if(coins[11]>coins[10]){
         std::cout<< "Coin 12 is fake and is heavier";
   }
    else if(coins[11]<coins[10])
         std::cout<< "Coin 12 is fake and is lighter";
     else 
         std::cout<< "All coins are genuine";
 }
 else if((coins[0]+coins[8])<(coins[9]+coins[10])){
    if(coins[9]==coins[10]){
         std::cout<< "Coin 9 is fake and is lighter";
    }
    else if(coins[9]<coins[10]){
           std::cout<< "Coin 11 is fake and is heavier";
    }
     else if(coins[9]>coins[10]){
           std::cout<< "Coin 10 is fake and is heavier";
    }
 }
 else if((coins[0]+coins[8])>(coins[9]+coins[10])){
       if(coins[9]==coins[10]){
         std::cout<< "Coin 9 is fake and is heavier";
    }
   else if(coins[9]<coins[10]){
           std::cout<< "Coin 10 is fake and is lighter";
    }
    else if(coins[9]>coins[10]){
           std::cout<< "Coin 11 is fake and is lighter";
    }
 }
 
}

else if(weighing(coins,0,4)>weighing(coins,4,8)){
    if((weighing(coins,0,3)+weighing(coins,4,6)<(coins[3]+weighing(coins,8,12)))){
            if(coins[4]<coins[5])
                   std::cout<< "Coin 5 is fake and is lighter";
            else if(coins[4]>coins[5])
                std::cout<< "Coin 6 is fake and is lighter";
            else
            std::cout<< "Coin 4 is fake and is heavier";
    }   
   if((weighing(coins,0,3)+weighing(coins,4,6)==(coins[3]+weighing(coins,8,12)))){
         if(coins[7]==coins[9])
            std::cout<< "Coin 7 is fake and is lighter";
        else
         std::cout<< "Coin 8 is fake and is lighter";
    }
    if((weighing(coins,0,3)+weighing(coins,4,6)>(coins[3]+weighing(coins,8,12)))){
         if(coins[0]==coins[1])
            std::cout<< "Coin 3 is fake and is heavier";
        else if(coins[0]<coins[1])
            std::cout<< "Coin 2 is fake and is heavier";
        else
          std::cout<< "Coin 1 is fake and is heavier";
    }
}

else if(weighing(coins,0,4)<weighing(coins,4,8)){
    if((weighing(coins,4,7)+weighing(coins,0,2)<(coins[7]+weighing(coins,8,12)))){
            if(coins[0]<coins[1])
                   std::cout<< "Coin 1 is fake and is lighter";
            else if(coins[0]>coins[1])
                std::cout<< "Coin 2 is fake and is lighter";
            else
            std::cout<< "Coin 8 is fake and is heavier";
    }   
    if((weighing(coins,4,7)+weighing(coins,0,2)==(coins[7]+weighing(coins,8,12)))){
         if(coins[3]==coins[9])
            std::cout<< "Coin 3 is fake and is lighter";
        else
            std::cout<< "Coin 4 is fake and is lighter";
    }
    if((weighing(coins,4,7)+weighing(coins,0,2)>(coins[7]+weighing(coins,8,12)))){
         if(coins[4]==coins[5])
            std::cout<< "Coin 7 is fake and is heavier";
        else if(coins[4]>coins[5])
            std::cout<< "Coin 5 is fake and is heavier";
        else
          std::cout<< "Coin 6 is fake and is heavier";
    }
}

return 0;
}
