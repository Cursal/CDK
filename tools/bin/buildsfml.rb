#! /usr/bin/ruby

#******************************************************************************
# CDK - Cursal Development Kit
# Copyright (C) 2013-2014 Marcel Renner
# 
# This software is provided 'as-is', without any express or implied warranty. 
# In no event will the authors be held liable for any damages arising from 
# the use of this software.
# 
# Permission is granted to anyone to use this software for any purpose, 
# including commercial applications, and to alter it and redistribute it 
# freely, subject to the following restrictions:
# 
#    1. The origin of this software must not be misrepresented; you must not
#       claim that you wrote the original software. If you use this software
#       in a product, an acknowledgment in the product documentation would be
#       appreciated but is not required.
# 
#    2. Altered source versions must be plainly marked as such, and must not 
#       be misrepresented as being the original software.
# 
#    3. This notice may not be removed or altered from any source distribution.
#******************************************************************************

#==============================================================================
#                                   REQUIRES
#==============================================================================

# FileUtils.copy, FileUtils.mkdir_p
require('fileutils')
# CDK::EnvCheck
require_relative('checkenv')

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

module CDK

#==============================================================================
#                                    CLASS
#==============================================================================

# Class to configure, compile and install SFML.
class SfmlBuilder

#==============================================================================
#                                  CONSTANTS
#==============================================================================

  # Default destination directory of compiled SFML
  DST_DIR = '../../thirdparty/sfml'

#==============================================================================
#                                   PUBLIC
#==============================================================================

  public

  def initialize
    @cur_path = Dir.getwd
    @src_path = EnvCheck.find_dir(/SFML/i, 'unknown')
    @bld_path = File.join(@src_path, 'build')
    @dst_path = File.expand_path(File.join(File.dirname(__FILE__), DST_DIR))

    puts("The source code directory is: #{@src_path}")
    puts("The destination directory is: #{@dst_path}")
    
    @valid = (@src_path != 'unknown')
    @valid &&= EnvCheck.has_file?(File.join(@src_path, 'CMakeLists.txt'))
    @valid &&= EnvCheck.verify
  end

  # Returns +true+ if all necessary commands and files exist, otherwise 
  # +false+.
  # 
  # @return [Boolean] +true+ if all necessary commands and files exist, 
  #                   otherwise +false+.
  def valid?
    @valid
  end

  # Configures, compiles and installs zlib if +valid?+ returns +true+.
  def exec
    if valid?
      _result   = configure
      _result &&= compile
      _result &&= install
    end
  end

#==============================================================================
#                                   PRIVATE
#==============================================================================

  private

  # Configures SFML.
  def configure
    FileUtils.mkdir_p(@bld_path)
    Dir.chdir(@bld_path)
    
    _cmd  = 'cmake '

    _cmd << "-D CMAKE_BUILD_TYPE=Release "
    _cmd << "-D CMAKE_INSTALL_PREFIX=\"#{@dst_path}\" "

    if EnvCheck.windows?
      _cmd << '-G "MSYS Makefiles" '
    end
    
    _cmd << '.. '

    system(_cmd)
  end

  # Compiles SFML.
  def compile
    system('make')
  end

  # Installs SFML.
  def install
    system('make install')
  end
  
end # class SfmlBuilder

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

end # module CDK

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

if __FILE__ == $0
  begin
    _sb = CDK::SfmlBuilder.new
    _sb.exec
  rescue => _e
    print(_e.class, "\n", _e.message, "\n", _e.backtrace.join("\n"), "\n")
  end
end
