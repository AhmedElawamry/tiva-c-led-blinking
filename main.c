#include "tm4c123gh6pm.h"
#define PORTF_MASK       (1U<<5)
#define DARK             (0U)
#define RED              (1U<<1)
#define BLUE             (1U<<2)
#define GREEN            (1U<<3)
#define YELLOW           (1U<<1 | 1U<<3)
#define SKYBLUE          (1U<<2 | 1U<<3)
#define PINK             (1U<<1 | 1U<<2)
#define WHITE            (1U<<1 | 1U<<2 |1U<<3)
#define Left_SW          (1U<<4)
#define Right_SW         (1U)

void PORTF_init(void){
    int dummy;
    dummy = SYSCTL_RCGCGPIO_R;
    SYSCTL_RCGCGPIO_R |= PORTF_MASK; // portf clock enable 0010 0000
    GPIO_PORTF_LOCK_R = 0x4c4f434b;
    GPIO_PORTF_CR_R = 0x01f;
    GPIO_PORTF_DEN_R |= 0x1f; // RED|BLUE|GREEN|Left_SW|Right_SW;
    GPIO_PORTF_DIR_R |= 0x0e;
    GPIO_PORTF_DIR_R &= ~0x11;
    GPIO_PORTF_PUR_R |= (Left_SW|Right_SW);
}

void delay(int n){
  for(int i=0;i<n;i++){}
}
  
int main(){
  char color[8] = {DARK, RED, BLUE, GREEN, YELLOW, SKYBLUE, PINK, WHITE};
  PORTF_init();
  int counter =0;
  int state =0;
  while(1){
    state = GPIO_PORTF_DATA_R & 0x11;
    delay(1000000);
    switch(state){
      case 0x11:
        break;
      case 0x01: 
          if (counter == 0)
            {counter = 8;}
          else
            {counter--;}
          GPIO_PORTF_DATA_R = color[counter];
          break;
      case 0x10:
          if (counter == 7)
            counter = 0;
          else {counter++;}
            GPIO_PORTF_DATA_R = color[counter];
          break;
      case 0x00: 
        counter = 7;
        GPIO_PORTF_DATA_R = color[counter];
        break;
    }
  }
  return 0;
}


