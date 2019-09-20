set(files
        src/Lexer.cpp

        src/Lexer/Tokens.cpp
        )

add_library(Lexer STATIC ${files})

target_include_directories(Lexer PUBLIC include)
