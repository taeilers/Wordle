#include <SFML/Graphics.hpp>

using namespace sf;

RectangleShape boxes[6][5];
Text letters[6][5];
String answer = "SWIFT";

RenderWindow window(VideoMode(400, 400), "Wordle");
RectangleShape bg(Vector2f(400, 400));

void newField()
{
    float letterboxPos[2];
    float letterboxSize = 50.f;
    float letterboxSpacing = 10.f;
    struct Margin { float x = 20.f; float y = 35.f; } margin;
    for (int i = 0; i < 6; i++)
    {
        letterboxPos[1] = i * 60 + margin.y;
        letterboxPos[0] = 0.f + margin.x;
        for (int j = 0; j < 5; j++)
        {
            letterboxPos[0] += letterboxSize + letterboxSpacing;

            letters[i][j].setFont(font);
            letters[i][j].setPosition(letterboxPos[0] - 2, letterboxPos[1] - 9);
            letters[i][j].setFillColor(Color::Black);

            boxes[i][j].setSize(Vector2f(letterboxSize, letterboxSize));
            boxes[i][j].setOrigin(25.f, 25.f);
            boxes[i][j].setPosition(letterboxPos[0], letterboxPos[1]);
            boxes[i][j].setFillColor(Color::White);
            boxes[i][j].setOutlineColor(Color::Black);
            boxes[i][j].setOutlineThickness(1.f);
        }
    }
}

bool match(int i)
{
    String match = "";
    for (int j = 0; j < 5; j++)
    {
        String guess = letters[i][j].getString();
        // If guess letter is correct
        if (guess == answer[j])
        {
            boxes[i][j].setFillColor(Color::Green);
            match += guess;
        }
        else
        {
            for (int k = 0; k < 5; k++)
            {
                // Finds if letter is anywhere in answer
                if (guess == answer[k])
                {
                    boxes[i][j].setFillColor(Color(245, 163, 62));
                    break;
                }
            }
        }
    }
    if (match == answer) return true;
    else return false;
}

void solved(bool solved)
{
    if (solved)
    {

    }
    return;
}

void input(char chr)
{
    static int j = 0;
    static int i = 0;

    if (chr == '\b' && j != 0)
    {
        j--;
        letters[i][j].setString("");
    }
    else
    {
        if (j < 5 && isalpha(chr))
        {
            letters[i][j].setString(chr);
            FloatRect bounds = letters[i][j].getLocalBounds();
            letters[i][j].setOrigin(bounds.width / 2, bounds.height / 2);
            j++;
        }
        else if (j >= 5 && chr == '\r')
        {
            if (match(i))
            {
                return; //true;
            }
            j = 0;
            i++;
        }

        if (i > 6)
        {
            //solve();
            return;
        }
    }
}



int main()
{
    bg.setFillColor(Color(220, 220, 220));
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/Arial.ttf");



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
                    input(toupper(event.text.unicode));
                    break;
                }
            }
        }

        window.clear();
        window.draw(bg);
        for (int i = 0; i < 6; i++)
        {
            for (int j=0; j<5; j++)
            {
                window.draw(boxes[i][j]);
                window.draw(letters[i][j]);
            }
        }
        window.display();
    }

    return 0;
}
