void encFunz() {
  value = encoder->getValue();

  if (value != 0 && mode == 0 && function == 1) {                                        /////////////// MASTER VOLUME
    masterVol += value;
    if (masterVol >= 127) {
      masterVol = 127;
    }
    if (masterVol <= 0) {
      masterVol = 0;
    }
    controlChange(0, 7, masterVol);         //(channel, cc, val)
    /*Serial.print("Master Vol = ");
      Serial.println(masterVol);*/
    delay(10);
  }

  else if (value != 0 && mode == 0 && function == 2) {                                    /////////////// HP1 VOLUME
    hp1Vol += value;
    if (hp1Vol >= 127) {
      hp1Vol = 127;
    }
    if (hp1Vol <= 0) {
      hp1Vol = 0;
    }
    controlChange(8, 111, hp1Vol);         //(channel, cc, val)
    /*Serial.print("HP1 Vol = ");
      Serial.println(hp1Vol);*/
    delay(10);
  }

  else if (value != 0 && mode == 0 && function == 3) {                                    /////////////// HP2 VOLUME
    hp2Vol += value;
    if (hp2Vol >= 127) {
      hp2Vol = 127;
    }
    if (hp2Vol <= 0) {
      hp2Vol = 0;
    }
    controlChange(8, 112, hp2Vol);         //(channel, cc, val)
    /*Serial.print("HP2 Vol = ");
      Serial.println(hp2Vol);*/
    delay(10);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (value != 0 && mode == 1 && function == 1) {                                /////////////// MOUSE SCROLL VERTICAL
    mouseMovement = value;
    int scroll = constrain(mouseMovement, -1, 1);
    Mouse.move(0, 0, scroll);
    delay(50);
  }


  if (value != 0 && mode == 1 && function == 2) {                                     /////////////// MOUSE DRAG VERTICAL
    encTimer = 0;
    relTimer = 0;
    mouseMovement = value;
    if (!Mouse.isPressed(MOUSE_LEFT) && mode == 1) {
      Mouse.press(MOUSE_LEFT);
    }
    Mouse.move(0, -mouseMovement * multiplierY, 0);
  }
  if (encTimer > ENC_TIME && value == 0) {
    if (Mouse.isPressed(MOUSE_LEFT && relTimer > CLICK_TIME)) {
      Mouse.release(MOUSE_LEFT);
    }
  }


  if (value != 0 && mode == 1 && function == 3) {                                     /////////////// MOUSE DRAG HORIZONTAL
    encTimer = 0;
    relTimer = 0;
    mouseMovement = value;
    if (!Mouse.isPressed(MOUSE_LEFT) && mode == 1) {
      Mouse.press(MOUSE_LEFT);
    }
    Mouse.move(mouseMovement * multiplierX, 0, 0);
  }
  if (encTimer > ENC_TIME && value == 0) {
    if (Mouse.isPressed(MOUSE_LEFT && relTimer > CLICK_TIME)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
}
