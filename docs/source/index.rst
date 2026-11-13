.. image:: https://img.shields.io/badge/arXiv-Preprint-b31b1b
   :target: https://arxiv.org/abs/2512.09058
   :alt: arXiv Preprint

.. image:: https://github.com/kul-optec/fancyqlone/actions/workflows/linux.yml/badge.svg
   :target: https://github.com/kul-optec/fancyqlone/actions/workflows/linux.yml
   :alt: CI: Linux

.. image:: https://img.shields.io/pypi/dm/fancyqlone?label=PyPI&logo=python
   :target: https://pypi.org/project/fancyqlone
   :alt: PyPI Downloads


FanCyqlone
==========

Fast, **parallel and vectorized solver** for linear systems with **multi-horizon optimal control structure**.

Also includes an implementation of the **FanCyQPALM** solver that uses the FanCyqlone linear solver as a
backend, with a parallel
exact line search.

Preprint
--------

The original Cyqlone algorithms used in this repository are described on arXiv:
`https://arxiv.org/abs/2512.09058 <https://arxiv.org/abs/2512.09058>`_

.. code-block:: bibtex

   @misc{pas_cyqlone_2025,
      title = {{Cyqlone}: {A} {Parallel}, {High}-{Performance} {Linear} {Solver} for {Optimal} {Control}},
      url = {http://arxiv.org/abs/2512.09058},
      doi = {10.48550/arXiv.2512.09058},
      publisher = {arXiv},
      author = {Pas, Pieter and Patrinos, Panagiotis},
      month = dec,
      year = {2025}
   }

Content
-------

.. toctree::
   :maxdepth: 1

   python.rst
   cpp.rst

Related projects
----------------

* `<https://github.com/kul-optec/QPALM>`_: general-purpose quadratic programming solver on which FanCyQPALM is based
* `<https://github.com/tttapa/batmat>`_: high-performance batched linear algebra routines (used by FanCyqlone)
* `<https://github.com/kul-optec/hyhound>`_: low-rank Cholesky factorization up- and downdate routines based on hyperbolic Householder transformations (with applications to e.g. Riccati recursion)
* `<https://github.com/kul-optec/alpaqa>`_: matrix-free, nonlinear programming solver
