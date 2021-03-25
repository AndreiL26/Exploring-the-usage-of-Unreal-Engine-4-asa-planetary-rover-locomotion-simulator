# CMake generated Testfile for 
# Source directory: /home/andrei/benchmark
# Build directory: /home/andrei/benchmark/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BENCHMARK_boxes_dt "/home/andrei/benchmark/build/BENCHMARK_boxes_dt" "--gtest_output=xml:/home/andrei/benchmark/build/test_results/BENCHMARK_boxes_dt.xml")
set_tests_properties(BENCHMARK_boxes_dt PROPERTIES  ENVIRONMENT "GAZEBO_MODEL_PATH=/home/andrei/benchmark/models:/usr/share/gazebo-9/models" TIMEOUT "500")
add_test(check_BENCHMARK_boxes_dt "/home/andrei/benchmark/tools/check_test_ran.py" "/home/andrei/benchmark/build/test_results/BENCHMARK_boxes_dt.xml")
add_test(csv_BENCHMARK_boxes_dt "/home/andrei/benchmark/tools/junit_to_csv.rb" "/home/andrei/benchmark/build/test_results/BENCHMARK_boxes_dt.xml" "/home/andrei/benchmark/test_results/BENCHMARK_boxes_dt")
add_test(BENCHMARK_boxes_model_count "/home/andrei/benchmark/build/BENCHMARK_boxes_model_count" "--gtest_output=xml:/home/andrei/benchmark/build/test_results/BENCHMARK_boxes_model_count.xml")
set_tests_properties(BENCHMARK_boxes_model_count PROPERTIES  ENVIRONMENT "GAZEBO_MODEL_PATH=/home/andrei/benchmark/models:/usr/share/gazebo-9/models" TIMEOUT "3000")
add_test(check_BENCHMARK_boxes_model_count "/home/andrei/benchmark/tools/check_test_ran.py" "/home/andrei/benchmark/build/test_results/BENCHMARK_boxes_model_count.xml")
add_test(csv_BENCHMARK_boxes_model_count "/home/andrei/benchmark/tools/junit_to_csv.rb" "/home/andrei/benchmark/build/test_results/BENCHMARK_boxes_model_count.xml" "/home/andrei/benchmark/test_results/BENCHMARK_boxes_model_count")
add_test(BENCHMARK_collide_spheres_dt "/home/andrei/benchmark/build/BENCHMARK_collide_spheres_dt" "--gtest_output=xml:/home/andrei/benchmark/build/test_results/BENCHMARK_collide_spheres_dt.xml")
set_tests_properties(BENCHMARK_collide_spheres_dt PROPERTIES  ENVIRONMENT "GAZEBO_MODEL_PATH=/home/andrei/benchmark/models:/usr/share/gazebo-9/models" TIMEOUT "240")
add_test(check_BENCHMARK_collide_spheres_dt "/home/andrei/benchmark/tools/check_test_ran.py" "/home/andrei/benchmark/build/test_results/BENCHMARK_collide_spheres_dt.xml")
add_test(csv_BENCHMARK_collide_spheres_dt "/home/andrei/benchmark/tools/junit_to_csv.rb" "/home/andrei/benchmark/build/test_results/BENCHMARK_collide_spheres_dt.xml" "/home/andrei/benchmark/test_results/BENCHMARK_collide_spheres_dt")
