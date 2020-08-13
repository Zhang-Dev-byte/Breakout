workspace "Breakout"
    configurations { "Debug", "Release" }

    project "Breakout"
        kind "ConsoleApp"
        language "C++"
        location "Breakout"
        cppdialect "C++17"
        files { "Breakout/src/**.h", "Breakout/src/**.cpp", "Breakout/src/**.inl", "Breakout/res/**.hlsl" }

        includedirs { "deps/glm" }

        targetdir ("bin/")
        objdir ("bin-int/")

        filter { "configurations:Debug" }
            defines { "DEBUG" }
            symbols "On"

        filter { "configurations:Release" }
            defines { "NDEBUG" }
            optimize "On"
        filter { "files:**.hlsl" }
            flags "ExcludeFromBuild"
            shadermodel "5.0"
            shaderobjectfileoutput("%{file.basename}"..".cso")
            shaderassembleroutput("%{file.basename}"..".asm")
        filter { "files:**_ps.hlsl" }
            removeflags "ExcludeFromBuild"
            shadertype "Pixel"
            shaderentry "main"
        filter { "files:**_vs.hlsl" }
            removeflags "ExcludeFromBuild"
            shadertype "Vertex"
            shaderentry "main"