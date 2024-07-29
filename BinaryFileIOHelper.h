// BinaryFileIOHelper.h
// Rev. 1 - 15/07/24 Original by D.O.J.J Software Development

//*******************************************************//
// This module defines the BinaryFileIOHelper template class,
// which provides functions for reading and writing objects
// of any class to and from a binary file. The class encapsulates
// file handling operations for ease of use.
//*******************************************************//

#ifndef BINARY_FILE_IO_HELPER
#define BINARY_FILE_IO_HELPER

#include <iostream>
#include <fstream>
using namespace std;

//*******************************************************//

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
// The BinaryFileIOHelper class provides methods to write and read
// objects of type T to and from a binary file.

//*******************************************************//

template <typename T>
bool BinaryFileIOHelper<T>::Write(T &item)
{
  if (!file.is_open())
  {
    cerr << "File not open for writing" << endl;
    return false;
  }
  file.write(reinterpret_cast<char *>(&item), sizeof(T));
  file.flush();
  return file.good();
}
// Implementation of the Write function for handling writes to a binary file

//*******************************************************//

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
// Implementation of the Read function for handling reads from a binary file
// to an object in RAM

#endif

//*******************************************************/