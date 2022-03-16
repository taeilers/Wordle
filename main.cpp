#include <SFML/Graphics.hpp>

using namespace sf;

char chars[6][5];
Text text[6][5];
RectangleShape letterBox[6][5];

void input(char chr)
{
    static int j = 0;
    static int i = 0;

    if (chr == '\b')
    {

    }
    else
    {
        chars[i][j] = chr;
        if (j > 5)
        {
            j = 0;
            i++;
        }
        if (i > 6)
        {
            //end
        }
        j++;
    }
}

int main()
{
    RenderWindow window(VideoMode(400, 400), "Wordle");

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
    
    float letterBoxPos[] = { 0.f, 10.f };
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            letterBoxPos[0] += 60.f;
            letterBoxPos[1] *= i;
            text[i][j].setFillColor(sf::Color::White);
            text[i][j].setFont(font);
            text[i][j].setPosition(Vector2f(75.f, 25.f));
            letterBox[i][j].setPosition(letterBoxPos[0], letterBoxPos[1]);
            letterBox[i][j].setSize(Vector2f(50.f, 50.f));
            letterBox[i][j].setFillColor(Color::Blue);
        }
    }



    while (window.isOpen())
    {
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
                    input(event.text.unicode);
                    break;
                }
            }
        }

        window.clear();
        for (int i = 0; i < 6; i++)
        {
            for (int j=0; j<5; j++)
            {
                //window.draw(letterBox[i][j]);
                window.draw(text[i][j]);
            }
        }
        window.display();
    }

    return 0;
}