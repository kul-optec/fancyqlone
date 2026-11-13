QPALM
=====

Solver
------

.. doxygenclass:: fancyqlone::qpalm::Solver
   :no-link:
   :members:
   :undoc-members:

Settings
--------

.. doxygenstruct:: fancyqlone::qpalm::Settings
   :no-link:
   :members:
   :undoc-members:

Statistics
----------

.. doxygenstruct:: fancyqlone::qpalm::SolverStats
   :no-link:
   :members:
   :undoc-members:
.. doxygenstruct:: fancyqlone::qpalm::DetailedStats
   :no-link:
   :members:
   :undoc-members:

Backends
--------

.. doxygenstruct:: fancyqlone::qpalm::unique_CyQPALMBackend
   :no-link:
   :members:
   :undoc-members:
.. doxygenfunction:: fancyqlone::qpalm::make_cyqpalm_backend
   :no-link:
.. doxygenfunction:: fancyqlone::qpalm::update_cyqpalm_backend(CyQPALMBackend<VL, DefaultOrder> &backend, const CyqloneStorage<real_t> &ocp)
   :no-link:
.. doxygenfunction:: fancyqlone::qpalm::update_cyqpalm_backend(CyQPALMBackend<VL, DefaultOrder> &backend, const LinearOCPStorage &ocp)
   :no-link:
