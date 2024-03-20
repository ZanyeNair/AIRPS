/*

*/

void setup() {
    //kesavan stuff
}

void loop() 
{
    if (!huskylens.request()) 
Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));

    else if(!huskylens.isLearned()) 
Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));

    else if(!huskylens.available()) 
Serial.println(F("No block or arrow appears on the screen!"));

    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
            sense(result);
        }    
    }
}


void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}

void sense(HUSKYLENSResult result)
{
  if(result.ID == 1){
    if(cC == 1){
      //white light
    }
    else if(cC == 2){
      //red light
    }
    else{
      //green light
    }

  }
  else if(result.ID == 2){
    if(cC == 1){
      //green light
    }
    else if(cC == 2){
      //white light
    }
    else{
      //red light
    }
  }
  else{
    if(cC == 1){
      //red light
    }
    else if(cC == 2){
      //green light
    }
    else{
      //white light
    }
  }
  
}
