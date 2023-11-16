#ifndef SONG_H
#define SONG_h
#include <iostream>
using namespace std;

class Song {
    string songName, camelot;
    int BPM;

    public:
        Song();
        Song(string, string, int);

        string getSongName() const;
        string getCamelot() const;
        int getBPM() const;

        void displayInfo() const;
};
#endif