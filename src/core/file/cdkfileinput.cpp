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

//=============================================================================
//                                   HEADERS
//=============================================================================

#include "cdkfileinput.h"

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
CdkFileInput::CdkFileInput()
{
  // Nothing to do.
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
CdkFileInput::~CdkFileInput()
{
  close();
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CdkFileInput::close()
{
  // Check if currently used file stream is an internal stream.
  if (!m_fileName.empty())
    delete m_stream;

  m_stream = nullptr;
  m_fileName.clear();
}

//=============================================================================
//                                  PROTECTED
//=============================================================================

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CdkFileInput::initialize(const std::string &_fileName)
{
  close();

  if (!_fileName.empty())
  {
    m_stream   = new std::ifstream(_fileName, std::ifstream::binary);
    m_fileName = _fileName;
  }
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
void CdkFileInput::initialize(std::ifstream *_stream)
{
  close();
  m_stream = _stream;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
int64_t CdkFileInput::read(char *_data, int64_t _size)
{
  if (m_stream)
  {
    m_stream->read(_data, _size);
    return m_stream->gcount();
  }
  else
    return -1;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
int64_t CdkFileInput::seek(int64_t _pos)
{
  if (m_stream)
  {
    m_stream->seekg(_pos);
    return m_stream->tellg();
  }
  else
    return -1;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
int64_t CdkFileInput::tell()
{
  if (m_stream)
    return m_stream->tellg();
  else
    return -1;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */
int64_t CdkFileInput::getSize()
{
  if (m_stream)
  {
    int64_t _pos;
    int64_t _size;

    _pos  = m_stream->tellg();
    m_stream->seekg(0, m_stream->end);
    _size = m_stream->tellg();
    m_stream->seekg(_pos);

    return _size;
  }

  return -1;
}

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}  // namespace CDK
