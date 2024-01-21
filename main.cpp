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
  sf::RenderWindow window(sf::VideoMode(700, 620), "My window");
  window.setFramerateLimit(60);

  Game game = Game();


  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed){
        window.close();
      }

      if(event.type == sf::Event::KeyPressed){
        sf::Keyboard::Key key = event.key.code;
        game.HandleInput(key);
      }

    }

    if(EventTriggered(game.grid.game_speed)) {
        game.MoveBLockDown();
    }
      
    window.clear(sf::Color(255, 182, 193));
  
    game.Draw(window);
    window.display();

  }


}