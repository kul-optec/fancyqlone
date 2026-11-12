#include <gtest/gtest.h>

#include <fancyqlone/linalg.hpp>
#include <fancyqlone/packing.hpp>
#include <batmat/linalg/triangular.hpp>

#include <tuple>
#include <type_traits>

namespace {

template <class M>
void fill_linear(M &m, double start, double step) {
    using fancyqlone::index_t;
    auto *ptr = m.data();
    for (index_t i = 0; i < m.size(); ++i)
        ptr[i] = start + step * static_cast<double>(i);
}

} // namespace

TEST(LinAlg, transformNElementwiseSumDiff) {
    using fancyqlone::index_t;
    using vl_t = std::integral_constant<index_t, 4>;
    batmat::matrix::Matrix<double, index_t, vl_t> A{{.depth = 16, .rows = 13, .cols = 17}};
    batmat::matrix::Matrix<double, index_t, vl_t> B{{.depth = 16, .rows = 13, .cols = 17}};
    batmat::matrix::Matrix<double, index_t, vl_t> C{{.depth = 16, .rows = 13, .cols = 17}};
    batmat::matrix::Matrix<double, index_t, vl_t> D{{.depth = 16, .rows = 13, .cols = 17}};
    fill_linear(A, 0.5, 0.25);
    fill_linear(B, -2.0, 0.75);

    const auto fun = [](auto ai, auto bi) { return std::make_tuple(ai + bi, ai - bi); };
    fancyqlone::linalg::transform_n_elementwise(fun, std::tie(C, D), A, B);

    for (index_t i = 0; i < A.size(); ++i) {
        const double a = A.data()[i];
        const double b = B.data()[i];
        EXPECT_DOUBLE_EQ(C.data()[i], a + b);
        EXPECT_DOUBLE_EQ(D.data()[i], a - b);
    }
}

TEST(LinAlg, transformNElementwiseInPlaceOutput) {
    using fancyqlone::index_t;
    using vl_t = std::integral_constant<index_t, 4>;
    batmat::matrix::Matrix<double, index_t, vl_t> A{{.depth = 8, .rows = 7, .cols = 5}};
    batmat::matrix::Matrix<double, index_t, vl_t> B{{.depth = 8, .rows = 7, .cols = 5}};
    fill_linear(A, 1.0, 0.5);
    fill_linear(B, -3.0, 0.2);
    auto A_ref = A;

    const auto fun = [](auto ai, auto bi) { return std::make_tuple(ai + bi); };
    fancyqlone::linalg::transform_n_elementwise(fun, std::tie(A), A, B);

    for (index_t i = 0; i < A.size(); ++i)
        EXPECT_DOUBLE_EQ(A.data()[i], A_ref.data()[i] + B.data()[i]);
}

TEST(LinAlg, unpackGeneral) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;
    batmat::matrix::Matrix<double, index_t, vl_t, vl_t> A{{.rows = 13, .cols = 17}};
    batmat::matrix::Matrix<double, index_t, one_t, vl_t> B{{.rows = 13, .cols = 17}};
    fill_linear(A, 0.5, 0.25);

    fancyqlone::linalg::unpack(A, B);
    for (index_t l = 0; l < A.depth(); ++l) {
        for (index_t r = 0; r < A.rows(); ++r) {
            for (index_t c = 0; c < A.cols(); ++c) {
                const double expected = A(l, r, c);
                const double actual   = B(l, r, c);
                EXPECT_DOUBLE_EQ(actual, expected) << " at (" << l << ", " << r << ", " << c << ")";
            }
        }
    }
}

TEST(LinAlg, unpackWrongDepth) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;
    batmat::matrix::Matrix<double, index_t, one_t, one_t> A{{.rows = 13, .cols = 17}};
    batmat::matrix::Matrix<double, index_t, one_t, vl_t> B{{.rows = 13, .cols = 17}};
    fill_linear(A, 0.5, 0.25);

    EXPECT_THROW(fancyqlone::linalg::unpack(A, B), std::logic_error);
}

TEST(LinAlg, unpackGeneralTransB) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;
    batmat::matrix::Matrix<double, index_t, vl_t, vl_t> A{{.rows = 13, .cols = 17}};
    batmat::matrix::Matrix<double, index_t, one_t, vl_t> B{{.rows = 17, .cols = 13}};
    fill_linear(A, 0.5, 0.25);

    fancyqlone::linalg::unpack(A, B.transposed());
    for (index_t l = 0; l < A.depth(); ++l) {
        for (index_t r = 0; r < A.rows(); ++r) {
            for (index_t c = 0; c < A.cols(); ++c) {
                const double expected = A(l, r, c);
                const double actual   = B(l, c, r); // Transposed access
                EXPECT_DOUBLE_EQ(actual, expected) << " at (" << l << ", " << r << ", " << c << ")";
            }
        }
    }
}

