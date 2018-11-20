#include <iostream>
#include "ui.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: ./chip8 <rom>" << endl;
        return 1;
    }

    UI ui;
    ui.run(argv[1], true);

    return 0;
}