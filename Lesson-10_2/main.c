// !! Stack Overflow and corruption!!

#include "lm4f120h5qr.h"
#include "delay.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

unsigned fact(unsigned n);

int main() {
  unsigned volatile x;
  
  x = fact(0U);
  x = 2U + 3U * fact(1U);
  (void)fact(7U);
  
  SYSCTL_RCGCGPIO_R      |= (1U << 5); //Enable and provide a clock to GPIO Port F in Run mode
  SYSCTL_GPIOHBCTL_R     |= (1U << 5); // Enable AHB for GPIOF
  GPIO_PORTF_AHB_DIR_R   |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIO_PORTF_AHB_DEN_R   |= (LED_RED | LED_BLUE | LED_GREEN);
  
  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
  while(1) {
  GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED; //Uses the Store (STR) instruction sequence instead of Read, Modify, Write sequence
  delay();
  GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
  delay();
  }
  return 0;
}

unsigned fact(unsigned n) {
  //0! = 1
  //n! = n(n-1)! for n>0
  unsigned foo[6];
  foo[n] = n;
  if (n == 0U) {
    return 1U;
  }
  else {
    return foo[n] * fact(n - 1U);
  }
}