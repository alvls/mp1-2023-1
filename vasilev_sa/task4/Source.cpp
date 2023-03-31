#include <iostream>
#include "Songbook.h"

int main() 
{
  Songbook songbook;

  // ��������� ��������� �����
  Songbook::Song song1 = { "Song 1", "Poet 1", "Composer 1", "Performer 1", "Album 1", 1, 1, 2021 };
  Songbook::Song song2 = { "Song 2", "Poet 2", "Composer 2", "Performer 2", "Album 2", 2, 2, 2022 };
  songbook.addSong(song1);
  songbook.addSong(song2);

  // �������� ��� ����� � ����� �����
  std::cout << "All songs in songbook:\n";
  for (const auto& song : songbook.songList())
    printSong(song);

  // ������� ����� �� �������� � �����������
  std::cout << "Find a song by name and performer:\n";
  Songbook::Song foundSong = songbook.findSong("Song 1", "Performer 1");
  if (foundSong.name != "")
    printSong(foundSong);
  else
    std::cout << "Song not found\n";

  // ������� ����� �� ��������
  std::cout << "Remove a song by name:\n";
  if (songbook.removeSong("Song 2"))
    std::cout << "Song removed\n";
  else
    std::cout << "Song not found\n";

  // ��������� ����� ����� � ����
  std::cout << "\nSave songbook to file \"songbook.bin\"\n";
  songbook.saveToFile("songbook.bin");

  // ��������� ����� ����� �� �����
  std::cout << "Load songbook from file \"songbook.bin\"\n";
  Songbook newSongbook;
  newSongbook.loadFromFile("songbook.bin");

  // �������� ��� ����� � ����� ����� �����
  std::cout << "\nAll songs in loaded songbook:\n";
  for (const auto& song : newSongbook.songList())
    printSong(song);

  system("pause");
  return 0;
}
