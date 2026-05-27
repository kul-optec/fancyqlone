#pragma once

#include <cyqlone/linalg.hpp>
#include <batmat/linalg/gemv.hpp>
#include <batmat/linalg/potrf.hpp>
#include <batmat/linalg/trsm.hpp>

namespace cyqlone {

namespace bla = batmat::linalg;
using bla::StorageOrder;

/// Simple serial solver for block-tridiagonal systems, for testing purposes.
template <class T = real_t, StorageOrder Order = StorageOrder::ColMajor>
struct TridiagonalSolver {
    using value_type = T;

    const index_t block_size; ///< Block size of the block-tridiagonal system.
    const index_t num_blocks; ///< Number of blocks.

    /// No batched vectorization.
    using vl_t = std::integral_constant<index_t, 1>;
    /// Owning type for a batch of matrices (with batch size v).
    using matrix = batmat::matrix::Matrix<value_type, index_t, vl_t, index_t, Order>;
    /// Non-owning immutable view type for @ref matrix.
    using view = batmat::matrix::View<const value_type, index_t, vl_t, index_t, index_t, Order>;
    /// Non-owning mutable view type for @ref matrix.
    using mut_view = batmat::matrix::View<value_type, index_t, vl_t, index_t, index_t, Order>;

    /// Diagonal blocks of the Cholesky factor.
    matrix L = [this] {
        return matrix{{.depth = num_blocks, .rows = block_size, .cols = block_size}};
    }();
    /// Superdiagonal blocks of the Cholesky factor.
    /// Actually only contains num_blocks - 1 blocks, but we allocate num_blocks to simplify
    /// packing and unpacking to/from batched matrices.
    matrix U = [this] {
        return matrix{{.depth = num_blocks, .rows = block_size, .cols = block_size}};
    }();

    void factor() {
        for (index_t i = num_blocks; i-- > 0;) {
            auto Mi = bla::tril(L.batch(i));
            if (i + 1 == num_blocks)
                bla::potrf(Mi); //                                L(n-1) = chol(M(n-1))
            else
                bla::syrk_sub_potrf(U.batch(i), Mi); //           L(i) = chol(M(i) - U(i) U(i)ᵀ)
            if (i > 0)
                bla::trsm(U.batch(i - 1), Mi.transposed()); //    U(i-1) = K(i-1) L(i)⁻ᵀ
        }
    }

    void solve_forward(mut_view λ) const {
        for (index_t i = num_blocks; i-- > 0;) {
            auto Li = bla::tril(L.batch(i));
            bla::trsm(Li, λ.batch(i)); //                      λ(i) = L(i)⁻¹ λ(i)
            if (i > 0)
                bla::gemv_sub(U.batch(i - 1), λ.batch(i),
                              λ.batch(i - 1)); //              λ(i-1) -= U(i-1) λ(i)
        }
    }

    void solve_reverse(mut_view λ) const {
        for (index_t i = 0; i < num_blocks; ++i) {
            auto Li = bla::tril(L.batch(i));
            bla::trsm(Li.transposed(), λ.batch(i)); //         λ(i) = L(i)⁻ᵀ λ(i)
            if (i + 1 < num_blocks)
                bla::gemv_sub(U.batch(i).transposed(), λ.batch(i),
                              λ.batch(i + 1)); //              λ(i+1) -= U(i)ᵀ λ(i)
        }
    }
};

} // namespace cyqlone
