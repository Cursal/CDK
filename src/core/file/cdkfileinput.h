/*****************************************************************************\
 * CDK - Cursal Development Kit
 * Copyright (C) 2013-2014 Marcel Renner
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *       claim that you wrote the original software. If you use this software
 *       in a product, an acknowledgment in the product documentation would be
 *       appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not
 *       be misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *       distribution.
\*****************************************************************************/

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifndef CDK_CDKFILEINPUT_H
# define CDK_CDKFILEINPUT_H

//=============================================================================
//                                   HEADERS
//=============================================================================

#include <fstream>
#include <string>
#include <CDK/Core>
#include <CDK/CdkFile>

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                    CLASS
//=============================================================================

/*!
 * \ingroup core
 *
 * \brief Base class to define and handle a CDK file input.
 */
class CdkFileInput : public CdkFile
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

public:

  /*!
   * \brief Initializes CdkFileInput.
   */
  CdkFileInput();

  /*!
   * \brief Terminates CdkFileInput.
   */
  virtual ~CdkFileInput();

  /*!
   * \brief Closes the file stream.
   */
  void close();

  /*!
   * \brief Clears the stream's error state flags.
   */
  inline void clear()
  {
    if (m_stream)
      m_stream->clear();
  }

  /*!
   * \brief Returns the file name.
   */
  inline std::string getFileName() const
  {
    return m_fileName;
  }

  /*!
   * \brief  Returns true if none of the stream's error state flags
   *         (+eofbit+, +failbit+ and +badbit+) is set.
   * \return True if no error exists, false otherwise.
   */
  inline bool isGood()
  {
    if (m_stream)
      return m_stream->good();

    return false;
  }

  /*!
   * \brief  Returns true if one of the stream's error state flags
   *         (+eofbit+, +failbit+ and +badbit+) is set.
   * \return True if an error exists, false otherwise.
   */
  inline bool isFailed()
  {
    return !isGood();
  }

//=============================================================================
//                                  PROTECTED
//=============================================================================

protected:

  /*!
   * \brief Initializes an internal file stream.
   * \param[in] _fileName File name of CDK file.
   */
  void initialize(const std::string &_fileName);

  /*!
   * \brief Initializes an external file stream.
   * \param[in] _stream Custom stream of CDK file.
   */
  void initialize(std::ifstream *_stream);

  /*!
   * \brief Reads data from the stream.
   *
   * \param[out] _data Buffer where to copy the read data.
   * \param[in]  _size Desired number of bytes to read.
   *
   * \return The number of bytes actually read, or -1 on error.
   */
  int64_t read(char *_data, int64_t _size);

  /*!
   * \brief Changes the current position.
   * \param[in] _pos The position to seek to, from the beginning.
   * \return The position actually sought to, or -1 on error.
   */
  int64_t seek(int64_t _pos);

  /*!
   * \brief Returns the current position.
   * \return The current position, or -1 on error.
   */
  int64_t tell();

  /*!
   * \brief Returns the current size of the stream.
   * \return The total number of bytes available in the stream, or -1 on error.
   */
  int64_t getSize();

//=============================================================================
//                                   PRIVATE
//=============================================================================

private:

//-----------------------------------------------------------------------------
// Private member variables
//-----------------------------------------------------------------------------

  std::ifstream *m_stream = nullptr;
  std::string    m_fileName;

};      // class CdkFileInput

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}       // namespace CDK

#endif  // CDK_CDKFILEINPUT_H
