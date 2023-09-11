#include <test.h>

std::string Test::getText(){
    return someText;
}

void Test::setText(std::string text){
    someText = text;
}