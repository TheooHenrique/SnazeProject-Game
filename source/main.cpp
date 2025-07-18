/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos
 */

#include "simulation.hpp"

/**
 * @brief The main function that drives the game.
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return 0 on successful execution, non-zero otherwise.
 */
int main(int argc, char* argv[]) {
  // SnazeSimulation is a singleton.
  SnazeSimulation &sg = SnazeSimulation::get_instance(); //Initalize Singleton sg (snakegame)
  sg.initialize(argc, argv);

  // The Game Loop.
  while (not sg.is_over) {
    sg.process_events(); // Handle current state logic.
    sg.update();         // Transition to the next state.
    sg.render();         // Render the current game screen.
  }
  return 0;
}
