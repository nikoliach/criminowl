#ifndef BUFFER_H
#define BUFFER_H

#include "OpenglPlatform.h"
#include <iostream>
#include <vector>

class Buffer
{
public:
  ///-----------------------------------------------------------------------------------------------------
  /// @brief used to specify the type of buffer
  ///-----------------------------------------------------------------------------------------------------
  enum BufferType { VERTEX, NORMAL, UV };
  ///-----------------------------------------------------------------------------------------------------
  /// @brief called after construction, used to generate and bind our Vertex array pbject, as well as,
  /// generate and bind our Buffer objects, (reset is called for this).
  /// @param _size is the size in bytes of the data type we are storing, float would be 4 (probably).
  /// @param _amountOfData is the number of data elements we will store.
  ///-----------------------------------------------------------------------------------------------------
  void init(const GLuint _size, const GLuint _amountOfData);
  ///-----------------------------------------------------------------------------------------------------
  /// @brief called to reset our buffers, removing data from them
  /// @param _size is the size in bytes of the data type we are storing, float would be 4 (probably).
  /// @param _amountOfData is the number of data elements we will remove.
  ///-----------------------------------------------------------------------------------------------------
  void reset(const GLuint _size, GLuint _amountOfData);
  ///-----------------------------------------------------------------------------------------------------
  /// @brief called to add new data into the specified buffer.
  /// @param _address is a pointer to the data we want to store.
  /// @param _type is the buffer we should append our data to.
  ///-----------------------------------------------------------------------------------------------------
  void append(const void * _address, const BufferType _type);
  ///-----------------------------------------------------------------------------------------------------
  /// @brief called to get the size of each data element we are storing.
  /// @return the size of the data elements in our buffer
  ///-----------------------------------------------------------------------------------------------------
  GLuint dataSize() const noexcept;
  ///-----------------------------------------------------------------------------------------------------
  /// @brief called to get the amount of data elements we are storing.
  /// @return the number of data elements in our buffer
  ///-----------------------------------------------------------------------------------------------------
  GLuint dataAmount() const noexcept;

private:
  ///-----------------------------------------------------------------------------------------------------
  /// @brief Buffer addresses.
  ///-----------------------------------------------------------------------------------------------------
  std::vector<GLuint> m_buffers   = {0,0,0};
  ///-----------------------------------------------------------------------------------------------------
  /// @brief Vertex array object.
  ///-----------------------------------------------------------------------------------------------------
  GLuint m_vao;
  ///-----------------------------------------------------------------------------------------------------
  /// @brief Current amount of data elements in the buffer.
  ///-----------------------------------------------------------------------------------------------------
  GLuint m_amountOfData = 0;
  ///-----------------------------------------------------------------------------------------------------
  /// @brief Current size of the stored data members in the buffer.
  ///-----------------------------------------------------------------------------------------------------
  GLuint m_size = 0;
};

#endif // BUFFER_H
