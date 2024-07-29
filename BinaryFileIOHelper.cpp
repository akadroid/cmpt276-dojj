#include "BinaryFileIOHelper.h"

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
