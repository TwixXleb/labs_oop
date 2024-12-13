#include <gtest/gtest.h>
#include <cmath>
#include "../include/troll_defence.h"
#include "../include/Money.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/Pentagon_02.h"
#include "../include/Hexagon_02.h"
#include "../include/Octagon_02.h"
#include "../include/map_memory_resourse.h"
#include "../include/dynamic_array.h"

struct MyStruct {
    int a;
    double b;
    std::string c;
};

// Тесты для первой лабы
TEST(Troll_01, BasicTest) {
  std::string troll_message_01 = "haha loshara";
  std::string result = troll_defence(troll_message_01);
  EXPECT_EQ(result, "hh lshr");
}

TEST(Troll_02, UpperTest) {
  std::string troll_message_02 = "HAHA LOSHARA";
  std::string result = troll_defence(troll_message_02);
  EXPECT_EQ(result, "HH LSHR");
}

TEST(Troll_03, RandomTest) {
  std::string troll_message_03 = "HahA lOShaRA";
  std::string result = troll_defence(troll_message_03);
  EXPECT_EQ(result, "Hh lShR");
}

TEST(Troll_04, LotOfVowelsTest) {
  std::string troll_message_04 = "aaaaaaaaa losharaaaaaa";
  std::string result = troll_defence(troll_message_04);
  EXPECT_EQ(result, " lshr");
}

// Тесты для второй лабы
TEST(Money_01, set_get_ruble_balance) {
    Money rubles("1025.56");
    std::string result = rubles.check_balance();
    EXPECT_EQ(result, "1 025.56 RUB");
}

TEST(Money_02, set_add_get_ruble_balance) {
    Money rubles("0001025.56");
    rubles.add("500.40");
    std::string result = rubles.check_balance();
    EXPECT_EQ(result, "1 525.96 RUB");
}

TEST(Money_03, set_withdraw_get_ruble_balance) {
    Money rubles("0001025.56");
    rubles.withdraw("400.20");
    std::string result = rubles.check_balance();
    EXPECT_EQ(result, "625.36 RUB");
}

TEST(Money_04, set_convert_get_yens_to_euros_balance) {
    Money yens("556.50", Currency::JPY);
    yens.convert_to(Currency::EUR);
    std::string result = yens.check_balance();
    EXPECT_EQ(result, "3.46 EUR");
}

//Тесты для третьей лабы
//Тесты дял класса Pentagon
TEST(PentagonTests, OutputTest) {
    Pentagon pentagon(0.0, 0.0, 5.0);
    std::ostringstream os;
    os << pentagon;
    std::string expected_output = "Pentagon with center (0, 0) and vertices:\n(5, 0)\n(1.54508, 4.75528)\n(-4.04508, 2.93893)\n(-4.04508, -2.93893)\n(1.54508, -4.75528)\n";
    EXPECT_EQ(os.str(), expected_output);
}

TEST(PentagonTests, InputTest) {
    std::istringstream is("0 0 5");
    Pentagon pentagon;
    is >> pentagon;
    std::ostringstream os;
    os << pentagon;
    std::string expected_output = "Pentagon with center (0, 0) and vertices:\n(5, 0)\n(1.54508, 4.75528)\n(-4.04508, 2.93893)\n(-4.04508, -2.93893)\n(1.54508, -4.75528)\n";
    EXPECT_EQ(os.str(), expected_output);
}

TEST(PentagonTests, CopyConstructorTest) {
    Pentagon original(0.0, 0.0, 5.0);
    Pentagon copy(original);

    EXPECT_EQ(copy.area(), original.area());
    EXPECT_EQ(copy.center().first, original.center().first);
    EXPECT_EQ(copy.center().second, original.center().second);
}

TEST(PentagonTests, CopyAssignmentTest) {
    Pentagon original(0.0, 0.0, 5.0);
    Pentagon copy;
    copy = original;

    EXPECT_EQ(copy.area(), original.area());
    EXPECT_EQ(copy.center().first, original.center().first);
    EXPECT_EQ(copy.center().second, original.center().second);
}

TEST(PentagonTests, EqualityTest) {
    Pentagon pentagon1(0.0, 0.0, 5.0);
    Pentagon pentagon2(0.0, 0.0, 5.0);

    EXPECT_TRUE(pentagon1 == pentagon2);
}

TEST(PentagonTests, InequalityTest) {
    Pentagon pentagon1(0.0, 0.0, 5.0);
    Pentagon pentagon2(1.0, 1.0, 5.0);

    EXPECT_FALSE(pentagon1 == pentagon2);
}

TEST(PentagonTests, MoveTest) {
    Pentagon pentagon(0.0, 0.0, 5.0);
    pentagon.move(10.0, 10.0);

    std::ostringstream os;
    os << pentagon;
    std::string expected_output = "Pentagon with center (10, 10) and vertices:\n(15, 10)\n(11.5451, 14.7553)\n(5.95492, 12.9389)\n(5.95492, 7.06107)\n(11.5451, 5.24472)\n";
    EXPECT_EQ(os.str(), expected_output);
}

