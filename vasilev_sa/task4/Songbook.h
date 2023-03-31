#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class Songbook 
{
public:
  struct Song 
  {
    std::string name;
    std::string poet;
    std::string composer;
    std::string performer;
    std::string album;
    int day;
    int month;
    int year;
  };

  void addSong(const Song& song) 
  {
    songs_.push_back(song);
    std::sort(songs_.begin(), songs_.end(), [](const Song& lhs, const Song& rhs) { return lhs.name < rhs.name; });
  }

  bool removeSong(const std::string& name) 
  {
    auto it = std::find_if(songs_.begin(), songs_.end(), [&name](const Song& song) { return song.name == name; });
    if (it != songs_.end()) 
    {
      songs_.erase(it);
      return true;
    }
    return false;
  }

  Song findSong(const std::string& name, const std::string& performer) const 
  {
    auto it = std::find_if(songs_.begin(), songs_.end(), [&name, &performer](const Song& song) { return song.name == name && song.performer == performer; });
    if (it != songs_.end())
      return *it;
    return Song{};
  }

  std::vector<Song> findSongsByPoet(const std::string& poet) const 
  {
    std::vector<Song> result;
    std::copy_if(songs_.begin(), songs_.end(), std::back_inserter(result), [&poet](const Song& song) { return song.poet == poet; });
    return result;
  }

  std::vector<Song> findSongsByComposer(const std::string& composer) const 
  {
    std::vector<Song> result;
    std::copy_if(songs_.begin(), songs_.end(), std::back_inserter(result), [&composer](const Song& song) { return song.composer == composer; });
    return result;
  }

  std::vector<Song> findSongsByPerformer(const std::string& performer) const 
  {
    std::vector<Song> result;
    std::copy_if(songs_.begin(), songs_.end(), std::back_inserter(result), [&performer](const Song& song) { return song.performer == performer; });
    return result;
  }

  int getCount() const 
  {
    return (int)songs_.size();
  }

  void saveToFile(const std::string& filename) const 
  {
    std::ofstream outfile(filename, std::ios::out | std::ios::binary);
    if (!outfile.is_open()) 
    {
      std::cerr << "Failed to open file for writing: " << filename << std::endl;
      return;
    }
    for (const Song& song : songs_) 
    {
      outfile.write(song.name.c_str(), song.name.size() + 1);
      outfile.write(song.poet.c_str(), song.poet.size() + 1);
      outfile.write(song.composer.c_str(), song.composer.size() + 1);
      outfile.write(song.performer.c_str(), song.performer.size() + 1);
      outfile.write(song.album.c_str(), song.album.size() + 1);
      outfile.write(reinterpret_cast<const char*>(&song.day), sizeof(song.day));
      outfile.write(reinterpret_cast<const char*>(&song.month), sizeof(song.month));
      outfile.write(reinterpret_cast<const char*>(&song.year), sizeof(song.year));
    }
    outfile.close();
  }

  void loadFromFile(const std::string& filename) 
  {
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    if (!infile.is_open()) 
    {
      std::cerr << "Failed to open file for reading: " << filename << std::endl;
      return;
    }
    Song song;
    while (infile) 
    {
      std::getline(infile, song.name, '\0');
      std::getline(infile, song.poet, '\0');
      std::getline(infile, song.composer, '\0');
      std::getline(infile, song.performer, '\0');
      std::getline(infile, song.album, '\0');
      infile.read(reinterpret_cast<char*>(&song.day), sizeof(song.day));
      infile.read(reinterpret_cast<char*>(&song.month), sizeof(song.month));
      infile.read(reinterpret_cast<char*>(&song.year), sizeof(song.year));
      if (!infile.eof())
        songs_.push_back(song);
    }
    infile.close();
  }

  std::vector<Song> songList() const 
  {
    std::vector<Song> list;
    for (const auto& song : songs_)
      list.push_back(song);
    return list;
  }

private:
  std::vector<Song> songs_;
};

void printSong(const Songbook::Song& song) 
{
  std::cout << "Name: " << song.name << "\n";
  std::cout << "Performer: " << song.performer << "\n";
  std::cout << "Composer: " << song.composer << "\n";
  std::cout << "Poet: " << song.poet << "\n";
  std::cout << "Album: " << song.album << "\n";
  std::cout << "Release date: " << song.day << "." << song.month << "." << song.year << "\n";
  std::cout << "\n";
}
