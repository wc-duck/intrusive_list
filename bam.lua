--[[
   Intrusive single/double linked list for C++.

   version 0.1, augusti, 2013

   Copyright (C) 2013- Fredrik Kihlander

   This software is provided 'as-is', without any express or implied
   warranty.  In no event will the authors be held liable for any damages
   arising from the use of this software.

   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
      claim that you wrote the original software. If you use this software
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original software.
   3. This notice may not be removed or altered from any source distribution.

   Fredrik Kihlander
--]]

BUILD_PATH = "local"

platform = "linux_x86_64"
if family == "windows" then
    platform = "winx64"
end
config   = "debug"

local settings = NewSettings()

local output_path = PathJoin( BUILD_PATH, PathJoin( config, platform ) )
local output_func = function(settings, path) return PathJoin(output_path, PathFilename(PathBase(path)) .. settings.config_ext) end
settings.cc.Output = output_func
settings.lib.Output = output_func
settings.link.Output = output_func

settings.cc.defines:Add("_INTRUSIVE_LIST_ASSERT_ENABLED")

if family ~= "windows" then
	settings.cc.flags:Add( "-Wconversion", "-Wextra", "-Wall", "-Werror", "-Wstrict-aliasing=2" )
else
	settings.link.flags:Add( "/NODEFAULTLIB:LIBCMT.LIB" );
	settings.cc.defines:Add("_ITERATOR_DEBUG_LEVEL=0")
end

settings.link.libpath:Add( 'local/' .. config .. '/' .. platform )

local objs  = Compile( settings, Collect( 'test/*.cpp' ) )
local tests = Link( settings, 'test_intrusive_lists', objs )

test_args = " -v"
test_valgrind = ""
if ScriptArgs["test"]     then test_args = test_args .. " -t " .. ScriptArgs["test"] end
if ScriptArgs["suite"]    then test_args = test_args .. " -s " .. ScriptArgs["suite"] end
if ScriptArgs["valgrind"] then test_valgrind = "valgrind -v --leak-check=full --track-origins=yes " end

if family == "windows" then
	AddJob( "test", "unittest", string.gsub( tests, "/", "\\" ) .. test_args, tests, tests )
else
	AddJob( "test", "unittest", test_valgrind .. tests .. test_args, tests, tests )
end

DefaultTarget( tests )
