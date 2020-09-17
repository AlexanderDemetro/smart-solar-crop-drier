// display function
void temp_Humidity_Display(){
  temperature=dht.readTemperature();
  humidity=dht.readHumidity();
  
 int ldr1val,sum1,i,ldre;
  int ldr2val,sum2,ldrw;

  for(i=0; i<5; i++){
  ldr1val=analogRead(A0);
  sum1 +=ldr1val;
  }
ldre=sum1/5;

  for(i=0; i<5; i++){
  ldr2val=analogRead(A1);
  sum2 +=ldr2val;
    }
    ldrw=sum2/5;
    int dfn=ldre-ldrw;
  
    
  if(isnan(temperature)||isnan(humidity)){
    lcd.clear();
    lcd.setCursor(5,0);
  lcd.print("Temp Sensors");
  lcd.setCursor(2,1);
  lcd.print("Disconnected");
  }
  else{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("TEMP :        C");
  lcd.setCursor(13,0);
  lcd.write(byte(0));
  lcd.setCursor(0,1);
  lcd.print("HUMID:        %");
   lcd.setCursor(0,2);
   /*
  lcd.print("LDRE :");
   lcd.setCursor(0,3);
  lcd.print("LDRw :");
 lcd.setCursor(11,2);
  lcd.print("DFN:");
  */
    lcd.setCursor(7,0);
  lcd.print(temperature);
      lcd.setCursor(7,1);
  lcd.print(humidity); 
/*
   lcd.setCursor(7,2);
  lcd.print(ldre);
   lcd.setCursor(7,3);
  lcd.print(ldrw);
   lcd.setCursor(16,2);
  lcd.print(dfn);
  */
   if(temperature>limTemp){
    digitalWrite(relay,LOW);
   }

   else{
    digitalWrite(relay,HIGH);
   }
  }
  
}


//this function is ued to write chars on the display.............

void writer(int row,int x1,int x2,int x3,int wait,char fore1[],char fore2[],char fore3[]){
int i;
for(i=0;i<strlen(fore1);i++){
  lcd.setCursor((x1+i),row);
  lcd.print(fore1[i]);
  delay(wait);
}
for(i=0;i<strlen(fore2);i++){
  lcd.setCursor((x2+i),row+1);
  lcd.print(fore2[i]);
  delay(wait);
  }   
  for(i=0;i<strlen(fore3);i++){
  lcd.setCursor((x3+i),row+2);
  lcd.print(fore3[i]);
  delay(wait);
  }
}
