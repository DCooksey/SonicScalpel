TEMPLATE = app
CONFIG += console c++11
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt



SOURCES += main.cpp \
    player.cpp \
    RtAudio.cpp \
    maxiSynths.cpp \
    maxiMFCC.cpp \
    maxiGrains.cpp \
    maxiFFT.cpp \
    maxiBark.cpp \
    maxiAtoms.cpp \
    fft.cpp \
    maximilian.cpp \
    stb_vorbis.c \



DISTFILES += \
    SSv5.pro.user \
    snare.wav \
    README

HEADERS += \
    stb_vorbis.h \
    portaudio.h \
    player.h \
    RtError.h \
    RtAudio.h \
    maximilian.h \
    sineTable.h \
    maxiSynths.h \
    maxiMFCC.h \
    maxim.h \
    maxiGrains.h \
    maxiFFT.h \
    maxiBark.h \
    maxiAtoms.h \
    fft.h \
    sndfile.hh \

