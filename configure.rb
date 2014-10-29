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
require_relative('tools/bin/checkenv')

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

module CDK

#==============================================================================
#                                    CLASS
#==============================================================================

# Class to configure CDK.
class Configuration

#==============================================================================
#                                  CONSTANTS
#==============================================================================

  # Specifies what build type will be built in this build tree by default.
  DEFAULT_BUILD_TYPE = 'Debug'

#==============================================================================
#                                   PUBLIC
#==============================================================================

  public

  def initialize
    Dir.chdir(File.expand_path(File.dirname(__FILE__)))
    
    @cur_path = Dir.getwd
    @bld_path = File.expand_path('build')
    
    @valid   = EnvCheck.has_file?('CMakeLists.txt')
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

  # Configures CDK if +valid?+ returns +true+.
  def configure
    if valid?
      FileUtils.mkdir_p(@bld_path)
      Dir.chdir(@bld_path)
      
      _cmd  = 'cmake '
  
      unless ARGV.empty?
        ARGV.each do |_arg|
          if _arg.include?(' ')
            _cmd << _arg.inspect << ' '
          else
            _cmd << _arg << ' '
          end
        end
      end
      
      # Default build type
      if !ARGV.any? { |_a| _a =~ /CMAKE_BUILD_TYPE/ }
        _cmd << "-D CMAKE_BUILD_TYPE=\"#{DEFAULT_BUILD_TYPE}\" "
      end
      
      # Default install prefix
      if !ARGV.any? { |_a| _a =~ /CMAKE_INSTALL_PREFIX/ }
        _cmd << "-D CMAKE_INSTALL_PREFIX=\"#{@cur_path}\" "
      end
      
      # Default makefile type in Windows
      if !ARGV.include?('-G') && EnvCheck.windows?
        _cmd << '-G "MSYS Makefiles" '
      end
      
      # Default work directory
      _cmd << "\"#{@cur_path}\" "
  
      system(_cmd)
    end
  end

end # class Configuration

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

end # module CDK

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

if __FILE__ == $0
  begin
    _config = CDK::Configuration.new
    _config.configure
  rescue => _e
    print(_e.class, "\n", _e.message, "\n", _e.backtrace.join("\n"), "\n")
  end
end
