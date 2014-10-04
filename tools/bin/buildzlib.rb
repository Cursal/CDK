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

# Class to configure, compile and install zlib.
class ZlibBuilder

#==============================================================================
#                                  CONSTANTS
#==============================================================================

  # Default destination directory of compiled zlib
  DST_DIR = '../../thirdparty/zlib'
  # Default binary directory relative to +DST_DIR+
  BIN_DIR = 'bin'
  # Default include directory relative to +DST_DIR+
  INC_DIR = 'include'
  # Default library directory relative to +DST_DIR+
  LIB_DIR = 'lib'

#==============================================================================
#                                   PUBLIC
#==============================================================================

  public

  def initialize
    @cur_path = Dir.getwd
    @src_path = EnvCheck.find_dir(/ZLIB/i, 'unknown')
    @dst_path = File.expand_path(File.join(File.dirname(__FILE__), DST_DIR))
    if EnvCheck.windows?
      @mkf_path = File.expand_path(File.join(@src_path, 'win32/Makefile.gcc'))
    else
      @mkf_path = File.expand_path(File.join(@src_path, 'Makefile'))
    end
    
    puts("The source code directory is: #{@src_path}")
    puts("The destination directory is: #{@dst_path}")
    
    @valid = (@src_path != 'unknown')
    @valid &&= EnvCheck.has_file?(@mkf_path)
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

  # Configures zlib.
  def configure
    Dir.chdir(@src_path)
  end

  # Compiles zlib.
  def compile
    _cmd  = "make -f \"#{@mkf_path}\" && "
    _cmd << "make test -f \"#{@mkf_path}\" "

    system(_cmd)
  end

  # Installs zlib.
  def install
    FileUtils.mkdir_p(@dst_path)
    _bin_path = File.join(@dst_path, BIN_DIR)
    _inc_path = File.join(@dst_path, INC_DIR)
    _lib_path = File.join(@dst_path, LIB_DIR)

    _cmd  = "install -dv \"#{_bin_path}\" && "
    _cmd << "install -dv \"#{_inc_path}\" && "
    _cmd << "install -dv \"#{_lib_path}\" && "
    _cmd << "install -v zlib.h \"#{_inc_path}\" && "
    _cmd << "install -v zlib1.dll \"#{_bin_path}\" && "
    _cmd << "install -v zconf.h \"#{_inc_path}\" && "
    _cmd << "install -v libz.a \"#{_lib_path}\" && "
    _cmd << "install -v libz.dll.a \"#{_lib_path}\" "

    system(_cmd)
  end
  
end # class ZlibBuilder

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

end # module CDK

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

if __FILE__ == $0
  begin
    _zb = CDK::ZlibBuilder.new
    _zb.exec
  rescue => _e
    print(_e.class, "\n", _e.message, "\n", _e.backtrace.join("\n"), "\n")
  end
end
