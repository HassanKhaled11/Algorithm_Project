
#include <iostream>
int coins[12]={1,1,1,1,1,1,1,1,1,1,1,1};

void fakeOneOut(int n){
    for (int i=1; i<n;i++){
        if (coins[0]==coins[i])
           {
              if(i==n-1)
              std::cout<< "all coins are genuine";
           }
    
        else if (coins[0]< coins[i]){
            if(coins[0]< coins[i+1]){
            std::cout<<"1th coin is the fake one and is lighter";
            break;}
            else 
            std::cout<<i+1<<"th coin is the fake one and is heavier";
            break;
        }
        else if(coins[0]> coins[i]){
            if(coins[0]> coins[i+1]){
            std::cout<<"1th coin is the fake one and is heavier";
            break;}
            else 
            std::cout<<i+1<<"th coin is the fake one and is lighter";
            break;
        }
    }
} 
int main() {

    int n=12;
    fakeOneOut(n);
    return 0;
}