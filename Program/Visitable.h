//
// Created by mpkow on 17.05.2023.
//

#ifndef LEXER_VISITABLE_H
#define LEXER_VISITABLE_H

#include "Visitator.h"

class Visitable {
    void accept(Visitator visitator){
        visitator.visit(this);
    };
};


#endif //LEXER_VISITABLE_H
