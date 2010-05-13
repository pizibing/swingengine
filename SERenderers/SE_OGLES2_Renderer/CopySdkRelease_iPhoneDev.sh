#!/bin/tcsh

set DIRS = `ls`
foreach dir (${DIRS})
    if (-d $dir && $dir != SE_iPhoneOES2_Renderer.xcodeproj && $dir != build) then
        echo $dir
        cd $dir
        set CURDIR = `pwd`
        set HEADERS = `ls *.h *.inl`
        foreach header (${HEADERS})
            cp -fp "${CURDIR}"/$header ../../../SDK/Include
        end
        cd ..
    endif
end

set RHEADERS = `ls *.h`
foreach rheader (${RHEADERS})
    cp -fp "${SRCROOT}"/$rheader ../../SDK/Include
end

cp -fp "${SRCROOT}"/build/Default/libSEiPhoneOES2Renderer_iPhoneDev.a ../../SDK/Lib/Release/libSEiPhoneOES2Renderer_iPhoneDev.a
ranlib ../../SDK/Lib/Release/libSEiPhoneOES2Renderer_iPhoneDev.a

