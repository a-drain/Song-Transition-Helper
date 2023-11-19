#include <fstream>
#include "helpers.h"

/*
COMPLETED UP TO 49 ON PLAYLIST
https://www.reddit.com/r/Beatmatch/comments/uyl5po/ways_to_transition_between_different_tempos_and/
https://www.reddit.com/r/DJs/comments/c98oeq/camelot_keywheel_rules_transitions_demonstration/
*/

int main(int argc, char* argv[]) {
    if (argc != 2) {
        if (argc < 2) {
            cout << "No File Detected! Please try again!" << endl;
            return 1;
        }
        if (argc > 2) {
            cout << "Too Many Files Detected! Please try again and only input one file!" << endl;
            return 1;
        }
    }
    system("clear");
    int numSongs = 0;
    int numRemovedSongs = 0;
    Song songArray[100];
    Song removedSongArray[100];
    string camelotArray[24] = {"1A", "1B", "2A", "2B", "3A", "3B", "4A", "4B", "5A", "5B", "6A", "6B", "7A", "7B", "8A", "9A", "9B", "10A", "10B", "11A", "11B", "12A", "12B"};
    string fileToOpen = argv[1];

    ifstream file(fileToOpen);
    if (!file.is_open()) {
        cerr << "File couldn't be opened!" << endl;
        return 1;
    }

    string header;
    getline(file, header);

    string first, songName, bpmTemp, camelot;
    while (getline(file, first, ',')) {
        getline(file, songName, ',');
        getline(file, bpmTemp, ',');
        getline(file, camelot, '\n');

        int bpm = stoi(bpmTemp); 

        songArray[numSongs] = Song(songName, camelot, bpm);
        numSongs += 1;
    }

    while (true) {
        int input = homePageInput();
        bool found = false;

        if (input == 0) {
            system("clear");
            cout << "Program ending..." << endl;
            break;
        }
        else if (input == 1) {
            system("clear");
            string song = songNameInput();
            for (int i = 0; i < numSongs; i += 1) {
                if (songArray[i].getSongName() == song) {
                    found = true;
                    Song first = songArray[i];
                    findNextSongs(first, songArray, numSongs);
                }
            }
            if (!found) {
                cout << "Could not find song! Please double-check your spelling and capitalization and try again :)" << endl;
            }
        }
        else if (input == 2) {
            while (true) {
                int choice = getAddRemoveInput();
                if (choice == 0) {
                    cout << "Returning to main menu..." << endl;
                    break;
                }
                else if (choice == 1) {
                    system("clear");
                    displaySongsInArray(songArray, numSongs);
                    string title = songNameInput();
                    removeAddSong(title, songArray, removedSongArray, numSongs, numRemovedSongs);
                }
                else if (choice == 2) {
                    system("clear");
                    displaySongsInArray(removedSongArray, numRemovedSongs);
                    string title = songNameInput();
                    removeAddSong(title, removedSongArray, songArray, numRemovedSongs, numSongs);
                }
                else {
                    cout << "Invalid input. Please try again :)" << endl;
                }
            }
        }
        else {
            cout << "Invalid input. Please try again :)" << endl;
        }
    }
    file.close();
    return 0;
}

