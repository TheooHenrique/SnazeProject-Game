/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos
 */

#include "player.cpp"
#include "level.cpp"
#include "reader.cpp"
#include "simulation.hpp"
#include "snake.cpp"

int main(int argc, char* argv[]) {
  // SnazeSimulation is a singleton.
  SnazeSimulation &sg = SnazeSimulation::get_instance(); //Initalize Singleton sg (snakegame)
  sg.initialize(argc, argv);

  // The Game Loop.
  while (not sg.is_over()) {
    sg.process_events();
    sg.update();
    sg.render();
  }
  return 0;
}