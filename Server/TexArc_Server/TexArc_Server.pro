QT -= gui
QT += network sql

CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src\main.cpp \
    src\network\masternetwork.cpp \
    src\network\pokerclient.cpp \
    src\network\pokertable.cpp \
    src\core\card.cpp \
    src\core\deck.cpp \
    src\core\player.cpp \
    src\core\gamedata.cpp \
    src\core\playergame.cpp \
    src\core\gameengine.cpp \
    src\core\gameturn.cpp \
    src\network\dbhandler.cpp \
    libs/OMPEval-master/omp/CardRange.cpp \
    libs/OMPEval-master/omp/CombinedRange.cpp \
    libs/OMPEval-master/omp/EquityCalculator.cpp \
    libs/OMPEval-master/omp/HandEvaluator.cpp \
    src/core/ai.cpp \
    src/core/proba.cpp \
    src/core/stats.cpp


HEADERS += \
    include\core\ai.h \
    include\core\proba.h \
    include\network\masternetwork.h \
    include\network\pokerclient.h \
    include\network\pokertable.h \
    include\core\card.h \
    include\core\deck.h \
    include\core\player.h \
    include\core\playeraction.h \
    include\core\gamedata.h \
    include\core\playergame.h \
    include\core\gameengine.h \
    include\core\gameturn.h \
    include\core\stats.h \
    include\network\dbhandler.h \
    libs/OMPEval-master/omp/CardRange.h \
    libs/OMPEval-master/omp/CombinedRange.h \
    libs/OMPEval-master/omp/Constants.h \
    libs/OMPEval-master/omp/EquityCalculator.h \
    libs/OMPEval-master/omp/Hand.h \
    libs/OMPEval-master/omp/HandEvaluator.h \
    libs/OMPEval-master/omp/OffsetTable.hxx \
    libs/OMPEval-master/omp/Random.h \
    libs/OMPEval-master/omp/Util.h
    libs/OMPEval-master/omp/Util.h \

