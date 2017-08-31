# miTaPaSS
minimal Task Partitioning Swarm Simulator

This simulator is used to simulate different engines based on the study of "Evolution of Self-Organized Task
Specialization in Robot Swarms" Ferrante et al. (doi:10.1371/journal.pcbi.1004273)

## Build
 1. go to build-folder ''cd build''
 1. generate makefile ''cmake ..''
 1. make program ''make''

## Usage
compiled progam is in ''bin/miTaPaSS''

### Quickstart
From the build folder run ''../bin/miTaPaSS''

### ConfigFile
miTaPaSS uses a configFile. A ''default.cfg'' is already provided in the build-folder.
To use it run miTaPaSS from the same folder as the ''default.cfg''.

To use another configFile run miTaPaSS with the path to your configFile.
All options are of the form [option]=[value]

 * Area size options
   * ''area_width'': the width of the simulation area
   * ''zone_nest_end'': at which index the nest ends
   * ''zone_cache_end'': at which index the cache ends
   * ''zone_slope_end'': at which index the slope ends
   * ''zone_source_end'': at which index the source ends, this is also the height of the simulation area
 * Simulation objects
   * ''robot_num'': how much robots are on the simulation area
   * ''token_num'': the inital amount of tokens
 * Simulation time
   * ''time_generations'': simulated generations, between generations, learning takes place
   * ''time_try'': times each generation is executed to average fitness
   * ''time_run'': simulationsteps for each try
   * ''area_num'': number of areas, that are simulated for each try, this builds the population for evolution based engines
 * ''engine'': which RobotEngine to use
   * value ''neural'': the neural engine
   * value ''manual'': a hardcoded generalist strategy
   * value ''ferrante'': a poor try to fake the winning controller of the original paper (does not work)
 * ''vizualization'': vizualization mode
   * value ''none'': no visualization
   * value ''visualize'': do a little terminal visualization as fast as possible
   * value ''manual'': same as visualize, but press enter to go to the next step
 * Log options: (use ''none'' as value to skip saving)
   * ''genSaveFile'': filname where to log some values of each generation, if using neuralengine; each row represents a generation.
     1. generation index
     1. index of best performing area
     1. retrieved tokens of best area in all trys
     1. tokens picked up from the slope (rough index of task partitioning) of best area summed up over all trys
     1. overall tokens at simulationend of best area summed up over all trys
     1. All following values are weights of the best areas neural net
   * ''genLoadFile'': file with weights to load for the neural engine (currently buggy)
   * ''stepSaveFilePrefix'': file-prefix for stepLogfile that log each step of each area in one generation values are:
     1. simulation step
     1. following the [y-coordinate]; [carrying]; of all robots
   * ''minGenToStepLog'': generation where to start logging each generation in a stepLogfile
   * ''maxGenToStepLog'': generation where to stop logging each generation in a stepLogfile


The output using the neural engine is similar to the genSaveFile outputs.
