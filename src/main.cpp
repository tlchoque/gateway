#include <SFML/Graphics.hpp>
#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include "gateway.h"

 
int main() {
    int width = 1400;
    int height = 800;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4; 
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(width, height)), "Gateway Editor", sf::Style::Close | sf::Style::Titlebar, settings);

    ImGui::SFML::Init(window);
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_DockingEnable;
    sf::Clock deltaClock;
       
    std::vector<std::shared_ptr<Gateway>> gateways;

    bool actionPerformed = false;  
    const char* items[] = { "","Input", "Output", "Bidirectional" };
    int currentItem = 0; 
    int selected = -1;
    char buffer[256] = "";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the left mouse button is pressed
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Check if the mouse is within the polygon
                    for (int i = gateways.size() - 1; i >= 0;--i) {
                        if (gateways[i]->shape().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            selected = i;
                            gateways[i]->offset(event.mouseButton.x, event.mouseButton.y);
                            break;
                        } 
                    } 
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    selected = -1;
                }
            }
        } 

        if (selected!=-1 && sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (!actionPerformed) {  
                gateways[selected]->rotate(90);
                actionPerformed = true;  
            }
        }
        else {
            actionPerformed = false;  
        }
         
        if (selected != -1) {
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            gateways[selected]->setPosition(mousePosition);
        }

        sf::Time deltaTime = deltaClock.restart();

        ImGui::SFML::Update(window, deltaTime);
         
        // gateway form 
        ImGui::Begin("Gateway Form"); 
        ImGui::InputText("Gateway Name", buffer, sizeof(buffer));
        ImGui::Combo("Type", &currentItem, items, IM_ARRAYSIZE(items)); 
        if (ImGui::Button("Insert")) {  
            std::string str(buffer); 
            if (str.empty() || currentItem==0) { 
                std::cout << "Invalid input!" << std::endl;
                continue; 
            }           
            switch (currentItem) {
            case 1: {
                gateways.push_back(std::make_shared<Input>(width / 2, height / 2, buffer));
                break;
            }                
            case 2: {
                gateways.push_back(std::make_shared<Output>(width / 2, height / 2, buffer));
                break;
            }                
            case 3: {
                gateways.push_back(std::make_shared<Bidirectional>(width / 2, height / 2, buffer));
                break;
            }                
            default:
                std::cout << "Invalid input!" << std::endl;
                break;
            }
            buffer[0] = '\0';
            currentItem = 0;
        }
        ImGui::End();

        // Clear the window
        window.clear(sf::Color(200, 200, 200)); 
        ImGui::SFML::Render(window);

        // Draw gateways
        for(auto gate:gateways)
            window.draw(*gate); 

        // Display the contents of the window
        window.display();
    }

    return 0;
}