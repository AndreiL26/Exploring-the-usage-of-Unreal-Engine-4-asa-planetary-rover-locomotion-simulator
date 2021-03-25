In order to run the Gazebo world containing the setup for recreating each experiment, the following steps are required:

1. Install Gazebo version 9.0 or higher. 
2. If you installed Gazebo from debians, make sure to also install the Gazebo development files, this can be achieved by running:
   $ sudo apt-get install libgazebo9-dev 
   * If you have any other version than 9, replace the 9 in the command above with your version.
3. Create a new folder, say Root. Inside this new folder copy the CMakeLists, force_pattern.cc and force_pattern_experiment.world files.
4. Inside the Root folder, create a build directory:
   $ mkdir build
5. Compile the code:
   $ cd build
   $ cmake ../
   $ make
6. Add your library path to the GAZEBO_PLUGIN_PATH:
   $ export GAZEBO_PLUGIN_PATH=${GAZEBO_PLUGIN_PATH}:~/Root/build
7. Open the world with gzserver:
   $ cd ..
   $ gzserver -u force_pattern_experiment.world
8. In a new terminal window, start the client:
   $ gzclient
 
In order to recreate a certain force pattern or constant force experiment, modify the variables from the force_pattern.cc file accordingly. More specifically,
running any of the 4 patterns can be achieved by changing the value of the patternNumber variable and then executing steps 5-8 from above again.