workspace "Breakout"
    configurations { "Debug", "Release" }

    project "Breakout"
        kind "ConsoleApp"
        language "C++"
        location "Breakout"
        cppdialect "C++17"
        files { "Breakout/src/**.h", "Breakout/src/**.cpp" }
        includedirs { "deps/glm" }

        targetdir ("bin/")
        objdir ("bin-int/")

        filter { "configurations:Debug" }
            defines { "DEBUG" }
            symbols "On"

        filter { "configurations:Release" }
            defines { "NDEBUG" }
            optimize "On"