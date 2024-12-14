#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include "../include/troll_defence.h"
#include "../include/Money.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/Pentagon_02.h"
#include "../include/Hexagon_02.h"
#include "../include/Octagon_02.h"
#include "../include/NOWAY/darray_memory_resourse.h"
#include "../include/NOWAY/dynamic_array.h"
#include "../include/Factory.h"
#include "../include/Utils.h"
#include "../include/CombatVisitor.h"
#include "../include/Observer.h"
#include "../include/Elf.h"
#include "../include/Dragon.h"
#include "../include/Druid.h"
#include "NOWAY/CombatVisitor_v2.h"
#include "NOWAY/Observer_v2.h"
#include "NOWAY/MovementFightCoroutine.h"
#include "NOWAY/CoroutineHelpers.h"

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
struct ComplexType {
    int a;
    double b;
    std::string c;
};

TEST(DynamicArrayTest, PushBackAndAccess) {
    darray_memory_resource mr;
    DynamicArray<int> arr(&mr);
    arr.push_back(42);
    arr.push_back(100);
    ASSERT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], 42);
    EXPECT_EQ(arr[1], 100);
}

TEST(DynamicArrayTest, ComplexTypeTest) {
    darray_memory_resource mr;
    DynamicArray<ComplexType> arr(&mr);
    arr.push_back(ComplexType{1, 2.5, "hello"});
    arr.push_back(ComplexType{2, 3.5, "world"});
    ASSERT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0].a, 1);
    EXPECT_DOUBLE_EQ(arr[0].b, 2.5);
    EXPECT_EQ(arr[0].c, "hello");
    EXPECT_EQ(arr[1].a, 2);
    EXPECT_DOUBLE_EQ(arr[1].b, 3.5);
    EXPECT_EQ(arr[1].c, "world");
}

TEST(DynamicArrayTest, IteratorTest) {
    darray_memory_resource mr;
    DynamicArray<int> arr(&mr);
    for (int i = 0; i < 5; ++i) {
        arr.push_back(i);
    }
    int sum = 0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 0+1+2+3+4);
    EXPECT_EQ(std::distance(arr.begin(), arr.end()), 5);
}

//Тесты для шестой лабы
TEST(NPCTest, Creation) {
    NPC* elf = NPCFactory::CreateNPC("Elf", "Elvin", 10, 20);
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->GetType(), "Elf");
    EXPECT_EQ(elf->GetName(), "Elvin");
    EXPECT_EQ(elf->GetX(), 10);
    EXPECT_EQ(elf->GetY(), 20);
    EXPECT_TRUE(elf->IsAlive());
    delete elf;

    NPC* drg = NPCFactory::CreateNPC("Dragon", "Smaug", 100, 200);
    ASSERT_NE(drg, nullptr);
    EXPECT_EQ(drg->GetType(), "Dragon");
    EXPECT_EQ(drg->GetName(), "Smaug");
    EXPECT_EQ(drg->GetX(), 100);
    EXPECT_EQ(drg->GetY(), 200);
    EXPECT_TRUE(drg->IsAlive());
    delete drg;

    NPC* drd = NPCFactory::CreateNPC("Druid", "Greenie", 300, 400);
    ASSERT_NE(drd, nullptr);
    EXPECT_EQ(drd->GetType(), "Druid");
    EXPECT_EQ(drd->GetName(), "Greenie");
    EXPECT_EQ(drd->GetX(), 300);
    EXPECT_EQ(drd->GetY(), 400);
    EXPECT_TRUE(drd->IsAlive());
    delete drd;
}

TEST(CombatTest, FightScenario) {
    Subject subject;
    ConsoleLoggerObserver consoleObs;
    FileLoggerObserver fileObs;
    subject.Attach(&consoleObs);
    subject.Attach(&fileObs);

    std::vector<NPC*> npcs;
    npcs.push_back(NPCFactory::CreateNPC("Elf", "Elvin", 100, 100));
    npcs.push_back(NPCFactory::CreateNPC("Dragon", "Smaug", 105, 100));
    npcs.push_back(NPCFactory::CreateNPC("Druid", "Greenie", 200, 200));

    float fightRange = 10.0f;
    {
        CombatVisitor visitor(npcs, fightRange, subject);
        for (auto npc : npcs) {
            if (npc->IsAlive())
                npc->Accept(visitor);
        }
    }

    int aliveCount = 0;
    for (auto npc : npcs) {
        if (npc->IsAlive()) aliveCount++;
    }
    EXPECT_EQ(aliveCount, 1);
    bool greenieAlive = false;
    for (auto npc : npcs) {
        if (npc->GetName() == "Greenie" && npc->IsAlive()) {
            greenieAlive = true;
            break;
        }
    }
    EXPECT_TRUE(greenieAlive);

    for (auto npc : npcs) delete npc;
}

//Тесты седьмой лабы
// Тестовый Observer для проверки уведомлений
class TestObserver_v2 : public Observer_v2 {
public:
    std::vector<std::string> kills;
    void OnKill_v2(const std::string &killerType, const std::string &killerName,
                   const std::string &victimType, const std::string &victimName) override {
        kills.emplace_back(killerType + " " + killerName + " убил " + victimType + " " + victimName);
    }
};

