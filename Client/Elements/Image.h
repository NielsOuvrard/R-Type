//
// Created by erwan on 10/20/23.
//

#pragma once

#include "Element.h"

class Image : public Element {
public:
    Image(Haze::Engine &engine, const std::string &filepath, AxisPair position = {0, 0}, AxisPair scale = {1, 1});
    void build() override;

private:
public:
    void update() override;

private:
    std::string _filepath;
};
