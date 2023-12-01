//
// Created by lyh on 11/19/2023.
//

#ifndef SYSY_COMPILER_PARAM_H
#define SYSY_COMPILER_PARAM_H

#include "../Value.h"

class Param : public Value {
public:
    int pos;

    std::vector<int> dims;

    Param(const std::string &name, ValueType valueType, int pos);

    std::string getName() override ;

    void addDim(int dim);

    std::string getType() override;
};


#endif //SYSY_COMPILER_PARAM_H
