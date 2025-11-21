#include <gtest/gtest.h>
#include <memory>

#include "Point.hpp"
#include "Rhombus.hpp"
#include "Pentagon.hpp"
#include "Hexagon.hpp"
#include "Vector.hpp"

// =====================================================
//                     Rhombus Tests
// =====================================================
TEST(RhombusTest, AreaAndCenter) {
    Rhombus<double> r({ {0,0}, {1,0}, {1,1}, {0,1} }); // допустим пример ромба
    double area = static_cast<double>(r);
    ASSERT_NEAR(area, 1, 1e-9);

    Point<double> c = r.center();
    ASSERT_NEAR(c.getX(), 0.5, 1e-9);
    ASSERT_NEAR(c.getY(), 0.5, 1e-9);
}

TEST(RhombusTest, InvalidThrows) {
    EXPECT_THROW(Rhombus<double>({ {0,0}, {2,0}, {1,1}, {0,1} }), std::runtime_error);
}

// =====================================================
//                     Pentagon Tests
// =====================================================
TEST(PentagonTest, AreaAndCenter) {
    Pentagon<double> p({ {1,0}, {5,0}, {6,2}, {3,4}, {0,2} });
    double area = static_cast<double>(p);
    ASSERT_NEAR(area, 16.0, 1e-9);

    Point<double> c = p.center();
    ASSERT_NEAR(c.getX(), 3, 1e-9);
    ASSERT_NEAR(c.getY(),  1.6666666666666667, 1e-9);
}

TEST(PentagonTest, InvalidThrows) {
    EXPECT_THROW(Pentagon<double>({ {0,0}, {1,0}, {1,1}, {0,1} }), std::runtime_error);
}

// =====================================================
//                     Hexagon Tests
// =====================================================
TEST(HexagonTest, AreaAndCenter) {
    Hexagon<double> h({ {0,0}, {1,0}, {2,1}, {1,2}, {0,2}, {-1,1} });
    double area = static_cast<double>(h);
    ASSERT_GT(area, 0.0);

    Point<double> c = h.center();
    ASSERT_NEAR(c.getX(), 0.5, 1e-9);
    ASSERT_NEAR(c.getY(), 1.0, 1e-9);
}

TEST(HexagonTest, InvalidThrows) {
    EXPECT_THROW(Hexagon<double>({ {0,0}, {1,0}, {1,1} }), std::runtime_error);
}

// =====================================================
//                     Vector Tests
// =====================================================
TEST(VectorTest, PushBackAndLength) {
    Vector<double> vec;
    vec.pushBack(std::make_shared<Rhombus<double>>(Rhombus<double>({ {0,0}, {1,0}, {1,1}, {0,1} })));
    vec.pushBack(std::make_shared<Pentagon<double>>(Pentagon<double>({ {0,0}, {1,0}, {1.5,1}, {0.5,2}, {-0.5,1} })));
    vec.pushBack(std::make_shared<Hexagon<double>>(Hexagon<double>({ {0,0}, {1,0}, {2,1}, {1,2}, {0,2}, {-1,1} })));

    ASSERT_EQ(vec.length(), 3);
}

TEST(VectorTest, AllAreaSum) {
    Vector<double> vec;
    vec.pushBack(std::make_shared<Rhombus<double>>(Rhombus<double>({ {0,0}, {1,0}, {1,1}, {0,1} })));
    vec.pushBack(std::make_shared<Pentagon<double>>(Pentagon<double>({ {0,0}, {1,0}, {1.5,1}, {0.5,2}, {-0.5,1} })));
    vec.pushBack(std::make_shared<Hexagon<double>>(Hexagon<double>({ {0,0}, {1,0}, {2,1}, {1,2}, {0,2}, {-1,1} })));

    double totalArea = vec.allArea();
    ASSERT_GT(totalArea, 0.0);
}

TEST(VectorTest, PopRemovesElement) {
    Vector<double> vec;
    vec.pushBack(std::make_shared<Rhombus<double>>(Rhombus<double>({ {0,0}, {1,0}, {1,1}, {0,1} })));
    vec.pushBack(std::make_shared<Pentagon<double>>(Pentagon<double>({ {0,0}, {1,0}, {1.5,1}, {0.5,2}, {-0.5,1} })));

    ASSERT_EQ(vec.length(), 2);
    vec.pop(0);
    ASSERT_EQ(vec.length(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
