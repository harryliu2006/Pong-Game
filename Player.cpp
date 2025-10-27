
#include "Player.h"

#include "Globals.h"
#include "Screen.h"

Player ::Player() {}

Player ::Player(double x_in, double y_in, int height_in) {
  x = x_in;
  y = y_in;
  height = height_in;
  width = 1;
}

double Player::getX() { return x; }

double Player::getY() { return y; }

int Player::getHeight() { return height; }

int Player::getWidth() { return width; }

void Player::decreaseHeight(int delta_to_decrease_by) {
  height -= delta_to_decrease_by;
  if (height < 3) {
    height = 3;
  }
}

void Player::update(char c) {
  if (c == 'A') {
    y += 2;
  } else if (c == 'B') {
    y -= 2;
  }
  if (y < 0) {
    y = 0;
  };
  if (y + height > HEIGHT) {
    y = HEIGHT - height;
  };
}

void Player::draw(Screen& screen_to_draw_to) {
  for (int i = 0; i < height; i++) {
    screen_to_draw_to.addPixel(x, y + i, '#');
  }
}
