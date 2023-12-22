void Task2code(void* pvParameters) {
  for (;;) {
    val_sensor1 = !digitalRead(pin_Sensor1);
    val_sensor4 = !digitalRead(pin_Sensor4);
    val_limit1 = !digitalRead(pin_Limit1);
    val_limit2 = !digitalRead(pin_Limit2);
    //debug();

    if (StageStop == 0) {
      if (stateN == 0) {
        Assemble_parts = 0;
        Servo4.write(0);
        Servo1.write(0);
        if (val_sensor1) {
          Workin_processt = 1;
          //digitalWrite(pin_Commu, 1);
          delay_N(100);
          //digitalWrite(pin_Commu, 0);
          delay_N(40000);  // Wait Golf 40 sec
          Servo1.write(180);
          stateN = 1;
        } else {
          belt1(0);
          belt2(0);
        }
      }
      if (stateN == 1) {
        Assemble_parts = 1;
        Serial.println("Stage 1 Belt 1 Moving");
        belt1(100);
        delay_N(2000);
        belt1(140);
        delay_N(6000);
        belt1(100);
        delay_N(2000);
        stateN = 2;
      } else if (stateN == 2) {
        Assemble_parts = 2;
        Serial.println("Stage 2 Cartesian");
        if (val_limit1) {
          belt1(0);
          bridge(0);
          Servo2.write(90);  //Open
          delay_N(1000);
          Servo3.write(0);  //Down
          delay_N(1000);
          Servo2.write(170);  //Close
          delay_N(1000);
          Servo3.write(180);  //up
          delay_N(1000);
          stateN = 3;
        } else {
          bridge(80);
        }
      } else if (stateN == 3) {
        Assemble_parts = 3;
        Serial.println("Stage 3 Cartesian Move to Belt 2");
        if (val_limit2) {
          bridge(0);
          Servo3.write(0);  //Down
          delay_N(1000);
          Servo2.write(95);  //Open
          delay_N(1000);
          Servo3.write(180);  //up
          stateN = 4;
        } else {
          bridge(-80);
        }
      } else if (stateN == 4) {
        Assemble_parts = 4;
        Serial.println("Stage 4 Belt 2");
        if (val_sensor4) {
          belt2(-200);
          //digitalWrite(pin_Commu, 1);
          //delay_N(100);
          //digitalWrite(pin_Commu, 0);
          //delay_N(100);
          //digitalWrite(pin_Commu, 1);
          //delay_N(100);
          //digitalWrite(pin_Commu, 0);
          delay_N(3000);
          belt2(0);
          delay_N(45000);     // Wait Golf 45 sec
          Servo4.write(180);  //up
          stateN = 5;
        } else {
          belt2(-150);
        }
      } else if (stateN == 5) {
        Assemble_parts = 5;
        Serial.println("Stage 5 Finish");
        // belt2(-200);
        // delay_N(5500);
        belt2(0);
        Servo4.write(0);
        Servo1.write(0);
        Workin_processt = 0;
        Finished_product += 1;
        StageStop = 1;
        stateN = 0;
      }
    } else if (StageStop == 1) {
      if (val_limit1 || val_limit2) { bridge(0); }
      belt1(0);
      belt2(0);
      Servo1.write(180);  //Open gate 1
      Servo2.write(95);   //Open Gripper
      //Servo2.write(170); //Close Gripper
      Servo3.write(180);  //Up Griper
      //Servo3.write(0);  //Down Griper
      Servo4.write(180);  //Open gate 2
      // bridge(-100);
    }
  }
}