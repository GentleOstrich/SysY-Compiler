//
// Created by lyh on 12/13/2023.
//

#ifndef SYSY_COMPILER_ANNOTATION_H
#define SYSY_COMPILER_ANNOTATION_H


#include "MipsInstruction.h"

class Annotation : public MipsInstruction {
public:
    std::string content;

    Annotation(const std::string &content);

    std::string translate() override ;
};


#endif //SYSY_COMPILER_ANNOTATION_H
