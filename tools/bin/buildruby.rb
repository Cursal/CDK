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

# FileUtils.copy, FileUtils.mkdir_p, FileUtils.rm_rf
require('fileutils')
# CDK::LibffiBuilder
require_relative('buildlibffi')
# CDK::ZlibBuilder
require_relative('buildzlib')
# CDK::EnvCheck
require_relative('checkenv')

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

module CDK

#==============================================================================
#                                    CLASS
#==============================================================================
  
  # Class to configure, compile and install Ruby.
class RubyBuilder

#==============================================================================
#                                  CONSTANTS
#==============================================================================

  # Default destination directory of compiled Ruby
  DST_DIR = '../../thirdparty/ruby'
  # Default include directory relative to +DST_DIR+
  INC_DIR = 'include'
  # Default library directory relative to +DST_DIR+
  LIB_DIR = 'lib'
  # Pass to --without-ext option of extmk.rb
  WITHOUT_EXT = [
    'dbm', 'gdbm', 'openssl', 'pty', 'readline', 'sdbm', 'syslog', 'tcl', 
    'tk', 'win32ole'
  ].join(',')

#==============================================================================
#                                   PUBLIC
#==============================================================================

  public

  def initialize
    @cur_path = Dir.getwd
    @src_path = EnvCheck.find_dir(/RUBY/i, 'unknown')
    @bld_path = File.join(@src_path, 'build')
    @dst_path = File.expand_path(File.join(File.dirname(__FILE__), DST_DIR))

    puts("The source code directory is: #{@src_path}")
    puts("The destination directory is: #{@dst_path}")
    
    _zlib_dst_dir = File.expand_path(ZlibBuilder::DST_DIR)
    @zlib_inc_dir = File.join(_zlib_dst_dir, ZlibBuilder::INC_DIR)
    @zlib_lib_dir = File.join(_zlib_dst_dir, ZlibBuilder::LIB_DIR)
    
    _libffi_dst_dir = File.expand_path(LibffiBuilder::DST_DIR)
    @libffi_inc_dir = File.join(_libffi_dst_dir, LibffiBuilder::INC_DIR)
    @libffi_lib_dir = File.join(_libffi_dst_dir, LibffiBuilder::LIB_DIR)
    
    @valid   = (@src_path != 'unknown')
    @valid &&= EnvCheck.has_file?(File.join(@src_path, 'configure'))
    @valid &&= EnvCheck.has_file?(File.join(@libffi_inc_dir, 'ffi.h'))
    @valid &&= EnvCheck.has_file?(File.join(@zlib_inc_dir, 'zlib.h'))
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
  
  # Configures, compiles and installs Ruby if +valid?+ returns +true+.
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

  # Configures Ruby.
  def configure
    _prefix = EnvCheck.windows? ? 'bash ' : ''

    FileUtils.mkdir_p(@bld_path)
    Dir.chdir(@bld_path)
    
    _cmd  = _prefix
    _cmd << '../configure '
    _cmd << "--prefix=\"#{@dst_path}\" "
    # Disable debug symbols
    _cmd << 'debugflags="" '
    
    if EnvCheck.windows?
      _cmd << '--target=i386-mingw32 '
    end
    
    _cmd << '--disable-install-doc '
    _cmd << '--disable-install-rdoc '
    _cmd << '--disable-rubygems '
    _cmd << '--disable-option-checking '

    _cmd << "--with-zlib-include=#{@zlib_inc_dir} "
    _cmd << "--with-zlib-lib=#{@zlib_lib_dir} "
    _cmd << "--with-libffi-include=#{@libffi_inc_dir} "
    _cmd << "--with-libffi-lib=#{@libffi_lib_dir} "
    
    _cmd << "--with-out-ext=\"#{WITHOUT_EXT}\" "

    system(_cmd)
  end

  # Compiles Ruby.
  def compile
    system('make && make test')
  end

  # Installs Ruby.
  def install
    system('make install')
  end
  
end # class RubyBuilder

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

end # module CDK

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

if __FILE__ == $0
  begin
    _rb = CDK::RubyBuilder.new
    _rb.exec
  rescue => _e
    print(_e.class, "\n", _e.message, "\n", _e.backtrace.join("\n"), "\n")
  end
end
