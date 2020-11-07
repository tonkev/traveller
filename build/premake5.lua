local ROOT = "../"

workspace "Traveller"

configurations { "Debug", "Release" }

filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On"
filter "configurations:Release"  defines { "NDEBUG" } optimize "On"

filter "system:windows" defines { "OS_WINDOWS" }

filter {}

local SourceDir = ROOT .. "src/"
local IncludeDir = ROOT .. "include/"

project "Traveller"
    kind "StaticLib"
    language "C"
    targetdir (ROOT .. "bin")
    targetname "traveller"
    files { SourceDir .. "**.c" }
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
    files { SandboxSourceDir .. "**.c" }
    includedirs {
        IncludeDir,
        SandboxIncludeDir
    }
    libdirs { ROOT .. "bin" }
    links{ "traveller" }