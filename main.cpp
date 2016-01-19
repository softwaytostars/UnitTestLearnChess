#include "UnitTestPGNReaderWriter.h"
#include "unittestalgocomputer.h"

int main(int argc, char *argv[])
{

    UnitTestPGNReaderWriter test1;
    QTest::qExec(&test1, argc, argv);

    UnitTestAlgoComputer test2;
    QTest::qExec(&test2, argc, argv);

    return 0;
}
