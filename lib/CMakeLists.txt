set(ASSIGNMENT_4_PLUGINS HelloWorld OpcodeCounter ArithmeticSimplifier)

set(HelloWorld_SOURCES HelloWorld.cpp)
set(OpcodeCounter_SOURCES OpcodeCounter.cpp)
set(ArithmeticSimplifier_SOURCES ArithmeticSimplifier.cpp)

foreach(plugin ${ASSIGNMENT_4_PLUGINS})
  # Create a library corresponding to 'plugin'
  add_library(${plugin} SHARED ${${plugin}_SOURCES})

  # Configure include directories for 'plugin'
  target_include_directories(${plugin}
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../include")

endforeach()
