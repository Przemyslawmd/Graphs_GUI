
#include <gtest/gtest.h>

#include "defines.h"
#include <graph/model.h>

#include <graph/model.cpp>
#include <services/keys.cpp>


TEST(AddNode, FirstTest)
{
    auto model = std::make_unique<Model>();
    ASSERT_FALSE(model == nullptr);
}