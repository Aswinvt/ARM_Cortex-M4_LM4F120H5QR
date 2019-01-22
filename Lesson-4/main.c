int main() {
  *((unsigned int *)0x400FE608U) = 0x20U; //Enable and provide a clock to GPIO Port F in Run mode
  *((unsigned int *)0x40025400U) = 0x0EU; //Configure GPIO F - 1, 2, 3 pin as output
  *((unsigned int *)0x4002551CU) = 0x0EU; //Configure GPIO F - 1, 2, 3 as digital output
  while(1) {
  *((unsigned int *)0x400253FCU) = 0x02U; //Configure GPIO F bit-1 to high
  int counter = 0;
  while (counter < 1000000) {
    ++counter;
  }
  *((unsigned int *)0x400253FCU) = 0x00U; //Configure GPIO F bit-1 to low
  while (counter < 1000000) {
    ++counter;
  }
  }
  return 0;
}
