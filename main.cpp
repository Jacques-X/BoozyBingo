#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

class songs {
private:
    std::string songTitles[100];
    int songSelection[40][25]; //[People][Songs]
    int songSheet[40][5][5];   //[People][Sheet Hight][Sheet Width]

public:
    //Getter for songTitles
    std::string getSongTitle(int index) const {
        if (index >= 0 && index < 100) {
            return songTitles[index];
        }
        return "";
    }

    //Setter for songTitles
    void setSongTitle(int index, const std::string &title) {
        if (index >= 0 && index < 100) {
            songTitles[index] = title;
        }
    }

    //Setter for entire songSelection array
    void setSongSelection(const int newSongSelection[40][25]) {
        for (int i = 0; i < 40; ++i) {
            for (int j = 0; j < 25; ++j) {
                songSelection[i][j] = newSongSelection[i][j];
            }
        }
    }
};

// Function to read song titles from a file
void readSongTitles(songs &s) {
    std::ifstream file("Songs.txt");
    std::string line, title;
    int index = 0;

    if (file.is_open()) {
        while (std::getline(file, title) && index < 100) {
            s.setSongTitle(index, title); // Set the title in the songs array
            index++;
        }
        file.close();
        std::cout << "Read " << index << " song titles from file.\n";
    } else {
        std::cerr << "Unable to open Songs.txt file.\n";
    }
}

// Function to choose random songs for each person
void chooseSongs(int songSelection[40][25]) {
    //Fill the 2D array with random numbers from 0 to 24
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 25; ++j) {
            songSelection[i][j] = rand() % 25; // Random song index between 0 and 24
        }
    }
}

// Function to randomize the song sheet
void randomiseSheet(int songSheet[40][5][5], const int songSelection[40][25]) {
    //Randomly distribute songs from the selectedSongs array to the songSheet array
    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < 5; ++k) {
                int randomSong = rand() % 25; // Pick a random song
                songSheet[i][j][k] = songSelection[i][randomSong];
            }
        }
    }
}

int main() {
    songs s;

    // Seed the random number generator once
    srand(time(0));

    // Read song titles from file
    readSongTitles(s);

    // Choosing songs for each person
    int songSelection[40][25];
    chooseSongs(songSelection);

    // Create sheet for each person
    int songSheet[40][5][5];
    randomiseSheet(songSheet, songSelection);

    // Output the songSheet array for each person
    for (int person = 0; person < 40; ++person) {
        std::cout << "Song Sheet for Person " << person + 1 << ":\n";
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                // Get the song title using the song index
                std::string songTitle = s.getSongTitle(songSheet[person][i][j]);
                std::cout << songTitle << "\t\t\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}
