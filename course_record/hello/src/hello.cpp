#include <iostream>
#include "generate_greeting.h"

using namespace std;

int main(int argc, char * argv[]) {
    if(2 != argc) {
        cout << "Usage: " << argv[0] << " <name>" << endl;
        return EXIT_FAILURE;
    }
    cout << generateGreeting(argv[1]) << endl;

    return EXIT_SUCCESS;
}