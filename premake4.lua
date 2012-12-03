solution "tpe"
	configurations { "Debug", "Release" }

	project "tpe"
		language "C++"
		kind "SharedLib"
		files { "src/**.cpp" }
		includedirs { "include" }
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
