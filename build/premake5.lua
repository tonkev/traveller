local ROOT = "../"

workspace "Traveller"

configurations  { "Debug", "Release" }
platforms       { "x64", "x32" }

filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On"
filter "configurations:Release"  defines { "NDEBUG" } optimize "On"

filter { "platforms:*32" } architecture "x86"
filter { "platforms:*64" } architecture "x64"

filter "system:windows" defines { "OS_WINDOWS" }

filter {}

local SourceDir = ROOT .. "src/"
local IncludeDir = ROOT .. "include/"

project "Traveller"
    kind "StaticLib"
    language "C"
    targetdir (ROOT .. "bin")
    targetname "traveller"
    files { 
        SourceDir .. "**.c",
        IncludeDir .. "**.h"
    }
    includedirs { IncludeDir }

filter "system:not windows"
    removefiles { SourceDir .. "win/**.c" }

local SandboxSourceDir = ROOT .. "sandbox/src/"
local SandboxIncludeDir = ROOT .. "sandbox/include/"

project "Sandbox"
    kind "ConsoleApp"
    language "C"
    targetdir (ROOT .. "bin")
    targetname "sandbox"
    files { 
        SandboxSourceDir .. "**.c",
        SandboxIncludeDir .. "**.h"
    }
    includedirs {
        IncludeDir,
        SandboxIncludeDir
    }
    libdirs { ROOT .. "bin" }
    links{ "traveller" }