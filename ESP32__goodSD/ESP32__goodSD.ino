
#include <mySD.h>
#define LED_BUILTIN 22
File root;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("Initializing SD card...");
  /* initialize SD library with SPI pins */
 if (!SD.begin(13,15,2,14)) {            //T1:13,15,2,14  T2: 23,5,19,18 M5：4,23,19,18 uint8_t csPin, int8_t mosi, int8_t miso, int8_t sck
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  /* Begin at the root "/" */
  root = SD.open("/");
  if (root) {    
    printDirectory(root, 0);
    root.close();
  } else {
    Serial.println("error opening test.txt");
  }
  /* open "test.txt" for writing */
  root = SD.open("test.txt", FILE_WRITE);
  /* if open succesfully -> root != NULL 
    then write string "Hello world!" to it
  */
  if (root) {
    root.println("Hello world!");
    root.flush();
   /* close the file */
    root.close();
  } else {
    /* if the file open error, print an error */
    Serial.println("error opening test.txt");
  }
  delay(1000);
  /* after writing then reopen the file and read it */
  root = SD.open("test.txt");
  if (root) {    
    /* read from the file until there's nothing else in it */
    while (root.available()) {
      /* read the file and print to Terminal */
      Serial.write(root.read());
    }
    root.close();
  } else {
    Serial.println("error opening test.txt");
  }
  
  Serial.println("done!");
}

void loop()
{
   digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

void printDirectory(File dir, int numTabs) {
  
  while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');   // we'll have a nice indentation
     }
     // Print the name
     Serial.print(entry.name());
     /* Recurse for directories, otherwise print the file size */
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       /* files have sizes, directories do not */
       Serial.print("\t\t");
       Serial.println(entry.size());
     }
     entry.close();
   }
}
