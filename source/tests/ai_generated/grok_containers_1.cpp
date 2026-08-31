/**
Model: Grok 4.5 Fast
Date: [2026-08-24 Mon 20:39]
*/

// ============================================================
//  array / linked_list API tests  (Catch2)  – corrected
//  Drop into (or next to) unity_catch2_core.cpp
// ============================================================

#include "include_tachyon_lib_core.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>
#include <catch2/catch_test_case_info.hpp>
using namespace tyon;


// ---------------------------------------------------------------------------
//  array<T>
// ---------------------------------------------------------------------------
TEST_CASE("array – construction & basic state", "[array]")
{
    SECTION("default construction")
    {
        array<i32> a;
        CHECK(a.size() == 0);
        CHECK(a.head_size == 0);
        CHECK(a.head == 0);
    }

    SECTION("initializer_list constructor")
    {
        array<i32> a{10, 20, 30, 40};
        CHECK(a.size() == 4);
        CHECK(a[0] == 10);
        CHECK(a[3] == 40);
        CHECK(a.head == 0);
    }

    SECTION("std::vector constructor")
    {
        std::vector<i32> src{1, 2, 3};
        array<i32> a(src);
        CHECK(a.size() == 3);
        CHECK(a[0] == 1);
        CHECK(a[2] == 3);
    }
}

TEST_CASE("array – change_allocation / resize / reserve", "[array]")
{
    array<i32> a;

    SECTION("change_allocation grows capacity")
    {
        REQUIRE(a.change_allocation(8));
        CHECK(a.size_ >= 8);
        CHECK(a.size() == 0);
        CHECK(a.head_size == 0);
    }

    SECTION("resize sets both capacity and logical size")
    {
        a.resize(5);
        CHECK(a.size() == 5);
        CHECK(a.size_ >= 5);
        for (i64 i = 0; i < a.size(); ++i)
            CHECK(a[i] == 0);
    }

    SECTION("reserve only affects capacity")
    {
        a.reserve(16);
        CHECK(a.size() == 0);
        CHECK(a.size_ >= 16);
    }

    SECTION("growing then shrinking (capacity first)")
    {
        a.resize(10);
        for (i64 i = 0; i < 10; ++i) a[i] = i32(i);
        a.resize(4);
        CHECK(a.size() == 4);
        CHECK(a[0] == 0);
        CHECK(a[3] == 3);
    }
}

TEST_CASE("array – push_tail / pop_tail / access", "[array]")
{
    array<i32> a;
    a.reserve(16);                     // capacity first

    SECTION("push_tail sequence")
    {
        a.push_tail(100);
        a.push_tail(200);
        a.push_tail(300);
        CHECK(a.size() == 3);
        CHECK(a[0] == 100);
        CHECK(a[1] == 200);
        CHECK(a[2] == 300);
        CHECK(a.tail() == 300);
        CHECK(a.tail_index() == 2);
    }

    SECTION("pop_tail")
    {
        a = {11, 22, 33, 44};           // initializer already sizes
        auto r1 = a.pop_tail();
        CHECK_FALSE(r1.error);
        CHECK(r1.value == 44);
        CHECK(a.size() == 3);

        auto r2 = a.pop_tail();
        CHECK(r2.value == 33);
        CHECK(a.size() == 2);

        a.pop_tail();
        a.pop_tail();
        auto empty = a.pop_tail();
        CHECK(empty.error);
    }

    SECTION("operator[] and address")
    {
        a = {5, 15, 25};
        CHECK(a[1] == 15);
        a[1] = 99;
        CHECK(a[1] == 99);
        CHECK(a.address(1) == &a[1]);
    }

    SECTION("push_back aliases")
    {
        a.push_back(7);
        a.push_back(8);
        CHECK(a.size() == 2);
        CHECK(a[1] == 8);
    }
}

TEST_CASE("array – search & iteration helpers", "[array]")
{
    array<i32> a{10, 20, 30, 40, 50};

    SECTION("linear_search with predicate")
    {
        auto r = a.linear_search([](i32 v){ return v == 30; });
        CHECK(r.match_found);
        CHECK(r.index == 2);
        CHECK(*r.match == 30);

        auto miss = a.linear_search([](i32 v){ return v == 999; });
        CHECK_FALSE(miss.match_found);
        CHECK(miss.index == linked_list_sentinel);
    }

    SECTION("linear_search_value")
    {
        auto r = a.linear_search_value(40);
        CHECK(r.match_found);
        CHECK(r.index == 3);
        CHECK(*r.match == 40);
    }

    SECTION("map_procedure")
    {
        i32 sum = 0;
        a.map_procedure([&](i32& v){ sum += v; });
        CHECK(sum == 150);
    }

    SECTION("map_procedure_indexed")
    {
        i32 checksum = 0;
        a.map_procedure_indexed([&](i32 v, i64 idx){ checksum += v * i32(idx); });
        CHECK(checksum == 0*10 + 1*20 + 2*30 + 3*40 + 4*50);
    }
}

TEST_CASE("array – copy assignment", "[array]")
{
    array<i32> src{1, 2, 3, 4};
    array<i32> dst;
    dst = src;
    CHECK(dst.size() == src.size());
    CHECK(dst[0] == 1);
    CHECK(dst[3] == 4);
    dst[0] = 99;
    CHECK(src[0] == 1);
}

// ---------------------------------------------------------------------------
//  linked_list<T>   – ALWAYS resize before obtaining node pointers
// ---------------------------------------------------------------------------
TEST_CASE("linked_list – construction & empty state", "[linked_list]")
{
    linked_list<i32> list;
    CHECK(list.size() == 0);
    CHECK(list.head_ < 0);
    CHECK(list.tail_ < 0);
}

