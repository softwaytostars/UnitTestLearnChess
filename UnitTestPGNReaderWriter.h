#ifndef UNITTESTPGNREADERWRITER_H
#define UNITTESTPGNREADERWRITER_H

#include <QtCore/QString>
#include <QtTest/QtTest>
#include "ImportExport/pgnreaderwriter.h"
#include "ChessBoardManager/ILoaderGame.h"
#include "ChessBoardManager/chessmanager.h"


class UnitTestPGNReaderWriter : public QObject,
                                public ILoaderGame
{
    Q_OBJECT

public:
    UnitTestPGNReaderWriter();
    ~UnitTestPGNReaderWriter();
    virtual void InitializeGame(bool aCreationPiece);
    virtual void AjouterDemiCoup (CommandPlay* aCommandPlay){_ListCommandesPlay.push_back(aCommandPlay);}
    virtual IChessManager& getChessManager()  {return _ChessManager;}

private:
    PGNReaderWriter *_pgn;
    ChessManager _ChessManager;
    QString _CRepFiles;
    QVector<CommandPlay *> _ListCommandesPlay;
private Q_SLOTS:
    void init();//will be called before each testfunction is executed.
    void cleanup();
    void testRead();
    void testRead_data();
    void testWrite();
};

#endif // UNITTESTPGNREADERWRITER_H