TEST(LinAlg, unpackGeneralTransA) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;
    batmat::matrix::Matrix<double, index_t, vl_t, vl_t> A{{.rows = 17, .cols = 13}};
    batmat::matrix::Matrix<double, index_t, one_t, vl_t> B{{.rows = 13, .cols = 17}};
    fill_linear(A, 0.5, 0.25);

    fancyqlone::linalg::unpack(A.transposed(), B);
    for (index_t l = 0; l < A.depth(); ++l) {
        for (index_t r = 0; r < A.rows(); ++r) {
            for (index_t c = 0; c < A.cols(); ++c) {
                const double expected = A(l, r, c);
                const double actual   = B(l, c, r); // Transposed access
                EXPECT_DOUBLE_EQ(actual, expected) << " at (" << l << ", " << r << ", " << c << ")";
            }
        }
    }
}

TEST(LinAlg, packGeneral) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;
    batmat::matrix::Matrix<double, index_t, vl_t, vl_t> A{{.rows = 3, .cols = 5}};
    batmat::matrix::Matrix<double, index_t, one_t, vl_t> B{{.rows = 3, .cols = 5}};
    fill_linear(B, 0.5, 0.25);

    fancyqlone::linalg::pack(B, A);
    for (index_t l = 0; l < A.depth(); ++l) {
        for (index_t r = 0; r < A.rows(); ++r) {
            for (index_t c = 0; c < A.cols(); ++c) {
                const double expected = B(l, r, c);
                const double actual   = A(l, r, c);
                EXPECT_DOUBLE_EQ(actual, expected) << " at (" << l << ", " << r << ", " << c << ")";
            }
        }
    }
}

TEST(LinAlg, packWrongDepth) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;
    batmat::matrix::Matrix<double, index_t, one_t, one_t> A{{.rows = 3, .cols = 5}};
    batmat::matrix::Matrix<double, index_t, one_t, vl_t> B{{.rows = 3, .cols = 5}};
    fill_linear(B, 0.5, 0.25);

    EXPECT_THROW(fancyqlone::linalg::pack(B, A), std::logic_error);
}

TEST(LinAlg, packGeneralTransB) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;
    batmat::matrix::Matrix<double, index_t, vl_t, vl_t> A{{.rows = 3, .cols = 5}};
    batmat::matrix::Matrix<double, index_t, one_t, vl_t> B{{.rows = 5, .cols = 3}};
    fill_linear(B, 0.5, 0.25);

    fancyqlone::linalg::pack(B.transposed(), A);
    for (index_t l = 0; l < A.depth(); ++l) {
        for (index_t r = 0; r < A.rows(); ++r) {
            for (index_t c = 0; c < A.cols(); ++c) {
                const double expected = B(l, c, r); // Transposed access
                const double actual   = A(l, r, c);
                EXPECT_DOUBLE_EQ(actual, expected) << " at (" << l << ", " << r << ", " << c << ")";
            }
        }
    }
}

TEST(LinAlg, packGeneralTransA) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;
    batmat::matrix::Matrix<double, index_t, vl_t, vl_t> A{{.rows = 5, .cols = 3}};
    batmat::matrix::Matrix<double, index_t, one_t, vl_t> B{{.rows = 3, .cols = 5}};
    fill_linear(B, 0.5, 0.25);

    fancyqlone::linalg::pack(B, A.transposed());
    for (index_t l = 0; l < A.depth(); ++l) {
        for (index_t r = 0; r < A.rows(); ++r) {
            for (index_t c = 0; c < A.cols(); ++c) {
                const double expected = B(l, c, r); // Transposed access
                const double actual   = A(l, r, c);
                EXPECT_DOUBLE_EQ(actual, expected) << " at (" << l << ", " << r << ", " << c << ")";
            }
        }
    }
}

using enum fancyqlone::linalg::MatrixStructure;
using enum fancyqlone::linalg::StorageOrder;

template <fancyqlone::linalg::MatrixStructure Struc_, fancyqlone::linalg::StorageOrder OrderA_,
          fancyqlone::linalg::StorageOrder OrderB_>
struct TriangularOrders {
    static constexpr auto Struc  = Struc_;
    static constexpr auto OrderA = OrderA_;
    static constexpr auto OrderB = OrderB_;

    static std::string GetName() {
        return std::format("{}.{}.{}",
                           Struc == General           ? "General"
                           : Struc == LowerTriangular ? "Lower"
                                                      : "Upper",
                           OrderA == ColMajor ? "cm" : "rm", OrderB == ColMajor ? "cm" : "rm");
    }
};

