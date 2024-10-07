#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

class songs {
    private:
        std::string songTitles[100];
        int songSelection[40][25];     //[People][Songs] 
        int songSheet[40][5][5];        //[People][Sheet Hight][Sheet Width]
    
    public:
        // Getter for songTitles
        std::string getSongTitle(int index) const {
            if (index >= 0 && index < 100) {
                return songTitles[index];
            }
            return "";
        }

        // Getter for songSheet
        int getSongSheetValue(int person, int height, int width) const {
            if (person >= 0 && person < 40 && height >= 0 && height < 5 && width >= 0 && width < 5) {
                return songSheet[person][height][width];
            }
            return -1; // Return -1 or another sentinel value to indicate an error
        }

        // Setter for songTitles
        void setSongTitle(int index, const std::string& title) {
            if (index >= 0 && index < 100) {
                songTitles[index] = title;
            }
        }

        // Setter for songSheet
        void setSongSheetValue(int person, int height, int width, int value) {
            if (person >= 0 && person < 40 && height >= 0 && height < 5 && width >= 0 && width < 5) {
                songSheet[person][height][width] = value;
            }
        }
};

void chooseSongs(int** songSelection){
    // Seed the random number generator with the current time
    srand(time(0));

    // Fill the 2D array with random numbers from 0 to 24
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 25; ++j) {
            songSelection[i][j] = rand() % 25;
        }
    }
};

int main() {
    
    return 0;
};