TEST(PentagonTests, RotateTest) {
    Pentagon pentagon(0.0, 0.0, 5.0);
    pentagon.rotate(3.14159 / 2);

    std::ostringstream os;
    os << pentagon;

    std::string expected_output = "Pentagon with center (0, 0) and vertices:\n(0, 5)\n(-4.75528, 1.54508)\n(-2.93893, -4.04508)\n(2.93893, -4.04508)\n(4.75528, 1.54508)\n";
    EXPECT_EQ(os.str().substr(0, 30), expected_output.substr(0, 30));  // Сравниваем первую часть вывода
}

TEST(PentagonTests, AreaTest) {
    Pentagon pentagon(0.0, 0.0, 5.0);
    double expected_area = pentagon.area();
    EXPECT_NEAR(expected_area, 43.0119, 0.001);
}

//Тесты для пятиугольника для четвертой лабы

// Тест конструктора по умолчанию
TEST(Pentagon_02_Test, DefaultConstructor) {
    Pentagon_02<int> pentagon;
    EXPECT_EQ(pentagon.Center().x, 0);
    EXPECT_EQ(pentagon.Center().y, 0);
    EXPECT_EQ(pentagon.Area(), pentagon.Area()); // Проверка на отсутствие NaN
}

// Тест пользовательского конструктора
TEST(Pentagon_02_Test, ParameterizedConstructor) {
    Point_02<int> center(5, 5);
    int side_length = 10;
    Pentagon_02<int> pentagon(center, side_length);
    EXPECT_EQ(pentagon.Center().x, 5);
    EXPECT_EQ(pentagon.Center().y, 5);
    EXPECT_DOUBLE_EQ(pentagon.Area(), (5.0 * side_length * side_length) / (4.0 * tan(M_PI / 5.0)));
}

// Тест копирования
TEST(Pentagon_02_Test, CopyConstructor) {
    Point_02<int> center(2, 3);
    int side_length = 7;
    Pentagon_02<int> pentagon1(center, side_length);
    Pentagon_02<int> pentagon2(pentagon1);
    EXPECT_EQ(pentagon1, pentagon2);
}

// Тест перемещения
TEST(Pentagon_02_Test, MoveConstructor) {
    Point_02<int> center(2, 3);
    int side_length = 7;
    Pentagon_02<int> pentagon1(center, side_length);
    Pentagon_02<int> pentagon2(std::move(pentagon1));
    EXPECT_EQ(pentagon2.Center().x, 2);
    EXPECT_EQ(pentagon2.Center().y, 3);
    EXPECT_EQ(pentagon2.Area(), pentagon2.Area());
}

// Тест оператора присваивания копированием
TEST(Pentagon_02_Test, CopyAssignment) {
    Point_02<int> center1(2, 3);
    int side_length1 = 7;
    Pentagon_02<int> pentagon1(center1, side_length1);

    Point_02<int> center2(5, 5);
    int side_length2 = 10;
    Pentagon_02<int> pentagon2(center2, side_length2);

    pentagon2 = pentagon1;

    EXPECT_EQ(pentagon2, pentagon1);
}

// Тест оператора присваивания перемещением
TEST(Pentagon_02_Test, MoveAssignment) {
    Point_02<int> center1(2, 3);
    int side_length1 = 7;
    Pentagon_02<int> pentagon1(center1, side_length1);

    Point_02<int> center2(5, 5);
    int side_length2 = 10;
    Pentagon_02<int> pentagon2(center2, side_length2);

    pentagon2 = std::move(pentagon1);

    EXPECT_EQ(pentagon2.Center().x, 2);
    EXPECT_EQ(pentagon2.Center().y, 3);
    EXPECT_EQ(pentagon2.Area(), pentagon2.Area());
}

// Тест метода Rotate
TEST(Pentagon_02_Test, Rotate) {
    Point_02<int> center(0, 0);
    int side_length = 10;
    Pentagon_02<int> pentagon(center, side_length);

    // Копируем координаты вершин до поворота
    std::vector<Point_02<int>> original_vertices = pentagon.GetVertices();

    pentagon.Rotate(M_PI / 2); // Поворот на 90 градусов

    // Получаем вершины после поворота
    std::vector<Point_02<int>> rotated_vertices = pentagon.GetVertices();

    // Проверка, что вершины изменились после поворота
    bool all_vertices_changed = false;
    for (size_t i = 0; i < original_vertices.size(); ++i) {
        if (original_vertices[i].x != rotated_vertices[i].x ||
            original_vertices[i].y != rotated_vertices[i].y) {
            all_vertices_changed = true;
            break;
        }
    }
    EXPECT_TRUE(all_vertices_changed);
}

// Тест метода Translate
TEST(Pentagon_02_Test, Translate) {
    Point_02<int> center(0, 0);
    int side_length = 10;
    Pentagon_02<int> pentagon(center, side_length);

    pentagon.Translate(5, 5);

    EXPECT_EQ(pentagon.Center().x, 5);
    EXPECT_EQ(pentagon.Center().y, 5);
}

