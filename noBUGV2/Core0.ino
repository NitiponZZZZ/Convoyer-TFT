void Task1code(void* pvParameters) {
  for (;;) {
    if (page == '1') { 
      tft.setTextSize(10);
      tft.setTextColor(tft.color24to16(0x3B3B3B));
      tft.setTextDatum(CC_DATUM);
      tft.drawNumber(Finished_product, 130, 120);
      tft.setTextSize(2);
      tft.setTextColor(tft.color24to16(0xFFFFFF));
      tft.setTextDatum(CC_DATUM);
      tft.drawNumber(Workin_processt, 350, 75);
      tft.drawNumber(Assemble_parts, 350, 165);
      tft.drawNumber(Defective_part, 350, 255);
      uint16_t x, y;
      if (tft.getTouch(&x, &y)) {
        if ((x > 250 && x < 455) && (y > 20 && y < 55)) about_page();
        if ((x > 360 && x < 450) && (y > 70 && y < 110)) StageStop = 0;
        else if ((x > 255 && x < 345) && (y > 70 && y < 110)) StageStop = 1;
      }
    }
    if (page == '2') {
      uint16_t x, y;
      if (tft.getTouch(&x, &y)) {
        if ((x > 5 && x < 95) && (y > 5 && y < 35)) main_page();
      }
    }
  }
}