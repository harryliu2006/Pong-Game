
#include <chrono>
#include <string>

#include "Ball.h"
#include "Globals.h"
#include "Player.h"
#include "Screen.h"
#include "io.h"

int main() {
  std::string messageToPutOnScreen;

  std::chrono::steady_clock::time_point begin_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point now_time;

  // instantiating objects and initializing variables
  Screen screen = Screen();
  int ballCount = 0;
  const int max_ballCount = 5;
  int score = 0;
  bool gameEnded = false;
  Ball balls_array[max_ballCount];
  balls_array[0] = Ball(30.0, 30.0, 1.7, 0, ballCount);
  ballCount++;
  Player player = Player(0, 5, 10);

  while (!gameEnded) {
    for (int frames = 0; frames < simulation_fps; frames++) {
      // handle input
      char c = get_input();
      if (c == 'q') {
        gameEnded = true;
      }
      if (c != '\0') {
        player.update(c);
      }

      // update balls
      for (int i = 0; i < ballCount; i++) {
        balls_array[i].update();

        // end game if ball hits left wall
        if (balls_array[i].getX() < 0.0) {
          gameEnded = true;
          break;
        }
        // scoring feature
        int overlap = balls_array[i].overlap(player);
        if (overlap != NO_OVERLAP) {
          score += 1;
          if (score % 2 == 0) {
            player.decreaseHeight(1);
          }
          if (score % 5 == 0 && ballCount < max_ballCount) {
            balls_array[ballCount] = Ball(30.0, 30.0, 0.9, 0, ballCount);
            ballCount += 1;
          }
        }
        // reflect ball off walls,ceiling,paddle. does nothing if no bounce
        balls_array[i].bounce(balls_array, ballCount, player);
      }
    }

    player.draw(screen);
    for (int j = 0; j < ballCount; j++) {
      balls_array[j].draw(screen);
    }

    messageToPutOnScreen = "Your score is: " + std::to_string(score);
    screen.update(messageToPutOnScreen);

    // wait until 1/fps seconds
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin_time)
               .count() < (long int)milliseconds_per_frame) {
    }

    begin_time = std::chrono::steady_clock::now();
  }

  messageToPutOnScreen = "Game over. Your score is: " + std::to_string(score);
  screen.update(messageToPutOnScreen);

  return 0;
}