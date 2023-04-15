workspace "Programming-4-Engine"
    configurations { "Debug", "Release" }
    platforms { "x86", "x64" }

vendorFolder = "3rdParty/"
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}

project "Engine"
    location "Engine"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" ..outputDir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputDir.. "/%{prj.name}")

    pchheader "pch.h"
    pchsource "%{prj.name}/pch.cpp"

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
        vendorFolder.."imgui/**.cpp",
        vendorFolder.."implot/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/",
        vendorFolder.."glm",
        vendorFolder.."SDL2/include",
        vendorFolder.."SDL2_image/include",
        vendorFolder.."SDL2_ttf/include",
        vendorFolder.."spdlog/include",
        vendorFolder.."imgui/",
        vendorFolder.."implot/",
        vendorFolder.."steamworks/public/steam",
    }

    links
    {
        "SDL2.lib",
        "SDL2main.lib",
        "SDL2_image.lib",
        "SDL2_ttf.lib",
        "opengl32.lib",
        "xinput.lib",
        "steam_api.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"
        warnings "extra"
        flags {"FatalWarnings"}

    filter "configurations:Debug"
        defines {"DEBUG", "IMGUI_DEFINE_MATH_OPERATORS"}
        symbols "On"


    filter "configurations:Release"
        defines {"NDEBUG", "IMGUI_DEFINE_MATH_OPERATORS"}
        optimize "On"

    filter { "platforms:x86" }
        libdirs
        {
            vendorFolder.."SDL2/lib/x86",
            vendorFolder.."SDL2_image/lib/x86",
            vendorFolder.."SDL2_ttf/lib/x86",
            vendorFolder.."steamworks/redistributable_bin/win32"
        }

        postbuildcommands
        {
            ("{COPY} ../3rdParty/SDL2/lib/x86/ ../bin/"..outputDir.."/Engine"),
            ("{COPY} ../3rdParty/SDL2_image/lib/x86/ ../bin/"..outputDir.."/Engine"),
            ("{COPY} ../3rdParty/SDL2_ttf/lib/x86/ ../bin/"..outputDir.."/Engine"),
            ("{COPY} ../Data ../bin/"..outputDir.."/Data"),
            ("{COPY} ../Data/STEAM/ ../bin/"..outputDir.."/Engine"),
            ("{COPY} ../3rdParty/steamworks/redistributable_bin/win32/ ../bin/"..outputDir.."/Engine")
        }




    filter { "platforms:x64" }
        libdirs
        {
            vendorFolder.."SDL2/lib/x64",
            vendorFolder.."SDL2_image/lib/x64",
            vendorFolder.."SDL2_ttf/lib/x64",
            vendorFolder.."steamworks/redistributable_bin/win64"
        }

        postbuildcommands
        {
            ("{COPY} ../3rdParty/SDL2/lib/x64/ ../bin/"..outputDir.."/Engine"),
            ("{COPY} ../3rdParty/SDL2_image/lib/x64/ ../bin/"..outputDir.."/Engine"),
            ("{COPY} ../3rdParty/SDL2_ttf/lib/x64/ ../bin/"..outputDir.."/Engine"),
            ("{COPY} ../Data ../bin/"..outputDir.."/Data"),
            ("{COPY} ../Data/STEAM/ ../bin/"..outputDir.."/Engine"),
            ("{COPY} ../3rdParty/steamworks/redistributable_bin/win64/ ../bin/"..outputDir.."/Engine")
        }



    filter "files:3rdParty/imgui/imgui**.cpp"
        flags {"NoPCH"}

    filter "files:3rdParty/implot/**.cpp"
        flags {"NoPCH"}