TEST_CASE("linked_list – push_tail & basic linking", "[linked_list]")
{
    linked_list<i32> list;
    list.resize(8);                    // capacity first – no later invalidation

    SECTION("single node")
    {
        auto* n = list.push_tail(42);
        REQUIRE(n != nullptr);
        CHECK(list.size() == 1);
        CHECK(list.head_ == list.tail_);
        CHECK(n->value == 42);
        CHECK(n->prev == linked_list_sentinel);
        CHECK(n->next == linked_list_sentinel);
        CHECK(list.head()->value == 42);
        CHECK(list.tail()->value == 42);
    }

    SECTION("three nodes – correct prev/next")
    {
        auto* n1 = list.push_tail(10);
        auto* n2 = list.push_tail(20);
        auto* n3 = list.push_tail(30);

        CHECK(list.size() == 3);
        CHECK(list.head()->value == 10);
        CHECK(list.tail()->value == 30);

        CHECK(n1->prev == linked_list_sentinel);
        CHECK(n1->next == n2->index);
        CHECK(n2->prev == n1->index);
        CHECK(n2->next == n3->index);
        CHECK(n3->prev == n2->index);
        CHECK(n3->next == linked_list_sentinel);
    }
}

TEST_CASE("linked_list – operator[] (index from head)", "[linked_list]")
{
    linked_list<i32> list;
    list.resize(8);

    list.push_tail(100);
    list.push_tail(200);
    list.push_tail(300);

    auto r0 = list[0];
    REQUIRE_FALSE(r0.error);
    CHECK(r0.value->value == 100);

    auto r1 = list[1];
    REQUIRE_FALSE(r1.error);
    CHECK(r1.value->value == 200);

    auto r2 = list[2];
    REQUIRE_FALSE(r2.error);
    CHECK(r2.value->value == 300);

    auto bad = list[5];
    CHECK(bad.error);
}

TEST_CASE("linked_list – insert_after / insert_before", "[linked_list]")
{
    linked_list<i32> list;
    list.resize(8);

    auto* a = list.push_tail(1);
    auto* c = list.push_tail(3);

    SECTION("insert_after")
    {
        auto* b = list.insert_after(a, 2);
        CHECK(list.size() == 3);
        // prefer index checks
        CHECK(list[0].value->value == 1);
        CHECK(list[1].value->value == 2);
        CHECK(list[2].value->value == 3);

        CHECK(a->next == b->index);
        CHECK(b->prev == a->index);
        CHECK(b->next == c->index);
        CHECK(c->prev == b->index);
    }

    SECTION("insert_before")
    {
        linked_list<i32> list2;
        list2.resize(8);
        auto* x = list2.push_tail(10);
        auto* z = list2.push_tail(30);
        auto* y = list2.insert_before(z, 20);

        CHECK(list2.size() == 3);
        CHECK(list2[0].value->value == 10);
        CHECK(list2[1].value->value == 20);
        CHECK(list2[2].value->value == 30);
    }
}

TEST_CASE("linked_list – remove_node", "[linked_list]")
{
    linked_list<i32> list;
    list.resize(8);

    TYON_BREAK();
    auto* n1 = list.push_tail(1);
    auto* n2 = list.push_tail(2);
    auto* n3 = list.push_tail(3);
    auto* n4 = list.push_tail(4);

    SECTION("remove middle")
    {
        TYON_BREAK();
        list.remove_node(n2);
        CHECK(list.size() == 3);
        CHECK(list[0].value->value == 1);
        CHECK(list[1].value->value == 3);
        CHECK(list[2].value->value == 4);
        CHECK(n1->next == n3->index);
        CHECK(n3->prev == n1->index);
    }

    SECTION("remove head")
    {
        list.remove_node(n1);
        CHECK(list.size() == 3);
        CHECK(list.head()->value == 2);
        CHECK(list.head()->prev == linked_list_sentinel);
    }

    SECTION("remove tail")
    {
        list.remove_node(n4);
        CHECK(list.size() == 3);
        CHECK(list.tail()->value == 3);
        CHECK(list.tail()->next == linked_list_sentinel);
    }

    SECTION("remove last remaining node")
    {
        linked_list<i32> one;
        one.resize(4);
        auto* only = one.push_tail(99);
        one.remove_node(only);
        CHECK(one.size() == 0);
        CHECK(one.head_ == 0);
        CHECK(one.tail_ == 0);
    }
}

TEST_CASE("linked_list – free-list behaviour (intended)", "[linked_list]")
{
    linked_list<i32> list;
    list.resize(8);                    // enough room for all operations

    auto* a = list.push_tail(1);
    auto* b = list.push_tail(2);
    auto* c = list.push_tail(3);

    list.remove_node(b);               // returns node to free list
    auto* d = list.push_tail(4);       // may reuse a free slot

    CHECK(list.size() == 3);
    // values via index (safe)
    CHECK(list[0].value->value == 1);
    CHECK(list[1].value->value == 3);
    CHECK(list[2].value->value == 4);
}

TEST_CASE("linked_list – resize / size_grow", "[linked_list]")
{
    linked_list<i32> list;
    list.resize(32);                   // pre-allocate node storage
    CHECK(list.nodes.size() >= 32);

    for (i32 i = 0; i < 20; ++i)
        list.push_tail(i);

    CHECK(list.size() == 20);
    CHECK(list[0].value->value == 0);
    CHECK(list[19].value->value == 19);
}
