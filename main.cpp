#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

using namespace sf;

RenderWindow window(VideoMode(400, 400), "Wordle");
sf::Font font;
enum State{ONGOING, WON, LOST};

std::string randomWord();
void ip_toupper(std::string& str);

class Game
{
    int x;
    int y;
    State state;
    String answer;

    public:
        RectangleShape boxes[6][5];
        Text letters[6][5];
        RectangleShape bg;
        Event event;
        Game() : bg(Vector2f(400, 400)) {}


        void newGame()
        {
            x = 0;
            y = 0;
            state = ONGOING;
            font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
            answer = randomWord();

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
                    letters[i][j].setString("");

                    boxes[i][j].setSize(Vector2f(letterboxSize, letterboxSize));
                    boxes[i][j].setOrigin(25.f, 25.f);
                    boxes[i][j].setPosition(letterboxPos[0], letterboxPos[1]);
                    boxes[i][j].setFillColor(Color::White);
                    boxes[i][j].setOutlineColor(Color::Black);
                    boxes[i][j].setOutlineThickness(1.f);
                }
            }
        }

        String getAnswer() { return answer; }

        State getState() { return state; }

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


        void input(char chr)
        {
            if (chr == '\b' && x != 0)
            {
                x--;
                letters[y][x].setString("");
            }
            else
            {
                if (x < 5 && isalpha(chr))
                {
                    letters[y][x].setString(chr);
                    FloatRect bounds = letters[y][x].getLocalBounds();
                    letters[y][x].setOrigin(bounds.width / 2, bounds.height / 2);
                    x++;
                }
                else if (x >= 5 && chr == '\r')
                {
                    if (match(y))
                    {
                        state = WON;
                        return;
                    }
                    x = 0;
                    y++;
                }

                if (y >= 6)
                {
                    state = LOST;
                    return;
                }
            }
        }


        void display()
        {
            window.draw(bg);
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    window.draw(boxes[i][j]);
                    window.draw(letters[i][j]);
                }
            }
            window.display();
        }
};

int main()
{
    srand(time(NULL));
    Game game;
    game.bg.setFillColor(Color(220, 220, 220));
    game.newGame();
        
    while (window.isOpen())
    {
        window.clear();
        game.display();


        while (window.pollEvent(game.event))
        {
            switch (game.event.type)
            {
                case Event::Closed:
                {
                    window.close();
                    break;
                }
                case Event::TextEntered:
                {
                    game.input(toupper(game.event.text.unicode));
                    break;
                }
            }


            if (game.getState() == WON)
            {
                Text str;
                str.setString("You got it!\nThe answer is " + game.getAnswer() + "\n\nType 'y' to play again\nType 'n' to quit");
                str.setFont(font);

                window.clear();
                window.draw(game.bg);
                window.draw(str);
                window.display();
                
                while (true)
                {
                    window.pollEvent(game.event);
                    if (game.event.text.unicode == 'n')
                    {
                        window.close();
                        return 0;
                    }
                    else if (game.event.text.unicode == 'y') 
                    { 
                        game.newGame(); 
                        break;
                    }
                }
            }
            else if (game.getState() == LOST)
            {
                Text str;
                str.setString("Out of guesses!\nThe answer is " + game.getAnswer() + "\n\nType y to play again\nType n to quit");
                str.setFont(font);

                window.clear();
                window.draw(game.bg);
                window.draw(str);
                window.display();

                while (true)
                {
                    window.pollEvent(game.event);
                    if (game.event.text.unicode == 'n')
                    {
                        window.close();
                        return 0;
                    }
                    else if (game.event.text.unicode == 'y')
                    {
                        game.newGame();
                        break;
                    }
                }
            }
        }
    }
    
    window.close();
    return 0;
}

void ip_toupper(std::string& str)
{
    int len = str.length();
    for (int i = 0; i < len; i++)
    {
        str[i] = toupper(str[i]);
    }
}

std::string randomWord()
{
    std::ifstream wordstream;
    wordstream.open("eng_words_998.txt");
    std::string word;
    while (true)
    {
        wordstream.clear();
        wordstream.seekg(0);
        int rn = rand() % 998;
        for (int i = 0; i < rn; i++)
        {
            getline(wordstream, word);
        }
        if (word.length() == 5)
        {
            ip_toupper(word);
            wordstream.close();
            return word;
        }
    }
}
