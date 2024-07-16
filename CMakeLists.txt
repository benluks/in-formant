cmake_minimum_required(VERSION 3.5)
set(CMAKE_OSX_DEPLOYMENT_TARGET $ENV{MACOSX_DEPLOYMENT_TARGET})
project(speech-analysis)

# Set the policy for CMP0076 to use absolute paths
cmake_policy(SET CMP0076 NEW)
set(CMAKE_SUPPORT_DIR "${PROJECT_SOURCE_DIR}/cmake_support")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SUPPORT_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-fPIC -ftree-vectorize -fno-omit-frame-pointer -fno-math-errno -mtune=generic")
set(CMAKE_CXX_FLAGS_DEBUG           "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE         "-O2 -g0 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "-O2 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL      "-Os -g0 -DNDEBUG")

if(ANDROID)
elseif(WIN32 OR APPLE OR UNIX)
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=i686 -msse")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64 -msse")
    endif()
endif()

set(CMAKE_ENABLE_EXPORTS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_SUPPORT_DIR}/CheckLowLevelExit.cmake)

set(SOURCES
    src/main.cpp
    src/context/context.h
    src/context/contextbuilder.h
    src/context/contextmanager.cpp
    src/context/contextmanager.h
    src/backtrace/backtrace.h
    src/android_redirect_log.cpp
    src/modules/audio/base/base.cpp
    src/modules/audio/base/base.h
    src/modules/audio/buffer/buffer.cpp
    src/modules/audio/buffer/buffer.h
    src/modules/audio/queue/queue.cpp
    src/modules/audio/queue/queue.h
    src/modules/audio/resampler/resampler.cpp
    src/modules/audio/resampler/resampler.h
    src/modules/audio/audio.h
    src/modules/app/pipeline/pipeline.cpp
    src/modules/app/pipeline/pipeline.h
    src/modules/app/app.h
    src/modules/modules.h
    src/nodes/node/nodeio_audiotime.cpp
    src/nodes/node/nodeio_audiotime.h
    src/nodes/node/nodeio_audiospec.cpp
    src/nodes/node/nodeio_audiospec.h
    src/nodes/node/nodeio_frequencies.cpp
    src/nodes/node/nodeio_frequencies.h
    src/nodes/node/nodeio_iirfilter.cpp
    src/nodes/node/nodeio_iirfilter.h
    src/nodes/node/nodeio.cpp
    src/nodes/node/nodeio.h
    src/nodes/node/node.cpp
    src/nodes/node/node.h
    src/nodes/prereqs/prereqs.cpp
    src/nodes/prereqs/prereqs.h
    src/nodes/resampler/resampler.cpp
    src/nodes/resampler/resampler.h
    src/nodes/spectrum/spectrum.cpp
    src/nodes/spectrum/spectrum.h
    src/nodes/tail/tail.cpp
    src/nodes/tail/tail.h
    src/nodes/pitchtracker/pitchtracker.cpp
    src/nodes/pitchtracker/pitchtracker.h
    src/nodes/preemph/preemph.cpp
    src/nodes/preemph/preemph.h
    src/nodes/linpred/linpred.cpp
    src/nodes/linpred/linpred.h
    src/nodes/formants/formants.cpp
    src/nodes/formants/formants.h
    src/nodes/invglot/invglot.cpp
    src/nodes/invglot/invglot.h
    src/nodes/nodes.h
    src/analysis/fft/realfft.cpp
    src/analysis/fft/complexfft.cpp
    src/analysis/fft/realrealfft.cpp
    src/analysis/fft/wisdom.cpp
    src/analysis/fft/fft.h
    src/analysis/filter/butterworth.cpp
    src/analysis/filter/zpk2sos.cpp
    src/analysis/filter/sosfilter.cpp
    src/analysis/filter/filter.cpp
    src/analysis/filter/filter.h
    src/analysis/pitch/amdf_m.cpp
    src/analysis/pitch/yin.cpp
    src/analysis/pitch/mpm.cpp
    src/analysis/pitch/rapt.cpp
    src/analysis/pitch/rapt.h
    src/analysis/pitch/pitch.h
    src/analysis/linpred/autocorr.cpp
    src/analysis/linpred/burg.cpp
    src/analysis/linpred/linpred.h
    src/analysis/formant/simplelp.cpp
    src/analysis/formant/filteredlp.cpp
    src/analysis/formant/formant.h
    src/analysis/invglot/iaif.cpp
    src/analysis/invglot/gfm_iaif.cpp
    #src/analysis/invglot/amgif.cpp
    src/analysis/invglot/invglot.h
    src/analysis/wavelet/wavelet.h
    src/analysis/wavelet/wavelets.cpp
    src/analysis/wavelet/wavelets.h
    src/analysis/wavelet/common.cpp
    src/analysis/wavelet/common.h
    src/analysis/wavelet/coeffs.cpp
    src/analysis/wavelet/coeffs.h
    src/analysis/wavelet/convolution.cpp
    src/analysis/wavelet/convolution.h
    src/analysis/wavelet/wt.cpp
    src/analysis/wavelet/wt.h
    src/analysis/gci/sigma.cpp
    src/analysis/gci/sigma.h
    src/analysis/gci/xewgrdel.cpp
    src/analysis/gmm/GMM.cpp
    src/analysis/gmm/GMM.h
    src/analysis/gmm/Kmeans.cpp
    src/analysis/gmm/Kmeans.h
    src/analysis/gmm/Matrix.cpp
    src/analysis/gmm/Matrix.h
    src/analysis/resampler/resampler.cpp
    src/analysis/resampler/resampler.h
    src/analysis/util/find_peaks.cpp
    src/analysis/util/find_roots.cpp
    src/analysis/util/laguerre.cpp
    src/analysis/util/laguerre.h
    src/analysis/util/polish_root.cpp
    src/analysis/util/eval_polynomial.cpp
    src/analysis/util/calc_formant.cpp
    src/analysis/util/sort_formants.cpp
    src/analysis/util/parabolic_interpolation.cpp
    src/analysis/util/zerocros.cpp
    src/analysis/util/util.h
    src/analysis/analysis.h
    external/r8brain-free-src/r8bbase.cpp
    external/r8brain-free-src/pffft.cpp
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(Eigen3 REQUIRED eigen3)
pkg_check_modules(FFTW REQUIRED fftw3)

check_low_level_exit(
    LL_EXIT_FUNC
    INCLUDES unistd.h stdlib.h process.h
    NAMES _Exit _exit
)

set(SOXR_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/r8brain-free-src)

### SEARCH AUDIO MODULES 

if(TRUE)
    message(STATUS "Including audio module: dummy")
    set(AUDIO_USE_DUMMY TRUE)
    list(APPEND SOURCES
        src/modules/audio/dummy/dummy.cpp
        src/modules/audio/dummy/dummy
    )
endif()

pkg_check_modules(portaudio QUIET portaudio-2.0)
if(portaudio_FOUND)
    message(STATUS "Including audio module: portaudio")
    set(AUDIO_USE_PORTAUDIO TRUE)
    list(APPEND SOURCES
        src/modules/audio/portaudio/portaudio.cpp
        src/modules/audio/portaudio/portaudio.h
    )
endif()

### CREATE CMAKE TARGET

add_executable(speech-analysis ${SOURCES})

target_include_directories(speech-analysis SYSTEM PUBLIC ${Eigen3_INCLUDE_DIRS} ${FFTW_INCLUDE_DIRS} ${SOXR_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/external/armadillo/include)
target_link_libraries(speech-analysis PUBLIC ${Eigen3_LDFLAGS} ${FFTW_LDFLAGS} ${SOXR_LIBRARIES})

target_compile_definitions(speech-analysis PUBLIC -DR8B_PFFFT=1 -DARMA_DONT_USE_WRAPPER)

if(AUDIO_USE_DUMMY)
    target_compile_definitions(speech-analysis PUBLIC -DAUDIO_USE_DUMMY=1)
endif()

if(AUDIO_USE_PORTAUDIO)
    # Specify the path to the PortAudio library
    set(PORTAUDIO_INCLUDE_DIRS "/usr/local/include")
    set(PORTAUDIO_LIBRARIES "/usr/local/Cellar/portaudio/19.7.0/lib/libportaudio.2.dylib")

    # Manually specify the PortAudio static library
    # set(PORTAUDIO_LIB "${PORTAUDIO_LIBRARY_DIR}/libportaudio.a")

    include_directories(${PORTAUDIO_INCLUDE_DIR})
    # Add the PortAudio include directory
    include_directories(${PROJECT_SOURCE_DIR}/include)

    # Add any necessary frameworks (for macOS)
    find_library(AUDIOUNIT_FRAMEWORK AudioUnit)
    find_library(AUDIO_TOOLBOX_FRAMEWORK AudioToolbox)
    find_library(COREAUDIO_FRAMEWORK CoreAudio)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_SERVICES_FRAMEWORK CoreServices)

    target_include_directories(speech-analysis SYSTEM PUBLIC ${PORTAUDIO_INCLUDE_DIRS})
    target_link_libraries(speech-analysis PUBLIC ${PORTAUDIO_LIBRARIES})
    target_compile_definitions(speech-analysis PUBLIC -DAUDIO_USE_PORTAUDIO=1)
endif()

if(AUDIO_USE_OBOE)
    target_include_directories(speech-analysis SYSTEM PUBLIC ${OBOE_DIR}/include)
    target_link_libraries(speech-analysis PUBLIC oboe)
    target_compile_definitions(speech-analysis PUBLIC -DAUDIO_USE_OBOE=1)
endif()

## PLATFORM SPECIFIC CODE

set(RESAMPLER_QUALITY SOXR_HQ)

if(UNIX AND NOT EMSCRIPTEN)
    target_sources(speech-analysis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/backtrace/unix.cpp)
    target_link_libraries(speech-analysis PUBLIC dl)
    set_target_properties(speech-analysis PROPERTIES LINK_FLAGS "-pthread -static-libstdc++")
endif()

if(NOT ANDROID AND NOT WIN32 AND CMAKE_BUILD_TYPE MATCHES "^Debug$")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -fsanitize=address -fsanitize=undefined")
endif()

target_compile_definitions(speech-analysis PUBLIC -DRESAMPLER_QUALITY=${RESAMPLER_QUALITY})
