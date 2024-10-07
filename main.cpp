#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

class songs {
private:
    std::string songTitles[100];
    int songSelection[40][25]; //[People][Songs]
    int songSheet[40][5][5];   //[People][Sheet Hight][Sheet Width]

public:
    // Getter for songTitles
    std::string getSongTitle(int index) const {
        if (index >= 0 && index < 100) {
            return songTitles[index];
        }
        return "";
    }

    // Getter for songSelection
    int getSongSelectionValue(int person, int song) const {
        if (person >= 0 && person < 40 && song >= 0 && song < 25) {
            return songSelection[person][song];
        }
        return -1; // Return -1 or another sentinel value to indicate an error
    }

    // Getter for entire songSelection array
    const int (*getSongSelection() const)[25] {
        return songSelection;
    }

    // Getter for songSheet
    int getSongSheetValue(int person, int height, int width) const {
        if (person >= 0 && person < 40 && height >= 0 && height < 5 && width >= 0 && width < 5) {
            return songSheet[person][height][width];
        }
        return -1; // Return -1 or another sentinel value to indicate an error
    }

    // Getter for entire songSheet array
    const int (*getSongSheet() const)[5][5] {
        return songSheet;
    }

    // Setter for songTitles
    void setSongTitle(int index, const std::string &title) {
        if (index >= 0 && index < 100) {
            songTitles[index] = title;
        }
    }

    // Setter for songSelection
    void setSongSelectionValue(int person, int song, int value) {
        if (person >= 0 && person < 40 && song >= 0 && song < 25) {
            songSelection[person][song] = value;
        }
    }

    // Setter for entire songSelection array
    void setSongSelection(const int newSongSelection[40][25]) {
        for (int i = 0; i < 40; ++i) {
            for (int j = 0; j < 25; ++j) {
                songSelection[i][j] = newSongSelection[i][j];
            }
        }
    }

    // Setter for songSheet
    void setSongSheetValue(int person, int height, int width, int value) {
        if (person >= 0 && person < 40 && height >= 0 && height < 5 && width >= 0 && width < 5) {
            songSheet[person][height][width] = value;
        }
    }
};

void chooseSongs(int songSelection[40][25]) {
    // Seed the random number generator with the current time
    srand(time(0));

    // Fill the 2D array with random numbers from 0 to 24
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 25; ++j) {
            songSelection[i][j] = rand() % 25;
        }
    }
};

void randomiseSheet(int songSheet[40][5][5], const int songSelection[40][25]) {
    srand(time(0));

    // Randomly distribute songs from the selectedSongs array to the songSheet array
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                // Choose a random song from the selectedSongs array
                int randomSong = rand() % 25;
                while (songSelection[i][randomSong] == -1) {
                    randomSong = rand() % 25;
                }

                // Place the song on the sheet
                songSheet[i][j][k] = songSelection[i][randomSong];
            }
        }
    }
};

int main() {
    songs s;

    // Choosing songs for each person
    const int(*songSelection)[25] = s.getSongSelection();
    // Create a non-const copy
    int songSelectionCopy[40][25];
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 25; ++j) {
            songSelectionCopy[i][j] = songSelection[i][j];
        }
    }
    chooseSongs(songSelectionCopy);

    // Create sheet for each person
    const int (*songSheet)[5][5] = s.getSongSheet();
    // Create a non-const copy
    int songSheetCopy[40][5][5];
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {  // Added this loop to handle the third dimension
                songSheetCopy[i][j][k] = (*songSheet)[j][k];
            }
        }
    }
    randomiseSheet(songSheetCopy, songSelectionCopy);

    return 0;
};