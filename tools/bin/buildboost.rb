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

# Class to configure, compile and install Boost.
class BoostBuilder

#==============================================================================
#                                  CONSTANTS
#==============================================================================

  # Default destination directory of compiled Boost
  DST_DIR = '../../thirdparty/boost'
  # Default include directory relative to +DST_DIR+
  INC_DIR = 'include'
  # Default library directory relative to +DST_DIR+
  LIB_DIR = 'lib'
  # Pass to --with-* option
  WITH_LIB = [
    'filesystem', 'program_options', 'system'
  ]

#==============================================================================
#                                   PUBLIC
#==============================================================================

  public

  def initialize
    @cur_path = Dir.getwd
    @src_path = EnvCheck.find_dir(/BOOST/i, 'unknown')
    @dst_path = File.expand_path(File.join(File.dirname(__FILE__), DST_DIR))
    @with_lib = WITH_LIB.join(' --with-')
    @with_lib.insert(0, '--with-')
    
    puts("The source code directory is: #{@src_path}")
    puts("The destination directory is: #{@dst_path}")
    
    @valid = (@src_path != 'unknown')
    @valid &&= EnvCheck.has_file?(File.join(@src_path, 'bootstrap.bat'))
    @valid &&= EnvCheck.has_file?(File.join(@src_path, 'bootstrap.sh'))
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
      _result &&= bcp
    end
  end

#==============================================================================
#                                   PRIVATE
#==============================================================================

  private

  # Configures Boost.
  def configure
    Dir.chdir(@src_path)
    
    if EnvCheck.windows?
      _cmd = 'bootstrap.bat mingw '
    else
      _cmd = 'bootstrap.sh '
    end

    system(_cmd)
  end

  # Compiles Boost.
  def compile
    system('b2 --clean')
    
    _cmd  = 'b2 '
    
    _cmd << '--build-dir="build" '
    _cmd << "#{@with_lib} "
    
    _cmd << 'toolset=gcc '
    _cmd << 'variant=release '
    _cmd << 'stage '
    
    system(_cmd)
  end

  # Installs Boost.
  def install
    _cmd  = 'b2 '
    
    _cmd << "--prefix=\"#{@dst_path}\" "

    _cmd << '--build-dir="build" '
    _cmd << "#{@with_lib} "
    
    _cmd << 'toolset=gcc '
    _cmd << 'variant=release '
    _cmd << 'install '

    system(_cmd)
  end

  # Compiles and executes +bcp+ executable to shrink Boost.
  def bcp
    Dir.chdir(File.join(@src_path, 'tools/bcp'))
    
    # Compile +bcp+ executable.
    _cmd  = '../../b2 '
    _cmd << '--build-dir="build" '
    _cmd << 'toolset=gcc '
    system(_cmd)
    
    # Find +bcp+ executable.
    _pattern = File.join(@src_path, 'tools/bcp/build', '**', 'bcp{,.exe}')
    _bcp = Dir.glob(_pattern).find do |_p| 
      File.file?(_p)
    end
    return false unless _bcp

    # Find oversized include directory of installed Boost.
    _inc_dir = File.join(@dst_path, INC_DIR)
    _base = Dir.glob(File.join(_inc_dir, 'boost-*')).find do |_p| 
      File.directory?(_p)
    end
    Dir.chdir(_base)
    return false unless _base

    # Run +bcp+ executable.
    _cmd = [_bcp, WITH_LIB, _inc_dir].flatten
    system(*_cmd)
    return false unless File.exist?(File.join(_inc_dir, 'boost'))

    # Remove oversized include directory of installed Boost.
    Dir.chdir(@dst_path)
    FileUtils.rm_rf(_base)
  end
  
end # class BoostBuilder

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

end # module CDK

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

if __FILE__ == $0
  begin
    _bb = CDK::BoostBuilder.new
    _bb.exec
  rescue => _e
    print(_e.class, "\n", _e.message, "\n", _e.backtrace.join("\n"), "\n")
  end
end
