//
// Created by lyh on 11/3/2023.
//

#ifndef SYSY_COMPILER_IDENT_H
#define SYSY_COMPILER_IDENT_H
#include <string>

class Ident {
public:
    std::string word;
    Ident(std::string word);
    void setWord(std::string word);
};


#endif //SYSY_COMPILER_IDENT_H
