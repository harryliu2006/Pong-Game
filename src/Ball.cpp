
#include "Ball.h"

#include "Globals.h"
#include "Screen.h"

Ball::Ball() {}

Ball::Ball(double x_in, double y_in, double velocity_x_in, double velocity_y_in,
           int id_in) {
  height = 1;
  width = 1;
  x = x_in;
  y = y_in;
  velocity_x = velocity_x_in;
  velocity_y = velocity_y_in;
  id = id_in;
}

double Ball::getX() { return x; }

int Ball::getID() { return id; }

void Ball::update() {
  velocity_y = velocity_y - 0.02 * timeStep;
  x = x + velocity_x * timeStep;
  y = y + velocity_y * timeStep;
}

int Ball::overlap(Ball& b) { return NO_OVERLAP; }

int Ball::overlap(Player& p) {
  double overlapHorizontal;
  double overlapVertical;

  double rightEdge = p.getX() + p.getWidth();
  double bottomEdge = p.getY();
  double topEdge = p.getY() + p.getHeight();

  double leftBall = x;
  double bottomBall = y;
  double topBall = y + height;

  if (bottomBall >= topEdge || leftBall >= rightEdge || topBall <= bottomEdge) {
    return NO_OVERLAP;
  }

  else {
    // case where the ball comes from right of the paddle
    overlapHorizontal = rightEdge - leftBall;
    // case where ball comes from below the paddle
    if (velocity_y > 0) {
      overlapVertical = bottomBall + height - bottomEdge;
    } else {
      overlapVertical = topEdge - bottomBall;
      // case where ball comes from ontop of the paddle
    }

    if (overlapVertical > overlapHorizontal) {
      return VERTICAL_OVERLAP;
    } else {
      return HORIZONTAL_OVERLAP;
    }
  }
}
void Ball::bounce(Ball arr[], int ballCount, Player player) {
  double leftBall = x;
  double rightBall = x + width;
  double bottomBall = y;
  double topBall = y + height;

  double leftEdge = player.getX();
  double rightEdge = player.getX() + player.getWidth();
  double bottomEdge = player.getY();
  double topEdge = player.getY() + player.getHeight();

  int paddleBounce = overlap(player);
  // bounce logic for overlap with paddle
  if (paddleBounce != NO_OVERLAP) {
    if (paddleBounce == VERTICAL_OVERLAP) {
      velocity_x = -velocity_x;
      x = rightEdge;
    } else {
      if (velocity_y < 0) {
        velocity_y = -velocity_y;
        y = bottomEdge - height;
      } else {
        velocity_y = -velocity_y;
        y = topEdge;
      }
    }
  }
  // bounce logic for overlap with walls
  if (rightBall > WIDTH) {
    velocity_x = -velocity_x;
    x = WIDTH - width;
  }
  if (topBall > HEIGHT) {
    velocity_y = -velocity_y;
    y = HEIGHT - height;
  }
  if (bottomBall < 0) {
    velocity_y = -velocity_y;
    y = 0;
  }
}

void Ball::draw(Screen& screen_to_draw_to) {
  screen_to_draw_to.addPixel(x, y, 'o');
}
