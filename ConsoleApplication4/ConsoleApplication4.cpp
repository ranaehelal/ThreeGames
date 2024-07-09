#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
using namespace sf;
using namespace std;



enum class Player { None, X, O };
std::ostream& operator<<(std::ostream& os, const Player& player) {
    switch (player) {
    case Player::None:
        os << "None";
        break;
    case Player::X:
        os << "X";
        break;
    case Player::O:
        os << "O";
        break;
    }
    return os;
}

class PyramidTicTacToe {
private:
    const int WINDOW_SIZE = 1100;
    const int GRID_SIZE = 5;
    const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;
    sf::RenderWindow window;
    std::vector<std::vector<Player>> board;
    Player currentPlayer;

public:
    PyramidTicTacToe() : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE - 440), "Tic Tac Toe", Style::Close | Style::Resize), currentPlayer(Player::X) {
        board.resize(GRID_SIZE, std::vector<Player>(GRID_SIZE, Player::None));
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;

            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int x = event.mouseButton.x / CELL_SIZE;
                        int y = event.mouseButton.y / CELL_SIZE;

                        if (isValidMove(x, y)) {
                            makeMove(x, y);
                            checkWin();
                            switchPlayer();
                        }
                    }
                }
            }

            window.clear(sf::Color::White);
            drawGrid();
            Block();
            drawSymbols();
            window.display();
        }
    }

private:
    bool isValidMove(int x, int y) {
        return board[y][x] == Player::None;
    }

    void makeMove(int x, int y) {
        board[y][x] = currentPlayer;
    }
    void Congratulation() {

        std::string winnerName;
        if (currentPlayer == Player::X) {
            winnerName = "Player X";
        }
        else if (currentPlayer == Player::O) {
            winnerName = "Player O";
        }

        if (!winnerName.empty()) {
            sf::Font font;
            if (!font.loadFromFile("D:\\Fonts\\arial.ttf")) {
                std::cerr << "Failed to load font file.\n";
                return;
            }

            sf::Text winnerText("\n\n\n\nCongratulations, " + winnerName + " wins!", font, 50);
            winnerText.setFillColor(sf::Color::Black);

            // Center the text on the window
            sf::FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            winnerText.setPosition(sf::Vector2f(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f));

            window.clear(sf::Color::White);
            drawGrid();
            drawSymbols();
            window.draw(winnerText);
            window.display();

            // Close the window after a delay (for demonstration)
            sf::sleep(sf::seconds(3)); // Close after 3 seconds, change as needed
            window.close();
            return;
        }
    }
    void DRAW() {
        sf::Font font;
        if (!font.loadFromFile("D:\\Fonts\\arial.ttf")) {
            std::cerr << "Failed to load font file.\n";
            return;
        }

        sf::Text winnerText("\n\n\n\nIT'S DRAW !!!", font, 50);
        winnerText.setFillColor(sf::Color::Black);

        // Center the text on the window
        sf::FloatRect textRect = winnerText.getLocalBounds();
        winnerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        winnerText.setPosition(sf::Vector2f(WINDOW_SIZE / 2.0f, WINDOW_SIZE / 2.0f));

        window.clear(sf::Color::White);
        drawGrid();
        drawSymbols();
        window.draw(winnerText);
        window.display();

        // Close the window after a delay (for demonstration)
        sf::sleep(sf::seconds(3)); // Close after 3 seconds, change as needed
        window.close();
        return;
    }
    void checkWin() {
        // Check rows

        if (board[1][1] != Player::None && board[1][1] == board[1][2] && board[1][1] == board[1][3]) {
            std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
            Congratulation();
            return;
        } if (board[2][0] != Player::None && board[2][0] == board[2][1] && board[2][0] == board[2][2]) {
            std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
            Congratulation();
            return;
        } if (board[2][1] != Player::None && board[2][1] == board[2][2] && board[2][1] == board[2][3]) {
            std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
            Congratulation();
            return;
        } if (board[2][2] != Player::None && board[2][2] == board[2][3] && board[2][2] == board[2][4]) {
            std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
            Congratulation();
            return;
        }


        // Check columns

        if (board[1][2] != Player::None && board[0][2] == board[1][2] && board[1][2] == board[2][2]) {
            std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
            Congratulation();
            return;
        }


        // Check diagonals
        if (board[0][2] != Player::None && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
            Congratulation();
            return;
        } if (board[0][2] != Player::None && board[0][2] == board[1][3] && board[1][3] == board[2][4]) {
            std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
            Congratulation();
            return;
        }


        // Check for a draw
        bool isDraw = true;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4 || i == 3 || i == 4)continue;
                if (board[i][j] == Player::None) {
                    isDraw = false;
                    break;
                }
            }
        }

        if (isDraw) {
            std::cout << "It's a draw!\n";
            DRAW();
            return;
        }
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n\n";
        }


    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    void drawGrid() {
        for (int i = 1; i < GRID_SIZE; i++) {
            sf::Vertex verticalLine[] = {
                 sf::Vertex(sf::Vector2f(i * CELL_SIZE, 0) , sf::Color::Blue),
                sf::Vertex(sf::Vector2f(i * CELL_SIZE, WINDOW_SIZE), sf::Color::Blue),
            };
            window.draw(verticalLine, 2, sf::Lines);

            sf::Vertex horizontalLine[] = {
                sf::Vertex(sf::Vector2f(0, i * CELL_SIZE), sf::Color::Blue),
                sf::Vertex(sf::Vector2f(WINDOW_SIZE, i * CELL_SIZE), sf::Color::Blue)
            };
            window.draw(horizontalLine, 2, sf::Lines);
        }
    }
    void Block() {
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4 || i == 3 || i == 4) {
                    sf::RectangleShape square(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    square.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                    square.setFillColor(sf::Color::Black);
                    window.draw(square);
                }
            }
        }
    }

    void drawSymbols() {
        sf::Font font;
        if (!font.loadFromFile("D:\\Fonts\\Amatic-Bold.ttf")) {
            std::cerr << "Failed to load font file.\n";
            return;
        }



        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (board[j][i] == Player::X) {
                    sf::Text text("X", font, 100);
                    text.setFillColor(sf::Color::Red);
                    text.setPosition(i * CELL_SIZE + 100, j * CELL_SIZE + 75);
                    window.draw(text);
                }
                else if (board[j][i] == Player::O) {
                    sf::Text text("O", font, 100);
                    text.setFillColor(sf::Color::Cyan);
                    text.setPosition(i * CELL_SIZE + 100, j * CELL_SIZE + 75);
                    window.draw(text);
                }
            }
        }
    }

};

