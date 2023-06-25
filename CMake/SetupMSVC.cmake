

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

function(setup_project target outputname)

    set_property(TARGET ${target} PROPERTY CXX_STANDARD          23)
    set_property(TARGET ${target} PROPERTY CXX_STANDARD_REQUIRED ON)
    set_property(TARGET ${target} PROPERTY CXX_EXTENSIONS        OFF)

    #set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/bin)
    #set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    #set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

    if(outputname STREQUAL "")
        set_target_properties(${target} PROPERTIES OUTPUT_NAME ${target})
    else()
        set_target_properties(${target} PROPERTIES OUTPUT_NAME "${outputname}")
    endif()


    set_target_properties(${target} PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_SOURCE_DIR}/bin
        PDB_NAME ${target}
        PDB_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/pdb"
    )

    if(MSVC)
        set_property(TARGET ${target} PROPERTY VS_STARTUP_PROJECT  ${target})

        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX "d")
        set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>")

        #target_compile_definitions(${target} PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_definitions(${target} PRIVATE UNICODE)
        target_compile_definitions(${target} PRIVATE _UNICODE)

        target_compile_definitions(${target} PRIVATE NOMINMAX)
        target_compile_definitions(${target} PRIVATE WIN32_LEAN_AND_MEAN)
        target_compile_definitions(${target} PRIVATE WIN32_EXTRA_LEAN)


        # Turn off stuff from windows.h
        #target_compile_definitions(${target} PRIVATE NOGDI)
        #target_compile_definitions(${target} PRIVATE NOMB)
        #target_compile_definitions(${target} PRIVATE NOUSER)
        #target_compile_definitions(${target} PRIVATE NOWH)
        #target_compile_definitions(${target} PRIVATE NOMSG)
        #target_compile_definitions(${target} PRIVATE NOWINMESSAGES)
        #target_compile_definitions(${target} PRIVATE NOVIRTUALKEYCODES)
        #target_compile_definitions(${target} PRIVATE NOWINSTYLES)

        target_compile_definitions(${target} PRIVATE NOIME)
        target_compile_definitions(${target} PRIVATE NOWINRES)
        target_compile_definitions(${target} PRIVATE NOGDICAPMASKS)
        target_compile_definitions(${target} PRIVATE NOSYSMETRICS)
        target_compile_definitions(${target} PRIVATE NOMENUS)
        target_compile_definitions(${target} PRIVATE NOICONS)
        target_compile_definitions(${target} PRIVATE NOKEYSTATES)
        target_compile_definitions(${target} PRIVATE NOSYSCOMMANDS)
        target_compile_definitions(${target} PRIVATE NORASTEROPS)
        target_compile_definitions(${target} PRIVATE NOSHOWWINDOW)
        target_compile_definitions(${target} PRIVATE OEMRESOURCE)
        target_compile_definitions(${target} PRIVATE NOATOM)
        target_compile_definitions(${target} PRIVATE NOCLIPBOARD)
        target_compile_definitions(${target} PRIVATE NOCOLOR)
        target_compile_definitions(${target} PRIVATE NOCTLMGR)
        target_compile_definitions(${target} PRIVATE NODRAWTEXT)
        target_compile_definitions(${target} PRIVATE NOMEMMGR)
        target_compile_definitions(${target} PRIVATE NOMETAFILE)
        target_compile_definitions(${target} PRIVATE NOOPENFILE)
        target_compile_definitions(${target} PRIVATE NOSCROLL)
        target_compile_definitions(${target} PRIVATE NOSERVICE)
        target_compile_definitions(${target} PRIVATE NOSOUND)
        target_compile_definitions(${target} PRIVATE NOTEXTMETRIC)
        target_compile_definitions(${target} PRIVATE NOWINOFFSETS)
        target_compile_definitions(${target} PRIVATE NOCOMM)
        target_compile_definitions(${target} PRIVATE NOKANJI)
        target_compile_definitions(${target} PRIVATE NOHELP)
        target_compile_definitions(${target} PRIVATE NOPROFILER)
        target_compile_definitions(${target} PRIVATE NODEFERWINDOWPOS)
        target_compile_definitions(${target} PRIVATE NOMCX)
        target_compile_definitions(${target} PRIVATE NOIME)
        target_compile_definitions(${target} PRIVATE NOPROXYSTUB)
        target_compile_definitions(${target} PRIVATE NOIMAGE)
        target_compile_definitions(${target} PRIVATE NOTAPE)



        target_compile_options(${target} PRIVATE /nologo)
        target_compile_options(${target} PRIVATE -Zc:__cplusplus /Zc:alignedNew)
        target_compile_options(${target} PRIVATE /utf-8)
        target_compile_options(${target} PRIVATE /EHsc)
        #target_compile_options(${target} PRIVATE /Za)

        target_compile_options(${target}  PRIVATE /fp:precise)
        target_compile_options(${target} PRIVATE /diagnostics:caret)


        target_compile_options(${target} PRIVATE /experimental:module)
        target_compile_options(${target} PRIVATE /Zc:preprocessor)
        target_compile_options(${target} PRIVATE /permissive-)
        target_compile_options(${target} PRIVATE /std:c++latest)
        target_compile_options(${target} PRIVATE /Zc:__cplusplus)

        target_compile_options(${target} PRIVATE /Wall)
        # target_compile_options(${target} PRIVATE /WX) # Warnings as errors

        
        # Generate out stub
        if(NOT EXISTS stub.bin)
             set(CMAKE_DISABLE_SOURCE_CHANGES OFF)
             file(WRITE newstub.txt "4D 5A FF 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 40 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00")

             # CertUtil has been included since Windows XP
             execute_process( COMMAND certutil -f -decodehex newstub.txt stub.bin WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_QUIET)
             file(REMOVE newstub.txt)
             set(CMAKE_DISABLE_SOURCE_CHANGES ON)
        endif()


         # Stub
         if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/stub.bin)
             target_link_options(${target} PRIVATE /stub:${CMAKE_CURRENT_SOURCE_DIR}/stub.bin )
        endif()

        # Debug
        if (${CMAKE_BUILD_TYPE} MATCHES "Debug")

            target_compile_options(${target}  PRIVATE /JMC)    # Just my debugging
            target_compile_definitions(${target} PRIVATE -DDEBUG)

            target_compile_options(${target}  PRIVATE /Od)

            target_compile_options(${target}  PRIVATE /RTC1)
            target_compile_options(${target}  PRIVATE /GS)
            target_compile_options(${target}  PRIVATE /Zi)     # /ZI edit/continue

            target_link_options(${target} PRIVATE /DEBUG)
            #target_link_options(${target} PRIVATE /ALIGN:16)
        endif()

        # Release
        if (${CMAKE_BUILD_TYPE} MATCHES "Release")
           #set_target_properties(${target} PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)

            target_compile_definitions(${target} PRIVATE -DNDEBUG)
        
            target_compile_options(${target}  PRIVATE /O2  /Os)
            target_compile_options(${target}  PRIVATE /GS-)

            target_link_options(${target} PRIVATE /Release)
            target_link_options(${target} PRIVATE /INCREMENTAL:NO)


            target_link_options(${target} PRIVATE /OPT:REF /OPT:ICF)

            # 0x800: LOAD_LIBRARY_SEARCH_SYSTEM32
            target_link_options(${target} PRIVATE /DEPENDENTLOADFLAG:0x800)
            


            # Undocumented options
            target_link_options(${target} PRIVATE  /emittoolversioninfo:no /emitpogophaseinfo)

            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/stub.bin)
            target_link_options(${target} PRIVATE  /stub:${CMAKE_CURRENT_SOURCE_DIR}/stub.bin )
            endif()
        endif()




        # Minimum Windows 10.
        # target_compile_definitions(CMakeTest+1 PRIVATE -DWINVER=0x0a00)
        # target_compile_definitions(CMakeTest+1 PRIVATE -D_WIN32_WINNT=0x0a00)


        # Manifest
        target_link_options(${target} PRIVATE /MANIFEST:NO)

        if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/manifest.txt")

            ADD_CUSTOM_COMMAND(
		    	TARGET ${target}
		    	POST_BUILD
		    	COMMAND "mt.exe" -nologo -manifest ${CMAKE_CURRENT_SOURCE_DIR}/manifest.txt -outputresource:$<TARGET_FILE:${target}>\;\#1
		    )

        endif()


        target_link_options(${target} PRIVATE  /MAP:map.txt)


        # Dynamic
        #set_target_properties(${target} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
        
        # Static
        set_target_properties(${target} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    

        # Disabled warnings
        target_compile_options(${target} PRIVATE 
        
            /wd5039 # pointer or reference to potentially throwing function passed to 'extern "C"' function under -EHc.

            /wd5262 # implicit fall-through occurs here; are you missing a break statement? Use [[fallthrough]] when a break 
                    # statement is intentionally omitted between cases
        )

    endif() # MSVC

    find_program(BUILDINC_TOOL "buildinc" NO_CACHE)
    if(BUILDINC_TOOL)
    add_custom_command(TARGET ${target}
                       PRE_BUILD
                       COMMAND ${BUILDINC_TOOL} ${CMAKE_CURRENT_SOURCE_DIR}/src/buildnumber.ixx ${target} -q -m 
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
                       COMMENT "Increase build number"

    )
    endif()

endfunction()

