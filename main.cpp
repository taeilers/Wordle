#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(400, 400), "Wordle");
    
    RectangleShape letterBox[5];
    Text text[5];
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    std::string str = "";

    
    float letterBoxPos[] = { 0.f, 10.f };
    for (int i = 0; i < 5; i++)
    {
        text[i].setFillColor(sf::Color::White);
        text[i].setFont(font);
        text[i].setPosition(Vector2f(50.f, 50.f));
        letterBoxPos[0] += 60.f;
        letterBox[i].setPosition(letterBoxPos[0], letterBoxPos[1]);
        letterBox[i].setSize(Vector2f(50.f, 50.f));
        letterBox[i].setFillColor(Color::White);
    }



    while (window.isOpen())
    {
        int k = 0;
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::Closed:
                {
                    window.close();
                    break;
                }
                case Event::TextEntered:
                {
                    str += event.text.unicode;
                    if (str.length() == 5)
                    {
                        text.setString(str);
                        str = "";
                        k++;
                    }
                    break;
                }
            }
        }

        window.clear();
        for (int i = 0; i < 5; i++)
        {
            window.draw();
        }
        window.display();
    }

    return 0;
}