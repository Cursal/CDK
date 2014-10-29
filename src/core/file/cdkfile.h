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

#ifndef CDK_CDKFILE_H
# define CDK_CDKFILE_H

//=============================================================================
//                                   HEADERS
//=============================================================================

#include <CDK/Core>
#include <CDK/NonCopyable>

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

namespace CDK
{

//=============================================================================
//                                    CLASS
//=============================================================================

/*!
 * \ingroup core
 *
 * \brief Base class to define and handle a CDK file.
 */
class CdkFile : public NonCopyable
{

//=============================================================================
//                                   PUBLIC
//=============================================================================

public:

  /*!
   * \brief Default file header
   */
  struct Header
  {
    uint32_t fileSig     = 0;  //!< File signature
    uint32_t fileVersion = 0;  //!< File version
    uint32_t fileSize    = 0;  //!< File size
    uint32_t rootNodePos = 0;  //!< Root node position
    uint32_t footerPos   = 0;  //!< Footer position
  };

  /*!
   * \brief Default file footer
   */
  struct Footer
  {
    uint32_t eofMarker   = 0;  //!< End of File Marker
  };

//=============================================================================
//                                   PUBLIC
//=============================================================================

public:

  /*!
   * \brief Initializes CdkFile.
   */
  CdkFile();

  /*!
   * \brief Terminates CdkFile.
   */
  virtual ~CdkFile();

};      // class CdkFile

/* -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- -- */

}       // namespace CDK

#endif  // CDK_CDKFILE_H
