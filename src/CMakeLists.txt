
add_executable(simple-compiler-01 main.cpp compiler.cpp parser.cpp stringops.cpp lexer.cpp operator_trie.cpp operators.cpp shunting_yard.cpp)
target_include_directories(simple-compiler-01 PRIVATE ${CMAKE_SOURCE_DIR}/include)
