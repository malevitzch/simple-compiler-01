
add_executable(simple-compiler-01 main.cpp compiler.cpp lexer.cpp operator_trie.cpp operators.cpp shunting_yard.cpp build_log.cpp)
target_include_directories(simple-compiler-01 PRIVATE ${CMAKE_SOURCE_DIR}/include)