class FiveTicTacToe {
private:
    const int WINDOW_SIZE = 1000;
    const int GRID_SIZE = 5;
    const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;
    int n_rows = 7;
    int n_cols = 6;
    sf::RenderWindow window;
    std::vector<std::vector<Player>> board;
    Player currentPlayer;

public:
    FiveTicTacToe() : window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Tic Tac Toe", sf::Style::Close | sf::Style::Resize), currentPlayer(Player::X) {
        board.resize(GRID_SIZE, std::vector<Player>(GRID_SIZE, Player::None));
    }


    void run() {
        int moves = 0;
        while (window.isOpen()) {
            sf::Event event;

            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int x = event.mouseButton.x / CELL_SIZE;
                        int y = event.mouseButton.y / CELL_SIZE;

                        if (isValidMove(x, y)) {
                            makeMove(x, y);
                            switchPlayer();
                            moves++;
                        }
                    }
                }
            }
            if (moves == 24) {
                checkWin();
            }
            window.clear(sf::Color::White);
            drawGrid();
            //   Block();
            drawSymbols();
            window.display();
        }
    }

private:
    bool isValidMove(int x, int y) {
        return board[y][x] == Player::None;
    }

    void makeMove(int x, int y) {
        board[y][x] = currentPlayer;
    }
    void Congratulation() {

        std::string winnerName;
        if (currentPlayer == Player::X) {
            winnerName = "Player X";
        }
        else if (currentPlayer == Player::O) {
            winnerName = "Player O";
        }

        if (!winnerName.empty()) {
            sf::Font font;
            if (!font.loadFromFile("D:\\Fonts\\arial.ttf")) {
                std::cerr << "Failed to load font file.\n";
                return;
            }

            sf::Text winnerText("\n\n\n\nCongratulations, " + winnerName + " wins!", font, 50);
            winnerText.setFillColor(sf::Color::Black);

            // Center the text on the window
            sf::FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            winnerText.setPosition(sf::Vector2f(750 / 2.0f, WINDOW_SIZE / 2.0f));

            window.clear(sf::Color::White);
            drawGrid();
            drawSymbols();
            window.draw(winnerText);
            window.display();

            // Close the window after a delay (for demonstration)
            sf::sleep(sf::seconds(3)); // Close after 3 seconds, change as needed
            window.close();
            return;
        }
    }
    void DRAW() {
        sf::Font font;
        if (!font.loadFromFile("D:\\Fonts\\arial.ttf")) {
            std::cerr << "Failed to load font file.\n";
            return;
        }

        sf::Text winnerText("\n\n\n\nIT'S DRAW !!!", font, 50);
        winnerText.setFillColor(sf::Color::Black);

        // Center the text on the window
        sf::FloatRect textRect = winnerText.getLocalBounds();
        winnerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        winnerText.setPosition(sf::Vector2f(700 / 2.0f, WINDOW_SIZE / 2.0f));

        window.clear(sf::Color::White);
        drawGrid();
        drawSymbols();
        window.draw(winnerText);
        window.display();

        // Close the window after a delay (for demonstration)
        sf::sleep(sf::seconds(3)); // Close after 3 seconds, change as needed
        window.close();
        return;
    }
    void checkWin() {
        map<Player, int>who_is_winner;
        for (int i : {0, 1, 2, 3, 4}) {
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                who_is_winner[board[i][0]]++;
            }
            if (board[i][1] == board[i][2] && board[i][2] == board[i][3]) {
                who_is_winner[board[i][1]]++;
            }
            if (board[i][2] == board[i][3] && board[i][3] == board[i][4]) {
                who_is_winner[board[i][2]]++;
            }
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                who_is_winner[board[0][i]]++;
            }
            if (board[1][i] == board[2][i] && board[2][i] == board[3][i]) {
                who_is_winner[board[1][i]]++;
            }
            if (board[2][i] == board[3][i] && board[3][i] == board[4][i]) {
                who_is_winner[board[2][i]]++;
            }
        }
        for (int i : {0, 1, 2}) {
            for (int j : {0, 1, 2}) {
                if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2]) {
                    who_is_winner[board[i][j]]++;
                }
            }
        }
        for (int i : {0, 1, 2}) {
            for (int j : {2, 3, 4}) {
                if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1] == board[i + 2][j - 2]) {
                    who_is_winner[board[i][j]]++;
                }
            }
        }
        cout << "Player X: " << who_is_winner[Player::X] << '\n';
        cout << "Player O: " << who_is_winner[Player::O] << '\n';

        if (who_is_winner[Player::X] > who_is_winner[Player::O]) {
            currentPlayer == Player::X;
            Congratulation();
            return;
        }
        else if (who_is_winner[Player::X] == who_is_winner[Player::O]) {
            std::cout << "It's a draw!\n";
            DRAW();
        }
        else {
            currentPlayer == Player::O;
            Congratulation();
            return;
        }

        // Check for a draw

    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    void drawGrid() {
        for (int i = 1; i < GRID_SIZE; i++) {
            sf::Vertex verticalLine[] = {
                 sf::Vertex(sf::Vector2f(i * CELL_SIZE, 0) , sf::Color::Blue),
                sf::Vertex(sf::Vector2f(i * CELL_SIZE, WINDOW_SIZE), sf::Color::Blue),
            };
            window.draw(verticalLine, 2, sf::Lines);

            sf::Vertex horizontalLine[] = {
                sf::Vertex(sf::Vector2f(0, i * CELL_SIZE), sf::Color::Blue),
                sf::Vertex(sf::Vector2f(WINDOW_SIZE, i * CELL_SIZE), sf::Color::Blue)
            };
            window.draw(horizontalLine, 2, sf::Lines);
        }
    }/*
    void Block() {
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4 || i == 3 || i == 4) {
                    sf::RectangleShape square(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    square.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                    square.setFillColor(sf::Color::Black);
                    window.draw(square);
                }
            }
        }
    }
    */

    void drawSymbols() {
        sf::Font font;
        if (!font.loadFromFile("D:\\Fonts\\Amatic-Bold.ttf")) {
            std::cerr << "Failed to load font file.\n";
            return;
        }

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (board[j][i] == Player::X) {
                    sf::Text text("X", font, 100);
                    text.setFillColor(sf::Color::Red);
                    text.setPosition(i * CELL_SIZE + 20, j * CELL_SIZE + 20);
                    window.draw(text);
                }
                else if (board[j][i] == Player::O) {
                    sf::Text text("O", font, 100);
                    text.setFillColor(sf::Color::Cyan);
                    text.setPosition(i * CELL_SIZE + 20, j * CELL_SIZE + 20);
                    window.draw(text);
                }
            }
        }
    }

};

