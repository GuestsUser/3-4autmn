#include"BJ_Head.h"

Slider::Slider() {

  SetValue(0);
  SetPosition(0, 0);
  SetHandleSize(0, 0);
  SetHandleColor(0xffffff);
  SetHandleEnabled(true);
  SetBackSize(0, 0);
  SetBackColor(0xc8c8c8);
  SetFillColor(0x00ffff);
}

void Slider::SetValue(float setValue) {

  value = setValue;

  if (value < minValue) value = minValue;
  else if (value > maxValue) value = maxValue;
}

void Slider::SetMaxValue(float setMaxValue) {

  if (setMaxValue <= minValue) setMaxValue = minValue + 1;

  maxValue = setMaxValue;
}

void Slider::SetMinValue(float setMinValue) {

  if (setMinValue >= maxValue) setMinValue = maxValue - 1;

  minValue = setMinValue;
}

float Slider::GetValue() {
  return value;
}

void Slider::SetPosition(float setPositionX, float setPositionY) {
  position = { setPositionX,setPositionY };
}

void Slider::SetHandleSize(float setHandleWidth, float setHandleHeight) {
  handleSize = { setHandleWidth,setHandleHeight };
}

void Slider::SetHandleColor(int setHandleColor) {
  handleColor = setHandleColor;
}

void Slider::SetHandleEnabled(bool setHandleEnabled) {
  handleEnabled = setHandleEnabled;
}

bool Slider::GetHandleEnabled() {
  return handleEnabled;
}

void Slider::SetBackSize(float setBackWidth, float setBackHeight) {
  backSize = { setBackWidth,setBackHeight };
}

void Slider::SetBackColor(int setBackColor) {
  backColor = setBackColor;
}

void Slider::SetFillColor(int setFillColor) {
  fillColor = setFillColor;
}

void Slider::Inisialize() {

  SetPosition(320, 240);
  SetHandleSize(25, 25);
  SetBackSize(150, 20);

  SetFillColor(0x00ffff);

  SetMinValue(0); //最大値と最小値の指定する順番に注意
  SetMaxValue(10000);  //先に最大値を指定しようとすると、その指定した値が現在の最小値よりも小さいと指定できません

  SetValue(0);

}

void Slider::Update(int mousePosX, int mousePoxY, bool isClick) {


  if (PixelAndBoxHit(mousePosX, mousePoxY, handlePosition.x, handlePosition.y, handleSize.x, handleSize.y) == true && isClick == true) {

    isHandleMove = true;
  }
  else if (PixelAndBoxHit(mousePosX, mousePoxY, position.x, position.y, backSize.x + 100, backSize.y + 50) == false || isClick == false) {

    isHandleMove = false;
  }

  if (isHandleMove == true) {

    handlePosition.x = mousePosX;

    if (handlePosition.x > position.x + backSize.x) handlePosition.x = position.x + backSize.x;
    else if (handlePosition.x < position.x - backSize.x) handlePosition.x = position.x - backSize.x;


    value = (int)((handlePosition.x - (position.x - backSize.x)) / (backSize.x * 2.0f) * (maxValue - minValue) + minValue) / 100;


    if (value < minValue) value = minValue;
    else if (value > maxValue) value = maxValue;

  }
  else {

    handlePosition = {
        (position.x - backSize.x) + (value - minValue) / (maxValue - minValue) * (backSize.x * 2),
        position.y,
    };
  }
}

void Slider::Draw() {

  DrawBox(
    position.x - backSize.x, position.y - backSize.y,
    position.x + backSize.x, position.y + backSize.y,
    backColor, true);


  DrawBox(
    position.x - backSize.x + 1, position.y - backSize.y + 1,
    handlePosition.x - 1, position.y + backSize.y - 1,
    fillColor, true);


  if (GetHandleEnabled()) {

    DrawBox(
      handlePosition.x - handleSize.x, handlePosition.y - handleSize.y,
      handlePosition.x + handleSize.x, handlePosition.y + handleSize.y,
      handleColor, true);
  }
}
