#include "unittestalgocomputer.h"
#include "Algo/algocomputer.h"
#include "ChessBoardManager/commandplay.h"

UnitTestAlgoComputer::UnitTestAlgoComputer():
    _ChessManager (true),
    _CRepFiles ("/home/alexis/UnitTestLearnChess/AlgoTestFiles/")
{
    _AlgoComputer = new AlgoComputer (_ChessManager, BLACK);
}

UnitTestAlgoComputer::~UnitTestAlgoComputer() {

    delete _AlgoComputer;
}

void UnitTestAlgoComputer::InitializeGame(bool aCreationPiece) {

    _ChessManager.ResetPieces();
    if (aCreationPiece)
        _ChessManager.CreationDesPieces();

    for (QVector<CommandPlay*>::const_iterator it =_ListCommandesPlay.begin();
         it != _ListCommandesPlay.end();
         ++it) {
        delete (*it);
    }
    _ListCommandesPlay.clear();
}

void UnitTestAlgoComputer::AjouterDemiCoup (CommandPlay* aCommandPlay) {

    _ListCommandesPlay.push_back(aCommandPlay);

    if (_ListCommandesPlay.count() == _DemiMoveAlgo) {
        sMove lMoveSelected;
        _AlgoComputer->FindMoveToPlay(_DemiMoveAlgo, aCommandPlay, lMoveSelected);
        switch (_TypeMoveAFaire) {
            case eMoveAlgoANePasFaire : {
                                            if ((lMoveSelected._OldPosX == _MoveAlgo._OldPosX) &&
                                                 (lMoveSelected._OldPosY == _MoveAlgo._OldPosY) &&
                                                 (lMoveSelected._newPosX == _MoveAlgo._newPosX) &&
                                                 (lMoveSelected._newPosY == _MoveAlgo._newPosY))

                                                QVERIFY2 (false, "Mauvais coup trouve!");
                                            break;
                                        }
            case eMoveAlgoAFaire      : {
                                            if (((lMoveSelected._OldPosX != _MoveAlgo._OldPosX) ||
                                                                (lMoveSelected._OldPosY != _MoveAlgo._OldPosY) ||
                                                                (lMoveSelected._newPosX != _MoveAlgo._newPosX) ||
                                                                (lMoveSelected._newPosY != _MoveAlgo._newPosY)))
                                                QVERIFY2 (false, "Mauvais coup trouve!");
                                            break;
                                        }
            case eMoveAlgoBougePiece : {if ((lMoveSelected._OldPosX != _MoveAlgo._OldPosX) ||
                                             (lMoveSelected._OldPosY != _MoveAlgo._OldPosY) )
                                                QVERIFY2 (false, "La piece devait bouger!");

                                         break;
                                        }
            default : break;
        }//switch
    }//if (_ListCommandesPlay.count() == _DemiMoveAlgo)
}

void UnitTestAlgoComputer::init() {

}

void UnitTestAlgoComputer::cleanup() {

    if (_pgn) {
        delete _pgn;
        _pgn = 0;
    }
}

void UnitTestAlgoComputer::testFindMove()
{
    _pgn = new PGNReaderWriter (_CRepFiles+QString (QTest::currentDataTag()));

    QVERIFY2((_pgn != 0), "Fail instance PGNReaderWriter");

    QFETCH(int, NoPartie);
    QFETCH(int, DemiMoveAlgo);
    QFETCH(int,TypeMoveAFaire);
    QFETCH(int, MoveAlgo_OldX);
    QFETCH(int, MoveAlgo_OldY);
    QFETCH(int, MoveAlgo_NewX);
    QFETCH(int, MoveAlgo_NewY);
    _DemiMoveAlgo = DemiMoveAlgo;
    _MoveAlgo = sMove (Queen,
                       MoveAlgo_OldX,
                       MoveAlgo_OldY,
                       MoveAlgo_NewX,
                       MoveAlgo_NewY,
                       0,
                       false);
    _TypeMoveAFaire = eTypeMoveAlgo (TypeMoveAFaire);
    _pgn->LoadGame(*this, NoPartie);
    QVERIFY2 (_ListCommandesPlay.count() >= _DemiMoveAlgo, "Erreur config data!");
}

//definit le data set
void UnitTestAlgoComputer::testFindMove_data()
{
    QTest::addColumn<int>("NoPartie");
    QTest::addColumn<int>("DemiMoveAlgo");//2*(N-1)+1 pour noir
    //descirption move
    QTest::addColumn<int>("TypeMoveAFaire");
    QTest::addColumn<int>("MoveAlgo_OldX");
    QTest::addColumn<int>("MoveAlgo_OldY");
    QTest::addColumn<int>("MoveAlgo_NewX");
    QTest::addColumn<int>("MoveAlgo_NewY");
    //l'argument de newrow est le datatag
    QTest::newRow("newtest.PGN")  << 1 << 53 << int(eMoveAlgoANePasFaire) << 4 << 8 << 3 << 8;//menace fourchette
    QTest::newRow("newtest.PGN")  << 1 << 60 << int(eMoveAlgoANePasFaire) << 6 << 8 << 7 << 8;//menace mat couloir
    QTest::newRow("test.PGN")     << 1 << 29 << int(eMoveAlgoANePasFaire) << 7 << 8 << 8 << 8;//menace mat couloir
    QTest::newRow("todebug.PGN")  << 1 << 63 << int(eMoveAlgoAFaire)      << 6 << 7 << 5 << 8;//empeche promotion du pion
    QTest::newRow("debug1.PGN")   << 1 << 45 << int(eMoveAlgoAFaire)      << 6 << 2 << 5 << 1;//doit prendre gain de la Tour
    QTest::newRow("bugQueen.PGN") << 1 << 31 << int (eMoveAlgoBougePiece) << 7 << 6 << 0 << 0;//La Reine doit bouger car menacee!!!
    QTest::newRow("bugBishop.PGN") << 1 << 11 << int (eMoveAlgoBougePiece) << 3 << 5 << 0 << 0;//Le Fou doit bouger car menace!!!
}

