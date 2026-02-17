#include <stdio.h>
#include <stdlib.h>

void analyze_amortized_cost(int num_bits) {
  long long total_steps = 1LL << num_bits;
  
  int* bits = (int*)calloc(num_bits, sizeof(int));
  int prev_credit = 0;
  
  printf("Step\t|Binary\t\t|Actual Cost(Ti)|Credit (Ci)\t|Amortized Cost (Ai)\n");
  printf("-------------------------------------------------------------------------------");
  
  for (int step=1; step<total_steps; step++) {
    int actual_cost = 0;
    int current_credit = 0;
    
    // calculate true cost by simulating binary +1
    for (int i=num_bits-1; i>=0; i--) {
      actual_cost++;
      if (bits[i] == 0) {
        bits[i] = 1;
        break;
      } else {
        bits[i] = 0;
      }
    }
    
    // calculate credit
    printf("\n%d\t|\t", step);
    for (int i=0; i<num_bits; i++) {
      if (bits[i] == 1) current_credit++;
      printf("%d", bits[i]);
    }
    
    // calculate amortized cost
    int amortized_cost = actual_cost + current_credit - prev_credit;
    printf("\t|\t%d\t|\t%d\t|\t%d", actual_cost, current_credit, amortized_cost);
    
    prev_credit = current_credit;
  }
}

int main() {
  analyze_amortized_cost(4);
  printf("\n");
  return 0;
}
