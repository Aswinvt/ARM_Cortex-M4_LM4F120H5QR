#include <stdint.h>
#include "tm4c_cmsis.h"
#include "delay.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

int16_t x = -1;
uint32_t y = LED_RED | LED_GREEN;

int16_t sqr[] = {
  1*1,
  2*2,
  3*3,
  4*4
};

typedef struct {
  uint8_t y;
  uint16_t x;
}point;

point p1, p2;

typedef struct {
  point top_left;
  point bottom_right;
}window;

window w = {
  {123U, 0x1234U},
  {234U, 0x6789U}
};

typedef struct {
  point corners[3];
}Triangle;

window w, w2;
Triangle t;

int main() {
  point *pp;
  window *wp;
  
  p1.x = sizeof(point);
  p1.y = 0xAAU;
  
  w.top_left.x = 1U;
  w.bottom_right.y = 2U;
  
  t.corners[0].x = 1U;
  t.corners[2].y = 2U;
  
  p2 = p1;
  w2 = w;
  
  pp = &p1;
  wp = &w2;
  
  (*pp).x = 1U;
  
  (*wp).top_left = *pp;
  
  pp->x = 1U;
  wp->top_left = *pp;
  
  SYSCTL->RCGC2          |= (1U << 5); //Enable and provide a clock to GPIO Port F in Run mode
  SYSCTL->GPIOHSCTL      |= (1U << 5); // Enable AHB for GPIOF
  GPIOF_HS->DIR          |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIOF_HS->DEN          |= (LED_RED | LED_BLUE | LED_GREEN);
  
  GPIOF_HS->DATA_Bits[LED_BLUE] = LED_BLUE;
  while(1) {
  GPIOF_HS->DATA_Bits[LED_RED] = LED_RED; //Uses the Store (STR) instruction sequence instead of Read, Modify, Write sequence
  delay();
  GPIOF_HS->DATA_Bits[LED_RED] = 0;
  delay();
  }
  return 0;
}