class FourInRowTicTacToe {
private:
    const int WINDOW_SIZE = 1000;
    const int GRID_SIZE = 8;
    const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE;
    int n_rows = 7;
    int n_cols = 6;
    sf::RenderWindow window;
    std::vector<std::vector<Player>> board;
    Player currentPlayer;

public:
    FourInRowTicTacToe() : window(sf::VideoMode(WINDOW_SIZE - 250, WINDOW_SIZE - 125), "Tic Tac Toe", sf::Style::Close | sf::Style::Resize), currentPlayer(Player::X) {
        board.resize(GRID_SIZE, std::vector<Player>(GRID_SIZE, Player::None));
    }


    void run() {
        while (window.isOpen()) {
            sf::Event event;

            while (window.pollEvent(event)) {

                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        int x = event.mouseButton.x / CELL_SIZE;
                        int y = event.mouseButton.y / CELL_SIZE;

                        if (isValidMove(x, y)) {
                            makeMove(x, y);
                            checkWin();
                            switchPlayer();
                        }
                    }
                }
            }

            window.clear(sf::Color::White);
            drawGrid();
            //   Block();
            drawSymbols();
            window.display();
        }
    }

private:
    bool isValidMove(int x, int y) {
        int i = 6;
        while (board[y][x] != Player::None) {

        }
        return board[y][x] == Player::None;

    }

    void makeMove(int x, int y) {
        int i = 6;
        while (board[i][x] != Player::None) {
            i--;
        }
        y = i;
        board[y][x] = currentPlayer;
    }
    void Congratulation() {

        std::string winnerName;
        if (currentPlayer == Player::X) {
            winnerName = "Player X";
        }
        else if (currentPlayer == Player::O) {
            winnerName = "Player O";
        }

        if (!winnerName.empty()) {
            sf::Font font;
            if (!font.loadFromFile("D:\\Fonts\\arial.ttf")) {
                std::cerr << "Failed to load font file.\n";
                return;
            }

            sf::Text winnerText("\n\n\n\nCongratulations, " + winnerName + " wins!", font, 50);
            winnerText.setFillColor(sf::Color::Black);

            // Center the text on the window
            sf::FloatRect textRect = winnerText.getLocalBounds();
            winnerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            winnerText.setPosition(sf::Vector2f(750 / 2.0f, WINDOW_SIZE / 2.0f));

            window.clear(sf::Color::White);
            drawGrid();
            drawSymbols();
            window.draw(winnerText);
            window.display();

            // Close the window after a delay (for demonstration)
            sf::sleep(sf::seconds(3)); // Close after 3 seconds, change as needed
            window.close();
            return;
        }
    }
    void DRAW() {
        sf::Font font;
        if (!font.loadFromFile("D:\\Fonts\\arial.ttf")) {
            std::cerr << "Failed to load font file.\n";
            return;
        }

        sf::Text winnerText("\n\n\n\nIT'S DRAW !!!", font, 50);
        winnerText.setFillColor(sf::Color::Black);

        // Center the text on the window
        sf::FloatRect textRect = winnerText.getLocalBounds();
        winnerText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        winnerText.setPosition(sf::Vector2f(700 / 2.0f, WINDOW_SIZE / 2.0f));

        window.clear(sf::Color::White);
        drawGrid();
        drawSymbols();
        window.draw(winnerText);
        window.display();

        // Close the window after a delay (for demonstration)
        sf::sleep(sf::seconds(3)); // Close after 3 seconds, change as needed
        window.close();
        return;
    }
    void checkWin() {
        // Check rows
        for (int i = 0; i < n_rows; ++i) {
            for (int j = 0; j <= n_cols - 4; ++j) {
                if (board[i][j] != Player::None &&
                    board[i][j] == board[i][j + 1] &&
                    board[i][j] == board[i][j + 2] &&
                    board[i][j] == board[i][j + 3]) {
                    std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
                    Congratulation();
                    return;
                }
            }
        }

        // Check for a vertical win | (ra2sii)
        for (int i = 0; i <= n_rows - 4; ++i) {
            for (int j = 0; j < n_cols; ++j) {
                if (board[i][j] != Player::None &&
                    board[i][j] == board[i + 1][j] &&
                    board[i][j] == board[i + 2][j] &&
                    board[i][j] == board[i + 3][j]) {
                    std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
                    Congratulation();
                    return;
                }
            }
        }

        // Check for a diagonal win (top left to bottom right  )
        for (int i = 0; i < n_rows - 3; i++) {
            for (int j = 0; j <= n_cols - 4; j++) {
                if (board[i][j] != Player::None &&
                    board[i][j] == board[i + 1][j + 1] &&
                    board[i][j] == board[i + 2][j + 2] &&
                    board[i][j] == board[i + 3][j + 3]) {
                    std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
                    Congratulation();
                    return;
                }
            }
        }

        // Check for a diagonal win (bottom left to top right)
        for (int i = 3; i < n_rows; ++i) {
            for (int j = 0; j <= n_cols - 4; ++j) {
                if (board[i][j] != Player::None &&
                    board[i][j] == board[i - 1][j + 1] &&
                    board[i][j] == board[i - 2][j + 2] &&
                    board[i][j] == board[i - 3][j + 3]) {
                    std::cout << "Player " << static_cast<int>(currentPlayer) << " wins!\n";
                    Congratulation();
                    return;
                }
            }
        }


        // No winner yet

       // Check for a draw
        bool isDraw = true;
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (i > 5 || j > 6)continue;
                isDraw = false;
                break;

            }
        }
        if (isDraw) {
            std::cout << "It's a draw!\n";
            DRAW();
            return;
        }
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n\n";
        }


    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
    }

    void drawGrid() {
        for (int i = 1; i < GRID_SIZE; i++) {
            sf::Vertex verticalLine[] = {
                 sf::Vertex(sf::Vector2f(i * CELL_SIZE, 0) , sf::Color::Blue),
                sf::Vertex(sf::Vector2f(i * CELL_SIZE, WINDOW_SIZE), sf::Color::Blue),
            };
            window.draw(verticalLine, 2, sf::Lines);

            sf::Vertex horizontalLine[] = {
                sf::Vertex(sf::Vector2f(0, i * CELL_SIZE), sf::Color::Blue),
                sf::Vertex(sf::Vector2f(WINDOW_SIZE, i * CELL_SIZE), sf::Color::Blue)
            };
            window.draw(horizontalLine, 2, sf::Lines);
        }
    }/*
    void Block() {
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (i == 0 && j == 0 || i == 0 && j == 1 || i == 0 && j == 3 || i == 0 && j == 4 || i == 1 && j == 0 || i == 1 && j == 4 || i == 3 || i == 4) {
                    sf::RectangleShape square(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    square.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                    square.setFillColor(sf::Color::Black);
                    window.draw(square);
                }
            }
        }
    }
    */

    void drawSymbols() {
        sf::Font font;
        if (!font.loadFromFile("D:\\Fonts\\Amatic-Bold.ttf")) {
            std::cerr << "Failed to load font file.\n";
            return;
        }

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                if (board[j][i] == Player::X) {
                    sf::Text text("X", font, 100);
                    text.setFillColor(sf::Color::Red);
                    text.setPosition(i * CELL_SIZE + 20, j * CELL_SIZE + 20);
                    window.draw(text);
                }
                else if (board[j][i] == Player::O) {
                    sf::Text text("O", font, 100);
                    text.setFillColor(sf::Color::Cyan);
                    text.setPosition(i * CELL_SIZE + 20, j * CELL_SIZE + 20);
                    window.draw(text);
                }
            }
        }
    }

};



































