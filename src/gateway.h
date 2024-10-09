#pragma once

#include <SFML/Graphics.hpp> 
#include <SFML/Graphics/Drawable.hpp>

class Gateway:public sf::Drawable {
public:
    Gateway(float x,float y,std::string label);
    inline sf::ConvexShape& shape() { return shape_; } 
    void rotate(float angle);
    void offset(float x, float y);
    void setPosition(sf::Vector2f pos);

    static sf::Font font_;
    static bool hasFont_;
protected:
    virtual void generate(float x, float y) = 0;
    sf::ConvexShape shape_;
private:      
    void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

    sf::Text text_;     
    sf::Vector2f shapeOffset_;
    sf::Vector2f textOffset_;
    
};

class Input:public Gateway {
public:
    Input(float x, float y, std::string label) :Gateway(x, y, label) {
        generate(x, y);
    }
protected:
    void generate(float x, float y);
};

class Output:public Gateway {
public:
    Output(float x, float y, std::string label) :Gateway(x,y,label) {
        generate(x, y);
    }
protected:
    void generate(float x, float y);
};

class Bidirectional:public Gateway {
public:
    Bidirectional(float x, float y, std::string label) :Gateway(x, y, label) {
        generate(x, y);
    }
protected:
    void generate(float x, float y);
};