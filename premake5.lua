workspace "Minecraft"
    architecture "x64"
    startproject "Minecraft"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
    {
        "MultiProcessorCompile"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "Minecraft/vendor/glfw"
group ""

include "Minecraft"