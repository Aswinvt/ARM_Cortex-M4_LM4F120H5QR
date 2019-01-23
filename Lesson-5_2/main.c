#include "lm4f120h5qr.h"

int main() {
  SYSCTL_RCGCGPIO_R = 0x20U; //Enable and provide a clock to GPIO Port F in Run mode
  GPIO_PORTF_DIR_R  = 0x0EU; //Configure GPIO F - 1, 2, 3 pin as output
  GPIO_PORTF_DEN_R = 0x0EU; //Configure GPIO F - 1, 2, 3 as digital output
  while(1) {
  GPIO_PORTF_DATA_R = 0x02U; //Configure GPIO F bit-1 to high
  
  int volatile counter = 0;
  while (counter < 1000000) {
    ++counter;
  }
  
  GPIO_PORTF_DATA_R = 0x00U; //Configure GPIO F bit-1 to low
  
  while (counter < 1000000) {
    ++counter;
  }
  }
  return 0;
}
