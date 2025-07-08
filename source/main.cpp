/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos
 */

#include "simulation.hpp"

int main(int argc, char* argv[]) {
  // SnazeSimulation is a singleton.
  SnazeSimulation &sg = SnazeSimulation::get_instance(); //Initalize Singleton sg (snakegame)
  sg.initialize(argc, argv);
  sg.get_levels()[0].print_level(sg.get_levels()[0]);

  sg.get_player();//.get_snake().set_position(sg.get_current_level(), 'c', sg.get_current_level().get_spawnpoint());
  sg.get_levels()[0].print_level(sg.get_levels()[0]);
  // The Game Loop.
  while (not sg.is_over()) {
    sg.process_events();
    sg.update();
    sg.render();
  }
  return 0;
}