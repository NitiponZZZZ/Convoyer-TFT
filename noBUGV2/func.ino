void belt1(int speed) {
  int dir;
  if (speed > 0) {
    dir = 0;
  } else if (speed < 0) {
    dir = 1;
  }
  ledcWrite(PWM1_Ch, abs(speed));
  digitalWrite(pin_Motor_B, dir);
}
void belt2(int speed) {
  int dir;
  if (speed > 0) {
    dir = 0;
  } else if (speed < 0) {
    dir = 1;
  }
  ledcWrite(PWM2_Ch, abs(speed));
  digitalWrite(pin_Motor_D, dir);
}
void bridge(int speed) {
  if (speed > 0) {
    ledcWrite(PWM3_Ch, abs(speed));
    digitalWrite(pin_Motor_F, 1);
    digitalWrite(pin_Motor_G, 0);
  } else if (speed < 0) {
    ledcWrite(PWM3_Ch, abs(speed));
    digitalWrite(pin_Motor_F, 0);
    digitalWrite(pin_Motor_G, 1);
  }
  if (speed == 0) {
    ledcWrite(PWM3_Ch, abs(5));
    digitalWrite(pin_Motor_F, 1);
    digitalWrite(pin_Motor_G, 1);
  }
}
void main_page() {
  tft.fillScreen(tft.color24to16(0x3B3B3B));
  tft.fillRoundRect(30, 200, 90, 40, 6, tft.color24to16(0x1ABC9C));     //Start
  tft.fillRoundRect(140, 200, 90, 40, 6, tft.color24to16(0xE74C3C));    // Stop
  tft.fillRoundRect(30, 250, 200, 40, 6, tft.color24to16(0x008000));    // about
  tft.fillRoundRect(250, 50, 200, 50, 10, tft.color24to16(0xFFA500));   //Work-in process :
  tft.drawRoundRect(250, 50, 200, 50, 10, tft.color24to16(0xFFFFFF));   //Work-in process :
  tft.fillRoundRect(250, 140, 200, 50, 10, tft.color24to16(0xFFA500));  //Assemble parts :
  tft.drawRoundRect(250, 140, 200, 50, 10, tft.color24to16(0xFFFFFF));  //Assemble parts :
  tft.fillRoundRect(250, 230, 200, 50, 10, tft.color24to16(0xFF4040));  //Defective part :
  tft.drawRoundRect(250, 230, 200, 50, 10, tft.color24to16(0xFFFFFF));  //Defective part :
  tft.fillRoundRect(30, 50, 200, 140, 10, tft.color24to16(0xFFFFFF));   //Finished product
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(ML_DATUM);
  tft.drawString("Finished product", 30, 30);
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(ML_DATUM);
  tft.drawString("Work-in process", 253, 30);
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(ML_DATUM);
  tft.drawString("Assemble parts", 253, 120);
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(ML_DATUM);
  tft.drawString("Defective part", 253, 210);
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(CC_DATUM);
  tft.drawString("START", 77, 220);
  tft.drawString("STOP", 187, 220);
  tft.drawString("ABOUT", 130, 270);
  page = '1';
}
void about_page() {
  uint16_t x, y;
  tft.fillScreen(tft.color24to16(0x3B3B3B));
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0xFF4040));
  tft.setTextDatum(CC_DATUM);
  tft.drawString("Robotic and Automation Engineering", 240, 40);
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(ML_DATUM);
  tft.drawString("1. Mr. Nitipon       Phairatsamee ", 40, 85);
  tft.drawString("2. Mr. Panuphong     Parapluung", 40, 115);
  tft.drawString("3. Mr. Napapol       Chatwikanet", 40, 145);
  tft.drawString("4. Mr. Ekarach       Lengnui", 40, 175);
  tft.drawString("5. Mr. Thanawat      Phoophoom", 40, 205);
  tft.drawString("6. Ms. Phetpon       Sodkaew", 40, 235);
  tft.fillRoundRect(380, 270, 90, 40, 6, tft.color24to16(0x1ABC9C));  //Back
  tft.setTextSize(2);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(CC_DATUM);
  tft.drawString("BACK", 425, 290);
  page = '2';
}
void delay_N(unsigned int period) {
  unsigned long last_time = millis();
  while (millis() - last_time < period) {
    ;
  }
}
void debug() {
  Serial.print(" IR1 :");
  Serial.print(val_sensor1);
  Serial.print(" IR2 :");
  Serial.print(val_sensor4);
  Serial.print(" Limit1 :");
  Serial.print(val_limit1);
  Serial.print(" Limit2 :");
  Serial.println(val_limit2);
}