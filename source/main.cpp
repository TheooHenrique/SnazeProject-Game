/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos
 */

#include "simulation.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  // SnazeSimulation is a singleton.
  SnazeSimulation &sg = SnazeSimulation::get_instance(); //Initalize Singleton sg (snakegame)
  sg.initialize(argc, argv);

  sg.get_current_level().print_level(sg.get_levels()[0]);
  sg.get_snake().set_position(sg.get_current_level(), 'C', sg.get_current_level().get_spawnpoint());

  std::cout << "\n";

  sg.get_current_level().print_level(sg.get_current_level());

  // The Game Loop.
  while (not sg.is_over()) {
    sg.process_events();
    sg.update();
    sg.render();
  }
  return 0;
}