//
// Created by lyh on 12/13/2023.
//

#include "Annotation.h"

Annotation::Annotation(const std::string &content) : content(content) {}

std::string Annotation::translate() {
    return this->content + "\n";
}
