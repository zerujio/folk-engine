//
// Created by sergio on 28-01-22.
//

#include "catch.hpp"

#include "folk/log.hpp"
#include "folk/utils/exception_handler.hpp"

void inc(int& px) {
    px++;
}

TEST_CASE("ExceptionHandler")
{
    using namespace Folk;

    ScopedInitializer<Log> log_init{LogLevel::Trace};
    ExceptionHandler handler {};

    SECTION("throwException") {
        handler.throwException<std::logic_error>("This is a dummy exception");
        handler.throwException<int>();
    }

    SECTION("catchException") {
        try {
            throw 1;
        } catch (...) {
            handler.catchException();
        }

        try {
            throw Error("Hello!");
        } catch (...) {
            handler.catchException();
        }
    }

    SECTION("handleException") {
        try {
            throw Error("some error");
        } catch (...) {
            handler.handleException(std::current_exception());
        }
    }

    SECTION("Critical error callback") {
        int x {0};
        handler.setCriticalErrorCallback<inc>(x);

        handler.throwException<CriticalError>("what", "file", 0, "function");
        REQUIRE(x == 1);

        handler.throwException<CriticalError>("What2", "file", 1, "function");
        REQUIRE(x == 2);
    }
}