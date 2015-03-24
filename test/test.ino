
#include "LedControl.h" // Pin 7 to Data In, 6 to Clk, 5 to LOAD, number of devices is 3 
LedControl lc=LedControl(7,6,5,2);

void setup() { 
// Initialize the 3 MAX7219 devices 
for(int k=0; k<2; k++){ 
      lc.shutdown(k,false); // Enable display 
      lc.setIntensity(k,5); // Set brightness level (0 is min, 15 is max) 
      lc.clearDisplay(k); // Clear display register 
      } 
} 
void loop() { 
long long nr = 0; 
long long aux =0;
long long aux2 =0;

  

while (1){
  aux = nr/100000000;
  aux2 = nr%100000000;

 for(int i=0; i<8; i++){ 
                
                 
                    
               lc.setDigit(1,i,aux2%10, false); // Decimal point enabled 
               aux2/=10;
                
                }
//  delay(1);
     
 for(int i=0; i<8; i++){ 
                
                 
                    
        lc.setDigit(0,i,aux%10, false); // Decimal point enabled 
        aux/=10;
                
                }
           // delay(1);
  
      
    
    
if(nr > 9999999999999999)
              nr=0;
nr+=1000;
} 

}