bool runVersion1 = false;
bool runVersion2 = false;
bool runVersion3 = false;

void runGame(int version) {
    // Add your code to run the selected version of the game
    std::cout << "Running Game Version " << version << std::endl;
    // Replace this with your code to run the game
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Menu");

    // Define fonts, text, and positions for the menu options
    sf::Font font;
    if (!font.loadFromFile("D:\\Fonts\\arial.ttf")) {
        std::cerr << "Font file not found!" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text title("Game of 3", font, 50);
    title.setPosition(280, 100);
    sf::Text option1("Pyramid", font, 30);
    option1.setPosition(320, 250);

    sf::Text option2("Four In Row", font, 30);
    option2.setPosition(320, 300);

    sf::Text option3("Five X Five", font, 30);
    option3.setPosition(320, 350);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (option1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    runVersion1 = true;
                }
                else if (option2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    runVersion2 = true;
                }
                else if (option3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    runVersion3 = true;
                }
            }
        }

        if (runVersion1) {
            PyramidTicTacToe game;
            game.run();
            runVersion1 = false; // Reset flag after running the version
        }
        else if (runVersion2) {
            FourInRowTicTacToe game;
            game.run();
            runVersion2 = false; // Reset flag after running the version
        }
        else if (runVersion3) {
            FiveTicTacToe game;
            game.run();
            runVersion3 = false; // Reset flag after running the version
        }

        window.clear(sf::Color::Black);

        // Draw all the menu options
        window.draw(title);
        window.draw(option1);
        window.draw(option2);
        window.draw(option3);

        window.display();
    }

    return 0;
}
