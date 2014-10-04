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

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

module CDK

#==============================================================================
#                                    CLASS
#==============================================================================

# Module to check available commands and development environment.
module EnvCheck

#==============================================================================
#                                   PUBLIC
#==============================================================================

  # Returns +true+ if all commands exists, otherwise +false+.
  # @return [Boolean] +true+ if all commands exists, otherwise +false+.
  def self.verify
    _valid   = has_cmd?('bash', /\d+\.\d+\.\d+/)
    _valid &&= has_cmd?('cmake', /\d+\.\d+\.\d+/)
    _valid &&= has_cmd?('gcc', /\d+\.\d+\.\d+/)
    _valid &&= has_cmd?('g++', /\d+\.\d+\.\d+/)
    _valid &&= has_cmd?('install', /\d+\.\d+/)
    _valid &&= has_cmd?('make', /\d+\.\d+/)
    _valid &&= has_cmd?('ruby', /\d+\.\d+\.\d+p\d+/)
  end

  # Returns +true+ if command exists, otherwise +false+.
  # 
  # @param _cmd    [String] Command
  # @param _regexp [Regexp] Regular expression to extract a string (e.g. 
  #                         version number)
  # @param _args   [String] Arguments of command
  # 
  # @return [Boolean] +true+ if command exists, otherwise +false+.
  def self.has_cmd?(_cmd, _regexp = nil, _args = '--version')
    print("Check for working CLI tool: #{_cmd}")
    
    begin
      _result = IO.popen([_cmd, _args]).read
    rescue Errno::ENOENT
      _result = nil
    end
    
    if _result
      _status = 'works'
      if _regexp
        _version = _result[_regexp]
        if _version
          _status << " (#{_version})"
        else
          _status << ' (unknown)'
        end
      end
    else
      _status = 'not found'
    end
    
    print(" - #{_status}\n")
    
    !_result.nil?
  end
  
  # Returns +true+ if file exists, otherwise +false+.
  # @param _file [String] File name
  # @return [Boolean] +true+ if file exists, otherwise +false+.
  def self.has_file?(_file)
    print("Check for existing file: #{File.basename(_file)}")
    
    _result = File.exist?(_file)

    if _result
      _status = 'exists'
    else
      _status = 'not found'
    end
    
    print(" - #{_status}\n")
    
    _result
  end
  
  # Returns directory name if directory exists, otherwise +_error_str+.
  # 
  # @param _regexp    [Regexp] Regular expression to find directory
  # @param _error_str [String] Returned string if directory not exists
  # 
  # @return [Strin,nil] Directory name if directory exists, otherwise 
  #                     +_error_str+.
  def self.find_dir(_regexp, _error_str = nil)
    _dir = Dir.glob('*').find do |_p| 
      File.directory?(_p) && _p[_regexp]
    end
    
    if _dir
      File.expand_path(_dir)
    else
      _error_str
    end
  end

  # Returns +true+ if environment is a Windows system, otherwise +false+.
  # @return [Boolean] +true+ if environment is a Windows system, otherwise 
  #                   +false+.
  def self.windows?
    (/cygwin|mswin|mingw|bccwin|wince|emx/ =~ RUBY_PLATFORM) != nil
  end
  
  # Returns +true+ if environment is a Mac system, otherwise +false+.
  # @return [Boolean] +true+ if environment is a Mac system, otherwise +false+.
  def self.mac?
   (/darwin/ =~ RUBY_PLATFORM) != nil
  end
  
  # Returns +true+ if environment is a Unix system, otherwise +false+.
  # @return [Boolean] +true+ if environment is a Unix system, otherwise +false+.
  def self.unix?
    !windows?
  end
  
  # Returns +true+ if environment is a Linux system, otherwise +false+.
  # @return [Boolean] +true+ if environment is a Linux system, otherwise 
  #                   +false+.
  def self.linux?
    unix? && !mac?
  end
  
end # module EnvCheck

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

end # module CDK

# -- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --- --

if __FILE__ == $0
  begin
    CDK::EnvCheck.verify
  rescue => _e
    print(_e.class, "\n", _e.message, "\n", _e.backtrace.join("\n"), "\n")
  end
end
