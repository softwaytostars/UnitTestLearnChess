#ifndef UNITTESTALGOCOMPUTER_H
#define UNITTESTALGOCOMPUTER_H

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "ImportExport/pgnreaderwriter.h"
#include "ChessBoardManager/ILoaderGame.h"
#include "ChessBoardManager/chessmanager.h"
#include "Types/TypeInfosAlgo.h"

class AlgoComputer;

class UnitTestAlgoComputer : public QObject,
                             public ILoaderGame
{
    Q_OBJECT

public:
    UnitTestAlgoComputer();
    ~UnitTestAlgoComputer();
    virtual void InitializeGame(bool aCreationPiece);
    virtual void AjouterDemiCoup (CommandPlay* aCommandPlay);
    virtual IChessManager& getChessManager()  {return _ChessManager;}
private:
    enum eTypeMoveAlgo {
        eMoveAlgoAFaire,
        eMoveAlgoANePasFaire,
        eMoveAlgoBougePiece
    };
    PGNReaderWriter *_pgn;
    ChessManager _ChessManager;
    AlgoComputer * _AlgoComputer;
    QString _CRepFiles;
    QVector<CommandPlay *> _ListCommandesPlay;
    int _DemiMoveAlgo;
    sMove _MoveAlgo;
    eTypeMoveAlgo _TypeMoveAFaire;
private Q_SLOTS:
    void init();//will be called before each testfunction is executed.
    void cleanup();
    void testFindMove();
    void testFindMove_data();
};

#endif // UNITTESTALGOCOMPUTER_H
