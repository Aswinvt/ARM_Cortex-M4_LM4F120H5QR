#define RCGCGPIO    (*((unsigned int *)0x400FE608U))
#define GPIOF_BASE  (0x40025000U)
#define GPIOF_DIR   (*((unsigned int *)(GPIOF_BASE + 0x400U)))
#define GPIOF_DEN   (*((unsigned int *)(GPIOF_BASE + 0x51CU)))
#define GPIOF_DATA  (*((unsigned int *)(GPIOF_BASE + 0x3FCU)))

int main() {
  RCGCGPIO = 0x20U; //Enable and provide a clock to GPIO Port F in Run mode
  GPIOF_DIR = 0x0EU; //Configure GPIO F - 1, 2, 3 pin as output
  GPIOF_DEN = 0x0EU; //Configure GPIO F - 1, 2, 3 as digital output
  while(1) {
  GPIOF_DATA = 0x02U; //Configure GPIO F bit-1 to high
  int counter = 0;
  while (counter < 1000000) {
    ++counter;
  }
  GPIOF_DATA = 0x00U; //Configure GPIO F bit-1 to low
  while (counter < 1000000) {
    ++counter;
  }
  }
  return 0;
}
