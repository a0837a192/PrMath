#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>

//without enter input

int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); 
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

//draw smth it is hard to explain

void drawMenu(const std::vector<std::string> &options, int selected) {
    std::cout << "\033[H\033[J";

    for (int i = 0; i < options.size(); ++i) {
        if (i == selected) {
            std::cout << "  \033[1;32m> " << options[i] << "  <\033[0m\n";
        } else {
            std::cout << "    " << options[i] << "\n";
        }
    }
}

//random number 

const int getCard(const int &random) {
    std::mt19937 mt{std::random_device{}()};
    std::uniform_int_distribution card{1, ((random + 1) * 10)};
    return card(mt);
}

//draw beautiful text

void getTx(const std::string_view text, const int &time) {
    for (int i = 0; i < text.length(); i++) {
        std::cout << text[i] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }
}

//just for do it easyer

enum Diff { easy, medium, hard, extreme };

//ignor symbols in input when you need number

void ignoreLine() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }

//main game

void printSol(const int ran1, const int ran2) {
    const int res{ran1 + ran2};
    int resU{};
    std::cout << "\n" << ran1 << " + " << ran2 << " = ";
    std::cin >> resU;
    if (resU == res) {
        std::cout << "Correct" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        std::cout << "\033[H\033[J";
    } else if (std::cin.fail()) {
        std::cin.clear();
        ignoreLine();
    } else {
        std::cout << "Incorrect" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        std::cout << "\033[H\033[J";
    }
}

//main function

int main() {



    std::this_thread::sleep_for(std::chrono::milliseconds(400)); // timer

    getTx("Hello! ", 50); // beautiful text

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 

    getTx("It is a math practic! ", 50);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    getTx("Choose the difficult: \n", 50);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::vector<std::string> options = {"Easy", "Medium", "Hard", "Extreme"};
    int selected = 0;
    bool running = true;

    //choose the diff text with arrow

    while (running) {
        drawMenu(options, selected);

        int key = getch();

        if (key == 27) {
            getch();
            switch (getch()) {
            case 'A':
                key = 'w';
                break;
            case 'B':
                key = 's';
                break;
            }
        }

        if (key == 'w' || key == 'W') {
            if (selected > 0)
                selected--;
        } else if (key == 's' || key == 'S') {
            if (selected < options.size() - 1)
                selected++;
        } else if (key == 10) {
            running = false;
        }
    }

    std::cout << "\nYour chose: " << options[selected] << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    std::cout << "\033[H\033[J";

    //infin game

    int random1, random2;
    while (true) {

        //this code chek your diff and give you a game 

        if (options[selected] == "Easy") {
            //give you two random numbers for game in your diff
            random1 = getCard(easy);
            random2 = getCard(easy);
        } else if (options[selected] == "Medium") {
            random1 = getCard(medium);
            random2 = getCard(medium);
        } else if (options[selected] == "Hard") {
            random1 = getCard(hard);
            random2 = getCard(hard);
        } else if (options[selected] == "Extreme") {
            random1 = getCard(extreme);
            random2 = getCard(extreme);
        }

        //and you need to solve the problem like 10+2 or 4+6 (easy) or in extreme problems like 36+18 or 34+7 and other

        printSol(random1, random2);
    }

    return 0;
}