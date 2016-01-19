#-------------------------------------------------
#
# Project created by QtCreator 2012-11-09T15:06:34
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_learnchess
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEPENDPATH  += /home/alexis/LearnChess
INCLUDEPATH += /home/alexis/LearnChess

CONFIG(debug, debug|release) {
    DEFINES += _DEBUG
}

SOURCES += \
    main.cpp \
    UnitTestPGNReaderWriter.cpp\
    Algo/algocomputer.cpp \
    Algo/evaluatorposition.cpp \
    Data/tablepiece.cpp \
    ChessBoardManager/chessmanager.cpp \
    infosgraphiques.cpp \
    ChessBoardManager/IRuleMovePiece.cpp \
    ChessBoardManager/RuleMoveRook.cpp \
    ChessBoardManager/FactoryRuleMovePiece.cpp \
    ChessBoardManager/RuleMoveKnight.cpp \
    ChessBoardManager/RuleMoveBishop.cpp \
    ChessBoardManager/RuleMoveQueen.cpp \
    ChessBoardManager/RuleMoveKing.cpp \
    ChessBoardManager/RuleMovePawn.cpp \
    infosconfiguration.cpp \
    ChessBoardManager/dialogaskpiece.cpp \
    Demos/actionsdemo.cpp \
    ChessBoardManager/commandplay.cpp \
    ImportExport/pgnreaderwriter.cpp \
    TypePiece.cpp \
    exceptionsInfos.cpp \
    Preferences/applicationstyle.cpp\
    qlistepieces.cpp \
    unittestalgocomputer.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    UnitTestPGNReaderWriter.h\
    Algo/algocomputer.h \
    Algo/evaluatorposition.h \
    Data/tablepiece.h \
    Data/ArticlePiece.hpp \
    TypePiece.hpp \
    TypeInfoChessBoard.hpp \
    ChessBoardManager/chessmanager.h \
    ChessBoardManager/ObserverChessManager.h \
    infosgraphiques.h \
    ChessBoardManager/Irulemovepiece.h \
    ChessBoardManager/IChessManager.h \
    ChessBoardManager/RuleMoveRook.h \
    ChessBoardManager/FactoryRuleMovePiece.h \
    ChessBoardManager/RuleMoveKnight.h \
    ChessBoardManager/RuleMoveBishop.h \
    ChessBoardManager/RuleMoveQueen.h \
    ChessBoardManager/RuleMoveKing.h \
    ChessBoardManager/RuleMovePawn.h \
    TypeDemo.hpp \
    infosconfiguration.h \
    ChessBoardManager/dialogaskpiece.h \
    Demos/actionsdemo.h \
    ChessBoardManager/commandplay.h \
    ImportExport/pgnreaderwriter.h \
    ChessBoardManager/ILoaderGame.h \
    TypeFichierPGN.h \
    exceptionsInfos.h \
    Preferences/applicationstyle.h \
    Types/TypePreferences.h\
    qlistepieces.h \
    unittestalgocomputer.h

FORMS    += ChessBoardManager/dialogaskpiece.ui

