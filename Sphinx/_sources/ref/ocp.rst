Optimal Control Problems
========================

Problems are usually formulated using :cpp:struct:`fancyqlone::LinearOCPStorage`.
To pass them to the Cyqlone solver, they need to be converted to :cpp:struct:`fancyqlone::CyqloneStorage`
format, where the initial state is eliminated. For testing, it can be helpful to convert the
problem to a sparse QP format, which is supported by :cpp:struct:`fancyqlone::LinearOCPSparseQP`.

.. doxygenstruct:: fancyqlone::LinearOCPStorage
   :no-link:
   :members:
   :undoc-members:
.. doxygenstruct:: fancyqlone::CyqloneStorage
   :no-link:
   :members:
   :undoc-members:
.. doxygenstruct:: fancyqlone::LinearOCPSparseQP
   :no-link:
   :members:
   :undoc-members:
