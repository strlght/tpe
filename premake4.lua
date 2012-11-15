solution "tpe"
	configurations { "Debug", "Release" }

	project "tpe"
		language "C++"
		kind "WindowedApp"
		files { "src/**.cpp" }
		includedirs { "include" }
		links { "sfml-system", "sfml-window", "sfml-graphics"}
		buildoptions { "-w", "-std=c++11" }

		configuration { "Debug" }
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration { "Release" }
			defines { "NDEBUG" }
			flags { "Optimize" }

	if _ACTION == "clean" then
	    os.rmdir("obj")
	end
