# CMake generated Testfile for 
# Source directory: /home/mint/nt5/src/external/cJSON
# Build directory: /home/mint/nt5/build/src/external/cJSON
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/home/mint/nt5/build/src/external/cJSON/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "/home/mint/nt5/src/external/cJSON/CMakeLists.txt;252;add_test;/home/mint/nt5/src/external/cJSON/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
