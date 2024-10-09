#include "gateway.h"
#include<iostream>

bool Gateway::hasFont_ = false;
sf::Font Gateway::font_;

Gateway::Gateway(float x, float y, std::string label)
{ 
    if (!hasFont_) { 
        if (!font_.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font" << std::endl;
            return;
        }
        hasFont_ = true;  
    }
    text_.setFont(font_);
    text_.setString(label);
    text_.setCharacterSize(20); 
    text_.setFillColor(sf::Color::Black); 

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(sf::Vector2f(textBounds.width / 2, textBounds.height / 2));  
    text_.setPosition(sf::Vector2f(x, y));  
}

void Gateway::rotate(float angle)
{
    shape_.rotate(sf::degrees(angle));
    text_.rotate(sf::degrees(angle));
}

void Gateway::offset(float x, float y)
{
    sf::Vector2f vec(x, y);
    shapeOffset_ = shape_.getPosition() - vec;
    textOffset_ = text_.getPosition() - vec;
}

void Gateway::setPosition(sf::Vector2f pos)
{
    shape_.setPosition(pos + shapeOffset_); // Update position with offset
    text_.setPosition(pos + textOffset_);
}

void Gateway::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    target.draw(shape_);
    target.draw(text_);
}

void Input::generate(float x, float y)
{
    std::vector<sf::Vector2f> border = { { -140, 20 }, { 160,20 }, { 160,-20 }, { -140,-20 }, { -160,0 } };
    shape_.setPointCount(border.size());
    for (int i = 0; const auto & point : border) {
        shape_.setPoint(i++, point);
    }
    shape_.setFillColor(sf::Color::Color(254, 215, 106));
    shape_.setOutlineColor(sf::Color::Black);
    shape_.setOutlineThickness(3);
    shape_.setPosition(sf::Vector2f(x, y));
    shape_.setOrigin(sf::Vector2f(0, 0));
}

void Output::generate(float x, float y)
{
    std::vector<sf::Vector2f> border = {{ -150, 20 }, { 150,20 }, { 170,0 }, { 150,-20 }, { -150,-20 }};
    shape_.setPointCount(border.size());
    for (int i = 0; const auto & point : border) {
        shape_.setPoint(i++, point);
    }
    shape_.setFillColor(sf::Color::Color(254, 215, 106)); 
    shape_.setOutlineColor(sf::Color::Black); 
    shape_.setOutlineThickness(3);  
    shape_.setPosition(sf::Vector2f(x, y));
    shape_.setOrigin(sf::Vector2f(10, 0));
}

void Bidirectional::generate(float x, float y)
{
    std::vector<sf::Vector2f> border = { { -140, 20 }, { 140,20 }, { 160,0 }, { 140,-20 }, { -140,-20 }, { -160,0 } };
    shape_.setPointCount(border.size());
    for (int i = 0; const auto & point : border) {
        shape_.setPoint(i++, point);
    }
    shape_.setFillColor(sf::Color::Color(254, 215, 106));
    shape_.setOutlineColor(sf::Color::Black);
    shape_.setOutlineThickness(3);
    shape_.setPosition(sf::Vector2f(x, y));
    shape_.setOrigin(sf::Vector2f(0, 0));
}
