void button () {

  button1.Update();
  if (button1.clicks == 1) {
    function = 1;
  }
  if (button1.clicks == 2) {
    function = 2;
  }
  if (button1.clicks == 3) {
    function = 3;
  }
  if (button1.clicks == -1) {
    if (mode == 0) {
      mode = 1;
      function = 1;
    }
    else if (mode == 1) {
      mode = 0;
    }
  }
}
