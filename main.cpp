#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "board.hpp"
#include "pieces.hpp"
#include "game.hpp"

double LastUpdateTime = 0;
sf::Clock gameClock;

bool EventTriggered(double interval) {
  double cur_time = gameClock.getElapsedTime().asMilliseconds();
  if(cur_time - LastUpdateTime >= interval) {
    LastUpdateTime = cur_time;
    return true;
  }
  return false;
}

int main()
{
  sf::RenderWindow window(sf::VideoMode({700, 620}), "My window");
  window.setFramerateLimit(60);

  Game game = Game();


  while (window.isOpen())
  {
    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>()){
        window.close();
      }

      if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
        game.HandleInput(keyPressed->code);
      }

    }

    if(EventTriggered(game.grid.game_speed)) {
        game.MoveBlockDown();
    }

    window.clear(sf::Color(255, 182, 193));

    game.Draw(window);
    window.display();

  }


}