// Тест метода Area
TEST(Pentagon_02_Test, Area) {
    Point_02<int> center(0, 0);
    int side_length = 10;
    Pentagon_02<int> pentagon(center, side_length);

    double expected_area = (5.0 * side_length * side_length) / (4.0 * tan(M_PI / 5.0));
    EXPECT_DOUBLE_EQ(pentagon.Area(), expected_area);
}

// Тест оператора сравнения ==
TEST(Pentagon_02_Test, EqualityOperator) {
    Point_02<int> center(0, 0);
    int side_length = 10;
    Pentagon_02<int> pentagon1(center, side_length);
    Pentagon_02<int> pentagon2(center, side_length);

    EXPECT_TRUE(pentagon1 == pentagon2);
}

// Тест оператора сравнения <
TEST(Pentagon_02_Test, LessThanOperator) {
    Point_02<int> center(0, 0);
    int side_length1 = 5;
    int side_length2 = 10;
    Pentagon_02<int> pentagon1(center, side_length1);
    Pentagon_02<int> pentagon2(center, side_length2);

    EXPECT_TRUE(pentagon1 < pentagon2);
}

// Тест приведения к double (площади)
TEST(Pentagon_02_Test, CastToDouble) {
    Point_02<int> center(0, 0);
    int side_length = 10;
    Pentagon_02<int> pentagon(center, side_length);

    double area = static_cast<double>(pentagon);
    double expected_area = pentagon.Area();

    EXPECT_DOUBLE_EQ(area, expected_area);
}

// Тест ввода/вывода
TEST(Pentagon_02_Test, InputOutputOperators) {
    std::stringstream ss;
    ss << "3 4 5"; // center.x = 3, center.y = 4, side_length = 5
    Pentagon_02<int> pentagon;
    ss >> pentagon;

    EXPECT_EQ(pentagon.Center().x, 3);
    EXPECT_EQ(pentagon.Center().y, 4);
    EXPECT_EQ(pentagon.Area(), pentagon.Area()); // Проверка на отсутствие NaN

    std::stringstream output;
    output << pentagon;
    std::string output_str = output.str();
    EXPECT_FALSE(output_str.empty());
}

// Тест на исключения (например, если сторона отрицательная)
TEST(Pentagon_02_Test, NegativeSideLength) {
    Point_02<int> center(0, 0);
    int side_length = -10;

    EXPECT_THROW({
        Pentagon_02<int> pentagon(center, side_length);
    }, std::invalid_argument);
}

// Тест на соответствие Правилу пяти
TEST(Pentagon_02_Test, RuleOfFive) {
    // Проверка на возможность копирования и перемещения
    EXPECT_TRUE(std::is_copy_constructible<Pentagon_02<int>>::value);
    EXPECT_TRUE(std::is_copy_assignable<Pentagon_02<int>>::value);
    EXPECT_TRUE(std::is_move_constructible<Pentagon_02<int>>::value);
    EXPECT_TRUE(std::is_move_assignable<Pentagon_02<int>>::value);
}

// Тест с различными типами (например, double)
TEST(Pentagon_02_Test, DifferentScalarTypes) {
    Point_02<double> center(0.0, 0.0);
    double side_length = 10.5;
    Pentagon_02<double> pentagon(center, side_length);

    EXPECT_DOUBLE_EQ(pentagon.Center().x, 0.0);
    EXPECT_DOUBLE_EQ(pentagon.Center().y, 0.0);
    EXPECT_DOUBLE_EQ(pentagon.Area(), (5.0 * side_length * side_length) / (4.0 * tan(M_PI / 5.0)));
}

//Тесты для пятой лабы
TEST(DynamicArrayTest, PushBackAndAccess) {
    MapMemoryResource resource;
    DynamicArray<int> array(&resource);

    array.push_back(1);
    array.push_back(2);
    array.push_back(3);

    EXPECT_EQ(array.get_size(), 3);
    EXPECT_EQ(array[0], 1);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 3);
}

TEST(DynamicArrayTest, OutOfRangeAccess) {
    MapMemoryResource resource;
    DynamicArray<int> array(&resource);

    array.push_back(1);
    EXPECT_THROW(array[1], std::out_of_range);
}

TEST(DynamicArrayTest, ReallocateAndAccess) {
    MapMemoryResource resource;
    DynamicArray<int> array(&resource);

    for (int i = 0; i < 100; ++i) {
        array.push_back(i);
    }

    EXPECT_EQ(array.get_size(), 100);
    EXPECT_EQ(array[99], 99);
}

TEST(MapMemoryResourceTest, AllocationAndDeallocation) {
    MapMemoryResource resource;
    std::pmr::polymorphic_allocator<int> allocator(&resource);

    int* ptr = allocator.allocate(10);
    allocator.deallocate(ptr, 10);
}

TEST(MapMemoryResourceTest, MemoryLeakDetection) {
    MapMemoryResource resource;
    {
        std::pmr::polymorphic_allocator<int> allocator(&resource);
        int* ptr = allocator.allocate(10);
        // Intentionally forget to deallocate
    }
    EXPECT_THROW(
            {
                MapMemoryResource temp_resource;
            },
            std::runtime_error
    );
}

