#include "UnitTestPGNReaderWriter.h"

#include "ChessBoardManager/commandplay.h"

UnitTestPGNReaderWriter::UnitTestPGNReaderWriter():
    _pgn (0),
    _ChessManager (true),
    _CRepFiles ("/home/alexis/UnitTestLearnChess/PGNFiles/")
{
}

UnitTestPGNReaderWriter::~UnitTestPGNReaderWriter() {

    InitializeGame (false);
    if (_pgn)
        delete _pgn;
}

void UnitTestPGNReaderWriter::InitializeGame(bool aCreationPiece) {

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

void UnitTestPGNReaderWriter::init()
{
}

void UnitTestPGNReaderWriter::cleanup()
{
    if (_pgn) {
        delete _pgn;
        _pgn = 0;
    }
}

void UnitTestPGNReaderWriter::testRead()
{
   _pgn = new PGNReaderWriter (_CRepFiles+QString (QTest::currentDataTag()));

    QVERIFY2((_pgn != 0), "Fail instance PGNReaderWriter");

    QFETCH(int, NoPartie);
    QFETCH(int, NbDemiCoupsLusAttendus);

    _pgn->LoadGame(*this, NoPartie);
    QString lMessage = QString ("Fail mauvais nbre demi-coups %1 != %2").arg(QString("%1").arg(_ListCommandesPlay.count()),
                                                                             QString("%1").arg(NbDemiCoupsLusAttendus));
    QVERIFY2( (NbDemiCoupsLusAttendus = _ListCommandesPlay.count()), lMessage.toStdString().c_str());
}

//definit le data set
void UnitTestPGNReaderWriter::testRead_data()
{
    QTest::addColumn<int>("NoPartie");
    QTest::addColumn<int>("NbDemiCoupsLusAttendus");
    //l'argument de newrow est le datatag
    QTest::newRow("Tal1.PGN") << 1 << 65;
    QTest::newRow("Tal2.PGN") << 1 << 36;
    QTest::newRow("Tal3.PGN") << 1 << 31;
    //TalSum est la somme de T&, Tal2 et Tal3
    QTest::newRow("TalSum.PGN") << 1 << 65;
    QTest::newRow("TalSum.PGN") << 2 << 36;
    QTest::newRow("TalSum.PGN") << 3 << 31;
    QTest::newRow("ExampleGame3.PGN") << 1 << 57;
    QTest::newRow("ExampleGame6.PGN") << 1 << 81;
    QTest::newRow("ExampleGame7.PGN") << 1 << 57;
    QTest::newRow("ExampleGame11.PGN") << 1 << 89;
    QTest::newRow("ExampleGame12.PGN") << 1 << 33;
    QTest::newRow("ExampleGame15.PGN") << 1 << 56;
    QTest::newRow("ExampleGame16.PGN") << 1 << 33;
    QTest::newRow("ExampleGame19.PGN") << 1 << 33;
    QTest::newRow("Anderssen1.PGN") << 1 << 100;
    QTest::newRow("Alekhine1.PGN") << 1 << 106;
    QTest::newRow("Alekhine4.PGN") << 1 << 21;
    QTest::newRow("Alekhine6.PGN") << 1 << 57;
    QTest::newRow("Alekhine7.PGN") << 1 << 132;
    QTest::newRow("Alekhine8.PGN") << 1 << 29;
    QTest::newRow("Alekhine9.PGN") << 1 << 75;
}

void UnitTestPGNReaderWriter::testWrite() {

    const QString CNameFileTest = "TestFusion.PGN";

    QFile::remove(CNameFileTest);

    QVector <QString> lNomsFichiers;
    lNomsFichiers.push_back("Alekhine1.PGN");
    lNomsFichiers.push_back("Alekhine4.PGN");
    lNomsFichiers.push_back("Alekhine6.PGN");
    lNomsFichiers.push_back("ExampleGame19.PGN");

    QVector <sDataTypeEntete> lEntetesParties;
    QVector <int> lNbreDemiCoupsParties;

    for (int iFichier=0; iFichier < lNomsFichiers.count(); iFichier++) {

        //lit le fichier
        _pgn = new PGNReaderWriter (_CRepFiles+lNomsFichiers[iFichier]);
        _pgn->LoadGame(*this, 1);

        lEntetesParties.push_back(sDataTypeEntete (_pgn->getEvent(),
                                                           _pgn->getSite(),
                                                           _pgn->getRound(),
                                                           _pgn->getDate(),
                                                           _pgn->getWhiteName(),
                                                           _pgn->getBlackName(),
                                                           _pgn->getWhiteELO(),
                                                           _pgn->getBlackELO(),
                                                           _pgn->getResultat()));

        lNbreDemiCoupsParties.push_back(_ListCommandesPlay.count());
        //l'ecrit dans CNameFileTest
        _pgn->WriteGame (CNameFileTest, lEntetesParties [lEntetesParties.count()-1], _ListCommandesPlay);
        delete _pgn;

    }//for (int iFichier


    //maintenant verifie toutes les infos à la lecture
    _pgn = new PGNReaderWriter (CNameFileTest);
    QVERIFY2 (_pgn->NbreGames() == lEntetesParties.count(), "Manque des parties");

    //lit premier fichier
    for (int LnoPartie= 1; LnoPartie <= _pgn->NbreGames(); LnoPartie++) {

        _pgn->LoadGame(*this, LnoPartie);
        sDataTypeEntete lEntete (_pgn->getEvent(),
                                 _pgn->getSite(),
                                 _pgn->getRound(),
                                 _pgn->getDate(),
                                 _pgn->getWhiteName(),
                                 _pgn->getBlackName(),
                                 _pgn->getWhiteELO(),
                                 _pgn->getBlackELO(),
                                 _pgn->getResultat());
        //verif des entetes
        QString lMessage = QString ("entetes differentes partie No: %1").arg(LnoPartie);
        QVERIFY2 (lEntete == lEntetesParties [LnoPartie-1], lMessage.toStdString().c_str());
        //verif nbre coups
        lMessage = QString ("Nbre demi-coups differents pour partie %1 : %2 != %3").arg(QString("%1").arg(LnoPartie),
                                                                                        QString("%1").arg(_ListCommandesPlay.count()),
                                                                                        QString("%1").arg(lNbreDemiCoupsParties [LnoPartie-1]));
        QVERIFY2 (_ListCommandesPlay.count() == lNbreDemiCoupsParties [LnoPartie-1], lMessage.toStdString().c_str());
    }
    bool lRemove = QFile::remove(CNameFileTest);
    QVERIFY2( lRemove, "fichier temporaire pas detruit!");

}