// Тест 1: Проверка создания NPC через фабрику
TEST(NPCTest_v2, Creation) {
    NPC* elf = NPCFactory::CreateNPC("Elf", "Legolas", 10, 20);
    ASSERT_NE(elf, nullptr);
    EXPECT_EQ(elf->GetType(), "Elf");
    EXPECT_EQ(elf->GetName(), "Legolas");
    EXPECT_EQ(elf->GetX(), 10);
    EXPECT_EQ(elf->GetY(), 20);
    EXPECT_TRUE(elf->IsAlive());
    delete elf;

    NPC* dragon = NPCFactory::CreateNPC("Dragon", "Smaug", 0, 0);
    ASSERT_NE(dragon, nullptr);
    EXPECT_EQ(dragon->GetType(), "Dragon");
    EXPECT_EQ(dragon->GetName(), "Smaug");
    EXPECT_EQ(dragon->GetX(), 0);
    EXPECT_EQ(dragon->GetY(), 0);
    EXPECT_TRUE(dragon->IsAlive());
    delete dragon;

    NPC* druid = NPCFactory::CreateNPC("Druid", "Elune", 50, 99);
    ASSERT_NE(druid, nullptr);
    EXPECT_EQ(druid->GetType(), "Druid");
    EXPECT_EQ(druid->GetName(), "Elune");
    EXPECT_EQ(druid->GetX(), 50);
    EXPECT_EQ(druid->GetY(), 99);
    EXPECT_TRUE(druid->IsAlive());
    delete druid;
}

// Тест 2: Проверка перемещения NPC
TEST(NPCTest_v2, Movement) {
    NPC* elf = NPCFactory::CreateNPC("Elf", "Mover", 10, 20);
    elf->SetPosition(15, 25);
    EXPECT_EQ(elf->GetX(), 15);
    EXPECT_EQ(elf->GetY(), 25);
    delete elf;
}

// Тест 3: Проверка убийства NPC
TEST(NPCTest_v2, Kill) {
    NPC* elf = NPCFactory::CreateNPC("Elf", "Fallen", 10, 20);
    EXPECT_TRUE(elf->IsAlive());
    elf->Kill();
    EXPECT_FALSE(elf->IsAlive());
    delete elf;
}

// Тест 4: Проверка боя через CombatVisitor_v2
TEST(CombatTest_v2, BasicFight) {
    std::vector<NPC*> npcs;
    npcs.push_back(NPCFactory::CreateNPC("Elf", "Legolas", 10, 10));
    npcs.push_back(NPCFactory::CreateNPC("Druid", "Malfurion", 11, 10));

    Subject_v2 subject;
    TestObserver_v2 testObs;
    subject.Attach_v2(&testObs);

    CombatVisitor_v2 visitor(npcs, 3.0f, subject, cout_mutex_v2);

    npcs[0]->Accept(visitor);

    if (!npcs[1]->IsAlive()) {
        ASSERT_EQ(testObs.kills.size(), 1);
        EXPECT_EQ(testObs.kills[0], "Elf Legolas убил Druid Malfurion");
    }

    for (auto npc : npcs) {
        delete npc;
    }
}

// Тест 5: Проверка Observer при убийстве
TEST(CombatTest_v2, ObserverNotify) {
    std::vector<NPC*> npcs;
    npcs.push_back(NPCFactory::CreateNPC("Dragon", "Smaug", 10, 10));
    npcs.push_back(NPCFactory::CreateNPC("Elf", "Legolas", 11, 10));

    Subject_v2 subject;
    TestObserver_v2 testObs;
    subject.Attach_v2(&testObs);

    CombatVisitor_v2 visitor(npcs, 3.0f, subject, cout_mutex_v2);

    npcs[0]->Accept(visitor);

    if (!npcs[1]->IsAlive()) {
        ASSERT_EQ(testObs.kills.size(), 1);
        EXPECT_EQ(testObs.kills[0], "Dragon Smaug убил Elf Legolas");
    }

    for (auto npc : npcs) {
        delete npc;
    }
}

// Тест 6: Проверка корутины перемещения и боя
TEST(CoroutineTest_v2, MovementAndFight) {
    std::vector<NPC*> npcs;
    npcs.push_back(NPCFactory::CreateNPC("Elf", "Legolas", 10, 10));
    npcs.push_back(NPCFactory::CreateNPC("Dragon", "Smaug", 12, 10));
    npcs.push_back(NPCFactory::CreateNPC("Druid", "Malfurion", 15, 15));

    for (auto npc : npcs) {
        ASSERT_NE(npc, nullptr);
    }

    Subject_v2 subject;
    TestObserver_v2 testObs;
    subject.Attach_v2(&testObs);

    std::shared_mutex npcMutex;
    MovementFightCoroutine mfc(npcs, subject, cout_mutex_v2, npcMutex);

    auto generator = mfc.run();

    std::thread coroutineThread([&generator]() {
        while (generator.next()) {
        }
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    mfc.stopCoroutine();
    coroutineThread.join();

    {
        std::shared_lock<std::shared_mutex> lock(npcMutex);
        EXPECT_TRUE(npcs[0]->GetX() != 10 || npcs[0]->GetY() != 10);
        EXPECT_TRUE(npcs[1]->GetX() != 12 || npcs[1]->GetY() != 10);
        EXPECT_TRUE(npcs[2]->GetX() != 15 || npcs[2]->GetY() != 15);
    }

    for (auto npc : npcs) {
        delete npc;
    }

    SUCCEED();
}
