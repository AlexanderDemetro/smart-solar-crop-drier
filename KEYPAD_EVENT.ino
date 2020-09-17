void keypadEvent(KeypadEvent key){
  int state=keypad.getState();
    if(state==HOLD&&key=='1'){
      lcd.clear();
      lcd.noBlink();
     char m2[]="Temperature";
     char m3[]="setting Menu";
     char m1[]="opening";
     writer(0,4,1,1,70,m1,m2,m3); 
     delay(1000);
   
     setTemperature();
  }
    if(state==HOLD&&key=='2'){
      lcd.clear();
      lcd.noBlink();
     char m2[]="Humidity";
     char m3[]="setting Menu";
     char m1[]="opening";
     writer(0,4,1,1,70,m1,m2,m3); 
     delay(1000);
     
     setHumidity();
  }
    
  if(state==HOLD&&key=='0'){
    lcd.noBlink();
      lcd.clear();
 char msg1[]="TEMP:";
 char msg2[]="HUMID:";
 char msg3[]=" ";
   lcd.setCursor(1,0);
  lcd.print("Control Limits");
  writer(1,1,1,1,90,msg1,msg2,msg3); 

  lcd.setCursor(14,1);
  lcd.print("C");
    lcd.setCursor(13,1);
  lcd.write(byte(0));
  lcd.setCursor(14,2); 
  lcd.print("%");
   lcd.setCursor(13,3);
  lcd.print(" ");

  
  lcd.setCursor(11,1);
  lcd.print(EEPROM.read(tempAddress));
  lcd.setCursor(11,2); 
  lcd.print(EEPROM.read(humAddress));
    
  delay(2000);
  }
}
