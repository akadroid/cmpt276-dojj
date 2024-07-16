#ifndef BINARY_FILE_IO_HELPER
#define BINARY_FILE_IO_HELPER

#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class BinaryFileIOHelper
{
public:
  // Writes an object of type T to file
  bool Write(T &item);

  // Reads an object of type T from file. Make sure the file is not at the end (EOF)
  bool Read(T &item);

protected:
  fstream file;
};

template <typename T>
bool BinaryFileIOHelper<T>::Write(T &item)
{
  if (!file.is_open())
  {
    cerr << "File not open for writing" << endl;
    return false;
  }
  file.write(reinterpret_cast<char *>(&item), sizeof(T));
  return file.good();
}

template <typename T>
bool BinaryFileIOHelper<T>::Read(T &item)
{
  if (!file.is_open())
  {
    cerr << "File not open for reading" << endl;
    return false;
  }
  file.read(reinterpret_cast<char *>(&item), sizeof(T));
  return file.good();
}

#endif