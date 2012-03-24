/*
** Morse Code
** Flash morse code in pin 13...
** Author: Melody Bliss <melody@melodybliss.org>
*/
/*
** Contants.
** 1 = dit
** 0 = dah
** 111 is the beginning header.
**
** Notice that the dit/dah is in reverse bit order after the header
*/

byte MORSETABLE[] = {
    B11100000, // 0[0]
    B11100001, // 1[1]
    B11100011, // 2[2]
    B11100111, // 3[3]
    B11101111, // 4[4]
    B11111111, // 5[5]
    B11111110, // 6[6]
    B11111100, // 7[7]
    B11111000, // 8[8]
    B11110000, // 9[9]
    B11101, // A[10]
    B1111110, // B[11]
    B1111010, // C[12]
    B111110, // D[13]
    B1111, // E[14]
    B1111011, // F[15]
    B111100, // G[16]
    B1111111, // H[17]
    B11111, // I[18]
    B1110001, // J[19]
    B111010, // K[20]
    B1111101, // L[21]
    B11100, // M[22]
    B11110, // N[23]
    B111000, // O[24]
    B1111001, // P[25]
    B1110100, // Q[26]
    B111101, // R[27]
    B111111, // S[28]
    B1110, // T[29]
    B111011, // U[30]
    B1110111, // V[31]
    B111001, // W[32]
    B1110110, // X[33]
    B1110010, // Y[34]
    B1111100, // Z[35]
};


const int farnsworth = 2;            // a multiplier between the pause
const int ditlength = 100;
const int dahlength = ditlength * 3;
const int between = ditlength * 5;
const int pause = (ditlength * 5) * farnsworth;

void dit()
{
  digitalWrite(13, HIGH);
  delay(ditlength);
  digitalWrite(13, LOW);
  delay(between);
}

void dah()
{
  digitalWrite(13, HIGH);
  delay(dahlength);
  digitalWrite(13, LOW);
  delay(between);
}

void send_morse(char c)
{
  int i = int(c);      // Convert c to an int
  // Is this a number?
  int n = i - 48;      // 48 is ascii 0
  if(n >= 10) {
    // This is a character, not a number
    n = i - 55;  // 65 is ascii A, 10 is where A starts. so we want to subtract
                 // 55
  }
  byte b = MORSETABLE[n];    // Get the byte array out of MORSETABLE
  byte r[8];
  int size=0;
  // Start iterating through the table while we have bits to process
  while(b != B0) {
    r[size] = b & 1;
    b = b >> 1;            // Shift bits by 1
    size++;
  }
  
  /*
  ** At this point, r contains an array of 1/0 and size-3 is the real size of
  ** this array
  */
  
  for(int i; i < (size - 3); i++)
  {
    if(r[i] == B1)
    {
      dit();
    }
      else
    {
      dah();
    }
  }
  
}

void send_morse_string(char *s)
{
  Serial.println("Sending...");
  Serial.print("s is ");
  Serial.println(s);
  for(int i = 0; s[i] != 0; i++)
  {
    Serial.print(s[i]);
    send_morse(s[i]);
  }
  Serial.println(".");
}


void setup() {                
  // initialize the digital pin as an output.
  // Pin 13 has an LED connected on most Arduino boards:
  pinMode(13, OUTPUT);     
  Serial.begin(9600);
  Serial.println("Sending Morse");
}

void loop() {
  //send_morse_string("SOS");
  //delay(pause);
  send_morse_string("KF6RMW");
  delay(pause);
  
}
