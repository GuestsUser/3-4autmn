#pragma once

class Slider {
private:

  int handleColor;
  int backColor;
  int fillColor;

  bool handleEnabled;
  bool isHandleMove;

  VECTOR position;
  VECTOR handleSize;
  VECTOR backSize;

  VECTOR handlePosition = {};

  float value;
  float maxValue = 1;
  float minValue = 0;

public:

  int Get_MaxValue();

  Slider();

  void SetValue(float setValue);
  void SetMaxValue(float setMaxValue);
  void SetMinValue(float setMinValue);
  float GetValue();
  void SetPosition(float setPositionX, float setPositionY);
  void SetHandleSize(float setHandleWidth, float setHandleHeight);
  void SetHandleColor(int setHandleColor);
  void SetHandleEnabled(bool setEnabled);
  bool GetHandleEnabled();
  void SetBackSize(float setBackWidth, float setBackHeight);
  void SetBackColor(int setBackColor);
  void SetFillColor(int setFillColor);

  void Inisialize();
  void Update(int mousePosX, int mousePosY, bool icClick);
  void Draw();

  //点の位置,Boxの位置(真ん中),ボックスのサイズ(真ん中から端)
  bool PixelAndBoxHit(float pixelX, float pixelY, float boxPosX, float boxPosY, float boxWidth, float boxHeight) {

    float vx = boxPosX - pixelX;
    float vy = boxPosY - pixelY;

    if (vx < 0) vx *= -1;
    if (vy < 0) vy *= -1;

    if (vx < boxWidth && vy < boxHeight) {
      return true;
    }

    return false;
  }
};
