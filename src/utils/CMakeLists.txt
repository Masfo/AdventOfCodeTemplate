 							   

add_library(utils STATIC)
set_property(TARGET utils PROPERTY CXX_STANDARD          23)
set_property(TARGET utils PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET utils PROPERTY CXX_EXTENSIONS        OFF)

if(MSVC)
    #set_property(TARGET utils PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    set_property(TARGET utils PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

#target_include_directories(utils PRIVATE ${CMAKE_CURRENT_LIST_DIR})

 target_compile_definitions(utils PRIVATE UNICODE)
 target_compile_definitions(utils PRIVATE _UNICODE)
 target_compile_definitions(utils PRIVATE NOMINMAX)
 target_compile_definitions(utils PRIVATE WIN32_LEAN_AND_MEAN)
 target_compile_definitions(utils PRIVATE WIN32_EXTRA_LEAN)

 target_compile_options(utils PRIVATE /experimental:module)
 target_compile_options(utils PRIVATE /Zc:preprocessor)
 target_compile_options(utils PRIVATE /permissive-)
 target_compile_options(utils PRIVATE /std:c++latest)

  #if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  if(CMAKE_BUILD_TYPE MATCHES Debug)

    target_compile_options(utils  PRIVATE /JMC)    # Just my debugging
    target_compile_options(utils  PRIVATE /RTC1)
    target_compile_options(utils  PRIVATE /Od)

    target_compile_options(utils  PRIVATE /GS)


    #target_compile_options(utils PRIVATE /ZI) # edit/continue
    target_compile_options(utils  PRIVATE /Zi)     
    target_link_options(utils PRIVATE /SAFESEH:NO)
    target_link_options(utils PRIVATE /DEBUG)
    target_link_options(utils PRIVATE /INCREMENTAL)

    #target_link_options(utils PRIVATE /ALIGN:16)
    target_compile_options(utils  PRIVATE /analyze /analyze:external- )

endif()
											
target_compile_options(utils PRIVATE /std:c++latest)
target_compile_options(utils PRIVATE /fp:precise)
target_compile_options(utils PRIVATE /diagnostics:caret)
target_compile_options(utils PRIVATE /experimental:module)
target_compile_options(utils PRIVATE /Zc:preprocessor)
target_compile_options(utils PRIVATE /Zc:__cplusplus)
target_compile_options(utils PRIVATE /EHsc)


target_sources(utils PRIVATE 
               FILE_SET cxx_modules 
               TYPE CXX_MODULES 
               FILES 

    aoc.ixx
    debug.ixx
    math.ixx 
    types.ixx
    print.ixx
    stringhelper.ixx
    readfile.ixx
 )


 #
target_compile_options(utils PRIVATE 
       
    /wd5039 # pointer or reference to potentially throwing function passed to 'extern "C"' function under -EHc.
    
    /wd5262 # implicit fall-through occurs here; are you missing a break statement? Use [[fallthrough]] when a break 
            # statement is intentionally omitted between cases
    /wd4710 # function not inlined
    /wd4711 # function selected for automatic inline expansion
    /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
    /wd5050 # Possible incompatible environment while importing module

    /wd4820 # bytes padding added after data member

    /wd4626 # assignment operator was implicitly defined as deleted
    /wd5027 # move assignment operator was implicitly defined as deleted
    /wd4061 # switch of enum is not explicitly handled by a case label

)
