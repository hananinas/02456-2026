#include <iostream>
#include <vector>
using namespace std;

int main(){

  // a shallow neural network is a function y = f[x, theta]

  vector<int> x_inputs{1,2,3,4,5,6,7,8,9,10};
  vector<int> theta_params{0,0,0,0,0,0,0,0,0};

  int y = 0;

  int L = 3;




  vector<float> weights;

  for (int i = 10; i == 0 ; i--)
       printf(weights.insert( weights.begin() + 1 , 0.2));

  for (auto x : x_inputs)
    printf("x%d,", x);
     for(auto t : theta_params)
        printf("   t %d, ", t);
         for(auto w : weights)
             printf("w %f ",w);

  cout << y;

  return 0;

}