struct TriangularOrdersName {
    template <typename T>
    static std::string GetName(int) {
        return T::GetName();
    }
};

using PackingTypes = ::testing::Types<TriangularOrders<General, ColMajor, ColMajor>,         //
                                      TriangularOrders<General, ColMajor, RowMajor>,         //
                                      TriangularOrders<General, RowMajor, ColMajor>,         //
                                      TriangularOrders<General, RowMajor, RowMajor>,         //
                                      TriangularOrders<LowerTriangular, ColMajor, ColMajor>, //
                                      TriangularOrders<LowerTriangular, ColMajor, RowMajor>, //
                                      TriangularOrders<LowerTriangular, RowMajor, ColMajor>, //
                                      TriangularOrders<LowerTriangular, RowMajor, RowMajor>, //
                                      TriangularOrders<UpperTriangular, ColMajor, ColMajor>, //
                                      TriangularOrders<UpperTriangular, ColMajor, RowMajor>, //
                                      TriangularOrders<UpperTriangular, RowMajor, ColMajor>, //
                                      TriangularOrders<UpperTriangular, RowMajor, RowMajor>  //
                                      >;

template <class Config>
class PackingTest : public testing::Test {};
TYPED_TEST_SUITE_P(PackingTest);

template <batmat::linalg::MatrixStructure Structure>
constexpr bool in_structure(fancyqlone::index_t rows, fancyqlone::index_t cols, fancyqlone::index_t row,
                            fancyqlone::index_t col) {
    if constexpr (Structure == LowerTriangular)
        return col <= row + std::max(rows, cols) - rows;
    else if constexpr (Structure == UpperTriangular)
        return row <= col + std::max(rows, cols) - cols;
    else
        return true;
}

template <batmat::linalg::MatrixStructure Struc, class MatrixA, class MatrixB>
void compare_structured(const MatrixA &A, const MatrixB &B) {
    using fancyqlone::index_t;
    for (index_t l = 0; l < A.depth(); ++l)
        for (index_t r = 0; r < A.rows(); ++r)
            for (index_t c = 0; c < A.cols(); ++c)
                if (in_structure<Struc>(A.rows(), A.cols(), r, c))
                    ASSERT_DOUBLE_EQ(B(l, r, c), A(l, r, c))
                        << " at (" << l << ", " << r << ", " << c << ")";
                else
                    ASSERT_DOUBLE_EQ(B(l, r, c), -99.0)
                        << " at (" << l << ", " << r << ", " << c << ") -- outside structure";
}

template <class Config>
void test_unpack(fancyqlone::index_t rows, fancyqlone::index_t cols) {
    using fancyqlone::index_t;
    using vl_t  = std::integral_constant<index_t, 4>;
    using one_t = std::integral_constant<index_t, 1>;

    using MatrixA = batmat::matrix::Matrix<double, index_t, vl_t, vl_t, Config::OrderA>;
    using MatrixB = batmat::matrix::Matrix<double, index_t, one_t, vl_t, Config::OrderB>;

    MatrixA A{{.rows = rows, .cols = cols}};
    MatrixB B{{.rows = rows, .cols = cols}};
    fill_linear(A, 0.5, 0.25);
    fill_linear(B, -99.0, 0.0);

    auto sA = batmat::linalg::make_structured<Config::Struc>(A);
    auto sB = batmat::linalg::make_structured<Config::Struc>(B);
    fancyqlone::linalg::unpack(sA, sB);
    compare_structured<Config::Struc>(A, B);
}

TYPED_TEST_P(PackingTest, square) {
    for (fancyqlone::index_t i : {1, 2, 3, 4, 5, 31})
        test_unpack<TypeParam>(i, i);
}

TYPED_TEST_P(PackingTest, wide) {
    for (fancyqlone::index_t i : {1, 2, 3, 4, 5, 31})
        for (fancyqlone::index_t j : {1, 2, 3, 4, 5, 31})
            if (j > i)
                test_unpack<TypeParam>(i, j);
}

TYPED_TEST_P(PackingTest, tall) {
    for (fancyqlone::index_t i : {1, 2, 3, 4, 5, 31})
        for (fancyqlone::index_t j : {1, 2, 3, 4, 5, 31})
            if (i > j)
                test_unpack<TypeParam>(i, j);
}

REGISTER_TYPED_TEST_SUITE_P(PackingTest, square, wide, tall);
INSTANTIATE_TYPED_TEST_SUITE_P(PackingOrders, PackingTest, PackingTypes, TriangularOrdersName);
