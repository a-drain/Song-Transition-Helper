#ifndef HELPERS_H
#define HELPERS_H
#include <iostream>
#include <algorithm>
#include <limits>
#include "song.h"
using namespace std;

void displaySongsInArray(Song songArray[], int numSongs);
int homePageInput();
string songNameInput();
int getAddRemoveInput();
void findNextSongs(Song original, Song songArray[], int numSongs);
void removeAddSong(string title, Song songArray1[], Song songArray2[], int& numSongs1, int& numSongs2);

#endif