// test_main.cpp 测试入口

#include <QApplication>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "src/ut_qtest.h"
#include "src/moduls/ut_basicmodul.h"

#include <QTest>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
