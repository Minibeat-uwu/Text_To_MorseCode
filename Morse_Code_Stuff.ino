//hand sign converted to morse code//

// a->b == (a*).b

//There are also Serial.readString();
//Global constants for the pins
int buz = 2;


//Global Variables
String strInput = "";
char strChar = 0;
int counter = 0;
bool check = false;
bool chkend = false;

//Morse Code Specific delays
const int McUnit = 75;
int McDit = McUnit;
int McDah = 3 * McUnit;
int letterDelay = 3 * McUnit;
int wordDelay = 7 * McUnit;

//MorseCode Library

char MorseLib[][10] = {
  ".-", "-...", "-.-.", "-..",          //A-D
  ".", "..-.", "--.", "....", "..",     //E-I
  ".---", "-.-", ".-..", "--", "-.",    //J-N
  "---", ".--.", "--.-", ".-.", "...",  //O-S
  "-", "..-", "...-", ".--", "-..-",    //T-X
  "-.--", "--..",                       //Y-Z
};

char MorseNum[][10] = {

  ".----", "..---", "...--", "....-", ".....",    //1-5
  "-....", "--...", "---..", "----.", "-----"     //6-0
};

//link list node

typedef struct List *node;    //It's like a initializer to the address of the new node.


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Please input a new input");
  pinMode(buz, OUTPUT);
}


void loop() {
  strChar = 0;
  unsigned int asc;
  char MC[10] = {0};
  readInput();


  if (strChar != 0) {
    asc = strChar;
    
    if (asc > 96 && asc < 123) { //small letters
      delay(letterDelay);
      strcpy(MC, MorseLib[asc - 97]);
    }
    else if (asc > 64 && asc < 91) { //Capital Letters
      delay(letterDelay);
      strcpy(MC, MorseLib[asc - 65]);
    }
    else if (asc == 32) { //space
      //Add delay:
      Serial.println("(SPACE)");
      delay(wordDelay);
      MC[0] = ' ';
    }
    else if(asc>47 && asc<58){
      delay(letterDelay);
      strcpy(MC,MorseNum[asc-48]);
      }

    else {}

    DiDa(MC);



  }//End of if

}//End of loop

void DiDa(char info[10]) {
  int i = 0;
  Serial.print(strChar);
  while (info[i] != 0) {

    if (info[i] == '.') {
      digitalWrite(buz, HIGH);
      Serial.print(" .");
      delay(McDit);
      digitalWrite(buz, LOW);
    }

    if (info[i] == '-') {
      digitalWrite(buz, HIGH);
      Serial.print(" -");
      delay(McDah);
      digitalWrite(buz, LOW);
    }
    delay(McUnit);
    i++;

  }// End of while loop
Serial.println(" ");
}//End of function

void readInput() {
  if (Serial.available() > 0) {
    strChar = Serial.read();
    if (strChar != '\n') {
      strInput += strChar;
    }
    else {
      Serial.print("Your input: ");
      Serial.println(strInput);
      strInput = "";
      strChar = 0;

    }
  }// End of if 

}
