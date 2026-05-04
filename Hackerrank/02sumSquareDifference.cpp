#include <iostream>
#include <math.h>




int main(){
		
	  int n{3};
	  int sqSum{};


	  if (n < 7){
		  int tot{};
		  for (int i = 1; i < n + 1; i++){
			  tot+= i;

		  }
		  std::cout << tot <<"\n";

        sqSum = std::pow(tot,2);
	  }else {
        sqSum = std::pow(((n/2)*(n+1)),2);

	  }
       int sumSq = ((n*((n+1)*(2*n+1)))/6);


	   std::cout << sqSum << '\n';
	   std::cout << sumSq << '\n';

	   std::cout << std::abs(sqSum - sumSq) << '\n';

	return 0;
}
