<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.16.1" doxygen_gitid="669aeeefca743c148e2d935b3d3c69535c7491e6">
  <compound kind="file">
    <name>README.md</name>
    <path>benchmarks/cyqpalm/</path>
    <filename>benchmarks_2cyqpalm_2README_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>README.md</name>
    <path></path>
    <filename>README_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>algorithms.md</name>
    <path>docs/source/doxygen/</path>
    <filename>algorithms_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>examples.md</name>
    <path>docs/source/doxygen/</path>
    <filename>examples_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>groups.dox</name>
    <path>docs/source/doxygen/</path>
    <filename>groups_8dox.html</filename>
  </compound>
  <compound kind="file">
    <name>solve-block-tridiagonal.cpp</name>
    <path>examples/</path>
    <filename>solve-block-tridiagonal_8cpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="packing_8hpp" name="packing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/packing.hpp</includes>
    <class kind="struct">TridiagSystem</class>
    <class kind="struct">BidiagUpdate</class>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; real_t, index_t &gt;</type>
      <name>matrices</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a93ebb2b3c08761f352b56f5a0ffa5606</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>fancyqlone::TricyqleSolver&lt; v, real_t &gt;</type>
      <name>TricyqleSolver</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>abafe9c41ffd7dbbfe382692a8709bc63</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>index_t</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a3033535835e47fa15276d18699766ea1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>double</type>
      <name>real_t</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a643846854e9562c033bced3bec5b8d48</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>TridiagSystem</type>
      <name>init_random_system</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>aea5086e4f91c5ef217def0c6e0a7b3e6</anchor>
      <arglist>(index_t block_size, index_t num_blocks, bool circular=false)</arglist>
    </member>
    <member kind="function">
      <type>BidiagUpdate</type>
      <name>init_random_update</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a315d00b0dd4c0dd4b1818aecaa236c62</anchor>
      <arglist>(index_t block_size, index_t num_blocks, index_t rank, bool circular=false)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a0ddf1224851353fc92bfbff6f499fa97</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
    <member kind="variable">
      <type>constexpr index_t</type>
      <name>v</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>ac818a8f049bd46d6d6996d28f22de4a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>centroidal-quadruped.cpp</name>
    <path>src/example-problems/centroidal-quadruped/</path>
    <filename>centroidal-quadruped_8cpp.html</filename>
    <includes id="conversion_8hpp" name="conversion.hpp" local="no" import="no" module="no" objc="no">fancyqlone/conversion.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>centroidal-quadruped.hpp</name>
    <path>src/example-problems/centroidal-quadruped/</path>
    <filename>centroidal-quadruped_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::problems::CentroidalQuadrupedGaitPhase</class>
    <class kind="struct">fancyqlone::qpalm::problems::CentroidalQuadrupedParams</class>
    <class kind="struct">fancyqlone::qpalm::problems::CentroidalQuadrupedProblem</class>
    <class kind="struct">fancyqlone::qpalm::problems::FanCentroidalQuadrupedProblem</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>csv.hpp</name>
    <path>src/example-problems/include/fancyqlone/fancyqpalm/example-problems/</path>
    <filename>csv_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>platooning.hpp</name>
    <path>src/example-problems/include/fancyqlone/fancyqpalm/example-problems/</path>
    <filename>platooning_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::problems::PlatooningParams</class>
    <class kind="struct">fancyqlone::qpalm::problems::PlatooningProblem</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>spring-mass.hpp</name>
    <path>src/example-problems/include/fancyqlone/fancyqpalm/example-problems/</path>
    <filename>spring-mass_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::problems::SpringMassParams</class>
    <class kind="struct">fancyqlone::qpalm::problems::SpringMassProblem</class>
    <class kind="struct">fancyqlone::qpalm::problems::FanSpringMassProblem</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>zoh.hpp</name>
    <path>src/example-problems/include/fancyqlone/fancyqpalm/example-problems/</path>
    <filename>zoh_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>csv.cpp</name>
    <path>src/example-problems/src/</path>
    <filename>csv_8cpp.html</filename>
    <includes id="csv_8hpp" name="csv.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/example-problems/csv.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>platooning.cpp</name>
    <path>src/example-problems/src/</path>
    <filename>platooning_8cpp.html</filename>
    <includes id="conversion_8hpp" name="conversion.hpp" local="no" import="no" module="no" objc="no">fancyqlone/conversion.hpp</includes>
    <includes id="platooning_8hpp" name="platooning.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/example-problems/platooning.hpp</includes>
    <includes id="zoh_8hpp" name="zoh.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/example-problems/zoh.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>spring-mass.cpp</name>
    <path>benchmarks/cyqpalm/</path>
    <filename>benchmarks_2cyqpalm_2spring-mass_8cpp.html</filename>
    <includes id="ocp-backend-fancyqlone_8hpp" name="ocp-backend-fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.hpp</includes>
    <includes id="spring-mass_8hpp" name="spring-mass.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/example-problems/spring-mass.hpp</includes>
    <includes id="settings_8hpp" name="settings.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/settings.hpp</includes>
    <includes id="solver_8hpp" name="solver.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/solver.hpp</includes>
    <includes id="status_8hpp" name="status.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/status.hpp</includes>
    <includes id="matio_8hpp" name="matio.hpp" local="no" import="no" module="no" objc="no">fancyqlone/matio.hpp</includes>
    <includes id="tracing_8hpp" name="tracing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/tracing.hpp</includes>
    <class kind="struct">Options</class>
    <class kind="struct">Problem</class>
    <class kind="struct">Solver</class>
    <class kind="struct">SpringMassParams</class>
    <member kind="typedef">
      <type>std::chrono::duration&lt; double &gt;</type>
      <name>seconds</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>aedfb63997e73d0dc8964ae5c1f36cd41</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>index_t</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a3033535835e47fa15276d18699766ea1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>double</type>
      <name>real_t</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a643846854e9562c033bced3bec5b8d48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>ProblemType</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a4c669cb1cb4d98dfea944e9ceec7d33e</anchor>
      <arglist></arglist>
      <enumvalue file="benchmarks_2cyqpalm_2spring-mass_8cpp.html" anchor="a4c669cb1cb4d98dfea944e9ceec7d33eafc57686bf20fc8e206157d78a9fb758b">WangBoyd2008</enumvalue>
      <enumvalue file="benchmarks_2cyqpalm_2spring-mass_8cpp.html" anchor="a4c669cb1cb4d98dfea944e9ceec7d33ea25d408c56cbbbab45f40c893418fb894">WangBoyd2008Width</enumvalue>
      <enumvalue file="benchmarks_2cyqpalm_2spring-mass_8cpp.html" anchor="a4c669cb1cb4d98dfea944e9ceec7d33eae7ce5734fbb933180d31b231c2eb7be1">Domahidi2012</enumvalue>
      <enumvalue file="benchmarks_2cyqpalm_2spring-mass_8cpp.html" anchor="a4c669cb1cb4d98dfea944e9ceec7d33eae327976f658280963c254af6d143c777">ActiveStateConstr</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>WarmStartHPIPM</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a1e5ece077879bedb19586a2c036f2c23</anchor>
      <arglist></arglist>
      <enumvalue file="benchmarks_2cyqpalm_2spring-mass_8cpp.html" anchor="a1e5ece077879bedb19586a2c036f2c23a5b85379fb6d4ff2312ca180d829fdf01">NoWarmStart</enumvalue>
      <enumvalue file="benchmarks_2cyqpalm_2spring-mass_8cpp.html" anchor="a1e5ece077879bedb19586a2c036f2c23a54db44089bbacc4895e3414518231c77">WarmZero</enumvalue>
      <enumvalue file="benchmarks_2cyqpalm_2spring-mass_8cpp.html" anchor="a1e5ece077879bedb19586a2c036f2c23abe144a42394a837bd7f50a6b10cf78be">WarmCopy</enumvalue>
      <enumvalue file="benchmarks_2cyqpalm_2spring-mass_8cpp.html" anchor="a1e5ece077879bedb19586a2c036f2c23a971d78d68790b314dad6cbe5b5431d8f">WarmShift</enumvalue>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>counter</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>aed9742e190fcdab12ce85ae28d0c0a66</anchor>
      <arglist>(auto x)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>counter_avg</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a0c126e7f6f691e9434fc9c999ed9b106</anchor>
      <arglist>(auto x)</arglist>
    </member>
    <member kind="function">
      <type>qp::problems::SpringMassProblem</type>
      <name>create_problem</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a87c3add091c930e9266aaf6c71d5b499</anchor>
      <arglist>(const SpringMassParams &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>disable_tracing</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a796f7650fc942bd964d67e29a30785c4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>trace_run</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>ad3b3d4b3fd7cf72bcb309c69323c1c1d</anchor>
      <arglist>(auto &amp;&amp;, const auto &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_traces</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a99ac5e937e8cd6649369830168443ed2</anchor>
      <arglist>(std::ostream &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>run_benchmark</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a9a50c58845ad3929bc28241ad1ef0991</anchor>
      <arglist>(benchmark::State &amp;state, const std::string &amp;param_name, const SpringMassParams &amp;params, qp::CyQPALMBackendSettings backend_settings, qp::Settings settings, bool warm=false, bool trace=false)</arglist>
    </member>
    <member kind="function">
      <type>std::generator&lt; Problem &gt;</type>
      <name>get_spring_mass_params</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>ab1a4727f1d17d76d3fb9c497efb1650b</anchor>
      <arglist>(const Options &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>export_problem</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a14f468c71f063f09688477ea3fd75bb8</anchor>
      <arglist>(const Options &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>std::string_view</type>
      <name>order</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>af61fff0ad381f171d5c3d5fdbb5835d5</anchor>
      <arglist>(qp::StorageOrder o)</arglist>
    </member>
    <member kind="function">
      <type>std::generator&lt; Solver &gt;</type>
      <name>get_cyqlone_solvers</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>ac3104388361a980a90810067441fdad2</anchor>
      <arglist>(const Options &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>std::generator&lt; Solver &gt;</type>
      <name>get_hpipm_solvers</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a114b0239a8ec074b2ceec7996775c9a0</anchor>
      <arglist>(const Options &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>std::generator&lt; Solver &gt;</type>
      <name>get_cyqlone_solvers_vl</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a151b1c60490223468d41623ebfdde774</anchor>
      <arglist>(const Options &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>std::generator&lt; Solver &gt;</type>
      <name>get_solvers</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a24b505c3306cc2abef80b9bf1bab9339</anchor>
      <arglist>(const Options &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>register_benchmarks</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a5e87583157c03d1f72c32e615762ca84</anchor>
      <arglist>(const Options &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>std::unique_ptr&lt; benchmark::BenchmarkReporter &gt;</type>
      <name>make_custom_reporter</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a4670f9f2112847d3390329c356aaabfe</anchor>
      <arglist>(size_t problem_name_width, size_t solver_name_width, bool print_extra, bool with_color)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_options</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a6301de13c9af8b12550574d0b6336157</anchor>
      <arglist>(const char *program, CLI::App &amp;app, Options &amp;opts)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>initialize_google_benchmark</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a2fab40ef532103fd442a6d633bde2edc</anchor>
      <arglist>(char *program, auto bm_args)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_context</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a2eb0bd8e125a8ca4d991c8146f1d9f53</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a3c04138a5bfe5d72780bb7e82a18e627</anchor>
      <arglist>(int argc, char **argv)</arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>v_native</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a7a4d39b575e51782c5391448b0a1f931</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>constexpr auto</type>
      <name>v</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>abd7c170326903ac2f678a7b7f48a1dca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::map&lt; std::string, ProblemType &gt;</type>
      <name>problem_type_map</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>af601e9d42ebf311a42fa20225d866186</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>spring-mass.cpp</name>
    <path>src/example-problems/src/</path>
    <filename>src_2example-problems_2src_2spring-mass_8cpp.html</filename>
    <includes id="ocp_8hpp" name="ocp.hpp" local="yes" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <includes id="conversion_8hpp" name="conversion.hpp" local="no" import="no" module="no" objc="no">fancyqlone/conversion.hpp</includes>
    <includes id="spring-mass_8hpp" name="spring-mass.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/example-problems/spring-mass.hpp</includes>
    <includes id="zoh_8hpp" name="zoh.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/example-problems/zoh.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::problems</namespace>
  </compound>
  <compound kind="file">
    <name>barrier.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>barrier_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <class kind="struct">fancyqlone::EmptyCompletion</class>
    <class kind="class">fancyqlone::TreeBarrier</class>
    <class kind="class">fancyqlone::TreeBarrier::arrival_token</class>
    <class kind="class">fancyqlone::TreeBarrier::arrival_token_typed</class>
    <class kind="struct">fancyqlone::TreeBarrier::Storage</class>
    <class kind="struct">fancyqlone::TreeBarrier::State</class>
    <class kind="class">fancyqlone::TreeBarrier::shuffle_token</class>
    <namespace>fancyqlone</namespace>
    <member kind="define">
      <type>#define</type>
      <name>CYQLONE_SANITY_CHECKS_BARRIER</name>
      <anchorfile>barrier_8hpp.html</anchorfile>
      <anchor>a4d1e252dc13b658ff525ba615f94ae8b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>config.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>config_8hpp.html</filename>
    <namespace>fancyqlone</namespace>
    <member kind="define">
      <type>#define</type>
      <name>FANCYQLONE_NS</name>
      <anchorfile>config_8hpp.html</anchorfile>
      <anchor>aa4b496c143fba922704a143c4411beb1</anchor>
      <arglist>(ns)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>conversion.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>conversion_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <class kind="struct">fancyqlone::LinearOCPSparseQP</class>
    <class kind="struct">fancyqlone::LinearOCPSparseQP::KKTMatrix</class>
    <class kind="struct">fancyqlone::SparseCSC</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>cyqlone-params.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/</path>
    <filename>cyqlone-params_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <class kind="struct">fancyqlone::TricyqleParams</class>
    <class kind="struct">fancyqlone::CyqloneParams</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>cyqlone-storage.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/</path>
    <filename>cyqlone-storage_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <class kind="struct">fancyqlone::CyqloneStorage</class>
    <class kind="struct">fancyqlone::FanCyqloneStorage</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>cyqlone.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/</path>
    <filename>cyqlone_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="cyqlone-params_8hpp" name="cyqlone-params.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone-params.hpp</includes>
    <includes id="cyqlone-storage_8hpp" name="cyqlone-storage.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone-storage.hpp</includes>
    <includes id="parallel_8hpp" name="parallel.hpp" local="no" import="no" module="no" objc="no">fancyqlone/parallel.hpp</includes>
    <includes id="sparse_8hpp" name="sparse.hpp" local="no" import="no" module="no" objc="no">fancyqlone/sparse.hpp</includes>
    <includes id="timing_8hpp" name="timing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/timing.hpp</includes>
    <class kind="struct">fancyqlone::StageIndexInv</class>
    <class kind="struct">fancyqlone::TricyqleSolver</class>
    <class kind="struct">fancyqlone::CyqloneSolver</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>cr.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>cr_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="tracing_8hpp" name="tracing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/tracing.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>data.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>data_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::detail</namespace>
  </compound>
  <compound kind="file">
    <name>factor.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>factor_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>indexing.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>indexing_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>mat-vec.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>mat-vec_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>pcg.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>pcg_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>pcr.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>pcr_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>riccati.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>riccati_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>schur.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>schur_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="tracing_8hpp" name="tracing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/tracing.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>sparse.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>sparse_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>update.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>update_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="tracing_8hpp" name="tracing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/tracing.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>tridiagonal-solver.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/</path>
    <filename>tridiagonal-solver_8hpp.html</filename>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <class kind="struct">fancyqlone::TridiagonalSolver</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>fancyqlone.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/fancyqlone/</path>
    <filename>fancyqlone_8hpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="tridiagonal-solver_8hpp" name="tridiagonal-solver.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/tridiagonal-solver.hpp</includes>
    <includes id="packing_8hpp" name="packing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/packing.hpp</includes>
    <class kind="struct">fancyqlone::SolverStorage</class>
    <class kind="struct">fancyqlone::FanStorage_t</class>
    <class kind="struct">fancyqlone::FanCyqloneSolver</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>fan-data.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/fancyqlone/implementation/</path>
    <filename>fan-data_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="yes" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="fancyqlone_8hpp" name="fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/fancyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::detail</namespace>
  </compound>
  <compound kind="file">
    <name>fan-factor.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/fancyqlone/implementation/</path>
    <filename>fan-factor_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="fancyqlone_8hpp" name="fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/fancyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="packing_8hpp" name="packing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/packing.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>fan-mat-vec.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/fancyqlone/implementation/</path>
    <filename>fan-mat-vec_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="fancyqlone_8hpp" name="fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/fancyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>fan-update.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/fancyqlone/implementation/</path>
    <filename>fan-update_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="fancyqlone_8hpp" name="fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/fancyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="packing_8hpp" name="packing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/packing.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>linalg.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>linalg_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::linalg</namespace>
  </compound>
  <compound kind="file">
    <name>matio.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>matio_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <includes id="sparse_8hpp" name="sparse.hpp" local="no" import="no" module="no" objc="no">fancyqlone/sparse.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>neumaier.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>neumaier_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <class kind="class">fancyqlone::NeumaierSum</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>ocp.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>ocp_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <class kind="struct">fancyqlone::OCPDim</class>
    <class kind="struct">fancyqlone::LinearOCPStorage</class>
    <class kind="struct">fancyqlone::LinearOCPStorage::Solution</class>
    <class kind="struct">fancyqlone::LinearOCPStorage::KKTError</class>
    <class kind="struct">fancyqlone::LinearOCPStorage::KKTErroru0Seperated</class>
    <class kind="struct">fancyqlone::LinearOCPStorage::KKTErroru0x0Seperated</class>
    <class kind="struct">fancyqlone::FanOCPStorage</class>
    <class kind="struct">fancyqlone::FanOCPStorage::Solution</class>
    <class kind="struct">fancyqlone::FanOCPStorage::KKTError</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>packing.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>packing_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <member kind="function">
      <type>void</type>
      <name>unpack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaa42da3bc15768d28dea6e9f9d10070ea</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga699631bdd8928031c01a6bdc9aea4aec</anchor>
      <arglist>(Structured&lt; VA, S &gt; A, Structured&lt; VB, S &gt; B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_add</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga62982e090fc0815e6ba05adc13ca0f14</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaddcef15139ef3f45552b83b51431bd4b</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaaecce2aaac4780def856ed1b5a5474b0</anchor>
      <arglist>(Structured&lt; VA, S &gt; A, Structured&lt; VB, S &gt; B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_add</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga1fd60de59ea38008c45e198b8bb8cadb</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::linalg</namespace>
  </compound>
  <compound kind="file">
    <name>parallel.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>parallel_8hpp.html</filename>
    <includes id="barrier_8hpp" name="barrier.hpp" local="no" import="no" module="no" objc="no">fancyqlone/barrier.hpp</includes>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <class kind="struct">fancyqlone::parallel::SharedContext</class>
    <class kind="struct">fancyqlone::parallel::FanSharedContext</class>
    <class kind="struct">fancyqlone::parallel::Context</class>
    <class kind="struct">fancyqlone::parallel::arrival_token_typed_fan</class>
    <class kind="struct">fancyqlone::parallel::arrival_token_fan</class>
    <class kind="struct">fancyqlone::parallel::FanContext</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::parallel</namespace>
  </compound>
  <compound kind="file">
    <name>random-ocp.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>random-ocp_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>sfan-data.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/</path>
    <filename>sfan-data_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="yes" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="serial-fancyqlone_8hpp" name="serial-fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::detail</namespace>
  </compound>
  <compound kind="file">
    <name>sfan-factor.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/</path>
    <filename>sfan-factor_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="packing_8hpp" name="packing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/packing.hpp</includes>
    <includes id="serial-fancyqlone_8hpp" name="serial-fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>sfan-mat-vec.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/</path>
    <filename>sfan-mat-vec_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="serial-fancyqlone_8hpp" name="serial-fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>sfan-update.tpp</name>
    <path>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/</path>
    <filename>sfan-update_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="serial-fancyqlone_8hpp" name="serial-fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>serial-fancyqlone.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/</path>
    <filename>serial-fancyqlone_8hpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="tridiagonal-solver_8hpp" name="tridiagonal-solver.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/tridiagonal-solver.hpp</includes>
    <includes id="fancyqlone_8hpp" name="fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/fancyqlone.hpp</includes>
    <class kind="struct">fancyqlone::SerialFanCyqloneSolver</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>sparse.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>sparse_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <class kind="struct">fancyqlone::SparseMatrix</class>
    <class kind="struct">fancyqlone::SparseMatrixBuilder</class>
    <class kind="struct">fancyqlone::SparseCOO</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>timing.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>timing_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>tracing.hpp</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>tracing_8hpp.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>CYQ_TRACE_WRITE</name>
      <anchorfile>tracing_8hpp.html</anchorfile>
      <anchor>aa73a42b98ae9dc83b1ba49bbaa8b9f78</anchor>
      <arglist>(...)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CYQ_TRACE_READ</name>
      <anchorfile>tracing_8hpp.html</anchorfile>
      <anchor>af06e8f0353c7efc7707c5d97747c4673</anchor>
      <arglist>(...)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>conversion.cpp</name>
    <path>src/fancyqlone/src/</path>
    <filename>conversion_8cpp.html</filename>
    <includes id="conversion_8hpp" name="conversion.hpp" local="no" import="no" module="no" objc="no">fancyqlone/conversion.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>cyqlone-storage.cpp</name>
    <path>src/fancyqlone/src/cyqlone/</path>
    <filename>cyqlone-storage_8cpp.html</filename>
    <includes id="cyqlone-storage_8hpp" name="cyqlone-storage.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone-storage.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>cyqlone.cpp</name>
    <path>src/fancyqlone/src/cyqlone/</path>
    <filename>cyqlone_8cpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="cr_8tpp" name="cr.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/cr.tpp</includes>
    <includes id="data_8tpp" name="data.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/data.tpp</includes>
    <includes id="factor_8tpp" name="factor.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/factor.tpp</includes>
    <includes id="indexing_8tpp" name="indexing.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/indexing.tpp</includes>
    <includes id="mat-vec_8tpp" name="mat-vec.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/mat-vec.tpp</includes>
    <includes id="pcg_8tpp" name="pcg.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/pcg.tpp</includes>
    <includes id="pcr_8tpp" name="pcr.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/pcr.tpp</includes>
    <includes id="riccati_8tpp" name="riccati.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/riccati.tpp</includes>
    <includes id="schur_8tpp" name="schur.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/schur.tpp</includes>
    <includes id="sparse_8tpp" name="sparse.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/sparse.tpp</includes>
    <includes id="update_8tpp" name="update.tpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/implementation/update.tpp</includes>
    <namespace>fancyqlone</namespace>
    <member kind="define">
      <type>#define</type>
      <name>CYQLONE_INSTANTIATE_TRICYQLE</name>
      <anchorfile>cyqlone_8cpp.html</anchorfile>
      <anchor>a39e072dda5243754590685f16f67e848</anchor>
      <arglist>(T, VL, O)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CYQLONE_INSTANTIATE_CYQLONE</name>
      <anchorfile>cyqlone_8cpp.html</anchorfile>
      <anchor>a56700da47cd2ddd2e55e71f57e5aedb4</anchor>
      <arglist>(VL, O)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>fancyqlone.cpp</name>
    <path>src/fancyqlone/src/fancyqlone/</path>
    <filename>fancyqlone_8cpp.html</filename>
    <includes id="fancyqlone_8hpp" name="fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/fancyqlone.hpp</includes>
    <includes id="fan-data_8tpp" name="fan-data.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/implementation/fan-data.tpp</includes>
    <includes id="fan-factor_8tpp" name="fan-factor.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/implementation/fan-factor.tpp</includes>
    <includes id="fan-mat-vec_8tpp" name="fan-mat-vec.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/implementation/fan-mat-vec.tpp</includes>
    <includes id="fan-update_8tpp" name="fan-update.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/implementation/fan-update.tpp</includes>
    <namespace>fancyqlone</namespace>
    <member kind="define">
      <type>#define</type>
      <name>FANCYQLONE_INSTANTIATE_CYQLONE</name>
      <anchorfile>fancyqlone_8cpp.html</anchorfile>
      <anchor>abddbfd6a248259aa1eaafd38fd4a7c1b</anchor>
      <arglist>(VL, O)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>matio.cpp</name>
    <path>src/fancyqlone/src/</path>
    <filename>matio_8cpp.html</filename>
    <includes id="matio_8hpp" name="matio.hpp" local="no" import="no" module="no" objc="no">fancyqlone/matio.hpp</includes>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <class kind="struct">fancyqlone::matio_traits&lt; float &gt;</class>
    <class kind="struct">fancyqlone::matio_traits&lt; double &gt;</class>
    <class kind="struct">fancyqlone::matio_traits&lt; I &gt;</class>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>ocp.cpp</name>
    <path>src/fancyqlone/src/</path>
    <filename>ocp_8cpp.html</filename>
    <includes id="ocp_8hpp" name="ocp.hpp" local="no" import="no" module="no" objc="no">fancyqlone/ocp.hpp</includes>
    <namespace>fancyqlone</namespace>
  </compound>
  <compound kind="file">
    <name>serial-fancyqlone.cpp</name>
    <path>src/fancyqlone/src/sequential-fancyqlone/</path>
    <filename>serial-fancyqlone_8cpp.html</filename>
    <includes id="sfan-data_8tpp" name="sfan-data.tpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/implementation/sfan-data.tpp</includes>
    <includes id="sfan-factor_8tpp" name="sfan-factor.tpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/implementation/sfan-factor.tpp</includes>
    <includes id="sfan-mat-vec_8tpp" name="sfan-mat-vec.tpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/implementation/sfan-mat-vec.tpp</includes>
    <includes id="sfan-update_8tpp" name="sfan-update.tpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/implementation/sfan-update.tpp</includes>
    <includes id="serial-fancyqlone_8hpp" name="serial-fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp</includes>
    <namespace>fancyqlone</namespace>
    <member kind="define">
      <type>#define</type>
      <name>SerialFANCYQLONE_INSTANTIATE_CYQLONE</name>
      <anchorfile>serial-fancyqlone_8cpp.html</anchorfile>
      <anchor>a3e6a19e2239c1fd686d371647b42e16a</anchor>
      <arglist>(VL, O)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tracing.cpp</name>
    <path>src/fancyqlone/src/</path>
    <filename>tracing_8cpp.html</filename>
    <includes id="tracing_8hpp" name="tracing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/tracing.hpp</includes>
  </compound>
  <compound kind="file">
    <name>ineq-constr.tpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/</path>
    <filename>ineq-constr_8tpp.html</filename>
    <includes id="ocp-backend-fancyqlone_8tpp" name="ocp-backend-fancyqlone.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.tpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>linalg.tpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/</path>
    <filename>linalg_8tpp.html</filename>
    <includes id="ocp-backend-fancyqlone_8tpp" name="ocp-backend-fancyqlone.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.tpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>solve.tpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/</path>
    <filename>solve_8tpp.html</filename>
    <includes id="ocp-backend-fancyqlone_8tpp" name="ocp-backend-fancyqlone.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.tpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>ocp-backend-fancyqlone.hpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/</path>
    <filename>ocp-backend-fancyqlone_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="fancyqlone_8hpp" name="fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqlone/fancyqlone.hpp</includes>
    <includes id="serial-fancyqlone_8hpp" name="serial-fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/sequential-fancyqlone/serial-fancyqlone.hpp</includes>
    <includes id="cyqlone-params_8hpp" name="cyqlone-params.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone-params.hpp</includes>
    <includes id="cyqlone-storage_8hpp" name="cyqlone-storage.hpp" local="no" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone-storage.hpp</includes>
    <includes id="solver_8hpp" name="solver.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/solver.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::CyqloneData</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackendSettings</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackendStats</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::CyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::CyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::FanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::FanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::SerialFanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::SerialFanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_stats_type&lt; CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::unique_CyQPALMBackend</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_type&lt; unique_CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &gt;</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::detail</namespace>
  </compound>
  <compound kind="file">
    <name>ocp-backend-fancyqlone.tpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/</path>
    <filename>ocp-backend-fancyqlone_8tpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="ocp-backend-fancyqlone_8hpp" name="ocp-backend-fancyqlone.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.hpp</includes>
    <includes id="breakpoint_8hpp" name="breakpoint.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/breakpoint.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="neumaier_8hpp" name="neumaier.hpp" local="no" import="no" module="no" objc="no">fancyqlone/neumaier.hpp</includes>
    <includes id="ineq-constr_8tpp" name="ineq-constr.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/backend-fancyqlone/ineq-constr.tpp</includes>
    <includes id="linalg_8tpp" name="linalg.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/backend-fancyqlone/linalg.tpp</includes>
    <includes id="backends_2backend-fancyqlone_2linesearch_8tpp" name="linesearch.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/backend-fancyqlone/linesearch.tpp</includes>
    <includes id="solve_8tpp" name="solve.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/backend-fancyqlone/solve.tpp</includes>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackend</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackend::Timings</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackend::PenaltySettings</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>detailed-stats.hpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/</path>
    <filename>detailed-stats_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::DetailedStats</class>
    <class kind="struct">fancyqlone::qpalm::DetailedStats::Entry</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>algorithms.hpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/implementation/</path>
    <filename>algorithms_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>breakpoint.hpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/implementation/</path>
    <filename>breakpoint_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="neumaier_8hpp" name="neumaier.hpp" local="no" import="no" module="no" objc="no">fancyqlone/neumaier.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::Breakpoint</class>
    <class kind="struct">fancyqlone::qpalm::ABSums</class>
    <class kind="struct">fancyqlone::qpalm::PartitionedBreakpoints</class>
    <class kind="struct">fancyqlone::qpalm::BreakpointsResult</class>
    <class kind="struct">fancyqlone::qpalm::compute_breakpoints_fn</class>
    <class kind="struct">fancyqlone::qpalm::get_partitioned_breakpoints_fn</class>
    <class kind="struct">fancyqlone::qpalm::get_breakpoints_fn</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>breakpoint.tpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/implementation/</path>
    <filename>breakpoint_8tpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="breakpoint_8hpp" name="breakpoint.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/breakpoint.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>linesearch.tpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/</path>
    <filename>backends_2backend-fancyqlone_2linesearch_8tpp.html</filename>
    <includes id="cyqlone_8hpp" name="cyqlone.hpp" local="yes" import="no" module="no" objc="no">fancyqlone/cyqlone/cyqlone.hpp</includes>
    <includes id="breakpoint_8hpp" name="breakpoint.hpp" local="yes" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/breakpoint.hpp</includes>
    <includes id="ocp-backend-fancyqlone_8tpp" name="ocp-backend-fancyqlone.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.tpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>linesearch.tpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/implementation/</path>
    <filename>implementation_2linesearch_8tpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="algorithms_8hpp" name="algorithms.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/algorithms.hpp</includes>
    <includes id="breakpoint_8hpp" name="breakpoint.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/breakpoint.hpp</includes>
    <includes id="breakpoint_8tpp" name="breakpoint.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/breakpoint.tpp</includes>
    <includes id="neumaier_8hpp" name="neumaier.hpp" local="no" import="no" module="no" objc="no">fancyqlone/neumaier.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::LineSearchSettings</class>
    <class kind="struct">fancyqlone::qpalm::LineSearch</class>
    <class kind="struct">fancyqlone::qpalm::LineSearch::Result</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <member kind="define">
      <type>#define</type>
      <name>LINE_SEARCH_COMPARE_IMPLEMENTATIONS</name>
      <anchorfile>implementation_2linesearch_8tpp.html</anchorfile>
      <anchor>acd7da36899cf9c72a6805d3aa8d632c3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>solver.tpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/implementation/</path>
    <filename>solver_8tpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="detailed-stats_8hpp" name="detailed-stats.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/detailed-stats.hpp</includes>
    <includes id="implementation_2linesearch_8tpp" name="linesearch.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/linesearch.tpp</includes>
    <includes id="solver_8hpp" name="solver.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/solver.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::SolverImplementation</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>qpalm.hpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/</path>
    <filename>qpalm_8hpp.html</filename>
  </compound>
  <compound kind="file">
    <name>settings.hpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/</path>
    <filename>settings_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::Settings</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>solver.hpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/</path>
    <filename>solver_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="detailed-stats_8hpp" name="detailed-stats.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/detailed-stats.hpp</includes>
    <includes id="settings_8hpp" name="settings.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/settings.hpp</includes>
    <includes id="status_8hpp" name="status.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/status.hpp</includes>
    <includes id="timing_8hpp" name="timing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/timing.hpp</includes>
    <class kind="struct">fancyqlone::qpalm::SolverTimings</class>
    <class kind="struct">fancyqlone::qpalm::SolverStats</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_type&lt; std::unique_ptr&lt; T, D &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_type&lt; T * &gt;</class>
    <class kind="class">fancyqlone::qpalm::Solver</class>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::qpalm::detail</namespace>
  </compound>
  <compound kind="file">
    <name>status.hpp</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/</path>
    <filename>status_8hpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>breakpoint.cpp</name>
    <path>src/fancyqpalm/src/</path>
    <filename>breakpoint_8cpp.html</filename>
    <includes id="algorithms_8hpp" name="algorithms.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/algorithms.hpp</includes>
    <includes id="breakpoint_8hpp" name="breakpoint.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/breakpoint.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>ocp-backend-cyqlone.cpp</name>
    <path>src/fancyqpalm/src/</path>
    <filename>ocp-backend-cyqlone_8cpp.html</filename>
    <includes id="parallel_8hpp" name="parallel.hpp" local="yes" import="no" module="no" objc="no">fancyqlone/parallel.hpp</includes>
    <includes id="ineq-constr_8tpp" name="ineq-constr.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/backend-fancyqlone/ineq-constr.tpp</includes>
    <includes id="linalg_8tpp" name="linalg.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/backend-fancyqlone/linalg.tpp</includes>
    <includes id="backends_2backend-fancyqlone_2linesearch_8tpp" name="linesearch.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/backend-fancyqlone/linesearch.tpp</includes>
    <includes id="solve_8tpp" name="solve.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/backend-fancyqlone/solve.tpp</includes>
    <includes id="ocp-backend-fancyqlone_8tpp" name="ocp-backend-fancyqlone.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/backends/ocp-backend-fancyqlone.tpp</includes>
    <includes id="solver_8tpp" name="solver.tpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/implementation/solver.tpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
    <member kind="define">
      <type>#define</type>
      <name>CYQLONE_INSTANTIATE_QPALM_Cyqlone</name>
      <anchorfile>ocp-backend-cyqlone_8cpp.html</anchorfile>
      <anchor>a76a67ff6a8b41587d5f86389cd45e853</anchor>
      <arglist>(v, order)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CYQLONE_INSTANTIATE_QPALM_FanCyqlone</name>
      <anchorfile>ocp-backend-cyqlone_8cpp.html</anchorfile>
      <anchor>a8aad14e3f787ae45b664db30a093af39</anchor>
      <arglist>(v, order, InnerSolver)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>qpalm.cpp</name>
    <path>src/fancyqpalm/src/</path>
    <filename>qpalm_8cpp.html</filename>
    <includes id="qpalm_8hpp" name="qpalm.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/qpalm.hpp</includes>
  </compound>
  <compound kind="file">
    <name>status.cpp</name>
    <path>src/fancyqpalm/src/</path>
    <filename>status_8cpp.html</filename>
    <includes id="status_8hpp" name="status.hpp" local="no" import="no" module="no" objc="no">fancyqlone/fancyqpalm/status.hpp</includes>
    <namespace>fancyqlone</namespace>
    <namespace>fancyqlone::qpalm</namespace>
  </compound>
  <compound kind="file">
    <name>test-pcr.cpp</name>
    <path>test/</path>
    <filename>test-pcr_8cpp.html</filename>
    <includes id="config_8hpp" name="config.hpp" local="no" import="no" module="no" objc="no">fancyqlone/config.hpp</includes>
    <includes id="linalg_8hpp" name="linalg.hpp" local="no" import="no" module="no" objc="no">fancyqlone/linalg.hpp</includes>
    <includes id="matio_8hpp" name="matio.hpp" local="no" import="no" module="no" objc="no">fancyqlone/matio.hpp</includes>
    <includes id="packing_8hpp" name="packing.hpp" local="no" import="no" module="no" objc="no">fancyqlone/packing.hpp</includes>
    <class kind="struct">fancyqlone::PCRFactorTest</class>
    <namespace>fancyqlone</namespace>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>test-pcr_8cpp.html</anchorfile>
      <anchor>ae66f6b31b5ad750f1fe042a706a4e3d4</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>BidiagUpdate</name>
    <filename>solve-block-tridiagonal_8cpp.html</filename>
    <anchor>structBidiagUpdate</anchor>
    <member kind="variable">
      <type>matrices</type>
      <name>B</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a8d8e08fa369c7b58de20b9292e167fda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrices</type>
      <name>F</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a4543c34e2e6c5a8ca443738ce3850d3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrices</type>
      <name>S</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a2763bc1cf341891c9e20ebdac9d60163</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::CyqloneParams</name>
    <filename>group__topic-ocp-solvers.html</filename>
    <anchor>structfancyqlone_1_1CyqloneParams</anchor>
    <templarg>class T</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>group__topic-ocp-solvers.html</anchorfile>
      <anchor>a0ce2efee9d162d00f9c6f37f9b81d1ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>eliminate_u0_first</name>
      <anchorfile>group__topic-ocp-solvers.html</anchorfile>
      <anchor>aa428f2cd679adc2da644ab4ededa53de</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::CyqloneSolver</name>
    <filename>structfancyqlone_1_1CyqloneSolver.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>class T</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class Ctx</templarg>
    <member kind="typedef">
      <type>TricyqleSolver&lt; VL, T, DefaultOrder, Ctx &gt;</type>
      <name>tricyqle_t</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>af3323632da392de32ebc78a52a735439</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tricyqle_t::Context</type>
      <name>Context</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a5ac1d7aa42f70939fb48b9759cf70b62</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tricyqle_t::SharedContext</type>
      <name>SharedContext</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a0746e10b6e235d2e6c9e0b35d6feaf35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tricyqle_t::simd</type>
      <name>simd</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a524b8d42ef9271fe19eb4020f4b49b30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>p</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ade06ec58030126785b36408056694db6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>n</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a4e417264cad1c6c9563893fb44649b30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr index_t</type>
      <name>v</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a0bf262b9d83b893040864975549a0e8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>lv</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a39f457b33a34cb5da7e5ca29cf47c994</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>lp</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ae0d42eadf9c37ba33223046746c756c2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>ceil_p</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aed0d5fc8fc9207e13c790b76f37155ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>ceil_P</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a0c0d64660a52480d8b464736d5c0e481</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::unique_ptr&lt; SharedContext &gt;</type>
      <name>create_parallel_context</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a98370bd249aa9c5a62411dad23a66c1a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>foreach_stage</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a5f171a85b38f7cdaee45e662d4d6dcc6</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func, auto &amp;&amp;...xs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>foreach_batch</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>adbb6875d48f9933de6b301141d3e892e</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func, auto &amp;&amp;...xs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_grad</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>abb81dc48ae2d64ac5baaf98c5db8b4c3</anchor>
      <arglist>(Context &amp;ctx, const auto &amp;grad, const std::string &amp;name) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_grad</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a3a2bdeeb144504e08b3baceb28ae4bed</anchor>
      <arglist>(const auto &amp;grad, const std::string &amp;name) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>foreach_stage_fwd</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ad1b26575ddf3cdbff88445acf921dd61</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func, auto &amp;&amp;...xs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>foreach_batch_fwd</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a177da26dd7244222deee3333d9ecba82</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func, auto &amp;&amp;...xs) const</arglist>
    </member>
    <member kind="typedef">
      <type>typename tricyqle_t::template matrix&lt; O &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a4267bcb2587bc35d8ebb7e32ace66524</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename tricyqle_t::template view&lt; O &gt;</type>
      <name>view</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ad9ee3a5e934e4fdb984e1d3f26f94fb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename tricyqle_t::template mut_view&lt; O &gt;</type>
      <name>mut_view</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ae5cc2373850d4be28614d6cd8866059b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename tricyqle_t::layer_stride</type>
      <name>layer_stride</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>affd86b08ebf1fccc9d43001852631dd0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename tricyqle_t::template batch_view&lt; O &gt;</type>
      <name>batch_view</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a617db84eed177588427e71dff4c23592</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename tricyqle_t::template mut_batch_view&lt; O &gt;</type>
      <name>mut_batch_view</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a5a67d4485218725795efe7de336e7f61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>default_order</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a82a614ee7b36bdd9059cae9b2520e422</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>column_major</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a55cfdb37276cb6e12794ce08aceebf8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>void(Context &amp;ctx, index_t i, batch_view&lt; default_order &gt; F, batch_view&lt;&gt; ux, batch_view&lt;&gt; b, mut_batch_view&lt;&gt; x_next)</type>
      <name>ddp_func_t</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a9279b12ff18b32b4affc10519605a9af</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ae294468e1ce952cc0892afcc845d3258</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, view&lt;&gt; Σ, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aa013baf671534313d8d77c87f109cf71</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, view&lt;&gt; Σ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_forward</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ab0c90f5724c6f4b91709d6d83d72d32b</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ad7ec129f8c72c1a2150266dec245dc41</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_mul</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a6117a1d16dc3dc567f7005bf8f234220</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ, mut_view&lt;&gt; Mᵀλ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_ddp</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a684ee36d10d0a6c6c17f91f61f0c43ea</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ, real_t α, const std::function&lt; ddp_func_t &gt; &amp;simulate)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_mul_ddp</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a6148a0b98fa607f4335677ba9c3ab4af</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ, real_t α, const std::function&lt; ddp_func_t &gt; &amp;simulate, mut_view&lt;&gt; Mᵀλ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>af04c9cf68682246047661f1bf841d308</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; ΔΣ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_solve</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a377d6ddc24df536e6454c5ac61920333</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; ΔΣ, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>N_horiz</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a86844b45fa1b3d657c6365867fc32c9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>nx</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a3066fd842071154d70d319459cd10efe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>nu</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>af66738d92f1f87d2a5f558cd055c7d4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>ny</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a904c8cc1b809406373a8767cab48a18c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>ny_0</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a48c63b9e1d95c048c5a09049b961bdbd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>ny_N</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a6dd8fe608988ab3763fce3c3bc2b1a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_variables</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ab58b5b42633d2ed4b33fb04f7a9d7000</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_dynamics_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a56241bebe096a5192053571e8389306b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_general_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a74547a1d95ce56996fe6599a465fb752</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable">
      <type>CyqloneParams&lt; value_type &gt;</type>
      <name>params</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aa7892fe3072fd3ba8c730ab1aafb187a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>CyqloneParams&lt; value_type &gt;</type>
      <name>get_params</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>adfdc1139cd32da45131a813aa06857df</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_params</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a0114e52a6e588dc99d34b2c90544ab98</anchor>
      <arglist>(const CyqloneParams&lt; value_type &gt; &amp;new_params)</arglist>
    </member>
    <member kind="function">
      <type>TricyqleParams&lt; value_type &gt;</type>
      <name>get_tricyqle_params</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ad390c7c56beee8df9a4723cf52b46283</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_tricyqle_params</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a2dd3b14ee1cf95f6e2b594d2a1f55562</anchor>
      <arglist>(const TricyqleParams&lt; value_type &gt; &amp;new_params)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_params_string</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a310d0ddc9f00f45b0147e2472618b13d</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable">
      <type>tricyqle_t</type>
      <name>tricyqle</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a19e86256c34a947c67777c4e1221a6e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>data_H</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a7640b1065f2adee30addd883ac351849</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>data_F</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a9ea609e5dc501bf5b3c6df24c7ec6e5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>data_Gᵀ</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a15e15a799d019f1e6935fa62bbd6cc56</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>riccati_LH</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aa9497f6c3903eda0f0461905cafd81be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>riccati_LAB</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ace9d460f30adfcd5c15f99de2286fe27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>riccati_V</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a1ce689954c3f6816950d4393e54006db</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>riccati_work</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a903b3ba6dd22ed7f9fe25b87d2aa23f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_Σ</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a6a372abf1188785fdb31df4fc2d6d4e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>riccati_Υ1</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a09c667bc9b6e2488e111aed5515703e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>riccati_Υ2</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a5fd8468573593bf929fc9c8163b41159</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>ceil_N</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ade259eea8d6505f94de98a200f81a147</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>ν2</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a19d1bbb1215a200fcebef8bb96d01dd3</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>ν2p</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a80f118c4015c6a54b677d999e10d7ee7</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>add_wrap_ceil_N</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ac5263242d59faba2e9982342a3a8d663</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>sub_wrap_ceil_N</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a320c772b6339639469f65f3862681df5</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>add_wrap_p</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a06bbd73088791f887a8c6d51fbc655ec</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>sub_wrap_p</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aff9b008a34fdabb1d3d266b9c177a2eb</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>add_wrap_ceil_p</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a852c1dac25c0e5b96f5f3de1f3811cec</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>sub_wrap_ceil_p</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>accf29af58410bc54ae4e4a525c2aba78</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>stage_index</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ae07c67d45c2005681b7191d4e698aa4e</anchor>
      <arglist>(index_t c, index_t i, index_t l) const</arglist>
    </member>
    <member kind="function">
      <type>StageIndexInv</type>
      <name>inverse_stage_index</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aae63382c046c6ec8ec41494bbd66cdbe</anchor>
      <arglist>(index_t j) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>sub_wrap_ceil_P</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a797924f97bb63fc7f27efda321b49981</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>add_wrap_ceil_P</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a1c5187ee3b1172dcd1264c4c2cadd20c</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>get_linear_batch_offset</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a010c92ac8ca8be6c1e6eb729cc4deaea</anchor>
      <arglist>(index_t biA) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_data</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a0542bf9de3afc74459b24cf567ed4dca</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_rhs</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a6770372a7369416de882a265acd4ea99</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp, mut_view&lt;&gt; rhs) const</arglist>
    </member>
    <member kind="function">
      <type>matrix</type>
      <name>initialize_rhs</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a6d633c7da7435bf722d1d64da17725d2</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_gradient</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a8e4f01b7ddbc2e5c6e3f34b8b8c5c223</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp, mut_view&lt;&gt; grad) const</arglist>
    </member>
    <member kind="function">
      <type>matrix</type>
      <name>initialize_gradient</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a7a80d33593860666bf90a304697b73fc</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_bounds</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a664e1e7e4017b069b40507b1736ed803</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp, mut_view&lt;&gt; b_min, mut_view&lt;&gt; b_max) const</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; matrix&lt;&gt;, matrix&lt;&gt; &gt;</type>
      <name>initialize_bounds</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aecd2ea35567a115f00a461744f9b9c22</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_variables</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a56ca72e75f95eb229eb011ac462817fa</anchor>
      <arglist>(std::span&lt; const value_type &gt; ux_lin, mut_view&lt;&gt; ux) const</arglist>
    </member>
    <member kind="function">
      <type>matrix</type>
      <name>pack_variables</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ad99d68e93aecebf8702eb31a9ad30ce9</anchor>
      <arglist>(std::span&lt; const value_type &gt; ux_lin) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_variables</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a426c05b7620fa7c7b75ab08424e232ce</anchor>
      <arglist>(view&lt;&gt; ux, std::span&lt; value_type &gt; ux_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_variables</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>af0a0f1b4f60123f1c3a1c265c1d66e35</anchor>
      <arglist>(view&lt;&gt; ux) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_dynamics</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aa4a3ae5918bfd63a57f77bd32e78450c</anchor>
      <arglist>(std::span&lt; const value_type &gt; λ_lin, mut_view&lt;&gt; λ) const</arglist>
    </member>
    <member kind="function">
      <type>matrix</type>
      <name>pack_dynamics</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aa0abee56922a3ed3c89a5a8e752d6f89</anchor>
      <arglist>(std::span&lt; const value_type &gt; λ_lin) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_dynamics</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ae543bfbaad88aaebf717fb7283838566</anchor>
      <arglist>(view&lt;&gt; λ, std::span&lt; value_type &gt; λ_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_dynamics</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a517fa3bef4dd8c7e51b82082d880b764</anchor>
      <arglist>(view&lt;&gt; λ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ab7191e7b25dbf766ab5186130d8ebb23</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_lin, mut_view&lt;&gt; y, value_type fill=0) const</arglist>
    </member>
    <member kind="function">
      <type>matrix</type>
      <name>pack_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a7ae3d1e3bb12f41009c19c47237b4174</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_lin, value_type fill=0) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a628180a90ae5d08e337e0a958cabd9db</anchor>
      <arglist>(view&lt;&gt; y, std::span&lt; value_type &gt; y_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>af4df5de61ac743d617edc5453fb8bef6</anchor>
      <arglist>(view&lt;&gt; y) const</arglist>
    </member>
    <member kind="function">
      <type>matrix</type>
      <name>initialize_variables</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a46edf913f6c512d1455e48fd7e166875</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>matrix</type>
      <name>initialize_dynamics_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a6031917f10494910ea41ebbc966c5948</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>matrix</type>
      <name>initialize_general_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aa7b87e1d9ac027f1f63c988ee5910ebb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CyqloneSolver</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>afe6fdf3a11c1345f4c423757d5462c65</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp, index_t p, CyqloneParams&lt; value_type &gt; params={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>residual_dynamics_constr</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>af8f2769af6bb9a01ada3130d39daf6be</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; x, view&lt;&gt; b, mut_view&lt;&gt; Mxb) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_dynamics_constr</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ad7d91603551679aa49c8d382f8e30fb2</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; λ, mut_view&lt;&gt; Mᵀλ, bool accum=false) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>general_constr</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aaa68b649d1430fa02824c1cab885f9a5</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; ux, mut_view&lt;&gt; DCux) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_general_constr</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a64f25a9541e4b2087e148dc9a93b9c1b</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; y, mut_view&lt;&gt; DCᵀy) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_general_constr</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a9a640f93a903bfe4db8c2340d8e313d1</anchor>
      <arglist>(view&lt;&gt; y, mut_view&lt;&gt; DCᵀy) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ad17d2104fb052033a72745bad977c4d7</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; ux, value_type α, view&lt;&gt; q, value_type β, mut_view&lt;&gt; grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient_regularized</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a8aae2aa18e2ca4efe160b2268d29726a</anchor>
      <arglist>(Context &amp;ctx, value_type γ, view&lt;&gt; ux, view&lt;&gt; ux0, view&lt;&gt; q, mut_view&lt;&gt; grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient_remove_regularization</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a07125a62d2481ba6b98818eedda4727e</anchor>
      <arglist>(Context &amp;ctx, value_type γ, view&lt;&gt; x, view&lt;&gt; x0, mut_view&lt;&gt; grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>riccati_thread_assignment</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a876877d03142bf6c9d6c41142fba1482</anchor>
      <arglist>(Context &amp;ctx) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_riccati_solve</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a1a54d2f6387fb8051458791c443609ff</anchor>
      <arglist>(Context &amp;ctx, value_type γ, view&lt;&gt; Σ, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute_schur</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a59173499b495733d16c7e50fd8a3376d</anchor>
      <arglist>(Context &amp;ctx, real_t ρ_inv, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_impl</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ab7796c313ddfc6910ff23d7c0a2545a4</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, view&lt;&gt; Σ, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_riccati_reverse_impl</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ab3c42fb35278aed8dc3950b792a1e3f1</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ, mut_view&lt;&gt; work, real_t α, const F &amp;simulate, std::optional&lt; mut_view&lt;&gt; &gt; Mᵀλ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_riccati_reverse</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>aecbc46921969041d67eb50d72d263618</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ, mut_view&lt;&gt; work, std::optional&lt; mut_view&lt;&gt; &gt; Mᵀλ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_riccati_reverse_ddp</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a9fdca3a22a8a37ea5076f89eacb6b548</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ, mut_view&lt;&gt; work, real_t α, const std::function&lt; ddp_func_t &gt; &amp;simulate, std::optional&lt; mut_view&lt;&gt; &gt; Mᵀλ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ae60aca052198976e670a4890984bebfd</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ, mut_view&lt;&gt; work, std::optional&lt; mut_view&lt;&gt; &gt; Mᵀλ=std::nullopt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_riccati_solve</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a4e2e3b6820444546b59a753e267af169</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; ΔΣ, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_riccati</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a68dd3e4a538dc045a9a2ff33e9557d73</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; ΔΣ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_solve_impl</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>af315547d3f30a382c9373a6a51f0d3b5</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; ΔΣ, mut_view&lt;&gt; ux, mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>k_to_l</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ae41c9f4f620ca6a3641bd1459c9cdfab</anchor>
      <arglist>(index_t k) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_solution</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a73bcfa571457ee70c8c4fac061358796</anchor>
      <arglist>(view&lt;&gt; x, mut_view&lt;&gt; x_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_dynamics</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>abd92b6090a24be8d086ad2bbb8e2e1d2</anchor>
      <arglist>(view&lt;&gt; λ, mut_view&lt;&gt; λ_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_constraints</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>ab502eab3ba1c454946ca75ba53a03ad9</anchor>
      <arglist>(view&lt;&gt; y, mut_view&lt;&gt; y_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>SparseMatrix</type>
      <name>build_sparse</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a95927cd867532aa0ad4af5fb075cb3f3</anchor>
      <arglist>(const CyqloneStorage&lt; value_type &gt; &amp;ocp, std::span&lt; const value_type &gt; Σ) const</arglist>
    </member>
    <member kind="function">
      <type>SparseMatrix</type>
      <name>build_sparse_no_penalty</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a894cbe69757e32d69d19900c54916e6a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>build_rhs</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a37f2b857b5b0b746b9144d456ff54002</anchor>
      <arglist>(view&lt;&gt; rq, view&lt;&gt; b, value_type scale_rq=-1, value_type scale_b=-1) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>build_sol</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a25de9b76aa8b009ba122f48e6ce4a0c4</anchor>
      <arglist>(view&lt;&gt; ux, view&lt;&gt; λ) const</arglist>
    </member>
    <member kind="function">
      <type>SparseMatrix</type>
      <name>build_sparse_factor</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>affaa4fad95b07c4ac432629ada3b52d9</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>SparseMatrix</type>
      <name>build_sparse_diag</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a1165d3ac41d517652bd2d7daa26bb0da</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>SparseMatrix</type>
      <name>build_sparse_reg</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a29643cd3df778da36c8e7960f6df2ab3</anchor>
      <arglist>(real_t γ, real_t ρ_inv_internal, real_t ρ_inv_windows) const</arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1CyqloneSolver.html</anchorfile>
      <anchor>a9de1c7f6fd4982118031fdf2d1171466</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::CyqloneStorage</name>
    <filename>structfancyqlone_1_1CyqloneStorage.html</filename>
    <templarg>class T</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a028ad997f8135a57613be34611bb846b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>ad1907d8d47418c29b66e444340aab95d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>LinearOCPStorage::Solution</type>
      <name>Solution</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a7106b71cd74dbe44063740d9424bc915</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>LinearOCPStorage::KKTError</type>
      <name>KKTError</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a9e4e9fc1949239ea581eeba50787a7fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_impl</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a3bff42de4872e05538c6794162e0e3a7</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a97c0cdadfeb3c74472cad3dce1439058</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reconstruct_ineq_multipliers</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a1650b5a4afaa9beebac92b44b3cb8289</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_compressed, std::span&lt; value_type &gt; y) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>reconstruct_ineq_multipliers</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a46b795fe32dbd7675d2e594a9a967139</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_compressed) const</arglist>
    </member>
    <member kind="function">
      <type>Solution</type>
      <name>reconstruct_solution</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>ad6a06de0becbfe7f701ab0f6cb1e5b3b</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp, std::span&lt; const value_type &gt; ux_compressed, std::span&lt; const value_type &gt; y_compressed, std::span&lt; const value_type &gt; λ_compressed) const</arglist>
    </member>
    <member kind="function">
      <type>KKTError</type>
      <name>compute_kkt_error</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a16091b5de9c2315a36f5bdc87a535b0e</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp, std::span&lt; const value_type &gt; ux_compressed, std::span&lt; const value_type &gt; y_compressed, std::span&lt; const value_type &gt; λ_compressed) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static CyqloneStorage</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a3070b42b5e205a963afe189d05362a71</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp, index_t ny_0=-1)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static index_t</type>
      <name>count_constr_0</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>aca0bf2323f741964ba59ed7b83de5bb5</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp, std::vector&lt; bool &gt; &amp;Ju0)</arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>N_horiz</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>ae5d71804704fe5a4ed90aa8cd466192d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>nx</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a045f70556e37fb527fda8ae2394a9f41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>nu</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a53e074f913c1eae41d77d6e6df2d72fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>ny</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>abca1a357d5dc809cfff7ea732b6f1850</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>ny_0</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a830ba9d705901b77aeecd5e77696fd05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>ny_N</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a72313144e6ae37ef5a59ef456b95306b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; bool &gt;</type>
      <name>Ju0</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>ae89f5b4245ccccc2b9a858a49184a78a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_H</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a980d4d5bad229f141c3d968acb06b2cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_F</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a863a4feabb70fc13101617dd014e4b43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_G</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a1dfbb6764acae362513383a723558761</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_G0N</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a02ce590497934243a1a5aeeb255d7088</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_rq</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>aef0910137b943eb17b8822831e28aecf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_c</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a0442d18a9aee6efafa8af36bc1becf58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_lb</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>ad66b418818c4baa11f3d79122bb879ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_lb0N</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>aab1e15b7792290d32b2108b92556c914</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_ub</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a5c85944066c6ba74af9c94872f34e920</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>data_ub0N</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a72994b206c6f81eb7d98a121208f88e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>indices_G0</name>
      <anchorfile>structfancyqlone_1_1CyqloneStorage.html</anchorfile>
      <anchor>a0c437924c86959eedf9daf75c77d861a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::EmptyCompletion</name>
    <filename>structfancyqlone_1_1EmptyCompletion.html</filename>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>structfancyqlone_1_1EmptyCompletion.html</anchorfile>
      <anchor>aa52081e36f7e15fbb1f55c2a49d96c22</anchor>
      <arglist>() const noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::FanCyqloneSolver</name>
    <filename>structfancyqlone_1_1FanCyqloneSolver.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>class T</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class Ctx</templarg>
    <member kind="typedef">
      <type>batmat::datapar::deduced_simd&lt; value_type, v &gt;</type>
      <name>simd</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a6c3af33268fc5a13dec809c57550db75</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, v &gt;</type>
      <name>vl_t</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a02acbb3b0e3f6f705773a92c9d71e4a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, v *alignof(value_type)&gt;</type>
      <name>align_t</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a2b80412a215cf759b4d0c63564db031d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t, vl_t, index_t, O, align_t &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>afcdbac1d8db24b498777c5cbb1c5c978</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanStorage_t&lt; matrix&lt;&gt;, value_type, DefaultOrder &gt;</type>
      <name>FanStorage</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>af8a91439338dd5f3b093198e5e990b9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>default_order</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>aea01a6e1f281f19e2b689816ea8b1098</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>column_major</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a1d34dee7a16be2654c7c9740c5ecd7eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>CyqloneParams&lt; value_type &gt;</type>
      <name>get_params</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a03ea800cd995b3094ff5d837eb497a3c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_params</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ac5f0eac48a490687a892ea524d0fb4f7</anchor>
      <arglist>(const CyqloneParams&lt; value_type &gt; &amp;new_params)</arglist>
    </member>
    <member kind="function">
      <type>TricyqleParams&lt; value_type &gt;</type>
      <name>get_tricyqle_params</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>aae74ad6d56aed5c083a0c1ef1d6a3cec</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_tricyqle_params</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>af2275db63cbdf799030bd99426e996b6</anchor>
      <arglist>(const TricyqleParams&lt; value_type &gt; &amp;new_params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>foreach_batch</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>af53e81ffedc795371424242689440460</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func, auto &amp;&amp;...xs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>foreach_batch_fwd</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ab7922f2dd8877dbb99261bcfc342bf0b</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func, auto &amp;&amp;...xs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_grad</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a2c8921dd9246be990485b98249b19e7c</anchor>
      <arglist>(Context &amp;ctx, const auto &amp;grad, const std::string &amp;name) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_grad</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>af9af2dd93e8d3a942157e6ec9513a1f1</anchor>
      <arglist>(const auto &amp;grad, const std::string &amp;name) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_solution</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a2fd7af5b8cddd0e03c9c54882fd8bbb9</anchor>
      <arglist>(const FanStorage &amp;x, FanStorage &amp;x_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_dynamics</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a42c55b09bf059f3625607da867f44fce</anchor>
      <arglist>(const FanStorage &amp;λ, FanStorage &amp;λ_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ac44a36a039a10e0330cfe86697336795</anchor>
      <arglist>(const FanStorage &amp;y, FanStorage &amp;y_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_data</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ada53c2d5a7a5e4defde5b8d87603b965</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_rhs</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a7a5877c54cf4d21e7090e382cea72b97</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, FanStorage &amp;rhs) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_rhs</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a3f2fd2e2fd88ebe951852a5bf3e98fac</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_gradient</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>aa754c745583370652c5d421d959c9056</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, FanStorage &amp;grad) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_gradient</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>abf78c4e31edb179642826c5560a61647</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_bounds</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ab68b9f9797573b17ce9f6f5acffa41cd</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, FanStorage &amp;b_min, FanStorage &amp;b_max) const</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; FanStorage, FanStorage &gt;</type>
      <name>initialize_bounds</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a6a9ebb7f9edefe4cc3c15fcc5406f514</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_variables</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a1fcdb1ed60d00f63be2cf1b9a6579bb7</anchor>
      <arglist>(std::span&lt; const value_type &gt; ux_lin, FanStorage &amp;ux) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>pack_variables</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a391ef73b02146d06f3fa23044b158f6c</anchor>
      <arglist>(std::span&lt; const value_type &gt; ux_lin) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_variables</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a8e0248569a0308578050a6b5c6e48b20</anchor>
      <arglist>(const FanStorage &amp;ux, std::span&lt; value_type &gt; ux_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_variables</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a088ccf387d3a6a3c3ecc869c6af20e4b</anchor>
      <arglist>(const FanStorage &amp;ux) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_dynamics</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a2dc0232118335c33081deb9265ecee4f</anchor>
      <arglist>(std::span&lt; const value_type &gt; λ_lin, FanStorage &amp;λ) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>pack_dynamics</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>abfd30fe0c7d9e610f9fcd7c188f213bf</anchor>
      <arglist>(std::span&lt; const value_type &gt; λ_lin) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_dynamics</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a7313a63c3babf92aae81999b832d713a</anchor>
      <arglist>(const FanStorage &amp;λ, std::span&lt; value_type &gt; λ_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_dynamics</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>af6db0848fecd187965c68ae83d5ac7d5</anchor>
      <arglist>(const FanStorage &amp;λ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a2406eced1fc38d727049f506d4082e2c</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_lin, FanStorage &amp;y, value_type fill=0) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>pack_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a5744916fccd8d4728b30d82713c21e53</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_lin, value_type fill=0) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a35b5784fd596b3b66c7699f95bb0a2d7</anchor>
      <arglist>(const FanStorage &amp;y, std::span&lt; value_type &gt; y_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a6fda11cb0b78217653857146413e629a</anchor>
      <arglist>(const FanStorage &amp;y) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_variables</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a6692ca25a780983cf9e164774ece254b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_dynamics_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a463a6fdb06b758103769dd58b9ca34b3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_general_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a24f5aa48d5021876f7fef7d0f465a75c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FanCyqloneSolver</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a3c9ee9b4d5883935fb8f9e880b408a50</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, std::vector&lt; index_t &gt; p, CyqloneParams&lt; value_type &gt; params={})</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FanCyqloneSolver</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>aed07ec8ce9584d520a76f1fdd5e46d0f</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, index_t p, CyqloneParams&lt; value_type &gt; params={})</arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>num_branches</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ace0d140511e19438f749e54b0ecbc63c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>nu</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>afdcd3a510655ededa4c0da3d1d6b6fb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>ny_0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a341560501584aaee158c787e1e6c602b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; SolverStorage&lt; VL, value_type, DefaultOrder, parallel::Context&lt;&gt; &gt; &gt;</type>
      <name>solver_storages</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a0111b1797aa86c2c25548d5a32c0912c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>CyqloneParams&lt; value_type &gt;</type>
      <name>params</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ae10d7a71265a96bb28ccadfc3732538e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>SBs</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>abb14a23375da0649a737d954c09ab834</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>rs</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>aedd989f52dcf4cddd121491131dcd908</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>R0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ac0aeb0c89c86b4d8132a986f96c8c74a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>r0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>afc8178c6a3b51478205e4b7a05dbc9fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>D0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a5e2808b5845e1758f234020bb41f44f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>ΔSBs</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a0510be695b3b1d0aef3b47bdcb6c261a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>p</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a82f395b3a128192b08ab50b0686465b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr index_t</type>
      <name>v</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>adb1ee077f94a3f62b46fdee6a0a8b91e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::unique_ptr&lt; parallel::FanSharedContext &gt;</type>
      <name>create_parallel_context</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a10235651e6e5dd36fe42c6e9ea247322</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_variables</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a4e52d2968700258475daad4ba74248bd</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_dynamics_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a660a5af9216a5875b569373ef4224566</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_general_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>aaf255806bbf9c8834963cc628500bb26</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_internal_constraints</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a254ae9c50d1a9e017cab376c20b7c875</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>nx</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a8c4939f055c0ab87b9ca9732330b9655</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>residual_dynamics_constr</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ae0533000a2a113802888e204ad272160</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;x, const FanStorage &amp;b, FanStorage &amp;Mxb) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_dynamics_constr</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a474871c96782fcb21afbc3b795ece705</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;λ, FanStorage &amp;Mᵀλ, bool accum=false) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>general_constr</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ae61deb015c2d66a86597a5868994f504</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;ux, FanStorage &amp;DCux) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_general_constr</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a114ff9f71ae38deccfee48ea483ef253</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;y, FanStorage &amp;DCᵀy) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_general_constr</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a83306d6e58dce0d47ac080b02ff8315d</anchor>
      <arglist>(const FanStorage &amp;y, FanStorage &amp;DCᵀy) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a647efc6dd644a58d7cfbcaea0e769d19</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;ux, value_type α, const FanStorage &amp;q, value_type β, FanStorage &amp;grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient_regularized</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a5bf58642defe3ca9cea359df832de603</anchor>
      <arglist>(Context &amp;ctx, value_type γ, const FanStorage &amp;ux, const FanStorage &amp;ux0, const FanStorage &amp;q, FanStorage &amp;grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient_remove_regularization</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a82f98b0958dd342589da2eb7dc90514d</anchor>
      <arglist>(Context &amp;ctx, value_type γ, const FanStorage &amp;x, const FanStorage &amp;x0, FanStorage &amp;grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a28c0975c1379e0a2c5c839f250f0f9da</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, const FanStorage &amp;Σ, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a3817ab8319f74212849a0e5f15c25b91</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, const FanStorage &amp;Σ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_forward</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>aa17310ed573668ff5cca02eb519f5052</anchor>
      <arglist>(Context &amp;ctx, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>af82023cc29193e1f1c576585232ccc21</anchor>
      <arglist>(Context &amp;ctx, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_mul</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a11d61d6f9d201f5d1031454a277b8ba9</anchor>
      <arglist>(Context &amp;ctx, FanStorage &amp;ux, FanStorage &amp;λ, FanStorage &amp;Mᵀλ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_solve</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a3fad76c1aa59b2943be9f2c061061bd2</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;ΔΣ, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_impl</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a781e0d5f8fe54bff428c708a4855b860</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, const FanStorage &amp;Σ, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a2ec04c25e96a32f669f27bfd7ce1a4df</anchor>
      <arglist>(Context &amp;ctx, FanStorage &amp;ux, FanStorage &amp;λ, std::optional&lt; FanStorage &gt; Mᵀλ=std::nullopt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_u0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a66fb1f9ad989ac0f0f0b340456e0d128</anchor>
      <arglist>(FanStorage &amp;ux) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_λ0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a5d6c91083fb69ddca9f391b176853b86</anchor>
      <arglist>(index_t branch, FanStorage &amp;ux, FanStorage &amp;λ) const</arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a09c4d3e115eb38dc4de7f48cb92507b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TricyqleSolver&lt; VL, T, DefaultOrder, Ctx &gt;</type>
      <name>tricyqle_t</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a8a15f1d42833016f9047f5ad59c3870d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Ctx</type>
      <name>Context</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a4e6160cb69ff4ddcdd5ac5b1c90189ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TridiagonalSolver&lt; value_type &gt;</type>
      <name>SolverLast</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ac350f4a0085e76da77988097c5bdb499</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tricyqle_t::SharedContext</type>
      <name>SharedContext</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a5bfd16c3d3599f4ffdf1992715c25e05</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_λ0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a9f8327fd19588b5c8febbbecc16d22b9</anchor>
      <arglist>(index_t branch, FanStorage &amp;λ, const FanStorage &amp;ux, const FanStorage &amp;Σ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_u0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>a5db94e3a5d6e223a889f5049f104d981</anchor>
      <arglist>(FanStorage &amp;ux, value_type γ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_solve_λ0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ae1a1a9f109c742b3d24494687556c9fe</anchor>
      <arglist>(index_t branch, FanStorage &amp;λ, const FanStorage &amp;ux)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_solve_u0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneSolver.html</anchorfile>
      <anchor>ae47ceec5c221db9fa9ad59dbdeecb982</anchor>
      <arglist>(FanStorage &amp;ux, const FanStorage &amp;ΔΣ)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::FanCyqloneStorage</name>
    <filename>structfancyqlone_1_1FanCyqloneStorage.html</filename>
    <templarg>class T</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a6ec98c6f163bb531bada151c008a236d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, 1 &gt;</type>
      <name>one_t</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>acd83bc1d714328f4ddae3033ed05f93a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t, one_t, one_t, StorageOrder::ColMajor &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a85b226aaa8ffb7ff4318ab74ab58eae7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanOCPStorage::Solution</type>
      <name>Solution</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>ab35b6607f45ff814ab2e55478075d69d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanOCPStorage::KKTError</type>
      <name>KKTError</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a23824654897f2a1a0279ff95478b1acc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_impl</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a8c52c7b2663ff80de9ceac0dabf903d6</anchor>
      <arglist>(const FanOCPStorage &amp;focp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a339ecb75ea4ed5a35645c620ae84b6fe</anchor>
      <arglist>(const FanOCPStorage &amp;focp)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>reconstruct_ineq_multipliers</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a5d580c0a5bea7fb7aafc0d644c0bc500</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_compressed) const</arglist>
    </member>
    <member kind="function">
      <type>Solution</type>
      <name>reconstruct_solution</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>ae4c0e73f39640b170695a8af7e3f49c6</anchor>
      <arglist>(const FanOCPStorage &amp;ocp, std::span&lt; const value_type &gt; ux_compressed, std::span&lt; const value_type &gt; y_compressed, std::span&lt; const value_type &gt; λ_compressed) const</arglist>
    </member>
    <member kind="function">
      <type>KKTError</type>
      <name>compute_kkt_error</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a989852630be997957bb37f59a0ffe52a</anchor>
      <arglist>(const FanOCPStorage &amp;ocp, std::span&lt; const value_type &gt; ux_compressed, std::span&lt; const value_type &gt; y_compressed, std::span&lt; const value_type &gt; λ_compressed) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static FanCyqloneStorage</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a35b7ff7479d884e4f2a37e6a1ef49381</anchor>
      <arglist>(const FanOCPStorage &amp;focp, index_t ny_0=-1)</arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>num_branches</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a2edb5de01f94b6e50b71467f7151ac06</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>nu</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a6cddf4f6ec1f966952db0b75df952851</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>ny_0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a36821ae6d0eef1ebc044e8e2be1bf5ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; CyqloneStorage&lt; value_type &gt; &gt;</type>
      <name>branches</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>ae4b8f968e3a02dee613d1eaeb80845b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; matrix &gt;</type>
      <name>Bs</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a60ad64d070be10f1728f186b099c142c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>r0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a73a67848f81c2c61332d0f46585cfa32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>R0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a1b0e6ca2aad21bf14f9e883b0b0d5dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>D0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a1876dc6cde65353fe8454f60d2d0e7d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>b_min_0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>a9b12f953ff5e5d7e3327232668ee17a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>b_max_0</name>
      <anchorfile>structfancyqlone_1_1FanCyqloneStorage.html</anchorfile>
      <anchor>ac416935a5c84944b3969779454e90246</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::FanOCPStorage</name>
    <filename>structfancyqlone_1_1FanOCPStorage.html</filename>
    <class kind="struct">fancyqlone::FanOCPStorage::Solution</class>
    <member kind="function">
      <type>index_t</type>
      <name>num_branches</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage.html</anchorfile>
      <anchor>a4c3dd985a1d707518b514703c4346932</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>KKTError</type>
      <name>compute_kkt_error</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage.html</anchorfile>
      <anchor>a15304a09f8cf9810fd209b73714678b9</anchor>
      <arglist>(const Solution &amp;sol, bool hpipm=false) const</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; LinearOCPStorage &gt;</type>
      <name>ocps</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage.html</anchorfile>
      <anchor>af4a8d99749d3c45c066a3b0a7afed335</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::FanOCPStorage::KKTError</name>
    <filename>structfancyqlone_1_1FanOCPStorage.html</filename>
    <anchor>structfancyqlone_1_1FanOCPStorage_1_1KKTError</anchor>
    <member kind="variable">
      <type>real_t</type>
      <name>stationarity</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage.html</anchorfile>
      <anchor>a65ceb483567e22193113b0d2e63c287e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>inequality_residual</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage.html</anchorfile>
      <anchor>abf54de362a996127b86c8ae3c277c686</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>equality_residual</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage.html</anchorfile>
      <anchor>a41f367640676291ff83b2af6cb2e848f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>complementarity</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage.html</anchorfile>
      <anchor>a2f48cdf3b418a23f7960ee7ab3f3552b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::FanOCPStorage::Solution</name>
    <filename>structfancyqlone_1_1FanOCPStorage_1_1Solution.html</filename>
    <member kind="function">
      <type>void</type>
      <name>print</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a663b8ebeeabc4986f9b470b54dff84e9</anchor>
      <arglist>(std::vector&lt; OCPDim &gt; OCPdims) const</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; LinearOCPStorage::Solution &gt;</type>
      <name>solutions</name>
      <anchorfile>structfancyqlone_1_1FanOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a28b6e9d1e700f519aa90712eb5084bcd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::FanStorage_t</name>
    <filename>structfancyqlone_1_1FanStorage__t.html</filename>
    <templarg>class matrix</templarg>
    <templarg>class T</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a46cdde81757188ec5dcd43a52c74b68d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, 1 &gt;</type>
      <name>one_t</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a057eda69b87b707e8d837e55b52f5660</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TridiagonalSolver&lt; value_type &gt;::matrix</type>
      <name>matrix_f</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a013f31d8806b6c48cb2318fb12f86547</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FanStorage_t</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a357b8eeb32d2baaf7d38038b308b5a4a</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FanStorage_t</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>aefce42a2f55e98fe85da66d0211bbd03</anchor>
      <arglist>(const FanStorage_t &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>FanStorage_t &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a5ec2dada337caab1ef06ad3afa2f7687</anchor>
      <arglist>(const FanStorage_t &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>FanStorage_t &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a3885704111079335dc4deca9b6f37937</anchor>
      <arglist>(FanStorage_t &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FanStorage_t</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>ad017d6173872183615c70cedb5f8f71a</anchor>
      <arglist>(FanStorage_t &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>FanStorage_t&lt; matrix, value_type, DefaultOrder &gt;</type>
      <name>clone</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>ae3f41fdfa5a4f6d746077d04dbca5f04</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; matrix &gt;</type>
      <name>branches</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a9c7a03c819601e2c5aff9e80b15fe251</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix_f</type>
      <name>first</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>ac8551afd82d7328c539f5a53d17dff8e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::LinearOCPSparseQP</name>
    <filename>structfancyqlone_1_1LinearOCPSparseQP.html</filename>
    <member kind="function">
      <type>KKTMatrix</type>
      <name>build_kkt</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a5c4ca071e6db0744b9ec8abe0cc7adb6</anchor>
      <arglist>(real_t S, std::span&lt; const real_t &gt; Σ, std::span&lt; const bool &gt; J) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static LinearOCPSparseQP</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>af30939fede774a69eb4e39b66da60d50</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>Q_outer_ptr</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a54435b850af2bc1afd33701923324067</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>Q_inner_idx</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a13a4a0c8b4c7c582ea6a06c816312542</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>Q_values</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a63209d5028ba0623ef973544b9f28b42</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SparseCSC&lt; index_t, index_t &gt;</type>
      <name>Q_sparsity</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a76a6dafd9e1a49362185bb5bdcbb322e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>A_outer_ptr</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>abc83630805abbd3468793fb492106ff3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>A_inner_idx</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a4f5b9cf21c823e1168591a5fc070d459</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>A_values</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>ad2a8dba8fa4ae3985dddd2bf59310534</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SparseCSC&lt; index_t, index_t &gt;</type>
      <name>A_sparsity</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a2ec98f63a335ef2d6f2acbcbf46fbdd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>n</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a533ee171212a4871ac0ff18888344129</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>m_eq</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a025f82564f60c14711d8e0d9a39f32b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>m_ineq</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>ae5e563eb846a572a7394df8f9c34ab75</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::LinearOCPSparseQP::KKTMatrix</name>
    <filename>structfancyqlone_1_1LinearOCPSparseQP.html</filename>
    <anchor>structfancyqlone_1_1LinearOCPSparseQP_1_1KKTMatrix</anchor>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>outer_ptr</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a0827018682359b844c1f937adfa83769</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>inner_idx</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a167c5aae5a809505b3a625fb332de852</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>values</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a549e7e935fac14391f42237aee110f88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SparseCSC&lt; index_t, index_t &gt;</type>
      <name>sparsity</name>
      <anchorfile>structfancyqlone_1_1LinearOCPSparseQP.html</anchorfile>
      <anchor>a68d955ddf3a22d32d10c6909f5814cb2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::LinearOCPStorage</name>
    <filename>structfancyqlone_1_1LinearOCPStorage.html</filename>
    <class kind="struct">fancyqlone::LinearOCPStorage::Solution</class>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>H</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ac9ffaec3d88ad5fe53e953c4a97fcc29</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>Q</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>aaced9f219b04dc25c0817bc04b9890d9</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>R</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ab0b91b1dac835a47452d45c0d2d9f1ee</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>S</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a46055cc9e375ddd69ea173667928d52a</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>S_trans</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a9d642f91f961e14b7ed372b34c5d8371</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>CD</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a79fd5025e97ec571a22aac597d2e793c</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>C</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ad991b26c207c150cf4117e3dea673b6d</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>D</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a755b42ad7574b683175254de50793aa0</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>AB</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>af9aaaa55d850faa3fd5b676f05f94c49</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>A</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>aaea931c3de39b21c1adc2adda6927391</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>B</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a069e76a6c76bd62ab2eb0c5546f74897</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>H</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a898167d9045f1a53b782cc01a6977455</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>Q</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a161dda1b8f2ca0362cf590e8af5a8104</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>R</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ac91c7428e235f3af6d7145fbd1de2b79</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>S</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a17b94bf468910584e3a2c1721fcf456f</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>S_trans</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ac020c63b3b06275c5ed6c428a11ba2a5</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>CD</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a5c9cd8631b3474cdb2b8fc2f0e5a47f8</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>C</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a402fee7a6439b63c07dcc69a1d32307f</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>D</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>af7c6fa03bed907a9b69c0577599bb0e2</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>AB</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a06f7a193e7eceacb89f26f26cfc3a6c2</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>A</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ac582fa61972da14bde570b3aa903e72a</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>B</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a9cfc18dbb90e6e731da5d12339d8f0ed</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_variables</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ad55df437b96b1ef8790814a9e048900e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_constraints</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a3c5d86cdf3f19586f414847529a5671c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_dynamics_constraints</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>add7bf920f26e1a37e0dd00d7aeecabc7</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>qr</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a087bd89a45d03b02126021b5fec8d1df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>qr</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a7e1dde39c63e9ea014e1327d17297c12</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>q</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ab03b4cc3577893f2c19db9fd2901ebab</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>r</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ae137ef05e092ee1a8b81e155c520c429</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>b</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a8aea35b5a5e016e82ec0f62bc9202c8a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>b</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a5bf0f53aa9f74b0655fa265dac731e69</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>b_min</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a3d26901e03695e9c20cfc4a762574b6c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>b_min</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ab68b7baa1d4e7f1048557a76f869703b</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>b_max</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a9537f3f21aa23aadbd02eecde6f92e35</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>b_max</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>aeb5a3dd4688593f16af7906c71d70b8d</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>qr</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>af544b91076b1169d827c4f92c33f4835</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>qr</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>afb8b8c56d0d49ad8044e038e7f27fc6a</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>q</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a8d7d72ffe088152a7a00f2a31169c015</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>r</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ae7e3db06e0885525cca86d75c4f0bcac</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>b</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a4ca0893ec5631a00781863f12e8bf4ff</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>b</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>acbbeaad6c130f73a454481cc7f8efe57</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>b_min</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>abb328430a5372685904c05cdd7398f86</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>b_min</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a223a115d5f2ef41ffc247011ccfe783e</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>b_max</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a3a8fd69282b0fdf34beef684095eaeff</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>b_max</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>abaaacb188f51bf9564e7193a9eb29fbb</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>KKTError</type>
      <name>compute_kkt_error</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a12952b0941c12e01365138e4638a182f</anchor>
      <arglist>(const Solution &amp;sol) const</arglist>
    </member>
    <member kind="function">
      <type>KKTErroru0Seperated</type>
      <name>compute_kkt_error_u0_seperated</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a5a1e18d96a195c6168118b8b077dec79</anchor>
      <arglist>(const Solution &amp;sol) const</arglist>
    </member>
    <member kind="function">
      <type>KKTErroru0x0Seperated</type>
      <name>compute_kkt_error_u0x0_seperated</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a131401d2e88983aa79abb0d216707672</anchor>
      <arglist>(const Solution &amp;sol) const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::vector&lt; real_t &gt;</type>
      <name>create_storage</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>aba227f4a469325d9edcbb7b553d0f2f1</anchor>
      <arglist>(OCPDim dim)</arglist>
    </member>
    <member kind="variable">
      <type>OCPDim</type>
      <name>dim</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a27006d25c166fadc27d783dc1da0b2e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>storage</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a481519fd6bca65ed130589a980bc3dd7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::LinearOCPStorage::KKTError</name>
    <filename>structfancyqlone_1_1LinearOCPStorage.html</filename>
    <anchor>structfancyqlone_1_1LinearOCPStorage_1_1KKTError</anchor>
    <member kind="variable">
      <type>real_t</type>
      <name>stationarity</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>af7c894d8059fddc1101c937aa0556ac3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>inequality_residual</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a16a0d8bc8d63222f16c995bc9952bec0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>equality_residual</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a85cd4b55f3f693cc573c555fb26ac328</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>complementarity</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ae6ddeb6b57645deaf3e5c0e72923a113</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::LinearOCPStorage::KKTErroru0Seperated</name>
    <filename>structfancyqlone_1_1LinearOCPStorage.html</filename>
    <anchor>structfancyqlone_1_1LinearOCPStorage_1_1KKTErroru0Seperated</anchor>
    <member kind="variable">
      <type>KKTError</type>
      <name>kkt</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a0c204707ab10bffd8357cc1503733653</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>stationarity_u0</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>ac624c5b93296066077c1272216750fc6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::LinearOCPStorage::KKTErroru0x0Seperated</name>
    <filename>structfancyqlone_1_1LinearOCPStorage.html</filename>
    <anchor>structfancyqlone_1_1LinearOCPStorage_1_1KKTErroru0x0Seperated</anchor>
    <member kind="variable">
      <type>KKTError</type>
      <name>kkt</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>aeaabb155425751a02ea3bf31595ce111</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>stationarity_u0</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>a0b177a3f92d447c2e097079f62154523</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>stationarity_x0</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage.html</anchorfile>
      <anchor>aa00959d7ee2168e5be7550829a98e003</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::LinearOCPStorage::Solution</name>
    <filename>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</filename>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>x</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a38fc48da9dae2a8ed2613d36ded5e64b</anchor>
      <arglist>(OCPDim dim)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>x</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a002eca993d997a23decf68871fae5306</anchor>
      <arglist>(OCPDim dim) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>x</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a96bce03cd9a0c89e6661da490f4f25d4</anchor>
      <arglist>(OCPDim dim, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>x</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a483cf59d3ab18d25caa517332a204826</anchor>
      <arglist>(OCPDim dim, index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>u</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a30a3ab8bb6b2828ba3340a91e796e959</anchor>
      <arglist>(OCPDim dim)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>u</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>aa92e0ba654ac2377dd01eba545a74a9f</anchor>
      <arglist>(OCPDim dim) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>u</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>aadc39288d4b51c61beaf7b3011f38995</anchor>
      <arglist>(OCPDim dim, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>u</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a28030c52985fc5c12fe49c982f19acc1</anchor>
      <arglist>(OCPDim dim, index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>λ</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>aff76f875493b2c24c38771d4ea685dac</anchor>
      <arglist>(OCPDim dim)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>λ</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>ae63280f81807ab174dc4d021c994247e</anchor>
      <arglist>(OCPDim dim) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>λ</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>aaff7a10be2d2faf11b836952cf01285c</anchor>
      <arglist>(OCPDim dim, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>λ</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>ae33291efa470120636922391653d713d</anchor>
      <arglist>(OCPDim dim, index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; real_t, index_t &gt;</type>
      <name>y</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>ab279f7449e63b02bb491ee9d82eb0a18</anchor>
      <arglist>(OCPDim dim, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>guanaqo::MatrixView&lt; const real_t, index_t &gt;</type>
      <name>y</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a0e7e04d78e768f489240acb22b81ed15</anchor>
      <arglist>(OCPDim dim, index_t i) const</arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>solution</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>acedcefabe390351bd8f1e87ea445d5a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>inequality_multipliers</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>ad75aed38816e87f9ba0439f68891d8e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>equality_multipliers</name>
      <anchorfile>structfancyqlone_1_1LinearOCPStorage_1_1Solution.html</anchorfile>
      <anchor>a57e5507ddbe2f6e051d258223092e21e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::matio_traits</name>
    <filename>namespacefancyqlone.html</filename>
    <anchor>structfancyqlone_1_1matio__traits</anchor>
    <templarg>class T</templarg>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::matio_traits&lt; double &gt;</name>
    <filename>structfancyqlone_1_1matio__traits_3_01double_01_4.html</filename>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>type</name>
      <anchorfile>structfancyqlone_1_1matio__traits_3_01double_01_4.html</anchorfile>
      <anchor>a75c12dd0742ce441af108d7ea9949d02</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>class_</name>
      <anchorfile>structfancyqlone_1_1matio__traits_3_01double_01_4.html</anchorfile>
      <anchor>ae793f2088ffa8b03402f5fb6108a2998</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::matio_traits&lt; float &gt;</name>
    <filename>structfancyqlone_1_1matio__traits_3_01float_01_4.html</filename>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>type</name>
      <anchorfile>structfancyqlone_1_1matio__traits_3_01float_01_4.html</anchorfile>
      <anchor>ad2abc92aee87b81cab99623025523b5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>class_</name>
      <anchorfile>structfancyqlone_1_1matio__traits_3_01float_01_4.html</anchorfile>
      <anchor>a4f314fe68d7bb61e087dbd7b90955735</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::matio_traits&lt; I &gt;</name>
    <filename>structfancyqlone_1_1matio__traits_3_01I_01_4.html</filename>
    <templarg>std::unsigned_integral I</templarg>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>type</name>
      <anchorfile>structfancyqlone_1_1matio__traits_3_01I_01_4.html</anchorfile>
      <anchor>a87592014cd12065e36dd71fd5dc7a0e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>class_</name>
      <anchorfile>structfancyqlone_1_1matio__traits_3_01I_01_4.html</anchorfile>
      <anchor>a54f677ac9b1f28540d98537ce1c3c36c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fancyqlone::NeumaierSum</name>
    <filename>classfancyqlone_1_1NeumaierSum.html</filename>
    <templarg>class T</templarg>
    <member kind="function">
      <type></type>
      <name>NeumaierSum</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a071dc37e60322a006c21585ea1eec407</anchor>
      <arglist>(T sum, T compensation)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>NeumaierSum</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>adc8f65316ae70c2b00add4507c497349</anchor>
      <arglist>(T value={})</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator T</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>ae7e835e9873b2305581e673744385ea3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>get</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a233655bb8696ab01177d35e624a6c73b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>NeumaierSum</type>
      <name>operator-</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a0b91b6662611c3350e081696ef9e4c5b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>NeumaierSum &amp;</type>
      <name>operator+=</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>ac2a6eed64beecd1dd227e0b28343cfe5</anchor>
      <arglist>(T v)</arglist>
    </member>
    <member kind="function">
      <type>NeumaierSum &amp;</type>
      <name>operator+=</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a1430ab4579f601ea4deed293627c4d2d</anchor>
      <arglist>(const NeumaierSum &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>NeumaierSum &amp;</type>
      <name>operator-=</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a7f274e5867b69c578e5ae122cd3fc576</anchor>
      <arglist>(T v)</arglist>
    </member>
    <member kind="function">
      <type>NeumaierSum &amp;</type>
      <name>operator-=</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>ad29ba11ff37e0c2a7f06de7ce6d542a1</anchor>
      <arglist>(const NeumaierSum &amp;other)</arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>sum</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>af95863352c7298d1003f3cdf1a20c099</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>compensation</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a96cde5a18358f2084270b42ddea67dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator+</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>aa1a0ff64fbd206621f3932fd3d889cbd</anchor>
      <arglist>(NeumaierSum lhs, T rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator+</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a79b2b0a27d953a81fd12901e4aa92482</anchor>
      <arglist>(T lhs, NeumaierSum rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator+</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a81cc781ba392c62870490923aec1b788</anchor>
      <arglist>(NeumaierSum lhs, NeumaierSum rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator-</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a7489c5f2d5249961c8edca3e95be9b30</anchor>
      <arglist>(NeumaierSum lhs, T rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator-</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a561f4df562069d61ae54b6fc1e5e5ede</anchor>
      <arglist>(T lhs, NeumaierSum rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator-</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a7f28fe9f7125430a30e6a086a5812bd7</anchor>
      <arglist>(NeumaierSum lhs, const NeumaierSum &amp;rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator*</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a27ec7543c36110a2281af26a9bedd8e5</anchor>
      <arglist>(NeumaierSum lhs, NeumaierSum rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator*</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a39555a9263f53e921f6606941f7325fe</anchor>
      <arglist>(NeumaierSum lhs, T rhs)</arglist>
    </member>
    <member kind="friend">
      <type>friend NeumaierSum</type>
      <name>operator*</name>
      <anchorfile>classfancyqlone_1_1NeumaierSum.html</anchorfile>
      <anchor>a78ba89c6c79ffd4b81408693c4b47171</anchor>
      <arglist>(T lhs, NeumaierSum rhs)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::OCPDim</name>
    <filename>structfancyqlone_1_1OCPDim.html</filename>
    <member kind="variable">
      <type>index_t</type>
      <name>N_horiz</name>
      <anchorfile>structfancyqlone_1_1OCPDim.html</anchorfile>
      <anchor>a082c467cf2ca52f4b594977905447ead</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>nx</name>
      <anchorfile>structfancyqlone_1_1OCPDim.html</anchorfile>
      <anchor>a34deb1679abea1ea44c9deceb4c1f7a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>nu</name>
      <anchorfile>structfancyqlone_1_1OCPDim.html</anchorfile>
      <anchor>a68bf290d668cdd356eb56e665451345a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>ny</name>
      <anchorfile>structfancyqlone_1_1OCPDim.html</anchorfile>
      <anchor>ad5131bd4667597f367fdb48c14b29d46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>ny_N</name>
      <anchorfile>structfancyqlone_1_1OCPDim.html</anchorfile>
      <anchor>a6e5441c0b740c5deb2d1fbfa05c2db38</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend constexpr bool</type>
      <name>operator==</name>
      <anchorfile>structfancyqlone_1_1OCPDim.html</anchorfile>
      <anchor>a4511f2022217e0599d1d2bc20054f1c9</anchor>
      <arglist>(OCPDim, OCPDim)=default</arglist>
    </member>
    <member kind="friend">
      <type>friend constexpr bool</type>
      <name>operator!=</name>
      <anchorfile>structfancyqlone_1_1OCPDim.html</anchorfile>
      <anchor>aebd30f5cebe1ca27cfdfd8354a0fa805</anchor>
      <arglist>(OCPDim, OCPDim)=default</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::parallel::arrival_token_fan</name>
    <filename>namespacefancyqlone_1_1parallel.html</filename>
    <anchor>structfancyqlone_1_1parallel_1_1arrival__token__fan</anchor>
    <member kind="typedef">
      <type>typename Context&lt; FanSharedContext &gt;::arrival_token</type>
      <name>total_token_t</name>
      <anchorfile>namespacefancyqlone_1_1parallel.html</anchorfile>
      <anchor>ac6cba6f4dba350bbb632e73a06180bd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename Context&lt; SharedContext &gt;::arrival_token</type>
      <name>branch_token_t</name>
      <anchorfile>namespacefancyqlone_1_1parallel.html</anchorfile>
      <anchor>a4c156be5fa172a625fc2c1b03e8cea62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::optional&lt; total_token_t &gt;</type>
      <name>total_token</name>
      <anchorfile>namespacefancyqlone_1_1parallel.html</anchorfile>
      <anchor>a73ab7fe0ff0bee48bbaaf1dc706066da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>branch_token_t</type>
      <name>branch_token</name>
      <anchorfile>namespacefancyqlone_1_1parallel.html</anchorfile>
      <anchor>afb0489d7d36557e4012f496d2152baf4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::parallel::arrival_token_typed_fan</name>
    <filename>namespacefancyqlone_1_1parallel.html</filename>
    <anchor>structfancyqlone_1_1parallel_1_1arrival__token__typed__fan</anchor>
    <templarg>class T</templarg>
    <member kind="typedef">
      <type>typename FanSharedContext::barrier_type::template arrival_token_typed&lt; T &gt;</type>
      <name>total_token_t</name>
      <anchorfile>namespacefancyqlone_1_1parallel.html</anchorfile>
      <anchor>a3a9cf4feb89276441339e4a432bd0278</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename SharedContext::barrier_type::template arrival_token_typed&lt; T &gt;</type>
      <name>branch_token_t</name>
      <anchorfile>namespacefancyqlone_1_1parallel.html</anchorfile>
      <anchor>a926f1b76ff6313b14d2a6affc127a3af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>total_token_t</type>
      <name>total_token</name>
      <anchorfile>namespacefancyqlone_1_1parallel.html</anchorfile>
      <anchor>a82e933c3174b55edcdb19eb4820a1da5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>branch_token_t</type>
      <name>branch_token</name>
      <anchorfile>namespacefancyqlone_1_1parallel.html</anchorfile>
      <anchor>afa581b036dfa9ea99c1d7e3ed3a9f3df</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::parallel::Context</name>
    <filename>structfancyqlone_1_1parallel_1_1Context.html</filename>
    <templarg>class SC</templarg>
    <member kind="typedef">
      <type>SC</type>
      <name>shared_context_type</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a2db636541de0063026a9e3ad8da2e0d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename shared_context_type::barrier_type::arrival_token</type>
      <name>arrival_token</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a2f86e4fbd108b71a537b16af315451f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>shared_context_type::barrier_type::template arrival_token_typed&lt; T &gt;</type>
      <name>arrival_token_typed</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>ae3857bcfb854a3bb15040c7a12fdd8a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>shared_context_type::barrier_type::template shuffle_token&lt; T &gt;</type>
      <name>shuffle_token</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>ac6f9cbb4caec54f521adb136c6e616b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_thr</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a8d0ae0086e4de699f62e8ae07d5a5ead</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_master</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>adb10b8647aeca664a177bc1fb4a5bf03</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>arrival_token</type>
      <name>arrive</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a084bced4dc23604ffe14862428c51cd0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>shared_context_type::barrier_type::arrival_token</type>
      <name>arrive_with_completion</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>ac92bc73d97e15ecff0b20bcc0e74688e</anchor>
      <arglist>(C func)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wait</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>ad697aa2df2923ddfac099279138955cf</anchor>
      <arglist>(arrival_token &amp;&amp;token)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>arrive_and_wait</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>aa7492ccf3bc500d6ae33a6b3a27fee1c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>arrive_and_wait</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a1ccbb1da1cdbf9299790d8cbb4bc7f99</anchor>
      <arglist>(int line)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>broadcast</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a80c2342335200ce3f89ff0bfbd0ca4d5</anchor>
      <arglist>(T x, index_t src=0)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>call_broadcast</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a3626aa7c4c2f58da58667c480d011979</anchor>
      <arglist>(F &amp;&amp;f, Args &amp;&amp;...args) -&gt; std::invoke_result_t&lt; F, Args... &gt;</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>arrive_reduce</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>aee7792cf9250cf101393ed3835542c73</anchor>
      <arglist>(T x, F func)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>arrive_reduce_with_completion</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>ad51bec8e4bcfff3ad1f381532b054bba</anchor>
      <arglist>(T x, F func, CF completion)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>wait_reduce</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a532b168b53b885631647084ebc694a79</anchor>
      <arglist>(arrival_token_typed&lt; T &gt; &amp;&amp;token)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>reduce</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>ad7b25f991d95093cda5f0410ba969559</anchor>
      <arglist>(T x, F func)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>reduce</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a68c2f3d619808b7cdd6b3e7f9bfd6314</anchor>
      <arglist>(T x)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>run_single_sync</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a2aac3724d3b2c1830193e74dea5d4e84</anchor>
      <arglist>(F &amp;&amp;f)</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>shuffle_wait</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a9ef01ebbf9c845e81946384b1eeaddc0</anchor>
      <arglist>(shuffle_token&lt; T &gt; &amp;&amp;token, F &amp;&amp;func)</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>shuffle_wait</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>ae0a2ce33c08b3cb64bca293ee631079a</anchor>
      <arglist>(shuffle_token&lt; T &gt; &amp;&amp;token)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>shuffle_rotr_start</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a45079b7a8eb2c81181570f19c21f8c08</anchor>
      <arglist>(T x, uint32_t n)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>shuffle_rotl_start</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a311d4e463f9a3a38be243ca4286bc6a9</anchor>
      <arglist>(T x, uint32_t n)</arglist>
    </member>
    <member kind="variable">
      <type>shared_context_type &amp;</type>
      <name>shared</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a63364b83ce8310ae9745bcedcee739ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>index</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>a44ef7d4977aad75037a4b302cf4cdafa</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend constexpr bool</type>
      <name>operator==</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1Context.html</anchorfile>
      <anchor>ae464c8a4dc0d8acc3e410fa51d3c33fd</anchor>
      <arglist>(const Context &amp;a, const Context &amp;b)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::parallel::FanContext</name>
    <filename>structfancyqlone_1_1parallel_1_1FanContext.html</filename>
    <templarg>class SC</templarg>
    <member kind="typedef">
      <type>SC</type>
      <name>shared_context_type</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a75bb7fe3d239e1d54b71964da0f8a946</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanSharedContext::barrier_type::template arrival_token_typed&lt; T &gt;</type>
      <name>arrival_token_typed</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>abcebbd69c08e5b9de9e02bc9af5745d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanSharedContext::barrier_type::arrival_token</type>
      <name>arrival_token</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a2d54a0d78724a9ca3b71c4248257a5d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Context&lt; SharedContext &gt;::arrival_token</type>
      <name>arrival_t</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a6f9841c17f571f356e0514956d6cdfb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Context&lt; FanSharedContext &gt;::arrival_token</type>
      <name>fan_arrival_t</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>ae9b748236e08bd2445358bf2531ced02</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_master</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a088fca5194863e4c521507cb73bc8f18</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>arrive</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>adb9cf462067ee4139a30a890d15089d6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wait</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>aec930e2ae0f2a18c1cfa199e3afd46d3</anchor>
      <arglist>(arrival_token_fan &amp;&amp;token)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>arrive_and_wait</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a5fc2e840fda993098174e8fc7c1e4ef8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>arrive_and_wait</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a33ecc4cf756fdb6560a99872c70e5129</anchor>
      <arglist>(int line)</arglist>
    </member>
    <member kind="function">
      <type>arrival_token_typed_fan&lt; T &gt;</type>
      <name>arrive_reduce</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a80df190d3d9e6d48b17e8f7002bcff36</anchor>
      <arglist>(T x, F func)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>wait_reduce</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a365f8a883ff71b787274825a826312b7</anchor>
      <arglist>(arrival_token_typed_fan&lt; T &gt; &amp;&amp;token)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>reduce</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>acbb9c72671eac2b78f5069248b809619</anchor>
      <arglist>(T x, F func)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>reduce</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a0d7d3a0bcd2c2f4a7d2f261482a17185</anchor>
      <arglist>(T x)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>run_single_sync</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>ad8ad650b5aa60f51ca974216978129be</anchor>
      <arglist>(F &amp;&amp;f)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>broadcast</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>ad8c5bc8bb1d82219d721eb26aa4433d8</anchor>
      <arglist>(T x, index_t src=0)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>call_broadcast</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a6d42b4f9c06f1b875419161fc022add5</anchor>
      <arglist>(F &amp;&amp;f, Args &amp;&amp;...args) -&gt; std::invoke_result_t&lt; F, Args... &gt;</arglist>
    </member>
    <member kind="variable">
      <type>Context&lt; SharedContext &gt;</type>
      <name>branch_ctx</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a1df1bbfcfcd0df73c73b686d48e2860e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Context&lt; FanSharedContext &gt;</type>
      <name>total_ctx</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>aa31104903840ac35304957050809a2cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>index</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanContext.html</anchorfile>
      <anchor>a7c8163be469c138cc103fd24123f7bb5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::parallel::FanSharedContext</name>
    <filename>structfancyqlone_1_1parallel_1_1FanSharedContext.html</filename>
    <member kind="typedef">
      <type>EmptyCompletion</type>
      <name>completion_type</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanSharedContext.html</anchorfile>
      <anchor>a0e95a802af1eee607e7c6eb722652683</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TreeBarrier&lt; completion_type, uint16_t &gt;</type>
      <name>barrier_type</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanSharedContext.html</anchorfile>
      <anchor>a46508c09511c1434210d0a4323b00534</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanSharedContext.html</anchorfile>
      <anchor>ae1e570595df82461a2c3d98d60bc1076</anchor>
      <arglist>(F &amp;&amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_spin_count</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanSharedContext.html</anchorfile>
      <anchor>ac7b9a578485d386e8087b9a07aa2f5ec</anchor>
      <arglist>(uint32_t spin_count)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>set_barrier_spin_count</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanSharedContext.html</anchorfile>
      <anchor>ae548b0de9cfaff7188fae55c22b40685</anchor>
      <arglist>(uint32_t spin_count)</arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>num_thr</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanSharedContext.html</anchorfile>
      <anchor>ad11d7c43b3d5bbd921a78002da8ca378</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; SharedContext &gt;</type>
      <name>branch_contexts</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanSharedContext.html</anchorfile>
      <anchor>aa48580edc575a00f9e58fea36718edc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>barrier_type</type>
      <name>barrier</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1FanSharedContext.html</anchorfile>
      <anchor>a85a92e22f132920240aa9fc16d5957cb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::parallel::SharedContext</name>
    <filename>structfancyqlone_1_1parallel_1_1SharedContext.html</filename>
    <member kind="typedef">
      <type>EmptyCompletion</type>
      <name>completion_type</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1SharedContext.html</anchorfile>
      <anchor>ad4e802147e86e66a1124f364c7580761</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TreeBarrier&lt; completion_type, uint16_t &gt;</type>
      <name>barrier_type</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1SharedContext.html</anchorfile>
      <anchor>a1176a87158faf062ca2f7065b934cedc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1SharedContext.html</anchorfile>
      <anchor>a54d38aec3c99a4c0e26c52497d0a778b</anchor>
      <arglist>(F &amp;&amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_spin_count</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1SharedContext.html</anchorfile>
      <anchor>a8e6fc4617a6024811777da413b9948ef</anchor>
      <arglist>(uint32_t spin_count)</arglist>
    </member>
    <member kind="function">
      <type>uint32_t</type>
      <name>set_barrier_spin_count</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1SharedContext.html</anchorfile>
      <anchor>a113e0a9d7da185a94826bd6f2b6bc203</anchor>
      <arglist>(uint32_t spin_count)</arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>num_thr</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1SharedContext.html</anchorfile>
      <anchor>a3079f49cc415bc93c91aed3ce329cad6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>barrier_type</type>
      <name>barrier</name>
      <anchorfile>structfancyqlone_1_1parallel_1_1SharedContext.html</anchorfile>
      <anchor>a823ede09626d116167d625b151e1a371</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::PCRFactorTest</name>
    <filename>structfancyqlone_1_1PCRFactorTest.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>class T</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>ab4ea1508096c158990a56717f6c29cd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, VL &gt;</type>
      <name>vl_t</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>ad94e27cb46e8c5bd3959dd29d2d6ecf2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, VL *alignof(T)&gt;</type>
      <name>align_t</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>ab038a2fbb41b2bf24cb95d2a509d45d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t, vl_t, index_t, O, align_t &gt;</type>
      <name>bmatrix</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>abf29a1386f68e032d69178d5d182e25f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t, vl_t, vl_t, O, align_t &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>abe00be3f74bdf1880d4f074ce50261ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>matrix&lt; O &gt;::view_type</type>
      <name>mut_view</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>ab377beb800ea9f9659a193e37088cfb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>matrix&lt; O &gt;::const_view_type</type>
      <name>view</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a5861e60daf4395c9385aaa6ba752bdf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_pcr</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>aaec0946d801e4166d33bc201b3feab53</anchor>
      <arglist>(view&lt;&gt; M0, view&lt;&gt; K0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_pcr_level</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a2d8af0c2b9d2b17ca7c3cf48b91c8b70</anchor>
      <arglist>(view&lt;&gt; M0, view&lt;&gt; K0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_pcr</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a77b3751b77ecf849c0236fae3b53a214</anchor>
      <arglist>(mut_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_pcr</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>adb4f297635d57c3689f6f9f10b17f6ce</anchor>
      <arglist>(mut_view&lt;&gt; λ, mut_view&lt;&gt; work_pcr) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_pcr_level</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>af24149fdcc2a048501fe9eed3f232973</anchor>
      <arglist>(mut_view&lt;&gt; λ, mut_view&lt;&gt; work_pcr) const</arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>n</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a07eff6bcfa6e7ce11a1ed316955d77f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bmatrix</type>
      <name>pcr_L</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a113d117185885da769b0034414d8b970</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bmatrix</type>
      <name>pcr_Y</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a10a3e85f7190340076e059d2aeb0f325</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bmatrix</type>
      <name>pcr_U</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>ad507970291a3094117ca6af9a2358884</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>pcr_M</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a88d3919a47233ed248dc1b3267960b82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>work</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a70739b8c1f4acfe1297cb48296acdd4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr index_t</type>
      <name>v</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>aa46683bf8a2e08a9a61f0002969703d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr index_t</type>
      <name>lv</name>
      <anchorfile>structfancyqlone_1_1PCRFactorTest.html</anchorfile>
      <anchor>a2c2279fc5bbb461c717ec71571e613f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::ABSums</name>
    <filename>structfancyqlone_1_1qpalm_1_1ABSums.html</filename>
    <member kind="variable">
      <type>ABSum_t</type>
      <name>a</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1ABSums.html</anchorfile>
      <anchor>ad57c7978b6c189679d0c2378cc684452</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ABSum_t</type>
      <name>b</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1ABSums.html</anchorfile>
      <anchor>a9c0c23060f2da7aeb33710c903b96f82</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>constexpr friend ABSums</type>
      <name>operator+</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1ABSums.html</anchorfile>
      <anchor>ad64dcba97952dece7508e4b6935335ce</anchor>
      <arglist>(const ABSums &amp;lhs, const ABSums &amp;rhs)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::Breakpoint</name>
    <filename>structfancyqlone_1_1qpalm_1_1Breakpoint.html</filename>
    <member kind="function">
      <type>real_t</type>
      <name>α</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Breakpoint.html</anchorfile>
      <anchor>acbd3298232222a11ad0d6e94dd4c512e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Breakpoint.html</anchorfile>
      <anchor>ab259bb40ebec19aab1a538f19443eecb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>δ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Breakpoint.html</anchorfile>
      <anchor>a4ee4b9c5cacbe1ad120c076296e7021b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::BreakpointsResult</name>
    <filename>namespacefancyqlone_1_1qpalm.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1BreakpointsResult</anchor>
    <member kind="variable">
      <type>PartitionedBreakpoints</type>
      <name>bp</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>aafb2edecbcd95f35aa65b5555e94a4bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ABSums</type>
      <name>ab_neg</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ae46b6c81e68f9b46777d44cb84fe3731</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::compute_breakpoints_fn</name>
    <filename>structfancyqlone_1_1qpalm_1_1compute__breakpoints__fn.html</filename>
    <member kind="typedef">
      <type>typename std::remove_cvref_t&lt; Backend &gt;::ineq_constr_vec_t</type>
      <name>vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1compute__breakpoints__fn.html</anchorfile>
      <anchor>a5ac23790c19aaddff4fdfebd4652c564</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>operator()</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1compute__breakpoints__fn.html</anchorfile>
      <anchor>a51acc97adeeba0d7903579ba4ef5015a</anchor>
      <arglist>(Backend &amp;backend, typename Backend::Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const vec_t&lt; Backend &gt; &amp;Σ, const vec_t&lt; Backend &gt; &amp;y, const vec_t&lt; Backend &gt; &amp;Ad, const vec_t&lt; Backend &gt; &amp;Ax, const vec_t&lt; Backend &gt; &amp;b_min, const vec_t&lt; Backend &gt; &amp;b_max) const noexcept(guanaqo::is_nothrow_tag_invocable_v&lt; compute_breakpoints_fn, Backend &amp;, typename Backend::Context &amp;, std::vector&lt; Breakpoint &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp; &gt;)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>operator()</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1compute__breakpoints__fn.html</anchorfile>
      <anchor>ab5299666a22397a875d2ee27a57fb038</anchor>
      <arglist>(Backend &amp;, typename Backend::Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const vec_t&lt; Backend &gt; &amp;Σ, const vec_t&lt; Backend &gt; &amp;y, const vec_t&lt; Backend &gt; &amp;Ad, const vec_t&lt; Backend &gt; &amp;Ax, const vec_t&lt; Backend &gt; &amp;b_min, const vec_t&lt; Backend &gt; &amp;b_max) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CycloneBackendTraits</name>
    <filename>namespacefancyqlone_1_1qpalm.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits</anchor>
    <templarg>class LinearSolver</templarg>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::CyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</name>
    <filename>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::CyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</class>
    <member kind="typedef">
      <type>fancyqlone::CyqloneSolver&lt; VL, real_t, DefaultOrder &gt;</type>
      <name>OCP_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</anchorfile>
      <anchor>ac7a65c66af59bc62f606457f7219e996</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename OCP_t::simd</type>
      <name>simd</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</anchorfile>
      <anchor>abd86bda2ccf3db8deabc697541dd9fee</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>CyqloneStorage&lt;&gt;</type>
      <name>CStorage</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</anchorfile>
      <anchor>a3a7faf5d2728c9e222ebfdcfe1272c7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>LinearOCPStorage</type>
      <name>OCPStorage</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</anchorfile>
      <anchor>a38acbf98ebd1faf2d3584b572ba377a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename OCP_t::template matrix&lt;&gt;</type>
      <name>store_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</anchorfile>
      <anchor>af9dfe2829d972fab0636b84497dd61df</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>WarmStartingStrategy</type>
      <name>warm_start_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</anchorfile>
      <anchor>aae22610f380c019efc1fcc710d5e87b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>supports_factorization_updates</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</anchorfile>
      <anchor>ae842a7bc8ffdda78e6b12eb384c971a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>requires_external_schur_solve</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re6c65b67e443ef0368336d9969a2b2411.html</anchorfile>
      <anchor>ace424e69a4f3cc26f1fc82bd86fcec89</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::CyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</name>
    <filename>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re671af03b46d3359135f59b3fadb28f43.html</filename>
    <templarg>class Tag</templarg>
    <member kind="function">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re671af03b46d3359135f59b3fadb28f43.html</anchorfile>
      <anchor>a2c13f694e25ba9d1692f6d713a453fa8</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="variable">
      <type>friend</type>
      <name>CyQPALMBackend&lt; VL, DefaultOrder, OCP_t &gt;</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re671af03b46d3359135f59b3fadb28f43.html</anchorfile>
      <anchor>a28db13ea6ab4475e59e0cf5829db52b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re671af03b46d3359135f59b3fadb28f43.html</anchorfile>
      <anchor>aea4e22d31583530a17c4e65990673d33</anchor>
      <arglist>(store_t &amp;&amp;o)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>check_dimensions_col</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1CyqloneSolver_3_01VL_00_01re671af03b46d3359135f59b3fadb28f43.html</anchorfile>
      <anchor>a4bd5dd7f76293e94c382e9320d961b9e</anchor>
      <arglist>(const storage_t &amp;other, const index_t &amp;dim_col) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::FanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</name>
    <filename>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::FanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</class>
    <member kind="typedef">
      <type>fancyqlone::FanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt;</type>
      <name>OCP_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</anchorfile>
      <anchor>ad02e72bc31e0f49dace1aafd2876a2a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename OCP_t::simd</type>
      <name>simd</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</anchorfile>
      <anchor>a4e444c87dcbe6e8be7efd65c46f5e5e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanCyqloneStorage&lt;&gt;</type>
      <name>CStorage</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</anchorfile>
      <anchor>abc1b71927c79bd9817ba08b4764e7666</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanOCPStorage</type>
      <name>OCPStorage</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</anchorfile>
      <anchor>a99188b308711fd07e305e8b4aa589f07</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanStorage_t&lt; typename OCP_t::template matrix&lt;&gt; &gt;</type>
      <name>store_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</anchorfile>
      <anchor>a83320b8c1f866583604e51f1a0f1ca70</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanWarmStartingStrategy</type>
      <name>warm_start_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</anchorfile>
      <anchor>a4539f7905e6826d72cbe0e3a84de9b4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>supports_factorization_updates</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</anchorfile>
      <anchor>a20fd14b1fe5833bee51ce28f3d6d5a89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>requires_external_schur_solve</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_01cf9a34b56f7155b9b1c5e99db9f86eb.html</anchorfile>
      <anchor>a6619875c2d09d9ae4cb43b7d2a8781b9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::FanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</name>
    <filename>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</filename>
    <templarg>class Tag</templarg>
    <base>fancyqlone::FanStorage_t&lt; typename OCP_t::template matrix&lt;&gt; &gt;</base>
    <member kind="typedef">
      <type>real_t</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a46cdde81757188ec5dcd43a52c74b68d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, 1 &gt;</type>
      <name>one_t</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a057eda69b87b707e8d837e55b52f5660</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TridiagonalSolver&lt; value_type &gt;::matrix</type>
      <name>matrix_f</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a013f31d8806b6c48cb2318fb12f86547</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>aae2a2a26b28a35d44a988ab665caac66</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>a90683900d656f44b84d0be14e9c79d97</anchor>
      <arglist>(storage_t &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>storage_t &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>a5bd1dc82847e1bb8628f702c0ae6a533</anchor>
      <arglist>(storage_t &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>a85c95628e86edec1fa5f9c18f90c0d27</anchor>
      <arglist>(const storage_t &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>storage_t &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>afb9299ca04a7d46f18861b3556097b0f</anchor>
      <arglist>(const storage_t &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>storage_t</type>
      <name>clone</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>a9910f45a620fd406b34fda676f49fd31</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable">
      <type>friend</type>
      <name>CyQPALMBackend&lt; VL, DefaultOrder, OCP_t &gt;</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>aafc7d5c618cc70086433570e64394fc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; matrix &gt;</type>
      <name>branches</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a9c7a03c819601e2c5aff9e80b15fe251</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix_f</type>
      <name>first</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>ac8551afd82d7328c539f5a53d17dff8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>a72c329770956629dd71690b6371d4ae1</anchor>
      <arglist>(store_t &amp;&amp;o)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>check_dimensions_col</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>af0a3fb126bdec7d25ddd648e3f14f0b4</anchor>
      <arglist>(const storage_t &amp;other, const index_t &amp;dim_col) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>index_t</type>
      <name>size</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1FanCyqloneSolver_3_01VL_00_06298f63ebf819c6f4e03a5867ab258eb.html</anchorfile>
      <anchor>a454b4effa5b4f4ac699ff798c86c598f</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::SerialFanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</name>
    <filename>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::SerialFanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</class>
    <member kind="typedef">
      <type>fancyqlone::SerialFanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt;</type>
      <name>OCP_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</anchorfile>
      <anchor>aacfdf274421c7a07b6860bd232b1f997</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename OCP_t::simd</type>
      <name>simd</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</anchorfile>
      <anchor>ae4d9b0e2a5ba17afaccd5d59095eea85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanCyqloneStorage&lt;&gt;</type>
      <name>CStorage</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</anchorfile>
      <anchor>aab16680783d32417ea3dbcdf897793b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanOCPStorage</type>
      <name>OCPStorage</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</anchorfile>
      <anchor>ac5d22a9b47bce1fd1470ea3e7d547bc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanStorage_t&lt; typename OCP_t::template matrix&lt;&gt; &gt;</type>
      <name>store_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</anchorfile>
      <anchor>a2d18d3f6f540cd90dc7b20c62e37c3e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanWarmStartingStrategy</type>
      <name>warm_start_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</anchorfile>
      <anchor>a9910164b52784efac2582dd8a616f322</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>supports_factorization_updates</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</anchorfile>
      <anchor>ae70a5dfb434dcb5decf80a44de14dc21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>requires_external_schur_solve</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vee92cd4a6c95599f8faa9bb93bc54908.html</anchorfile>
      <anchor>a32e8821a40f675aace01594552f4b44a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::SerialFanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;::storage_t</name>
    <filename>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</filename>
    <templarg>class Tag</templarg>
    <base>fancyqlone::FanStorage_t&lt; typename OCP_t::template matrix&lt;&gt; &gt;</base>
    <member kind="typedef">
      <type>real_t</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a46cdde81757188ec5dcd43a52c74b68d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, 1 &gt;</type>
      <name>one_t</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a057eda69b87b707e8d837e55b52f5660</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TridiagonalSolver&lt; value_type &gt;::matrix</type>
      <name>matrix_f</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a013f31d8806b6c48cb2318fb12f86547</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>a9214c4a780668c8d80e45806a64cda3f</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>a54ee82962b7ad1ddf63f1c2f6437cd4c</anchor>
      <arglist>(storage_t &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type>storage_t &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>a68020bcc76210eeba608d1ac87e22f7b</anchor>
      <arglist>(storage_t &amp;&amp;)=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>a27d3ff896b58e8ee12e39cd76463f769</anchor>
      <arglist>(const storage_t &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>storage_t &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>aa54f919bbad9174035ec2451ee8bc6d4</anchor>
      <arglist>(const storage_t &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>storage_t</type>
      <name>clone</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>a0f43051311173a151331dd0e85193e51</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable">
      <type>friend</type>
      <name>CyQPALMBackend&lt; VL, DefaultOrder, OCP_t &gt;</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>a35e76e95f355c7bc9a82bf0fbd79dcdf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; matrix &gt;</type>
      <name>branches</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>a9c7a03c819601e2c5aff9e80b15fe251</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix_f</type>
      <name>first</name>
      <anchorfile>structfancyqlone_1_1FanStorage__t.html</anchorfile>
      <anchor>ac8551afd82d7328c539f5a53d17dff8e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>storage_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>a0d22b5abd7033db45b4b6d253ea29fea</anchor>
      <arglist>(store_t &amp;&amp;o)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>check_dimensions_col</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>a6c95b4526aab5adab3b6c575e11d0fb9</anchor>
      <arglist>(const storage_t &amp;other, const index_t &amp;dim_col) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>index_t</type>
      <name>size</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CycloneBackendTraits_3_01fancyqlone_1_1SerialFanCyqloneSolver_3_01Vf7b171bffc760673034c5ba1d9d8bf97.html</anchorfile>
      <anchor>ab0804c69b8e30803894db7667d1093b3</anchor>
      <arglist>() const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CyqloneData</name>
    <filename>group__topic-optimization-solvers-ocp.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1CyqloneData</anchor>
    <member kind="variable">
      <type>std::span&lt; const real_t &gt;</type>
      <name>initial_variables</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ab77a021f2f97c46942f5ad6cd1ac9ff9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::span&lt; const real_t &gt;</type>
      <name>initial_inequality_multipliers</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>a097110456baa8420a2d53664ba93bf05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::span&lt; const real_t &gt;</type>
      <name>initial_equality_multipliers</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>a39f2543d4cdbfec0a25ba7797256efb6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CyQPALMBackend</name>
    <filename>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class LinearSolver</templarg>
    <member kind="function">
      <type>BreakpointsResult</type>
      <name>compute_partition_breakpoints</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ad57a7ec2da64f1a6c14b56b934a4fa33</anchor>
      <arglist>(Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const ineq_constr_vec_t &amp;Σ, const ineq_constr_vec_t &amp;y, const ineq_constr_vec_t &amp;Ad, const ineq_constr_vec_t &amp;Ax, const ineq_constr_vec_t &amp;b_min, const ineq_constr_vec_t &amp;b_max)</arglist>
    </member>
    <member kind="function">
      <type>BreakpointsResult</type>
      <name>compute_partition_breakpoints_cyq</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a6293a02fd5eef14dc6e3a55f3336009f</anchor>
      <arglist>(Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const ineq_constr_vec_t &amp;Σ, const ineq_constr_vec_t &amp;y, const ineq_constr_vec_t &amp;Ad, const ineq_constr_vec_t &amp;Ax, const ineq_constr_vec_t &amp;b_min, const ineq_constr_vec_t &amp;b_max)</arglist>
    </member>
    <member kind="function">
      <type>BreakpointsResult</type>
      <name>compute_partition_breakpoints_fan</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ab8ae67297a7c7838dcabccdf9ab22c35</anchor>
      <arglist>(Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const ineq_constr_vec_t &amp;Σ, const ineq_constr_vec_t &amp;y, const ineq_constr_vec_t &amp;Ad, const ineq_constr_vec_t &amp;Ax, const ineq_constr_vec_t &amp;b_min, const ineq_constr_vec_t &amp;b_max)</arglist>
    </member>
    <member kind="function">
      <type>BreakpointsResult</type>
      <name>compute_partition_breakpoints_sfan</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aa76923d7538180e9b0668be2c7c41134</anchor>
      <arglist>(Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const ineq_constr_vec_t &amp;Σ, const ineq_constr_vec_t &amp;y, const ineq_constr_vec_t &amp;Ad, const ineq_constr_vec_t &amp;Ax, const ineq_constr_vec_t &amp;b_min, const ineq_constr_vec_t &amp;b_max)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>merge_chunk</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a3097ccd26c5f4e36f7a8a35fe59626ec</anchor>
      <arglist>(std::span&lt; const T &gt; chunk, size_t chunk_index, std::span&lt; const std::array&lt; size_t, N &gt; &gt; separators, std::span&lt; T &gt; out)</arglist>
    </member>
    <member kind="friend">
      <type>friend BreakpointsResult</type>
      <name>guanaqo_tag_invoke</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ab7ed283c88ad466c65ddbe181abbf3a8</anchor>
      <arglist>(guanaqo::tag_t&lt; get_breakpoints &gt;, CyQPALMBackend &amp;backend, Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const ineq_constr_vec_t &amp;Σ, const ineq_constr_vec_t &amp;y, const ineq_constr_vec_t &amp;Ad, const ineq_constr_vec_t &amp;Ax, const ineq_constr_vec_t &amp;b_min, const ineq_constr_vec_t &amp;b_max)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>xaxpy</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aebfb84fa9158c853e3dae0de209a64cb</anchor>
      <arglist>(Context &amp;ctx, real_t a, const T &amp;x, U &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>xcopy</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>acd455413fd7af8c61e1872f868e99f38</anchor>
      <arglist>(Context &amp;ctx, const T &amp;x, U &amp;y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_constant</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>afe0728c38f970c8cbb7532d83c00359b</anchor>
      <arglist>(Context &amp;ctx, T &amp;x, const U &amp;y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a652ae94ef8141979bfbfd9a9d04446e7</anchor>
      <arglist>(Context &amp;ctx, real_t s, T &amp;x) const</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>dot</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>abfee2b6b804062d0f379f22785e8c431</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;a, const var_vec_t &amp;b) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>local_dots</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a7ce7fa43b230c3371cebbc769354856a</anchor>
      <arglist>(std::span&lt; real_t, 1+sizeof...(Args)/2 &gt; out, const auto &amp;a, const auto &amp;b, const Args &amp;...others) const</arglist>
    </member>
    <member kind="function">
      <type>std::array&lt; real_t, sizeof...(Args)/2 &gt;</type>
      <name>dots</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a4868afcc9321a7c0550ce2eb6c44bbfc</anchor>
      <arglist>(Context &amp;ctx, const Args &amp;...args) const</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>norm_inf_l1_sq</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a0df9c055c67efeb805a11851a60a7741</anchor>
      <arglist>(Context &amp;ctx, const T &amp;x) const</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>norm_inf</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a146a2158817ed431cd9e085624cfee7b</anchor>
      <arglist>(Context &amp;ctx, const T &amp;x) const</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>norm_squared</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a1da0791174a9099a5fe64485f823ca9b</anchor>
      <arglist>(Context &amp;ctx, const T &amp;x) const</arglist>
    </member>
    <member kind="typedef">
      <type>LinearSolver</type>
      <name>OCP_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>afb57bbfeae38d1925eb8067b6093a3bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>CycloneBackendTraits&lt; OCP_t &gt;</type>
      <name>traits</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ab63c5dd73be163f354cd81b4ef42f03d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>traits::template storage_t&lt; struct ineq &gt;</type>
      <name>ineq_constr_vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a79da3b03b6c91e5d26b418bb8a45f043</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>traits::template storage_t&lt; struct eq &gt;</type>
      <name>eq_constr_vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a6d41a058f02195b6031e2f0c28ca0158</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>traits::template storage_t&lt; struct var &gt;</type>
      <name>var_vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a67d3fa53d355fe0540ab18d1a6a97ef7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>traits::template storage_t&lt; struct active_set &gt;</type>
      <name>active_set_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a37d5737fcf552b904455ae336b503b4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename OCP_t::Context</type>
      <name>Context</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a8d522d2260e6b985d7dcbe3ed6044f4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename traits::simd</type>
      <name>simd</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a53a914cf236a52dd50c340579755e530</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>CyQPALMBackendStats</type>
      <name>Stats</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ab1079b4323fb8daee24b3b542ff26886</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CyQPALMBackend</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ac648c68f03d94009d36e86036f058de0</anchor>
      <arglist>(const traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>run</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a43a7e744787315d4a8a54b9884bc790a</anchor>
      <arglist>(F &amp;&amp;f)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_data</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a523a926325a987322f4954b5829289bd</anchor>
      <arglist>(const traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_b_eq</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a349f1978757cc429bf7a3017922e49ff</anchor>
      <arglist>(std::span&lt; const real_t &gt; b_eq)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_b_lb</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a2d6fbf503fd353692ecdbdab71d5cb2e</anchor>
      <arglist>(std::span&lt; const real_t &gt; b_lb)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_b_ub</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aa174e72ca78fb65bbbff0941f2153ee1</anchor>
      <arglist>(std::span&lt; const real_t &gt; b_ub)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warm_start</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a8721afa95fdbde655868c1f3bd88458b</anchor>
      <arglist>(const var_vec_t &amp;x, const ineq_constr_vec_t &amp;y, const eq_constr_vec_t &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a1f93726d7546efc8491247391fe486fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_var</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ae2048127b0dfcf3a5588738a45669f25</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_eq_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>afb02ba6d3f4b96c68038867dabc61571</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_ineq_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a9fbc2a387ddae4faa6a91d1dec2be1fb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>var_vec_t</type>
      <name>var_vec</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>afb9225d57525e6c71cec2e912dc8a3ee</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>eq_constr_vec_t</type>
      <name>eq_constr_vec</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a2c70de13ad0f45d9ce984b40fb88b16b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>ineq_constr_vec_t</type>
      <name>ineq_constr_vec</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ab0ceaf542e6a828fd0184a1fb12af115</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>active_set_t</type>
      <name>active_set</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a0def49f1383f7bd4ecc5f47d369db220</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_active_set</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aa19ab2006ed9d49dabff30bcd41e7b77</anchor>
      <arglist>(Js &amp;...js) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_var_vec</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>abe2c77fdcab8d809df2603825b08d704</anchor>
      <arglist>(Xs &amp;...xs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_ineq_constr_vec</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ae6073a3b5d845228a709e89c8514d52a</anchor>
      <arglist>(Ys &amp;...ys) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_eq_constr_vec</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a78673c2631ce80dc5a38794119475a92</anchor>
      <arglist>(Λs &amp;...λs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initial_variables</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a2e2e5eb7fd9e1f936f1b68ff43181cc4</anchor>
      <arglist>(Context &amp;ctx, var_vec_t &amp;x) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initial_multipliers_eq</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a84531081ace75ea3deac98e3abcfd1ee</anchor>
      <arglist>(Context &amp;ctx, eq_constr_vec_t &amp;λ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initial_multipliers_ineq</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a0004112524acd86179405d374456330f</anchor>
      <arglist>(Context &amp;ctx, ineq_constr_vec_t &amp;y) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ineq_constr_resid</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>afb3e756dfcdcce5370670403917a1dc9</anchor>
      <arglist>(Context &amp;ctx, const ineq_constr_vec_t &amp;Ax, ineq_constr_vec_t &amp;e) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>project_multipliers_ineq</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a37792ec863ca16c3f49af0888eb1f2af</anchor>
      <arglist>(Context &amp;ctx, ineq_constr_vec_t &amp;y) const</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>ineq_constr_viol</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a287a248e9ed0e1d7a7b9f2dfd79d4871</anchor>
      <arglist>(Context &amp;ctx, const ineq_constr_vec_t &amp;Ax) const</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>ineq_constr_resid_al</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a6ba2e7cc1ba931180f4dbb9f956eccab</anchor>
      <arglist>(Context &amp;ctx, const ineq_constr_vec_t &amp;y, const ineq_constr_vec_t &amp;ŷ, const ineq_constr_vec_t &amp;Σ, ineq_constr_vec_t &amp;e)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>eq_constr_resid</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>adb052fac86a9eb35307b7ef699c0577f</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x, eq_constr_vec_t &amp;Mxb)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mat_vec_MT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ae4450b16f5368eee7c226a1c106fe4be</anchor>
      <arglist>(Context &amp;ctx, const eq_constr_vec_t &amp;λ, var_vec_t &amp;Mᵀλ)</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>unscaled_eq_constr_viol</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aece5df31307b0083861327b7cbb1970c</anchor>
      <arglist>(Context &amp;ctx, const eq_constr_vec_t &amp;Mxb) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mat_vec_AT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>acc332e86b3797e479b9da752bd247ca9</anchor>
      <arglist>(Context &amp;ctx, const ineq_constr_vec_t &amp;y, var_vec_t &amp;Aᵀy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mat_vec_AT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a40ed4f8612c00ce1dfdde3758775f519</anchor>
      <arglist>(const ineq_constr_vec_t &amp;y, var_vec_t &amp;Aᵀy)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mat_vec_A</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aceec2197ca2a3ff95bfab533ee586d40</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x, ineq_constr_vec_t &amp;Ax)</arglist>
    </member>
    <member kind="function">
      <type>ineq_constr_vec_t</type>
      <name>mat_vec_A</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a8136f7f5140d97a534d35240c35ba146</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>grad_f</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a08e718ff100037592143afed0e072f1a</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x, var_vec_t &amp;grad_f)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>grad_f_regularized</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a7fa5d62b3356e1f94a3c0fafba6ba84c</anchor>
      <arglist>(Context &amp;ctx, real_t S, const var_vec_t &amp;x, const var_vec_t &amp;x_reg, var_vec_t &amp;grad_f)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>grad_f_remove_regularization</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a48305a86e780beff8c94e5ecc5ffb82b</anchor>
      <arglist>(Context &amp;ctx, real_t S, const var_vec_t &amp;x, const var_vec_t &amp;x_reg, var_vec_t &amp;grad_f)</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>f_grad_f</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>abf57e6d3831c3fca2ec1b07088c34ef1</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x, var_vec_t &amp;grad_f)</arglist>
    </member>
    <member kind="function">
      <type>std::tuple&lt; real_t, var_vec_t &gt;</type>
      <name>f_grad_f</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a264a8102ae5a651c09261419797756c3</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>update_penalty_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aefcda6b2136e99f703d02bc2f4befec8</anchor>
      <arglist>(Context &amp;ctx, ineq_constr_vec_t &amp;Σ, const ineq_constr_vec_t &amp;e, const ineq_constr_vec_t &amp;e_old, const PenaltySettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_regularization_changed</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a7c829b778a339dd17e02fc3f3484d5df</anchor>
      <arglist>(Context &amp;ctx, real_t S_new, real_t S_old)</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>boost_regularization</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ab472816f8f52a825fcd7839ae4198b28</anchor>
      <arglist>(Context &amp;ctx, real_t S, real_t S_boost)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_penalty_changed</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a23f8623500fb4479646561d73b465edf</anchor>
      <arglist>(Context &amp;ctx, const ineq_constr_vec_t &amp;Σ, index_t num_Σ_changed)</arglist>
    </member>
    <member kind="function">
      <type>const ineq_constr_vec_t &amp;</type>
      <name>Ax_min</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a4ea5f33d4db9ea6e9148cf2c5c72b897</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>const ineq_constr_vec_t &amp;</type>
      <name>Ax_max</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aca8170ba3dd171c1e7d36bb7d63db6ef</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>calc_ŷ_Aᵀŷ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>acf72555503958eca9595e2e91f3c42df</anchor>
      <arglist>(Context &amp;ctx, const ineq_constr_vec_t &amp;Ax, const ineq_constr_vec_t &amp;Σ, const ineq_constr_vec_t &amp;y, ineq_constr_vec_t &amp;ŷ, var_vec_t &amp;Aᵀŷ, active_set_t &amp;J)</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>unscaled_aug_lagr_norm</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aa4bc8c410b273a0b3629fc1ef1f4f3f1</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;grad_f, const var_vec_t &amp;Mᵀλ, const var_vec_t &amp;Aᵀŷ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale_variables</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aedb7e09b10e6961b62516410bcb383fb</anchor>
      <arglist>(std::span&lt; const real_t &gt; in, var_vec_t &amp;out) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale_ineq_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a12482716ef68f26c4ce582faa4188743</anchor>
      <arglist>(std::span&lt; const real_t &gt; in, ineq_constr_vec_t &amp;out) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale_eq_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a8797bc7b2e639c85da2cdf00418de718</anchor>
      <arglist>(std::span&lt; const real_t &gt; in, eq_constr_vec_t &amp;out) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unscale_variables</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a8265f995cd27c83a761908813e76c7b1</anchor>
      <arglist>(const var_vec_t &amp;in, std::span&lt; real_t &gt; out) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unscale_ineq_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a59010269498fc571a6d4902bed528eff</anchor>
      <arglist>(const ineq_constr_vec_t &amp;in, std::span&lt; real_t &gt; out) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unscale_ineq_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a3f9f6ffd55d39960fb814376801f2575</anchor>
      <arglist>(const active_set_t &amp;in, std::span&lt; real_t &gt; out) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unscale_eq_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aadb52cfd3d64e4faef4f9fb11cb7439f</anchor>
      <arglist>(const eq_constr_vec_t &amp;in, std::span&lt; real_t &gt; out) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>active_set_change</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aad7471be099427ab8bb1a2be417d843d</anchor>
      <arglist>(Context &amp;ctx, real_t, const ineq_constr_vec_t &amp;Σ, const active_set_t &amp;J, const active_set_t &amp;J_old)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>recompute_inner</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a0527b5772ee8f9241aefd652212d2ccc</anchor>
      <arglist>(Context &amp;ctx, real_t S, const var_vec_t &amp;x_outer, const var_vec_t &amp;x, const eq_constr_vec_t &amp;λ, var_vec_t &amp;grad, ineq_constr_vec_t &amp;Ax, var_vec_t &amp;Mᵀλ)</arglist>
    </member>
    <member kind="function">
      <type>real_t</type>
      <name>recompute_outer</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a5117f1e7b4e29120db3dfc0256bcc843</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x, const var_vec_t &amp;Aᵀŷ, const eq_constr_vec_t &amp;λ, var_vec_t &amp;grad, ineq_constr_vec_t &amp;Ax, var_vec_t &amp;Mᵀλ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_solve_rhs_norms</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aeac08a45b9e245fdc9ca882f72ff2552</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;d, const eq_constr_vec_t &amp;Δλ, const var_vec_t &amp;grad, const var_vec_t &amp;Mᵀλ, const var_vec_t &amp;Aᵀŷ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_solve_resid_norms</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ab82534ab1b29bcd364d26466ba5036fe</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x, const var_vec_t &amp;d, const var_vec_t &amp;grad, const var_vec_t &amp;ξ, const var_vec_t &amp;Mᵀλ, const var_vec_t &amp;Aᵀŷ, const var_vec_t &amp;MᵀΔλ, const ineq_constr_vec_t &amp;Ad, const active_set_t &amp;J)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>adad14581c51906620c70a01e83c2bd71</anchor>
      <arglist>(Context &amp;ctx, const var_vec_t &amp;x, const var_vec_t &amp;grad, const var_vec_t &amp;Mᵀλ, const var_vec_t &amp;Aᵀŷ, const eq_constr_vec_t &amp;Mxb, real_t S, const ineq_constr_vec_t &amp;Σ, const active_set_t &amp;J, var_vec_t &amp;d, var_vec_t &amp;ξ, ineq_constr_vec_t &amp;Ad, eq_constr_vec_t &amp;Δλ, var_vec_t &amp;MᵀΔλ)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>get_timed</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a1e0031a163e9e3a870835fd5458d262f</anchor>
      <arglist>(Timings::type Timings::*member) const</arglist>
    </member>
    <member kind="function">
      <type>Stats</type>
      <name>clear_stats</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a7b267fec2723cd68578389f4c0416099</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::map&lt; std::string, typename Timings::type &gt;</type>
      <name>clear_timings</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>af6a4737aabe4990406fff0b8723c63c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>OCP_t</type>
      <name>ocp</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aa384fd30cfd154523e098ad60e2e05af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::unique_ptr&lt; typename OCP_t::SharedContext &gt;</type>
      <name>parallel_ctx</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a4763d2fcbf94fc301b9aede505fdaf15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>CyQPALMBackendSettings</type>
      <name>settings</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a00cc65bb52594c1ba5898615a3cb09a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_constr_vec_t</type>
      <name>b_min_strided</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a8f2d91d1920a1436ce55d7a20397bfda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_constr_vec_t</type>
      <name>b_max_strided</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aaeb43bd20cee863e30fef9d3ba0fbb2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>eq_constr_vec_t</type>
      <name>b_eq_strided</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a148b202f74557a91b2cef085efe2c4f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>grad_strided</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ae9fdeda1e957407dfb36a8b20448dfd3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_constr_vec_t</type>
      <name>ΔΣ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a8e5fad7fc00e2eb29b51ed89bf9b04bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::optional&lt; var_vec_t &gt;</type>
      <name>x0</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a75aa6a010dc42f204c1b31251e9b5d18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::optional&lt; ineq_constr_vec_t &gt;</type>
      <name>y0</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aa44b6bcd3ed7b205411fa9068a89e34b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::optional&lt; eq_constr_vec_t &gt;</type>
      <name>λ0</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a82c3c29417f6f0684d9445f0bdf4eee6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::array&lt; size_t, 4 &gt; &gt;</type>
      <name>thread_indices</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a876ecb36641b6e7c01528a40d697faca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; Breakpoint &gt;</type>
      <name>breakpoints_temp</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>acd9e78bf9d0b6d39e21e8fd3403a0642</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>reset_factorization</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a0f53c9a2b34dbaaca09a9cb8cd2d9524</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>update_pending</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a34f4063a12fa22e76b6d7fbe0fbad0ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>num_updates</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a83f3bbea39a83081de3e16995ce8d67c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::unique_ptr&lt; Timings &gt;</type>
      <name>ocp_timings</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>adb4cdf360456d5fa93ee401602ac1ee6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>temp_var</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a35baabb172636f4335c78b1d954965bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>eq_constr_vec_t</type>
      <name>temp_eq</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a5f135d95f7935d1e9a2d93dfbf83d6e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_constr_vec_t</type>
      <name>temp_ineq</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ae6255ab6793f7b278fc2adba5ca522ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Stats</type>
      <name>stats</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a6d6e4c4894c2ae64b829deb113a6bbef</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CyQPALMBackend::PenaltySettings</name>
    <filename>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1CyQPALMBackend_1_1PenaltySettings</anchor>
    <member kind="variable">
      <type>real_t</type>
      <name>θ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a3503b67ca3c03402b5273d5a37d76579</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>Δy</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ad877fb1ad17082c78c1b026cade55930</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>Δy_always</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a47d0baaec2df30f582eb1350147e548b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>max_penalty_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a0a5447b841bc916f4a25432afc7b70e8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CyQPALMBackend::Timings</name>
    <filename>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1CyQPALMBackend_1_1Timings</anchor>
    <member kind="typedef">
      <type>DefaultTimings</type>
      <name>type</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a724c7b117174b08ba4b3074bfefb3754</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>guanaqo::Timed&lt; batmat::DefaultTimings &gt;</type>
      <name>timed_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a5e4f10382b024c9060b47caa3c9eca28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>breakpoints</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a8d8de3a4f42fe8eaf1bf1369c87577f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>calc_y_hat</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>af9ebd22714d0f319719304c64745b0f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>calc_y_hat_AT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a1ba1a48eb82ad0af5df4219a45201c74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>update_active_set_change</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a82417e36933e8ea05f69798390c6e7be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>update_factorization</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a7f355330a9a276fc2c511ddb2290130a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>factor</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a25ddef4fed81210794df479535037dae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>solve</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a967a06e856f0a0e556d4963225a855f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>solve_MT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ad465e304f42a9ed2329ce66b0540829b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>solve_A</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a602695e7ac6ce1f0e9722a5ac8b5b896</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>solve_grad</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ac063c7b797b95d834f5e8210a2ae71bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>solve_resid</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a398d0b471fc191c187b4be6d1592372a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>recompute_outer_grad</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a66f0a57aa1bccb05473eb945fccf1f86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>recompute_outer_A</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ad8f4ea0333532c2e19f297dc2b1d06be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>recompute_outer_AT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aeaedc23fdb4a738d2018b876bcf01883</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>recompute_outer_MT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>ac49b7fc7961c86fa55597ed6e419e4a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>recompute_outer_norm</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a76c5010f7409a704fb28c3b9d76503a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>recompute_inner_grad</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a95ad43c6e2d1d08a7af01cef49e61399</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>recompute_inner_A</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a48a43fa4c49fdd084ccfa40fc69208ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>recompute_inner_MT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aa96c9c51f4e02d8c2a501fddce19f02d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>ineq_constr_resid</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aedb562a8e11cb66fccf81d6f33c79c42</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>ineq_constr_viol</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a30734be3808e532699fa03b10f36d1a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>ineq_constr_resid_al</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>a39797ee07b0b8acb952e651c94305061</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>type</type>
      <name>update_penalty_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1CyQPALMBackend.html</anchorfile>
      <anchor>aa303a1254c4bc1e773cb401bfb85bde8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CyQPALMBackendSettings</name>
    <filename>group__topic-optimization-solvers-ocp.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1CyQPALMBackendSettings</anchor>
    <member kind="variable">
      <type>index_t</type>
      <name>processors</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>a18f9794881668ebfca3e5184c5d73ac4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>print_residuals</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ac19d3e9a8a8ffe0e2358a75c5d72e617</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>print_precision</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>a8fc5a6d972faff0bb450a45b1d5b5de6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>changing_constr_factor</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>a3b1b95630e5123b6c7acb315c4e67293</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>max_update_count</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ae59a1ddb7e2589acdefb7fe7966b0c76</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>detailed_timings</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>aa418e27c51a14390ab0eb4b68cc26041</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>fancyqlone::TricyqleParams&lt; real_t &gt;</type>
      <name>tricyqle_params</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>a3aeec64cba09d6847e23d7f9decbe09f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>spin_count</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>aadba1d46308e13bf564d75afec16b4bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>WarmStartingStrategy</type>
      <name>strategy</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>aa373f519bbc753135e481d4188c77c91</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::CyQPALMBackendStats</name>
    <filename>group__topic-optimization-solvers-ocp.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1CyQPALMBackendStats</anchor>
    <member kind="variable">
      <type>index_t</type>
      <name>num_updates</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ad61f69a15b9082390dcff94207aa9d09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>rank_updates</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>a39ccff5d04291617afbbff9be156dcdf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>num_factor</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>a5b5a034bdda4cd09e63d0839eb485d64</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::detail::backend_stats_type</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1detail.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1detail_1_1backend__stats__type</anchor>
    <templarg>class T</templarg>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::detail::backend_stats_type&lt; CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &gt;</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1detail.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1detail_1_1backend__stats__type_3_01CyQPALMBackend_3_01VL_00_01Defaubd648f5f0e10a35ee91edfe54afecd28</anchor>
    <templarg>index_t VL</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class LinearSolver</templarg>
    <member kind="typedef">
      <type>CyQPALMBackendStats</type>
      <name>type</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1detail.html</anchorfile>
      <anchor>afb46dddb42347b2306a8aa45affb6f53</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::detail::backend_type</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1detail.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1detail_1_1backend__type</anchor>
    <templarg>class T</templarg>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::detail::backend_type&lt; std::unique_ptr&lt; T, D &gt; &gt;</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1detail.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1detail_1_1backend__type_3_01std_1_1unique__ptr_3_01T_00_01D_01_4_01_4</anchor>
    <templarg>class T</templarg>
    <templarg>class D</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>type</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1detail.html</anchorfile>
      <anchor>ae264dcc0f97e4bcf837e2c42065926d6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::detail::backend_type&lt; T * &gt;</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1detail.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1detail_1_1backend__type_3_01T_01_5_01_4</anchor>
    <templarg>class T</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>type</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1detail.html</anchorfile>
      <anchor>a21067f69c17e81a30664e925a4013404</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::detail::backend_type&lt; unique_CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &gt;</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1detail.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1detail_1_1backend__type_3_01unique__CyQPALMBackend_3_01VL_00_01Defa306830a29b74570e9069a8a538af8ff0</anchor>
    <templarg>index_t VL</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class LinearSolver</templarg>
    <member kind="typedef">
      <type>CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt;</type>
      <name>type</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1detail.html</anchorfile>
      <anchor>ae29114b42ac1827184b3a69ceaeaa229</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::DetailedStats</name>
    <filename>structfancyqlone_1_1qpalm_1_1DetailedStats.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>ExitReason</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Busy</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4a1e09cea3694db6fc5d651b9bda0cc725</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Converged</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4a2a2d0f9274e02f2638d78d1c8d7090ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NoActiveSetChange</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4a43232261d9812be7067f2526855cae80</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Fail</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4a0ff02ea9e82a89d4b223bb9d03d1772a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Busy</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4a1e09cea3694db6fc5d651b9bda0cc725</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Converged</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4a2a2d0f9274e02f2638d78d1c8d7090ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NoActiveSetChange</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4a43232261d9812be7067f2526855cae80</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Fail</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a81aa219ba9cf504f50b0050b779557c4a0ff02ea9e82a89d4b223bb9d03d1772a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; Entry &gt;</type>
      <name>entries</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>af98782913e11f16d892416cdeb033055</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::DetailedStats::Entry</name>
    <filename>structfancyqlone_1_1qpalm_1_1DetailedStats.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1DetailedStats_1_1Entry</anchor>
    <member kind="variable">
      <type>unsigned</type>
      <name>outer_iter</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>af9e7927ca67506604ec4d987cebcdc6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>inner_iter</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a7f71e4f351ef7fde7850c9a044a52a0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>stationarity</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>ac81e537a835b841242fed8d6f23f9372</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>ineq_constr_viol</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a19ba00696ef6c5dcc6a2ae4ba5b5f70e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>eq_constr_viol</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>ad371dfc5b3db38e0f064b77f8b6ea49b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>linesearch_step_size</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>a228d8e8caa7498a92cf256bb2e1bc6f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>size_t</type>
      <name>linesearch_breakpoint_index</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>acb8999d0e42de4749c705a38c8edca75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>num_active_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>abee26b75e55cd0b7e0b38b39ca186e8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>num_changing_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>ad0e2e847f965f40c70cc5a1a6497fe3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ExitReason</type>
      <name>exit_reason</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1DetailedStats.html</anchorfile>
      <anchor>adce842b5223bb4ec4c1d3fd61af2f0f4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::get_breakpoints_fn</name>
    <filename>structfancyqlone_1_1qpalm_1_1get__breakpoints__fn.html</filename>
    <member kind="typedef">
      <type>typename std::remove_cvref_t&lt; Backend &gt;::ineq_constr_vec_t</type>
      <name>vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1get__breakpoints__fn.html</anchorfile>
      <anchor>a584a67cec60ec5a91e265bab6c10cc58</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>operator()</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1get__breakpoints__fn.html</anchorfile>
      <anchor>abbfec5f75bf7f11eb004e3a360323301</anchor>
      <arglist>(Backend &amp;backend, typename Backend::Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const vec_t&lt; Backend &gt; &amp;Σ, const vec_t&lt; Backend &gt; &amp;y, const vec_t&lt; Backend &gt; &amp;Ad, const vec_t&lt; Backend &gt; &amp;Ax, const vec_t&lt; Backend &gt; &amp;b_min, const vec_t&lt; Backend &gt; &amp;b_max) const noexcept(guanaqo::is_nothrow_tag_invocable_v&lt; get_breakpoints_fn, Backend &amp;, typename Backend::Context &amp;, std::vector&lt; Breakpoint &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp; &gt;)</arglist>
    </member>
    <member kind="function">
      <type>BreakpointsResult</type>
      <name>operator()</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1get__breakpoints__fn.html</anchorfile>
      <anchor>ab18c580285f140a1f5eff6f05fef1cac</anchor>
      <arglist>(Backend &amp;backend, typename Backend::Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const vec_t&lt; Backend &gt; &amp;Σ, const vec_t&lt; Backend &gt; &amp;y, const vec_t&lt; Backend &gt; &amp;Ad, const vec_t&lt; Backend &gt; &amp;Ax, const vec_t&lt; Backend &gt; &amp;b_min, const vec_t&lt; Backend &gt; &amp;b_max) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::get_partitioned_breakpoints_fn</name>
    <filename>structfancyqlone_1_1qpalm_1_1get__partitioned__breakpoints__fn.html</filename>
    <member kind="typedef">
      <type>typename std::remove_cvref_t&lt; Backend &gt;::ineq_constr_vec_t</type>
      <name>vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1get__partitioned__breakpoints__fn.html</anchorfile>
      <anchor>aa67f3cfa9c21f9b2c51b4a42f53a8498</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>PartitionedBreakpoints</type>
      <name>operator()</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1get__partitioned__breakpoints__fn.html</anchorfile>
      <anchor>aadcf1e610e1d081c4e2fc22a03625074</anchor>
      <arglist>(Backend &amp;backend, typename Backend::Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const vec_t&lt; Backend &gt; &amp;Σ, const vec_t&lt; Backend &gt; &amp;y, const vec_t&lt; Backend &gt; &amp;Ad, const vec_t&lt; Backend &gt; &amp;Ax, const vec_t&lt; Backend &gt; &amp;b_min, const vec_t&lt; Backend &gt; &amp;b_max) const noexcept(guanaqo::is_nothrow_tag_invocable_v&lt; get_partitioned_breakpoints_fn, Backend &amp;, typename Backend::Context &amp;, std::vector&lt; Breakpoint &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp;, const vec_t&lt; Backend &gt; &amp; &gt;)</arglist>
    </member>
    <member kind="function">
      <type>PartitionedBreakpoints</type>
      <name>operator()</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1get__partitioned__breakpoints__fn.html</anchorfile>
      <anchor>a90135a1b8fab05a615f03b2271fc1404</anchor>
      <arglist>(Backend &amp;backend, typename Backend::Context &amp;ctx, std::vector&lt; Breakpoint &gt; &amp;breakpoints, const vec_t&lt; Backend &gt; &amp;Σ, const vec_t&lt; Backend &gt; &amp;y, const vec_t&lt; Backend &gt; &amp;Ad, const vec_t&lt; Backend &gt; &amp;Ax, const vec_t&lt; Backend &gt; &amp;b_min, const vec_t&lt; Backend &gt; &amp;b_max) const</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::LineSearch</name>
    <filename>structfancyqlone_1_1qpalm_1_1LineSearch.html</filename>
    <templarg>class Vec</templarg>
    <member kind="typedef">
      <type>Vec</type>
      <name>vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1LineSearch.html</anchorfile>
      <anchor>a6a8bcded2a7f8fa0f932deadd591330d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Result</type>
      <name>operator()</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1LineSearch.html</anchorfile>
      <anchor>a1909ab2d87fa89fb19898d0c76be770a</anchor>
      <arglist>(auto &amp;ctx, auto &amp;backend, real_t η, real_t β, const vec_t &amp;Σ, const vec_t &amp;y, const vec_t &amp;Ad, const vec_t &amp;Ax, const vec_t &amp;b_min, const vec_t &amp;b_max)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Result</type>
      <name>find_stepsize_base</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1LineSearch.html</anchorfile>
      <anchor>ab3b33f5bc89f66f6a1d31d24050f9fb7</anchor>
      <arglist>(ABSum_t a, ABSum_t b, size_t i0, std::span&lt; Breakpoint &gt; pos_bp)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Result</type>
      <name>find_stepsize</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1LineSearch.html</anchorfile>
      <anchor>a9da35dd777d095759adba69a264b87b5</anchor>
      <arglist>(ABSum_t a, ABSum_t b, size_t i0, std::span&lt; Breakpoint &gt; pos_bp, bool partition_1=true)</arglist>
    </member>
    <member kind="variable">
      <type>LineSearchSettings</type>
      <name>settings</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1LineSearch.html</anchorfile>
      <anchor>af1970d4320189502c7b3c6a80d6a4578</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; Breakpoint &gt;</type>
      <name>breakpoints</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1LineSearch.html</anchorfile>
      <anchor>ab9fc3849d0183f88a05dadb43fa0d38f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::LineSearch::Result</name>
    <filename>structfancyqlone_1_1qpalm_1_1LineSearch.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1LineSearch_1_1Result</anchor>
    <member kind="variable">
      <type>real_t</type>
      <name>τ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1LineSearch.html</anchorfile>
      <anchor>a6b8fa265b6f62db063c06988c5a30a42</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>size_t</type>
      <name>index</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1LineSearch.html</anchorfile>
      <anchor>a87f6eb4c850974d1f6633d665893c5eb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::LineSearchSettings</name>
    <filename>namespacefancyqlone_1_1qpalm.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1LineSearchSettings</anchor>
    <member kind="variable">
      <type>bool</type>
      <name>find_smallest_breakpoint_first</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>acf1045e3ec5821846ff4ab070c6b12ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::PartitionedBreakpoints</name>
    <filename>namespacefancyqlone_1_1qpalm.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1PartitionedBreakpoints</anchor>
    <member kind="variable">
      <type>std::span&lt; Breakpoint &gt;</type>
      <name>neg_bp</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a3c0530a084bfe68e91682261f97b6e38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::span&lt; Breakpoint &gt;</type>
      <name>pos_bp</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>aa716efd59a006b2088a65c399dc2f990</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::CentroidalQuadrupedGaitPhase</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1problems.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedGaitPhase</anchor>
    <member kind="variable">
      <type>index_t</type>
      <name>duration</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>aa6eb8a088581d6aedd62059cb3b367df</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::array&lt; bool, 4 &gt;</type>
      <name>contacts</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>aa11800628e2c7e1950e5d4e893e35ef5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::CentroidalQuadrupedParams</name>
    <filename>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</filename>
    <member kind="function">
      <type></type>
      <name>CentroidalQuadrupedParams</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>ad0ea6ad0dd8f63eeb599373a06fb1edd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>CentroidalQuadrupedParams</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a8cc261c96374c2fd0efab4d205fc09c7</anchor>
      <arglist>(index_t N, uint64_t seed, real_t Ts, real_t force_weight=5e-5, real_t reg=0)</arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>dt</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>abc48889c22bac2e35b735464309f9a64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>mu</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a1bc3835a2d764573c46ad977a11e4e71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>mass</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a63b033555393bcc93eea9bebafc5416d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>f_max</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a1540bea47a7122cfa884576697d5f6b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>gravity</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>ab879e0814053d773e96f2e3ec19520c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>N_horiz</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a39bb1be196c30a7f4a99754dceb40d3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>initial_stage</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>ae2c211426954dd86fe3b5ffc71490d0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>base_height</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a34c39df9caefe2052ebc58ac2eecd1d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>foot_x</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a9a689150c297d950a142999cb760f6e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>foot_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>ae22830fd85e26c2d28a7ce56f7c3b60e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::array&lt; real_t, 3 &gt;</type>
      <name>v_ref</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a23ff7b282b56b2a1b346b77c1850b697</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::array&lt; real_t, 9 &gt;</type>
      <name>inertia</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a47f8b720ff2014b9fd5895d8bd4588be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::array&lt; real_t, 12 &gt;</type>
      <name>state_weights</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>acec6ee0d2f9984b9dd3d70b3895fc582</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::array&lt; real_t, 12 &gt;</type>
      <name>force_weights</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>ae632aa0072f83a674ef2912d52936c9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; CentroidalQuadrupedGaitPhase &gt;</type>
      <name>gait</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>a1ca193cb823d00c1de45aedbed9c5642</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>seed</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>ad9cb59884c8cc8e7884b7d3a73bc8bef</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static std::vector&lt; CentroidalQuadrupedGaitPhase &gt;</type>
      <name>make_gait</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedParams.html</anchorfile>
      <anchor>ab24f634f68f282c9a7aae74728971d73</anchor>
      <arglist>(index_t N)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::CentroidalQuadrupedProblem</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1problems.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1problems_1_1CentroidalQuadrupedProblem</anchor>
    <member kind="variable">
      <type>LinearOCPStorage</type>
      <name>ocp</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>ae5a6e6ccfb7eada389151c1744329f4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>reference</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a5f6c087e1bdaac3faf4899d21f2e89f3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::FanCentroidalQuadrupedProblem</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1problems.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1problems_1_1FanCentroidalQuadrupedProblem</anchor>
    <member kind="variable">
      <type>FanOCPStorage</type>
      <name>ocp</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>adb14d6526e2bd936bcee183c12c4f1ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>friction_coefficients</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a2b0e9b8c50902512eb20e033215deba4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::FanSpringMassProblem</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1problems.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1problems_1_1FanSpringMassProblem</anchor>
    <member kind="variable">
      <type>FanOCPStorage</type>
      <name>ocp</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>ab9c584ddd7c42f1eb31f27e2832e6ba9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>ref</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a687537f0b92912a204e6443c073402c5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::PlatooningParams</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1problems.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1problems_1_1PlatooningParams</anchor>
    <member kind="variable">
      <type>real_t</type>
      <name>friction</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a88f78df37958bdf3f976a993fb8fa07f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>F_max</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a273aeeeba1ae769ba508ea1e04ab2e78</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>v_max</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a928de9d8c7468ce98e7efb47df7c00f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>dist_min</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a4d13a8d404917263c4d289a1f9074833</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>dist_init</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>ae574bb1582aa67d783009f0c29908f51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_target</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a8eacc3e256b2b7df6961338524c4e098</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>N_horiz</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a66621b59aafde7792093f827861762e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>T_horiz</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a78a5576a2f94d735900650259cee975d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>scale_cost</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a92338826956b02eff6eb831c63d0ec02</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>masses</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a5b9fa5ebf0093fd6fc14888bfe94c06d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::PlatooningProblem</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1problems.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1problems_1_1PlatooningProblem</anchor>
    <member kind="variable">
      <type>LinearOCPStorage</type>
      <name>ocp</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a348aea758db4d3c18613ab5e361c29cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>ref</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a83901de8ad08d00e7e90b4a81670fbce</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::SpringMassParams</name>
    <filename>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>ActuatorPlacement</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IndividualActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ac28debccf0ec03098e0d622441b97501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RandomActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ace4c2af40b98dbf0cb5a6c221a89b735</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RandomPairsOfActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5aa1d1d5f166ac34202eda32af48eeefbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>WangBoydActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ab7136f7e85d24b484e2dc94d4ba33d5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IndividualActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ac28debccf0ec03098e0d622441b97501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RandomActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ace4c2af40b98dbf0cb5a6c221a89b735</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RandomPairsOfActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5aa1d1d5f166ac34202eda32af48eeefbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>WangBoydActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ab7136f7e85d24b484e2dc94d4ba33d5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SpringMassParams</type>
      <name>wang_boyd_2008</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a65b5c9d486cbadc47c682e04dd3174d2</anchor>
      <arglist>(index_t n_masses, index_t N_horiz=30, uint64_t seed=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SpringMassParams</type>
      <name>wang_boyd_2008_width</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a35e0b8bbcef5d37c4f6d7b1d296d9702</anchor>
      <arglist>(index_t n_masses, index_t N_horiz=30, uint64_t seed=0, double steady_state_spring_length=0.1)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SpringMassParams</type>
      <name>domahidi_2012</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a9983a23525833f95bc7955ea6c719a13</anchor>
      <arglist>(index_t n_masses, index_t N_horiz, uint64_t seed=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SpringMassParams</type>
      <name>active_state_constr</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a2b3c6215d1f45bcf7b522b952b98cac9</anchor>
      <arglist>(index_t n_masses=18, index_t N_horiz=256, uint64_t seed=0)</arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>friction</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>aa3bb54a4ca88ab2b1cf5a181eef31ce8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>k_spring</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>aed0f60da86572d85c4bc99f156216eb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>F_max</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a76e7d91c9e87d37d0955f9afad53f846</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_max</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a258e8b49d16185b306f31dec843c8a70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_min</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>ae8f483bc01bb19969aba0b83054e53a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_min_f</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>acba02f1a5a83c23dfe9a5484fb716c2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_max_f</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a192d6833a5f25b5f12530fe336c9e66e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>v_max</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a5f4c951467b3f93bce635b623802a704</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>v_max_f</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a6d633bc3b4eb7231f6e85b0c9aa2c833</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>width</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a357b32c5456d16dccde256b6399cdbe3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>N_horiz</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a7a8d1e0374f87744590361e0716fbb7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>T_horiz</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a89a70c9b03f36c55f702bc2e272d87ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>q_vel</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a0381978841501bc74680613c211f2b63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>q_pos</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>afa903242f8e5f4270a156a84c3d87702</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>q_vel_f</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a866961b0395fad85fa519113069a5bdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>q_pos_f</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a089bcd6d646a0341ef8590ca816e0b18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>r_act</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a65eb165b4cff46cd6c59d9df05997cfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>masses</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a66c4b295339d39d8a623b68cbd687fb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>n_actuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a43d1d5ad7ca31fcb4242f20b642f2b22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>enum fancyqlone::qpalm::problems::SpringMassParams::ActuatorPlacement</type>
      <name>actuator_placement</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a9dc0a5da6779fd9a342b32ee7344ee25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>seed</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>ab574c84dacb8d6f6ec661cb14b0a3743</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::problems::SpringMassProblem</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1problems.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassProblem</anchor>
    <member kind="variable">
      <type>LinearOCPStorage</type>
      <name>ocp</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>ab9cecf9882fcb9668cac94b1632e4bd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>ref</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a5dbff369282a38338509c0c4cae8ff2c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::Settings</name>
    <filename>structfancyqlone_1_1qpalm_1_1Settings.html</filename>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a7297c1cc26d2f7f4bd84bc7889b173c0</anchor>
      <arglist>(const Settings &amp;) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator!=</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>adcc0989a2437d4b48d6977a89e61bfe8</anchor>
      <arglist>(const Settings &amp;other) const</arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>max_outer_iter</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a503e9eb8d840a68f37b16dc206ffd440</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>max_inner_iter</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a1a5f9c090e0240ca0f99990463c713c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>max_total_inner_iter</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a8f7c17c4374dcc0a845b9ecb657774cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::chrono::microseconds</type>
      <name>max_time</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a088439178e1c50a29e96411c25dfb2b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>tolerance</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a7e19ef7da04fe7b497f455806b4fac07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>dual_tolerance</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a4a9761232818f40aa28a3a6390bce311</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>eq_constr_tolerance</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a8cac2f86a77e08ccf9823453941e3f92</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>initial_inner_tolerance</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>af1ae9b0797c33283c94e38ecf0eb3f27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>ρ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a2069f08884d20a78d8b66bf95b3561af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>θ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a98b8cf1c8cb47fb1b9c5cafe937bb394</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>Δy</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a975bea37b9700d3183e6f83d4a17ec13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>Δy_always</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a87adae90d0babbb1ee900563b5ecbd6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>max_penalty_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a5f0f4bf881558472117ec74ed299d564</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>initial_penalty_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a08b494958c16a3abc0562cdbb19dd8a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>scale_initial_penalty_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a7f22bff5c25b35e7a5213158a2dc889a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>Δx</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>aa45e62c9fb500f2cd4ef9acf30164f8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>max_penalty_x</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>ac3bd70c98c96d5b9ea4b011bc5f8505b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>boost_penalty_x</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a6147e3b7ee8db5436b8921989988c434</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>initial_penalty_x</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>abb6756b9a51cba37b191a2424399c1b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>proximal</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a8cbfd3b43f89bca125ff14c53d6cb81d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>recompute_eq_res</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a11c25746e5571e9b00908dc924e08e37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>recompute_inner</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a9ce3eb8e2b278b5ae9e4e5d574902c48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>recompute</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>ad7581fda29453336114d05ff3174e415</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>verbose</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a82f0d6f07b0aa0c3489f741b87764bef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>print_precision</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a684148b27f4c004d8c4082789b062a2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>max_no_changes_active_set</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>aecf5f7c747dac641b564e7faf42edd71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>linesearch_include_multipliers</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>ab897a4544fa2e8a7eaa0a998aa78d0ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>force_linesearch_if_no_set_change</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a8f7dc2a7cedb7bf71e2b006d8ff12e69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>force_linesearch_if_dir_deriv_pos</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a02fdf7d1873feb740ee970ae58691d0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>detailed_stats</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a474a969a9138f946e09efebc74cdbd7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>scale_newton_step</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a38b33955fc2b29e0de6e6e58437bb9cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>print_directional_deriv</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a5d42bfef9864390b62f86454469c7b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>print_linesearch_inputs</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1Settings.html</anchorfile>
      <anchor>a1439db8444857c8d72759bc3227759ba</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fancyqlone::qpalm::Solver</name>
    <filename>classfancyqlone_1_1qpalm_1_1Solver.html</filename>
    <templarg>class Backend</templarg>
    <member kind="typedef">
      <type>typename detail::backend_stats_type&lt; backend_type &gt;::type</type>
      <name>BackendStats</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a542bb07db5aed8c5b8c0765abea2efa7</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SolverStatus</type>
      <name>operator()</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a2aee1d8cf07c13e5d4a574f033de87ef</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>get_num_variables</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>ade67a39b7de8d754c6b34516913b94f4</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>get_num_equality_constraints</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a3d34b4bf63cf4a64d75a28661b18ad3e</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>get_num_inequality_constraints</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a9087fec3b36d2e7795555e097b81ae56</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_result</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>aaf903dfe0171e1f52b7b3be5a8ab5c3a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_solution</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>ae4d201b79ee15c1fb9a5be2128a04c68</anchor>
      <arglist>(std::span&lt; real_t &gt;) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; real_t &gt;</type>
      <name>get_solution</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>aa641b1c16589f7957f78ac175eb5000b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_equality_multipliers</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a4884fb12e75d2ca2667e9c6044201e5d</anchor>
      <arglist>(std::span&lt; real_t &gt;) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; real_t &gt;</type>
      <name>get_equality_multipliers</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a8b96f0f22f26395472962929b9549c5f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_equality_constraints</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a6dc0e385224505aeb966c670a4a7e2d3</anchor>
      <arglist>(std::span&lt; real_t &gt;) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; real_t &gt;</type>
      <name>get_equality_constraints</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>aaa6ce03c9fa6566942e784d0d7b04881</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_inequality_multipliers</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>ac03face48fec747837c37f794b025de3</anchor>
      <arglist>(std::span&lt; real_t &gt;) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; real_t &gt;</type>
      <name>get_inequality_multipliers</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a0a41c7830f109e5c8a0594652bfd2410</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_inequality_constraints</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a40effc9d8e12effae34d392e68ee16a6</anchor>
      <arglist>(std::span&lt; real_t &gt;) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; real_t &gt;</type>
      <name>get_inequality_constraints</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>abc8b439ef78d256d68b9db2ed5541256</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_penalty_factors</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a5e04d45a336c4fb12c4021f3bbdf25d7</anchor>
      <arglist>(std::span&lt; real_t &gt;) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; real_t &gt;</type>
      <name>get_penalty_factors</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>ab31c33c657cdf3702528d02b51d6085a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>warm_start_solution</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>abaef224fb463ba3a15bfce92eabc94ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_initial_guess</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>add9ec6bd553362b1445da9234e3b7899</anchor>
      <arglist>(std::span&lt; const real_t &gt; x, std::span&lt; const real_t &gt; y, std::span&lt; const real_t &gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_initial_guess</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a088f56e2c4b01879da588ff5e108ec9a</anchor>
      <arglist>(std::span&lt; real_t &gt; x, std::span&lt; real_t &gt; y, std::span&lt; real_t &gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_b_eq</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>ad3663285ee0b100080181b4d5e5c05a6</anchor>
      <arglist>(std::span&lt; const real_t &gt; b_eq)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_b_lb</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>af0fd34bfe915e89b65edb57a42481756</anchor>
      <arglist>(std::span&lt; const real_t &gt; b_lb)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_b_ub</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a164292e938142aea28bd9dffa3663d64</anchor>
      <arglist>(std::span&lt; const real_t &gt; b_ub)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>stop</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>adb145dd3e5f7f8a94730d5b86195182b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Solver</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>abbec795f190d8aae0f4ccfa968bd7264</anchor>
      <arglist>(Backend backend, Settings settings={})</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Solver</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>aa35b651c330fec353069ca2cd96fd73e</anchor>
      <arglist>(const Solver &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>Solver &amp;</type>
      <name>operator=</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a2f245c4ef5c44a77bc96c66dd936af45</anchor>
      <arglist>(const Solver &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Solver</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a2765ef900d1635c20eb7a9d3bdbf0082</anchor>
      <arglist>(Solver &amp;&amp;) noexcept</arglist>
    </member>
    <member kind="function">
      <type>Solver &amp;</type>
      <name>operator=</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>ae1c62e390d6ef043d3b82c9095c09b44</anchor>
      <arglist>(Solver &amp;&amp;) noexcept</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Solver</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>aba52d3c92fafceb6fe39f937f2d73db3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>Backend</type>
      <name>backend</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>af182f08cd7a8d608a6a31f2fd90540d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Settings</type>
      <name>settings</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a5c6eaebce9526ffbe806c147bdc09440</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::unique_ptr&lt; SolverImplementation&lt; backend_type &gt; &gt;</type>
      <name>impl</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>adcccd917cf1f4d674cb17f7da4eac01c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::optional&lt; SolverStats &gt;</type>
      <name>stats</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a1fe6faba7845403358c97550beb2d31d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::optional&lt; BackendStats &gt;</type>
      <name>stats_backend</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>af8953830ed7f7b541b0a64f24e55f202</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>guanaqo::AtomicStopSignal</type>
      <name>stop_signal</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>acbfb74f0082f9027638762d8a6004c48</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>detail::backend_type_t&lt; Backend &gt;</type>
      <name>backend_type</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>ae4e7dbf2f441165985217b4c84211fbb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>SolverStatus</type>
      <name>do_solve</name>
      <anchorfile>classfancyqlone_1_1qpalm_1_1Solver.html</anchorfile>
      <anchor>a86283f73247832e1c17ea3c639d99d6c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::SolverImplementation</name>
    <filename>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</filename>
    <templarg>class Backend</templarg>
    <member kind="typedef">
      <type>Backend</type>
      <name>backend_type</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a34b5e2426ebd0d71d21f16887df4bf1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename backend_type::active_set_t</type>
      <name>active_set_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a4a95f2b09837056ef83acdd140fd6df7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename backend_type::ineq_constr_vec_t</type>
      <name>ineq_vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a8a02734652268c4b851b414b6e1577b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename backend_type::eq_constr_vec_t</type>
      <name>eq_vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>ae88f822b56c365593c1d19fe2d90021d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename backend_type::var_vec_t</type>
      <name>var_vec_t</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>ae732b02c810a2d89cdd42ab321f97454</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ensure_storage</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a081f98c54da1e61a3cd4aff2c455b640</anchor>
      <arglist>(backend_type &amp;backend)</arglist>
    </member>
    <member kind="function">
      <type>SolverStatus</type>
      <name>do_main_loop</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a68a8d399599111330d5048b81a67f2ef</anchor>
      <arglist>(Backend::Context &amp;ctx, backend_type &amp;backend, const Settings &amp;settings, guanaqo::AtomicStopSignal &amp;stop_signal, SolverStats &amp;stats)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>initialize_penalty_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a4bc47a06e0eba099513ff65f253b80ee</anchor>
      <arglist>(Backend::Context &amp;ctx, backend_type &amp;backend, real_t f0, const ineq_vec_t &amp;e0, ineq_vec_t &amp;Σ, const Settings &amp;settings)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static index_t</type>
      <name>update_penalty_y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a9b80dc8ea42a8aae326ba3492f3cf05d</anchor>
      <arglist>(Backend::Context &amp;ctx, backend_type &amp;backend, ineq_vec_t &amp;Σ, const ineq_vec_t &amp;e, const ineq_vec_t &amp;e_old, const Settings &amp;settings)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static real_t</type>
      <name>update_penalty_x</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a30681bb7f9314cb69eb0cf0e70c7614b</anchor>
      <arglist>(real_t S, const Settings &amp;settings)</arglist>
    </member>
    <member kind="variable">
      <type>LineSearch&lt; ineq_vec_t &gt;</type>
      <name>linesearch</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a711e127d98e93c34393d3759e1e533ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>active_set_t</type>
      <name>active_set</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a0aca234b285d2762519a5edda3d13fa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>active_set_t</type>
      <name>active_set_old</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a575132310c956596c9ae99e466845d63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_vec_t</type>
      <name>Σ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a8aef1639357eac6aba3aa914bf65e08e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_vec_t</type>
      <name>y</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a61f0e5f027ccfb2c1796b123cd24a9e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_vec_t</type>
      <name>ŷ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>abc178d84bafcd83d93bab9b92860a0b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_vec_t</type>
      <name>e</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>aad045f72af7be16f4da2f5177cd732a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_vec_t</type>
      <name>e_old</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a9ac432d4e2e37428629d27dc76e1f70d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_vec_t</type>
      <name>Ax</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>abd7e00c824e4c9876004aa9dd767989d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ineq_vec_t</type>
      <name>Ad</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>aa7f5dfb7d99259e4a1b366f054b876fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>eq_vec_t</type>
      <name>Mxb</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a6280ab655c0cdc0fd6d8ab578e8c8688</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>eq_vec_t</type>
      <name>Δλ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a66fc134949ddfb8f36d8274be3408c12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>eq_vec_t</type>
      <name>λ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a594285677e62ced0ac264fabfe29db2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>x</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a3b1c84a9ac0a619fbdbe16df9a411bb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>grad</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a6d885f039b39b7b3c3da97286b1d273b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>Mᵀλ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>ae473a1ab441ad36ec754e8905b1148c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>Aᵀŷ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>ab152359c8dbce7fb78a69cc13f6c4be7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>x_outer</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a5a60a140d77dd97dea362f731057a0ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>MᵀΔλ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>af2d3c35e6e135c484d812706acc8c326</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>d</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a94afb10137a463487173349dd55abba9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>ξ</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>ad791339bebfe31e3939943a04c07ec99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>var_vec_t</type>
      <name>grad_add</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverImplementation.html</anchorfile>
      <anchor>a6d47028932e9559b54719f919cf77fa8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::SolverStats</name>
    <filename>group__topic-optimization-solvers.html</filename>
    <anchor>structfancyqlone_1_1qpalm_1_1SolverStats</anchor>
    <member kind="variable">
      <type>unsigned</type>
      <name>inner_iter</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>acd1ab548ef92540155f745884a95b56e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>outer_iter</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>adf5b9006dcc4a02cc42cb2784ece81f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>stationarity</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>aab074658df1ad9f4deeb2df5ff0ce564</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>primal_residual_norm</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>a2ee3cfb0bba38bcad06b7aa1b8414d84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>max_penalty</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>af6d72c672f946c8ec4b0f57ee2f0331d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverTimings</type>
      <name>timings</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>ae97315a1c4a830aca627fb698ec010d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::optional&lt; DetailedStats &gt;</type>
      <name>detail</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>a32640faecbf9e9a79360fa093a39f297</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::SolverTimings</name>
    <filename>structfancyqlone_1_1qpalm_1_1SolverTimings.html</filename>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>total</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a5c07e1d4ce62c59236c7b530fb9dc731</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>scaling</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>af1ab57cceb5b82ef4da881a72617c4af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>line_search</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>adef8f9e4303820edf1a9ea9f9bcbd242</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>recompute_inner</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a120087a1bc52b1502b2785113309e3a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>recompute_outer</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a4d3db5ec8ef938d1beb2c803543485dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>mat_vec_M</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a6a837b0ff15ecc6da5554c08edd5826b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>mat_vec_MT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a67dd079c50a37b031655d13fc0c02e9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>mat_vec_A</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>ad095aa1ab8c1698bdc197be1c6935d3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>mat_vec_AT</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>afa360ccb3f64be02feb26afc7d707e2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>mat_vec_Q</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a0288d608b2f61578facd60cbd66293d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>active_set_change</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a570f329f65f40d8462c3d46cb0a7f1b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>update_penalty</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a03a9a4399a51882b2ca13f9a2a81cb11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>update_regularization</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a8775e3cc7d961157cc55db4dec49d58e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>boost_regularization</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a1653b97c4af6f88fd517bae229222d5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>DefaultTimings</type>
      <name>solve</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>ad820174663a5e1b6e1d97c165a96c218</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::map&lt; std::string, DefaultTimings &gt;</type>
      <name>backend</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>aee79e3c791cc4f3ebb3ccda8372dc274</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1SolverTimings.html</anchorfile>
      <anchor>a3177822c4e8bd78867cb8736f643e562</anchor>
      <arglist>(std::ostream &amp;, const SolverTimings &amp;)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::qpalm::unique_CyQPALMBackend</name>
    <filename>structfancyqlone_1_1qpalm_1_1unique__CyQPALMBackend.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class LinearSolver</templarg>
    <member kind="function">
      <type></type>
      <name>unique_CyQPALMBackend</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1unique__CyQPALMBackend.html</anchorfile>
      <anchor>a079000ac5b4001aa5ba1af80aa6552d1</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>unique_CyQPALMBackend</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1unique__CyQPALMBackend.html</anchorfile>
      <anchor>ac498faf5c77427b13ba76d7dea8c9e64</anchor>
      <arglist>(unique_CyQPALMBackend &amp;&amp;) noexcept=default</arglist>
    </member>
    <member kind="function">
      <type>unique_CyQPALMBackend &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1unique__CyQPALMBackend.html</anchorfile>
      <anchor>a47068fb7be83eb7606a2921c7c1e3aaf</anchor>
      <arglist>(unique_CyQPALMBackend &amp;&amp;) noexcept=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~unique_CyQPALMBackend</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1unique__CyQPALMBackend.html</anchorfile>
      <anchor>a02e6d84ba0e5a086cdce17700fc6247d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>unique_CyQPALMBackend</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1unique__CyQPALMBackend.html</anchorfile>
      <anchor>a8681f9e22c7cdd40ad535b73256ce277</anchor>
      <arglist>(std::unique_ptr&lt; CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &gt; &amp;&amp;o) noexcept</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::SerialFanCyqloneSolver</name>
    <filename>structfancyqlone_1_1SerialFanCyqloneSolver.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>class T</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class Ctx</templarg>
    <member kind="typedef">
      <type>batmat::datapar::deduced_simd&lt; value_type, v &gt;</type>
      <name>simd</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a9664b4dcc392901740252495915c5d50</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, v &gt;</type>
      <name>vl_t</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a7fcfeb3e11cec8248d3f018dc87aab6b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, v *alignof(value_type)&gt;</type>
      <name>align_t</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aed62e86b31d174bdb6b39c8bea482a8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t, vl_t, index_t, O, align_t &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a24c783f1c71bc33120b21a90ffea2be7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanStorage_t&lt; matrix&lt;&gt;, value_type, DefaultOrder &gt;</type>
      <name>FanStorage</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a03d2f7bb55c59066d284c27ac8b22d6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>default_order</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a21692f2307dc76191f90295ae59d34d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>column_major</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a8ae6e5928ca8cc473661234010e2e796</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>CyqloneParams&lt; value_type &gt;</type>
      <name>get_params</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a1e6dbee480ba8652d2ae6f5b86e9a1a3</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_params</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a1631b2d3722d94a2abd6b7e336b3415e</anchor>
      <arglist>(const CyqloneParams&lt; value_type &gt; &amp;new_params)</arglist>
    </member>
    <member kind="function">
      <type>TricyqleParams&lt; value_type &gt;</type>
      <name>get_tricyqle_params</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a4c78dab0649b0cbfc9d244131b56c195</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_tricyqle_params</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a39f365ac309551377b4f32b5aaa0f531</anchor>
      <arglist>(const TricyqleParams&lt; value_type &gt; &amp;new_params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>foreach_batch</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a56a2649936e048a026d98e823991a1ab</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func, auto &amp;&amp;...xs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>foreach_batch_fwd</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a0e6bd8bc8d720af1ccb0f636d380b122</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func, auto &amp;&amp;...xs) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_grad</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a13bd5ad4c86af7df0bc6b2e3b6d8a16a</anchor>
      <arglist>(Context &amp;ctx, const auto &amp;grad, const std::string &amp;name) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print_grad</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a4598862ee28fe61d524c5d18463a2026</anchor>
      <arglist>(const auto &amp;grad, const std::string &amp;name) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_solution</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aa29adedf46776b925d2737e5b2fdc78b</anchor>
      <arglist>(const FanStorage &amp;x, FanStorage &amp;x_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_dynamics</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a50214f617e07e308bca9888812a6a31b</anchor>
      <arglist>(const FanStorage &amp;λ, FanStorage &amp;λ_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shift_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a6bba7f6ddbf862af958118015a49d31a</anchor>
      <arglist>(const FanStorage &amp;y, FanStorage &amp;y_shifted) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_data</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a755ae5d8bc223565f7e94d06210e0220</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_rhs</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ac2a2175b5f1633c315877ce5abd1f99d</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, FanStorage &amp;rhs) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_rhs</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ae919772c82d1254e815d89974ab2144f</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_gradient</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a1309bd53b335ab1a012d448e521a39fc</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, FanStorage &amp;grad) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_gradient</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a14fde12e609beaeca16b5868bd775018</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>initialize_bounds</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a0b9192a0de183751bd197144244fdc64</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, FanStorage &amp;b_min, FanStorage &amp;b_max) const</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; FanStorage, FanStorage &gt;</type>
      <name>initialize_bounds</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a1c54801603c30a2f8cb7f468d82f818f</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_variables</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ac6fd15c5f1fdd34245be5ca3ff4cf140</anchor>
      <arglist>(std::span&lt; const value_type &gt; ux_lin, FanStorage &amp;ux) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>pack_variables</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ad51655b6a75b9eb874ef732db17b8465</anchor>
      <arglist>(std::span&lt; const value_type &gt; ux_lin) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_variables</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a828934ff5648f8555268411e0cd698ea</anchor>
      <arglist>(const FanStorage &amp;ux, std::span&lt; value_type &gt; ux_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_variables</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>adfc79ab140c547f88ac9724b36cdd298</anchor>
      <arglist>(const FanStorage &amp;ux) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_dynamics</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a3407f299eb2c9f2136e13676369b0040</anchor>
      <arglist>(std::span&lt; const value_type &gt; λ_lin, FanStorage &amp;λ) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>pack_dynamics</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a5a07981e6a96defc0a74ab636046c68f</anchor>
      <arglist>(std::span&lt; const value_type &gt; λ_lin) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_dynamics</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aefa7d7b05f878ea6a8f21cd26dcd74eb</anchor>
      <arglist>(const FanStorage &amp;λ, std::span&lt; value_type &gt; λ_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_dynamics</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ac33eb3776490de5bf6d153fd5757ab4b</anchor>
      <arglist>(const FanStorage &amp;λ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a5c93cc10d883db2c1e8b999cd7bc78d9</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_lin, FanStorage &amp;y, value_type fill=0) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>pack_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a196011c2375a3607e7acc91253708dcf</anchor>
      <arglist>(std::span&lt; const value_type &gt; y_lin, value_type fill=0) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aa329b72d7b5be23c6affc37c44968646</anchor>
      <arglist>(const FanStorage &amp;y, std::span&lt; value_type &gt; y_lin) const</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; value_type &gt;</type>
      <name>unpack_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a19221da33d057223e425c4f253a46a96</anchor>
      <arglist>(const FanStorage &amp;y) const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_variables</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ae172accecfa3a09cc27e898c26588451</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_dynamics_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a0233c28d70510150c5bf1b81c42f9969</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>FanStorage</type>
      <name>initialize_general_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a042b8e5d0b2ad25d8c7fc3743ce251bd</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SerialFanCyqloneSolver</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a29b01676729b5c489ec1624f6a89a3d0</anchor>
      <arglist>(const FanCyqloneStorage&lt; value_type &gt; &amp;ocp, index_t p, CyqloneParams&lt; value_type &gt; params={})</arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>num_branches</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ae5cd6645c3a033fd7c0014be45c8508b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>nu</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ae0ad252046ba978d1c0b10c9a83307c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>ny_0</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ad6207b065de38b577afe0dc1d39fe634</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; SolverStorage&lt; VL, value_type, DefaultOrder, parallel::Context&lt;&gt; &gt; &gt;</type>
      <name>solver_storages</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>abfc3b8bda6a9ade61e0358361b6e52ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>CyqloneParams&lt; value_type &gt;</type>
      <name>params</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>af83159d9f32938128e1b8c597a09ffa3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>SBs</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a8fb389cb3b849d7155528ecdbd8c0daa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>rs</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a0cf64f3705f647833db5792ceb2760af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>R0</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ac6cb6ba51e17477628718f266b3bd7c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>r0</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a5675d79223c1a725e606abe7a1246e4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast::matrix</type>
      <name>D0</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aa3090476a6095add2e11048b25496676</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>p</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a079b9088e431bd0b8782b6c4fceb58b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr index_t</type>
      <name>v</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>acac1b07bf3f6904a57e111f1dae8b4ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>std::unique_ptr&lt; parallel::SharedContext &gt;</type>
      <name>create_parallel_context</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a46cc36e23b74883507eb2719443796af</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_variables</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a3a8ffe41637a342f012c4011149df542</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_dynamics_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a2f0fabd6e279670307dacd4e829544fa</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_general_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a0f1e7f8c520487772e45c9941a68dc67</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>num_internal_constraints</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a8ebb7c19f443950705ba7383f769cbc2</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>nx</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aacbc8b18e7355c62ff2c927f6985586b</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>residual_dynamics_constr</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a74a433c7a5aaaadfb57fc41b8dccdb24</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;x, const FanStorage &amp;b, FanStorage &amp;Mxb) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_dynamics_constr</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a354d1450272913aee547ee4afca2de5a</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;λ, FanStorage &amp;Mᵀλ, bool accum=false) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>general_constr</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a27dd39467a8d20d8493cee83b9fbb17c</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;ux, FanStorage &amp;DCux) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_general_constr</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aeceda7016366b409d0dbbb095388ca5b</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;y, FanStorage &amp;DCᵀy) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>transposed_general_constr</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a39fa948ca06d53404c031c0bde21c5e0</anchor>
      <arglist>(const FanStorage &amp;y, FanStorage &amp;DCᵀy) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a111b961f5c2e423f10bcca07f4b49135</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;ux, value_type α, const FanStorage &amp;q, value_type β, FanStorage &amp;grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient_regularized</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a5e1f8e8171b4c1d047536ebd417244da</anchor>
      <arglist>(Context &amp;ctx, value_type γ, const FanStorage &amp;ux, const FanStorage &amp;ux0, const FanStorage &amp;q, FanStorage &amp;grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cost_gradient_remove_regularization</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aeba75ff141a06fe8705abd237f7e0056</anchor>
      <arglist>(Context &amp;ctx, value_type γ, const FanStorage &amp;x, const FanStorage &amp;x0, FanStorage &amp;grad_f) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a538b12a72085777f8dc7fe7dc1b95c26</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, const FanStorage &amp;Σ, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a783fcd41121e939801ba5bac990e4212</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, const FanStorage &amp;Σ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_forward</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a4ac8a1c5959347d38e5ba03730abdcc2</anchor>
      <arglist>(Context &amp;ctx, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a20147ef2e1e970dfc6a39b72ebeeabfe</anchor>
      <arglist>(Context &amp;ctx, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_mul</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a7e87b88cdc0ca3d40fba1fb44d775bae</anchor>
      <arglist>(Context &amp;ctx, FanStorage &amp;ux, FanStorage &amp;λ, FanStorage &amp;Mᵀλ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_solve</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a5898bd62510fcfd459c58fd32ca62096</anchor>
      <arglist>(Context &amp;ctx, const FanStorage &amp;ΔΣ, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_impl</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a6819abd3787a181ca5006efd121a40af</anchor>
      <arglist>(Context &amp;ctx, value_type γ, real_t ρ_inv, const FanStorage &amp;Σ, FanStorage &amp;ux, FanStorage &amp;λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ad3337da2a9b3c9c623bb7e49ab80c3d9</anchor>
      <arglist>(Context &amp;ctx, FanStorage &amp;ux, FanStorage &amp;λ, std::optional&lt; FanStorage &gt; Mᵀλ=std::nullopt) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_u0</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a75162b4eba2f8e7621e777281907db07</anchor>
      <arglist>(FanStorage &amp;ux) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_λ0</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a9a741fc9c85a3d02e1e07dc75da57665</anchor>
      <arglist>(index_t branch, FanStorage &amp;ux, FanStorage &amp;λ) const</arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aa757b16d69e0bd7aae7ecbed88dff966</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TricyqleSolver&lt; VL, T, DefaultOrder, Ctx &gt;</type>
      <name>tricyqle_t</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a5d8aad6c261f60f27576c83118b24052</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Ctx</type>
      <name>Context</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a225ee6b6ad7b1a1294226d66874d4839</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TridiagonalSolver&lt; value_type &gt;</type>
      <name>SolverLast</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>a8bf22b2c645a00d7a4de8300abb14ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tricyqle_t::SharedContext</type>
      <name>SharedContext</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>ab2bd12c442b9c6052c5105b09cefb41d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_λ0</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>afd5c7a540dbc2dec7ac948833bfee755</anchor>
      <arglist>(index_t branch, FanStorage &amp;λ, const FanStorage &amp;ux, const FanStorage &amp;Σ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_u0</name>
      <anchorfile>structfancyqlone_1_1SerialFanCyqloneSolver.html</anchorfile>
      <anchor>aaceac564ea5d6ec707dec44e90f66b4c</anchor>
      <arglist>(FanStorage &amp;ux, value_type γ)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::SolverStorage</name>
    <filename>structfancyqlone_1_1SolverStorage.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>class T</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class Ctx</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>a2ad87c1c01e16af4fafc076667f5099f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TricyqleSolver&lt; VL, T, DefaultOrder, Ctx &gt;</type>
      <name>tricyqle_t</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>ac371da26b007b56e2b79c62afc3fca5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TridiagonalSolver&lt; value_type &gt;</type>
      <name>SolverLast</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>a5c55c6c666e2459751ece438c3a3a178</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, 1 &gt;</type>
      <name>one_t</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>ace66283bd419dc252ac56aefa9242b24</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t, one_t, one_t, DefaultOrder &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>aa9270d846f5137d927b7ca1f59db250b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SolverLast::matrix</type>
      <name>matrix_s</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>ad1d863c887b146bb50e8642b4b0fddfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tricyqle_t::SharedContext</type>
      <name>SharedContext</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>af9c01fa429f349425abf44a2e3f3bbe5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>CyqloneSolver&lt; VL, value_type, DefaultOrder, Ctx &gt;</type>
      <name>cyqlone_solver</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>a0244b672083e3ac9a2f0ff67a581e193</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolverLast</type>
      <name>tridiagonal_solver</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>ad3e83f92c133443897f7d9f4df94ff55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>B0</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>ada7ef528389e327b8f8f1612196f4934</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>L_old</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>a543101f37ca53a2981b99f132c289ac8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>LB</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>afa833106ac87644c98f275cea242851c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix_s</type>
      <name>Mxb_row</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>abe6ff1a9a9d18febb18f12bda3149af0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix_s</type>
      <name>Mᵀλ_row</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>a20eb68474ac24c638bcb523178cf91f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix_s</type>
      <name>λ_last</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>a16fa023de04383125bb29f2b1626f6a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix_s</type>
      <name>temp</name>
      <anchorfile>structfancyqlone_1_1SolverStorage.html</anchorfile>
      <anchor>adbb652b9eb2b94a6497f4d0f060be4c7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::SparseCOO</name>
    <filename>structfancyqlone_1_1SparseCOO.html</filename>
    <templarg>class class Index</templarg>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::SparseCSC</name>
    <filename>structfancyqlone_1_1SparseCSC.html</filename>
    <templarg>class class Index</templarg>
    <templarg>class class StorageIndex</templarg>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::SparseMatrix</name>
    <filename>structfancyqlone_1_1SparseMatrix.html</filename>
    <member kind="function">
      <type>auto</type>
      <name>iter_coo</name>
      <anchorfile>structfancyqlone_1_1SparseMatrix.html</anchorfile>
      <anchor>ae547a63ff9b3f900d0f7fc88fb0aaf52</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="variable">
      <type>const std::vector&lt; index_t &gt;</type>
      <name>row_indices</name>
      <anchorfile>structfancyqlone_1_1SparseMatrix.html</anchorfile>
      <anchor>a0a8d68ccf8fffff9a607026429f2e6ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::vector&lt; index_t &gt;</type>
      <name>col_indices</name>
      <anchorfile>structfancyqlone_1_1SparseMatrix.html</anchorfile>
      <anchor>af7c4e47b5be9c19fb9dc8c0bff7d130c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const std::vector&lt; real_t &gt;</type>
      <name>values</name>
      <anchorfile>structfancyqlone_1_1SparseMatrix.html</anchorfile>
      <anchor>a8365ad6a99e81d7f647411bc2fcbe403</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const SparseCOO&lt; index_t &gt;</type>
      <name>sparsity</name>
      <anchorfile>structfancyqlone_1_1SparseMatrix.html</anchorfile>
      <anchor>ae38d2bccab556db5fe8df4eb011150cd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::SparseMatrixBuilder</name>
    <filename>structfancyqlone_1_1SparseMatrixBuilder.html</filename>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>a8a9be837cc42d71c7556484efcdbc7a1</anchor>
      <arglist>(index_t row, index_t col, real_t value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>a84769484263ce73dcad09dd96d20eda8</anchor>
      <arglist>(index_t row, index_t col, guanaqo::MatrixView&lt; T, I, S, O &gt; dense, std::remove_cvref_t&lt; T &gt; scale=1, batmat::linalg::MatrixStructure structure=batmat::linalg::MatrixStructure::General)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_diag</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>afccb9bffc65065ce783ab5e0d92ac8c6</anchor>
      <arglist>(index_t row, index_t col, real_t value, index_t n)</arglist>
    </member>
    <member kind="function">
      <type>SparseMatrix</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>a6e3eb1f9307e5acb853241d004138b57</anchor>
      <arglist>() const &amp;</arglist>
    </member>
    <member kind="function">
      <type>SparseMatrix</type>
      <name>build</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>adb35c1836a586f7a5664fc9138225915</anchor>
      <arglist>() &amp;&amp;</arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>rows</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>a8955faf0c223c42715992023f4eaf147</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>cols</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>af7a69b07d81dd4de9c5611a331d2531c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Symmetry</type>
      <name>symmetry</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>aa83461f2cff4c71d692a743021ad24ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>row_indices</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>a922c7a28508ab403631dc28cd9d297b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>col_indices</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>a82f3172ca1005096d8e05c41df9669d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>values</name>
      <anchorfile>structfancyqlone_1_1SparseMatrixBuilder.html</anchorfile>
      <anchor>a029b6f3ea97ec2294e795bcbaea86045</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::StageIndexInv</name>
    <filename>namespacefancyqlone.html</filename>
    <anchor>structfancyqlone_1_1StageIndexInv</anchor>
    <member kind="variable">
      <type>index_t</type>
      <name>c</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a68ed30ac1dc65c53319d017fdb43d70d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>i</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a0fd1d8496ff8d4ff0846e89b45c0607f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>l</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a73ac05e0479e4015b92af7b20a9dd676</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fancyqlone::TreeBarrier</name>
    <filename>classfancyqlone_1_1TreeBarrier.html</filename>
    <templarg>typename CompletionFn</templarg>
    <templarg>class PhaseType</templarg>
    <class kind="class">fancyqlone::TreeBarrier::arrival_token</class>
    <class kind="class">fancyqlone::TreeBarrier::arrival_token_typed</class>
    <class kind="struct">fancyqlone::TreeBarrier::Storage</class>
    <class kind="struct">fancyqlone::TreeBarrier::State</class>
    <class kind="class">fancyqlone::TreeBarrier::shuffle_token</class>
    <member kind="enumeration">
      <type></type>
      <name>BarrierPhase</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a8aa0a8c6ade3525e99efb950bd72139e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TreeBarrier</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a6d54e9ab947af6bf5f2c444145a2dc24</anchor>
      <arglist>(uint32_t expected, CompletionFn completion)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TreeBarrier</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a6608037e06d9c8a288459cd0c45de243</anchor>
      <arglist>(const TreeBarrier &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TreeBarrier</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>ae33ad5af5efb88ceac23e61ea906b9de</anchor>
      <arglist>(TreeBarrier &amp;&amp;other) noexcept</arglist>
    </member>
    <member kind="function">
      <type>TreeBarrier &amp;</type>
      <name>operator=</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a7b30e650ac3640c7fd0cdaaf79d2ed82</anchor>
      <arglist>(const TreeBarrier &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>TreeBarrier &amp;</type>
      <name>operator=</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a13cabba1f7b1f7edcc8615c0c13ab7ac</anchor>
      <arglist>(TreeBarrier &amp;&amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>arrival_token</type>
      <name>arrive_with_completion</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>aec0a639e83e2d56df18631d9778c84c1</anchor>
      <arglist>(uint32_t thread_id, C &amp;&amp;custom_completion)</arglist>
    </member>
    <member kind="function">
      <type>arrival_token</type>
      <name>get_arrival_token</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>aa172bc3219792bce916f5c05b279beda</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>arrival_token_typed&lt; T &gt;</type>
      <name>get_typed_token</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a1a1da88ed85fbefc5a8717dcd8553a0f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>arrival_token</type>
      <name>arrive</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a1e16a4fa48eb471928ca51afd2bd648e</anchor>
      <arglist>(uint32_t thread_id)</arglist>
    </member>
    <member kind="function">
      <type>arrival_token</type>
      <name>arrive</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>aab6053813cdf32978918bdd13018b1c7</anchor>
      <arglist>(uint32_t thread_id, int line)</arglist>
    </member>
    <member kind="function">
      <type>BarrierPhase</type>
      <name>current_phase</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a6b970c685efe9c5ae0bb76392aecfbeb</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>wait_may_block</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>aab8bb93bd21232e0af39f0b4b758e853</anchor>
      <arglist>(const arrival_token &amp;token) const noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>wait</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a07d3dc32c955801e3ebd0dcaf361bcb3</anchor>
      <arglist>(arrival_token &amp;&amp;token) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>arrive_and_wait</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a45aca0b295dbb8317c2c5e7909a2cbca</anchor>
      <arglist>(uint32_t thread_id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>arrive_and_wait</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a740776cd985d606597c39a5c6f275f1f</anchor>
      <arglist>(uint32_t thread_id, int line)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>arrive_and_wait_with_completion</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a80287f7d7d312f5a48dff068229d3efc</anchor>
      <arglist>(uint32_t thread_id, C &amp;&amp;custom_completion)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>arrive_and_wait_with_completion</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a0aa0a4974334842f7ae5203edf48d3fd</anchor>
      <arglist>(uint32_t thread_id, C &amp;&amp;custom_completion)</arglist>
    </member>
    <member kind="function">
      <type>arrival_token_typed&lt; T &gt;</type>
      <name>arrive_reduce</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>aa08a6fe4b247e0399389c762c5afd458</anchor>
      <arglist>(uint32_t thread_id, T x, F reduce, CF custom_completion)</arglist>
    </member>
    <member kind="function">
      <type>arrival_token_typed&lt; T &gt;</type>
      <name>arrive_reduce</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a644416667659efc3406896e32f61227a</anchor>
      <arglist>(uint32_t thread_id, T x, F reduce)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>wait_reduce</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a80c39456c87a2a707e0bd783c341d0e2</anchor>
      <arglist>(arrival_token_typed&lt; T &gt; &amp;&amp;token)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>reduce</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>aae574e8188bea8b623e0eb0f4fa00630</anchor>
      <arglist>(uint32_t thread_id, T x, F reduce)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>broadcast</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>ab8bbc42b942cce94a31cb2d86420e70f</anchor>
      <arglist>(uint32_t thread_id, T &amp;&amp;x, uint32_t src=0)</arglist>
    </member>
    <member kind="function">
      <type>shuffle_token&lt; T &gt;</type>
      <name>shuffle_start</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>ab708281682ba8e26a1974cf712309cf3</anchor>
      <arglist>(uint32_t thread_id, T x, uint32_t src)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>shuffle_wait</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>acbcd7d942260998f2cb4925327809382</anchor>
      <arglist>(uint32_t thread_id, shuffle_token&lt; T &gt; &amp;&amp;token, F &amp;&amp;func)</arglist>
    </member>
    <member kind="function">
      <type>std::invoke_result_t&lt; F &amp;&amp;, T &amp;&amp; &gt;</type>
      <name>shuffle_wait</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>ac18c471eb1d4c3d8d00bd9bc648e30a8</anchor>
      <arglist>(uint32_t thread_id, shuffle_token&lt; T &gt; &amp;&amp;token, F &amp;&amp;func)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>shuffle_wait</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>acfaf6fb359f9bb4423f1253f35ec95f8</anchor>
      <arglist>(uint32_t thread_id, shuffle_token&lt; T &gt; &amp;&amp;token)</arglist>
    </member>
    <member kind="function">
      <type>shuffle_token&lt; T &gt;</type>
      <name>shuffle_rotr_start</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>abf08463e0b6dbcfae3cdd49dbf3b6df2</anchor>
      <arglist>(uint32_t thread_id, T x, uint32_t n)</arglist>
    </member>
    <member kind="function">
      <type>shuffle_token&lt; T &gt;</type>
      <name>shuffle_rotl_start</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a9e0f2d7062ddc026cbd2f97f85568cd5</anchor>
      <arglist>(uint32_t thread_id, T x, uint32_t n)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr uint32_t</type>
      <name>max</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a17c8bd883172d66c2d463abd34a2f556</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>uint32_t</type>
      <name>spin_count</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a0f24581b62ac628bee1a56f1247f1f0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>typename State::ticket_t::value_type</type>
      <name>ticket_value_type</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a922552c50e0d877bd73725bc755622f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>State::ticket_t &amp;</type>
      <name>get_shuffle_ticket</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>afaa905ac36eba180a87aaec6df5a63ae</anchor>
      <arglist>(uint32_t thread_id) noexcept</arglist>
    </member>
    <member kind="function" protection="private">
      <type>State::ticket_t &amp;</type>
      <name>get_local_phase</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>abf515ba22e9c5c057b5ed1e1f79c64df</anchor>
      <arglist>(uint32_t thread_id) noexcept</arglist>
    </member>
    <member kind="function" protection="private">
      <type>State::ticket_t &amp;</type>
      <name>get_local_line</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a2b89f8cfda4ad371c864476ba89b71cd</anchor>
      <arglist>(uint32_t thread_id) noexcept</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>sanity_check_arrival</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a6f83be86fc2df5f89c7b8b371a6c37fd</anchor>
      <arglist>(uint32_t thread_id, BarrierPhase cur_phase) noexcept</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>arrive_impl</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a918ff6cce9cb715ca8c82d7123243eac</anchor>
      <arglist>(BarrierPhase old_phase, uint32_t thread_id)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>std::optional&lt; T &gt;</type>
      <name>arrive_impl</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>acc9ffd50c6126efdc8a11073ac4a12a2</anchor>
      <arglist>(BarrierPhase old_phase, uint32_t thread_id, T value, F reduce)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>arrival_token</type>
      <name>arrive_with_completion</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a5f8c5f2ae69564be38abc63991d205ff</anchor>
      <arglist>(uint32_t thread_id, A arrival, C &amp;&amp;custom_completion)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>atomic_wait_ne_acq</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a5b0490321386fa0317ee77a29e8e8f1c</anchor>
      <arglist>(const std::atomic&lt; T &gt; &amp;a, T old) const</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>atomic_wait_eq_acq</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>aac0cdb386b168a93ed6927b0118003e5</anchor>
      <arglist>(const std::atomic&lt; T &gt; &amp;a, T target) const</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>expected</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>aaac2c23d5ea2791a4cf0043b2b09d77a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::unique_ptr&lt; State[]&gt;</type>
      <name>state</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a429ac76d59e59e172a330c184717bf45</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::unique_ptr&lt; Storage[]&gt;</type>
      <name>storage</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a3b7b57ec186357bbc28e5d410f00b079</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Storage</type>
      <name>broadcast_storage</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a154be37a328ecb1148a5a779eae69486</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>CompletionFn</type>
      <name>completion</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a7e283536548d011a6ef15eac342259b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::atomic&lt; BarrierPhase &gt;</type>
      <name>phase</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a2ceeebe2f2f399f6691f7d0517d9fa24</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static constexpr size_t</type>
      <name>cache_line_size</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>a04980b9b0ad0dd719a156368e88c6014</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend void</type>
      <name>swap</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier.html</anchorfile>
      <anchor>ad4d9646827a64100cd5328fd937d336a</anchor>
      <arglist>(TreeBarrier &amp;a, TreeBarrier &amp;b) noexcept=delete</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fancyqlone::TreeBarrier::arrival_token</name>
    <filename>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</filename>
    <member kind="function">
      <type></type>
      <name>arrival_token</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>a19a7a8bf066a78622146a4e2c7b5cf6c</anchor>
      <arglist>(const arrival_token &amp;phase)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>arrival_token</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>a6a6d1655e963af7263e87699d6322310</anchor>
      <arglist>(arrival_token &amp;&amp;phase)=default</arglist>
    </member>
    <member kind="function">
      <type>arrival_token &amp;</type>
      <name>operator=</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>acc081f926971e20704a1fc53035bbf16</anchor>
      <arglist>(const arrival_token &amp;phase)=delete</arglist>
    </member>
    <member kind="function">
      <type>arrival_token &amp;</type>
      <name>operator=</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>aa5209b893098f1898a375e4b26ac6675</anchor>
      <arglist>(arrival_token &amp;&amp;phase)=default</arglist>
    </member>
    <member kind="function">
      <type>BarrierPhase</type>
      <name>get</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>ab390272000928793dab646b3cc0d3351</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>arrival_token</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>a4c5ecb9922bfa679e2a5c4fa9ea780bc</anchor>
      <arglist>(BarrierPhase phase)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BarrierPhase</type>
      <name>phase</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>af574588108b5b32e2a2b23e75bbb1430</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>friend</type>
      <name>TreeBarrier</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>ad0e531e25907f5cd748d921583fbe122</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fancyqlone::TreeBarrier::arrival_token_typed</name>
    <filename>classfancyqlone_1_1TreeBarrier_1_1arrival__token__typed.html</filename>
    <templarg>class T</templarg>
    <base>fancyqlone::TreeBarrier&lt; CompletionFn, PhaseType &gt;::arrival_token</base>
    <member kind="function">
      <type>BarrierPhase</type>
      <name>get</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>ab390272000928793dab646b3cc0d3351</anchor>
      <arglist>() const noexcept</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>BarrierPhase</type>
      <name>phase</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>af574588108b5b32e2a2b23e75bbb1430</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>friend</type>
      <name>TreeBarrier</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1arrival__token.html</anchorfile>
      <anchor>ad0e531e25907f5cd748d921583fbe122</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>fancyqlone::TreeBarrier::shuffle_token</name>
    <filename>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</filename>
    <templarg>class T</templarg>
    <member kind="function">
      <type></type>
      <name>shuffle_token</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</anchorfile>
      <anchor>ad4dedb1b60a5bfb099f5a82dc6dab8e2</anchor>
      <arglist>(const shuffle_token &amp;phase)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>shuffle_token</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</anchorfile>
      <anchor>ab9bc091835cb692c5fcc2ef879c1a8a9</anchor>
      <arglist>(shuffle_token &amp;&amp;phase)=default</arglist>
    </member>
    <member kind="function">
      <type>shuffle_token &amp;</type>
      <name>operator=</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</anchorfile>
      <anchor>ad9e0f26cd39de3d0af3342755abc6132</anchor>
      <arglist>(const shuffle_token &amp;phase)=delete</arglist>
    </member>
    <member kind="function">
      <type>shuffle_token &amp;</type>
      <name>operator=</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</anchorfile>
      <anchor>a5a54af715488a76e0cdafd94fd8b8423</anchor>
      <arglist>(shuffle_token &amp;&amp;phase)=default</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>shuffle_token</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</anchorfile>
      <anchor>a5d042eb6e379c431c06de91c2e75d102</anchor>
      <arglist>(uint32_t src, ticket_value_type ticket)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>uint32_t</type>
      <name>src</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</anchorfile>
      <anchor>ae1d9501f71b2ac3f82dbb6a178abda69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ticket_value_type</type>
      <name>ticket</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</anchorfile>
      <anchor>a88950cc15e2cb000f235c5471c6bf93a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>friend</type>
      <name>TreeBarrier</name>
      <anchorfile>classfancyqlone_1_1TreeBarrier_1_1shuffle__token.html</anchorfile>
      <anchor>a00eec5737b46bb2744baf1dfb64d09f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::TreeBarrier::State</name>
    <filename>structfancyqlone_1_1TreeBarrier_1_1State.html</filename>
    <member kind="typedef">
      <type>std::atomic&lt; unsigned char &gt;</type>
      <name>atomic_byte</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1State.html</anchorfile>
      <anchor>ab25356543f08b63867337dc72d0b6b45</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::atomic&lt; uint32_t &gt;</type>
      <name>atomic_word</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1State.html</anchorfile>
      <anchor>af1f6f79ce2b8a5a1bc59609b12a66dab</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::conditional_t&lt; only_word_lock_free, atomic_word, atomic_byte &gt;</type>
      <name>ticket_t</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1State.html</anchorfile>
      <anchor>a701cec8604e6ee7e412d2a5fbd423431</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::array&lt; ticket_t, num_levels &gt;</type>
      <name>tickets</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1State.html</anchorfile>
      <anchor>a523b46b5e093bfad3680aac8ea9d51dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>only_word_lock_free</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1State.html</anchorfile>
      <anchor>aad02834c0874fc16c8df81c5c4fa3eb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr size_t</type>
      <name>num_levels</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1State.html</anchorfile>
      <anchor>ab114227976edef07c2bfee1d0ae26778</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::TreeBarrier::Storage</name>
    <filename>structfancyqlone_1_1TreeBarrier_1_1Storage.html</filename>
    <member kind="typedef">
      <type>void(*)(void *) noexcept</type>
      <name>destructor_t</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a20342bccb5b13a5a0ed78a6b87b8d84e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Storage</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a14915c4c9ba8ebf0e0abef78a3b02abd</anchor>
      <arglist>()=default</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Storage</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a28018c7327b19b09ef24fb97efd6d270</anchor>
      <arglist>(const Storage &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>Storage &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a7a8c6326cf1e14e9e8c0812620213afb</anchor>
      <arglist>(const Storage &amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Storage</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a041cb8d069652f9a440b1cc9f8387713</anchor>
      <arglist>(Storage &amp;&amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type>Storage &amp;</type>
      <name>operator=</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>aa5a8efb35d53b9da0af12b83987d88c7</anchor>
      <arglist>(Storage &amp;&amp;)=delete</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Storage</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>ae43852f20d9e7021566af69bae00cc76</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a2cf556d9d3bec90e437be6446a308322</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>emplace</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>acdce266ea9dc685653ed264822b0ec75</anchor>
      <arglist>(Args &amp;&amp;...args) noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>store</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a4649e891e4be4573278638d9c8f8b7f2</anchor>
      <arglist>(U &amp;&amp;value) noexcept</arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>load</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a345c2cef90d428a234c20f791f21170d</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="variable">
      <type>std::array&lt; std::byte, payload_size &gt;</type>
      <name>payload</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a0da7943273b256b282d2340a81baee4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>destructor_t</type>
      <name>destructor</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a8569c0370d6e9f5bc16f6d707789150d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr std::size_t</type>
      <name>payload_size</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>a2f6c721d55034b3d5c2a04e679424ec4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>is_compatible</name>
      <anchorfile>structfancyqlone_1_1TreeBarrier_1_1Storage.html</anchorfile>
      <anchor>aa3dc9671fb7e5f8a1083d07095a18762</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::TricyqleParams</name>
    <filename>group__topic-block-tridiag-solvers.html</filename>
    <anchor>structfancyqlone_1_1TricyqleParams</anchor>
    <templarg>class T</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>ac8ccd54fceab2ca5d45e4283a8670f5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>enable_prefetching</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>a30b7332db0e61ec548f71156df4de4f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>pcg_max_iter</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>a210ccd590f20dbaf5ecf8c3ae33a6947</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>value_type</type>
      <name>pcg_tolerance</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>a73b33493dc3b236499647b0dae9c7755</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>pcg_print_resid</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>aaaded6f939767536b950c5b1655ff8ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SolveMethod</type>
      <name>solve_method</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>a0dba2378f2f1d16718569d318898492b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>pcr_max_update_fraction</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>a7f1e1fabdc765df35d6dddecc9491551</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>cr_max_update_fraction_Y0</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>a9320fd179b09efa8ee8140053a2626fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>parallel_solve_cr_threshold</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>a0502c7479d74808336a819522952b81e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>parallel_factor_pcr_threshold</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>a07ba880afa9f31cf6efb4c792f340393</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::TricyqleSolver</name>
    <filename>structfancyqlone_1_1TricyqleSolver.html</filename>
    <templarg>index_t VL</templarg>
    <templarg>class T</templarg>
    <templarg>StorageOrder DefaultOrder</templarg>
    <templarg>class Ctx</templarg>
    <member kind="typedef">
      <type>batmat::datapar::deduced_simd&lt; value_type, v &gt;</type>
      <name>simd</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a1eb039c4f76ec1d82e147e404918ff90</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, v &gt;</type>
      <name>vl_t</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a656cd242e15c07e42b9883f4fceec49e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, v *alignof(value_type)&gt;</type>
      <name>align_t</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a37622540ecdb9bd0e12cedc26f02ef6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>p</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ae0169694cc2cd872518f31fbb881c9f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr index_t</type>
      <name>v</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a6f5cb236f16cea897a734025f04a7923</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>lp</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a6554776ddee0681f90141f12f4bf754a</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>ceil_p</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a84005e99d2268860a3a4b114a5b5229c</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>ceil_P</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a73433180506419e3470fc2c690d9e1d6</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>std::unique_ptr&lt; SharedContext &gt;</type>
      <name>create_parallel_context</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ad51436cdaea31a5f7f282688031172d5</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static constexpr index_t</type>
      <name>lv</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a39a0b2be6a2e1530f27b3a5c859ba9bf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t, vl_t, index_t, O, align_t &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ab940cc21518ba0de3119dd9803526627</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::View&lt; const value_type, index_t, vl_t, index_t, index_t, O &gt;</type>
      <name>view</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ad2215914cb0c8048d1d6a213eccc1651</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::View&lt; value_type, index_t, vl_t, index_t, index_t, O &gt;</type>
      <name>mut_view</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a2aab8af6923ee1442eddf16681e73c00</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::DefaultStride</type>
      <name>layer_stride</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ac1e7b6b6c3f2addd90f299aaabf92a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::View&lt; const value_type, index_t, vl_t, vl_t, layer_stride, O &gt;</type>
      <name>batch_view</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a9cf720cf2f9335601942caa13255937c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::View&lt; value_type, index_t, vl_t, vl_t, layer_stride, O &gt;</type>
      <name>mut_batch_view</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a8c5d0496d8c2acc655507b2fa3cf5b3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>default_order</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a34d77dd7cbd699c0ac633634104841b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr auto</type>
      <name>column_major</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a07a2128a8b00896e7d74b65b2432aeed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>block_size</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ab50bcfa09e96596e36f08d6da68f3371</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>max_rank</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a74d312bc0aad829fc9eef3f9509c3af6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>circular</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a61c73a343f6bc37c748ea2273a100ab5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Params</type>
      <name>params</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a4579dcf6734fc652d07c694844133966</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Params</type>
      <name>get_params</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a24da1d2962818a79a16c57b0d42bf27f</anchor>
      <arglist>() const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_params</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a82b0609ab6f8881179b30e4ecd7e3b1a</anchor>
      <arglist>(const Params &amp;new_params)</arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>cr_L</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a83e35f41f2aa440db9906be0afd26143</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>cr_U</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ad5f43f0f59fa39f9c6b25472b86868e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>cr_Y</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>adc2e23ae01c093d435ec354e0e1b6fc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_cr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>af831d232f9880476ae23259fc3df127a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>pcr_L</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>aaf025033a964a339155eab5bd2c7e98f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>pcr_Y</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a0af07942ec343584cedb3b2e845368cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>pcr_U</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ab6ff264d09800273d8759d52fa8db03b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; default_order &gt;</type>
      <name>pcr_M</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ab9ef79d076f38dd543d289ba53a2d10d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_pcg</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a7acc319875c4729aede9170c8051f512</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; index_t &gt;</type>
      <name>m_update</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a7d60325a2f4c37b0d94333de23cf7594</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>m_update_u0</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a9e75541f13cb359446e0dc580a57c21d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_update_Σ</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a1caa8c11a767cb28c007664a15c9b7b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_update</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>aae6bbdac4d595b1a66a5b1dc2e9b34aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_hyh</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>adb23b95ae191a52f38c52e2b22f396ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_update_pcr_Σ</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a7b7726c9a51077c5bc24e24ec132c27c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_update_pcr_L</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>abc56c123e693d89bb1d2670ed36cf352</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix&lt; column_major &gt;</type>
      <name>work_update_pcr_UY</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>abe20b315942d39221da342a98a5d65b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static constexpr bool</type>
      <name>merge_last_level_pcr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a8f323f2db387b518217aab3fadc923f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_pcr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a88c8efa2c1b4fb441fe7424271baa992</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_pcr_level</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a0ddd45d87cc2bb115936b4ca4c26eebb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_pcr_parallel</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a62d8a513286d912285cc60325faeabca</anchor>
      <arglist>(Context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_pcr_level_parallel</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a36a488d78af26510cc767710444793c9</anchor>
      <arglist>(Context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_pcr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a51950f514a15dded5883e6f4f9983f3e</anchor>
      <arglist>(mut_batch_view&lt;&gt; λ, mut_batch_view&lt;&gt; work_pcr) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_pcr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a91b2684b59c1bf66e6ef8bb8482fbd2b</anchor>
      <arglist>(mut_batch_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_pcr_level</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a9960001f1afdbef305b25f4a512421de</anchor>
      <arglist>(mut_batch_view&lt;&gt; λ, mut_batch_view&lt;&gt; work_pcr) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>ν2</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ae6ea20c44c2990d24cd583528ac490b0</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>ν2p</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a35f7b6dfc0032fb088d759479798d654</anchor>
      <arglist>(index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>add_wrap_ceil_p</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a261bbccc2e0dfbe2b3bbbcc205bcbf96</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>add_wrap_p</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ac10eca3db0d9867bd91a324207f3cf02</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>sub_wrap_ceil_p</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a8d7b8557ee3e06e14fa6c0addcbf94b9</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>sub_wrap_p</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a2dd6f70f3bae5be8c9b8233b25106f8f</anchor>
      <arglist>(index_t a, index_t b) const</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>init_diag</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a90d6f88471a77ea3413670fc37e5487e</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func)</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>init_subdiag</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a256ecd4afebbf7c15b1f8cb129306191</anchor>
      <arglist>(Context &amp;ctx, auto &amp;&amp;func)</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>init_rhs</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>abf30e3710c5598e01b07895110d0a158</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; b, auto &amp;&amp;func) const</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>init_update</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a9a00781118cf776e5bf9bcc8e3b2b21c</anchor>
      <arglist>(Context &amp;ctx, index_t rank, auto &amp;&amp;func)</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>get_solution</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a1eca61c4a63adb5136d0a979c9d19127</anchor>
      <arglist>(Context &amp;ctx, view&lt;&gt; λ, auto &amp;&amp;func) const</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>get_solution</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>af1a0a2527429244cecacf2987815fa37</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, auto &amp;&amp;func) const</arglist>
    </member>
    <member kind="function">
      <type>decltype(auto)</type>
      <name>get_solution</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>abbba0c145d876ac3329164f5c9794e90</anchor>
      <arglist>(Context &amp;ctx, Λ &amp;&amp;λ, F &amp;&amp;func) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a6bd9f90e3929add817f1a0eb2ebf8544</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, index_t stride=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a7c969afdcd407a6db71702fe956487b0</anchor>
      <arglist>(Context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_forward</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a12e93ad69975e7b47e6686a5a72bd4ff</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, index_t stride=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a7bb1ca6aa878f77c03b1aa6c1920428a</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, mut_view&lt;&gt; work, index_t stride=1) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a51bfc54160a05c3faa11a080b59fd92d</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, index_t stride=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_skip_first</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>afa102260376e5af2193eac928b5493a7</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, index_t stride=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_skip_first</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>aa5f2aa8aaaa74ec80e625c52b855fec1</anchor>
      <arglist>(Context &amp;ctx)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_forward_skip_first</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>aa8952f21f093f18d2273c79204c7181d</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, index_t stride=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_solve_impl</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a5ee63f6664aabc6102103819bf12a461</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, index_t stride=1)</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>cr_thread_assignment</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a5f51053198df470da155e7b11698e077</anchor>
      <arglist>(index_t l, index_t c) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_U</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>af67da69ba7d7287cd1c8071ac09dd23c</anchor>
      <arglist>(index_t l, index_t iU)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_Y</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a6d252e74e27db746aa917a4cf7a86c96</anchor>
      <arglist>(index_t l, index_t iY)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor_L</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ac32a709bbc5763e55e7e45bc7cacf2f0</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_K</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a3dec96c5b3ef9cdd96a130ac7b885a52</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_u_forward</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ac82d41d5369d5565269838246adb4307</anchor>
      <arglist>(index_t l, index_t iU, mut_view&lt;&gt; λ, index_t stride) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_y_forward</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ace7bc6cf9898ba81c18e0147e4f79a34</anchor>
      <arglist>(index_t l, index_t iY, mut_view&lt;&gt; λ, mut_view&lt;&gt; w, index_t stride) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_λ_forward</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>aa423f5baf151b5e01d75e76ec71556ab</anchor>
      <arglist>(index_t l, index_t iL, mut_view&lt;&gt; λ, view&lt;&gt; w, index_t stride) const</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>mul_Mv</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>af2ad6a094ed8a72fb57a85033d6278b0</anchor>
      <arglist>(batch_view&lt;&gt; p, mut_batch_view&lt;&gt; Mp, batch_view&lt; default_order &gt; L, batch_view&lt; default_order &gt; K) const</arglist>
    </member>
    <member kind="function">
      <type>value_type</type>
      <name>mul_precond</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a068cc1efa0c8a67ecd12764e0c6a9ad5</anchor>
      <arglist>(batch_view&lt;&gt; r, mut_batch_view&lt;&gt; z, mut_batch_view&lt;&gt; w, batch_view&lt; default_order &gt; L, batch_view&lt; default_order &gt; K) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_pcg</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ac06382efc119dbfa8b896d4c89ac10f1</anchor>
      <arglist>(mut_batch_view&lt;&gt; λ, mut_batch_view&lt;&gt; work_pcg) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_pcg</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>acf73789aabc8e73f53d0641c43633c71</anchor>
      <arglist>(mut_batch_view&lt;&gt; λ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_parallel</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a79c76067be8386ba98fdd01c35ab3163</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, mut_view&lt;&gt; work, index_t stride) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse_serial</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ab2aa28b1c00eb45b11992872ecee6db1</anchor>
      <arglist>(mut_view&lt;&gt; λ, mut_view&lt;&gt; work, index_t stride) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_u_backward</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a25690137875416b36fe22d360fe45074</anchor>
      <arglist>(index_t l, index_t iU, mut_view&lt;&gt; λ, mut_view&lt;&gt; w, index_t stride) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_y_backward</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a1950f2ecabe1eb21b2ba98744907f902</anchor>
      <arglist>(index_t l, index_t iY, mut_view&lt;&gt; λ, index_t stride) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_λ_backward</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a4e791a5d4740be150069ad2fda7eb879</anchor>
      <arglist>(index_t biL, mut_view&lt;&gt; λ, view&lt;&gt; w, index_t stride) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_thread_update_rank</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a820efc8a188dcf184ce041877555c6da</anchor>
      <arglist>(Context &amp;ctx, index_t c, index_t m)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_update_rank_extra</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ad1f8f681d9f74551304d5228d2304a8b</anchor>
      <arglist>(index_t m)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_update_rank_extra</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>aa2c903550160905bf6c3c75d0c7d4581</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; index_t, index_t &gt;</type>
      <name>cols_Ups_fwd</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a885585739868f51adbd4e32492d65645</anchor>
      <arglist>(index_t l, index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; index_t, index_t &gt;</type>
      <name>cols_Ups_bwd</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a0ea1342de0f27ff3a80889444945fe59</anchor>
      <arglist>(index_t l, index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>std::pair&lt; index_t, index_t &gt;</type>
      <name>cols_Q_cr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>acdc9f21f01e38198ede89f7fdad0e6eb</anchor>
      <arglist>(index_t l, index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>work_Ups_fwd_w</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a89191680df14828b1d0073987f195206</anchor>
      <arglist>(index_t l, index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>index_t</type>
      <name>work_Ups_bwd_w</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>aff577a6afc7daab605b86f66774b5ea9</anchor>
      <arglist>(index_t l, index_t i) const</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Ups_fwd</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>afa05c6697d5d211970d959d3294cc16a</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Ups_bwd</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a10c2782c6b9c509b74a9be065fe4a955</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Q_cr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a2a04ed48c267ebd3d1b74cd80cfd51a6</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Σ_fwd</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ae88a596189dddc66663eabb436ff4890</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Σ_bwd</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a7c22d7433179e5a3f4c8aaf29589aee4</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Σ_Q</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a5fb4a041cf72a0512ed13e2ad99a2625</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Ups_fwd_last</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a693f1936d93b3fc7ae9def8f5d8ed585</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Ups_bwd_last</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ae813f5cfadf887bccb537f7e18cc991d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Σ_fwd_last</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a274bf7b206afeb34aaa1bc52713b69e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Σ_bwd_last</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a343689ae20256dc505952f7ab0280b98</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Ups_extra</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a9b85c345a4c7aaaf296c786808164e56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>mut_batch_view&lt; column_major &gt;</type>
      <name>work_Σ_extra</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ad080af5a76b4440e51fd9839007c7946</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_solve_cr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a8e6bdd54594938b4af50a38a38613be9</anchor>
      <arglist>(Context &amp;ctx, mut_view&lt;&gt; λ, index_t stride=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_L</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>af56cf8702e1c175ee5c2116fa00b9f96</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_U</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a3192c12805c838627783f50ca22cb8e7</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_Y</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>abf3be2969d8543e1cb58bbb280e5e00e</anchor>
      <arglist>(index_t l, index_t i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_pcr_level</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a52fb0b3171521b04cf9f4379caa369a9</anchor>
      <arglist>(index_t m, mut_batch_view&lt;&gt; WYU, mut_batch_view&lt;&gt; WΣ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_pcr</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>aa5b0f71a6938626c9061d8daad643dec</anchor>
      <arglist>(batch_view&lt;&gt; fwd, batch_view&lt;&gt; bwd, batch_view&lt;&gt; Σ)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prefetch</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a6d97f3693ae1a718e97e819c8d32c8a6</anchor>
      <arglist>(batch_view&lt; O &gt; X) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prefetch_L</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a30559023d5f6dc84e4ecd1ef767f23b8</anchor>
      <arglist>(batch_view&lt; O &gt; X) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prefetch_L</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>ac2873168b7df0c6e624280622af6292e</anchor>
      <arglist>(index_t bi) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prefetch_U</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a4969edf72727f434e5becedcefa2c033</anchor>
      <arglist>(index_t l, index_t iU) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prefetch_Y</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a4eafd2e4cc7a3dc504918ccedf15f15a</anchor>
      <arglist>(index_t l, index_t iY) const</arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a7d3dff9fd51e339f9fd7f968d98dc39a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TricyqleParams&lt; value_type &gt;</type>
      <name>Params</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a2fcde245d6fc92c940b538c8c822a65d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Ctx</type>
      <name>Context</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a2e84b288317c97177e5e16bef7508379</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>typename Context::shared_context_type</type>
      <name>SharedContext</name>
      <anchorfile>structfancyqlone_1_1TricyqleSolver.html</anchorfile>
      <anchor>a4d348e07dbb61f1610d86f17e9b2bb6a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>fancyqlone::TridiagonalSolver</name>
    <filename>structfancyqlone_1_1TridiagonalSolver.html</filename>
    <templarg>class T</templarg>
    <templarg>StorageOrder Order</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>value_type</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>ad9d5d9ea55f6a43967e30e518d280d9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::integral_constant&lt; index_t, 1 &gt;</type>
      <name>vl_t</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>a8153f4198cd60e6dd5bd039f9e554c58</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::Matrix&lt; value_type, index_t, vl_t, index_t, Order &gt;</type>
      <name>matrix</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>ab772a45a1d86245c589c91ddbd2405b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::View&lt; const value_type, index_t, vl_t, index_t, index_t, Order &gt;</type>
      <name>view</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>ab1ebcf03780d907b83d027167f2c6ef5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::matrix::View&lt; value_type, index_t, vl_t, index_t, index_t, Order &gt;</type>
      <name>mut_view</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>aacbf3653b51f6a5fe25715c1eb395e2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>factor</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>a05b29f2742b39cfaaf3a72ba1356268d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_forward</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>afe71065b798ee5defe25ec7cc2427ba7</anchor>
      <arglist>(mut_view λ) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>solve_reverse</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>ad710038906936b871c26a01e9669f3d7</anchor>
      <arglist>(mut_view λ) const</arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>block_size</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>ac04c8a316e8876d36c9d0800c24c825a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const index_t</type>
      <name>num_blocks</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>a31ecb44158d7660566bda249a42b212c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>L</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>a28ec8b7e572877a314583ae37701f2a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrix</type>
      <name>U</name>
      <anchorfile>structfancyqlone_1_1TridiagonalSolver.html</anchorfile>
      <anchor>a30634bee9a29e386545dda3402596a52</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Options</name>
    <filename>benchmarks_2cyqpalm_2spring-mass_8cpp.html</filename>
    <anchor>structOptions</anchor>
    <member kind="variable">
      <type>bool</type>
      <name>cold</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a3de04e8f7bbb951b210863e1714ed62a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>warm_shift</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>af35db881cccf91a2eded77afa50b70fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>warm_copy</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a33a25a66e106fd98e8eb8e22a2ad6952</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>no_updates</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a15b9dc7e39dbeb050697735dbe1929e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; int &gt;</type>
      <name>parallelism</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a84366d66b118e7062a152985348239cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; int &gt;</type>
      <name>vector_length</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a7c864f62e787e28ea788125a0b5b59c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>rm</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a028a843a11fc7b7ed2654be9b8c82a42</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>cm</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>aa87c76cef3252d6411bce3893b442e5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>pcr</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>ae4d3df5515efa3730d7789445f52fd97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>hpipm</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a5fb516d0404207b4a43f572c2df77f10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; int &gt;</type>
      <name>horizon</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>add5121947cc0caf0f36002d9139b42d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; int &gt;</type>
      <name>masses</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a6e54944195345a63ad09c39e0bf0e073</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>num_instances</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a28f0b7978ade7a3be01900e7ce473280</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>seed</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>ad0cd58ab8b36006862e57094b9be42b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ProblemType</type>
      <name>problem_type</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a30184c9dceaa1948064492129b48dea0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>pcr_max_update_fraction</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a8090adb2740c14588adaf6a54259fcc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>cr_max_update_fraction</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a6dcb695bee4b0a8bd43c71a59af746f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>parallel_solve_cr_threshold</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a9ed388d2e25d400369ad3c4dbee92ed0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>parallel_factor_pcr_threshold</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>aae3b8bfee6ceac8cd95a967c33cad452</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>changing_constr_factor</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a6016e9e0cd591f88d4b471f602a1bab7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>custom_reporter</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a7127e3b6cdb1170a62208979c97c32aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>print_extra</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>ae279fc65b1d933a072077a630cbc9e3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>use_color</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a0c157ff2f12fcd0535ad0d57680dc155</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>trace</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a2078f04e236cb4491abc5d00d863ed81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>export_problem</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>af57c4c88687fda5d62a62e8b0dc4008d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Problem</name>
    <filename>benchmarks_2cyqpalm_2spring-mass_8cpp.html</filename>
    <anchor>structProblem</anchor>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a2086d27dcbd2dc82aa31c44869aada91</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SpringMassParams</type>
      <name>params</name>
      <anchorfile>benchmarks_2cyqpalm_2spring-mass_8cpp.html</anchorfile>
      <anchor>a56720c210bc176b2068647ae4795b4f9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Solver</name>
    <filename>structSolver.html</filename>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>structSolver.html</anchorfile>
      <anchor>aa3cc0c1424c904084583322bc3a14f5f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::function&lt; void(benchmark::State &amp;, SpringMassParams)&gt;</type>
      <name>run</name>
      <anchorfile>structSolver.html</anchorfile>
      <anchor>aae9371b91862765a1a99f1287ed4cdf7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>SpringMassParams</name>
    <filename>structSpringMassParams.html</filename>
    <member kind="enumeration">
      <type></type>
      <name>ActuatorPlacement</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IndividualActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ac28debccf0ec03098e0d622441b97501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RandomActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ace4c2af40b98dbf0cb5a6c221a89b735</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RandomPairsOfActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5aa1d1d5f166ac34202eda32af48eeefbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>WangBoydActuators</name>
      <anchorfile>structfancyqlone_1_1qpalm_1_1problems_1_1SpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ab7136f7e85d24b484e2dc94d4ba33d5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IndividualActuators</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ac28debccf0ec03098e0d622441b97501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RandomActuators</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ace4c2af40b98dbf0cb5a6c221a89b735</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RandomPairsOfActuators</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5aa1d1d5f166ac34202eda32af48eeefbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>WangBoydActuators</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a3870c15ac408fa3157f56ae43e175ac5ab7136f7e85d24b484e2dc94d4ba33d5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SpringMassParams</type>
      <name>wang_boyd_2008</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a65b5c9d486cbadc47c682e04dd3174d2</anchor>
      <arglist>(index_t n_masses, index_t N_horiz=30, uint64_t seed=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SpringMassParams</type>
      <name>wang_boyd_2008_width</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a35e0b8bbcef5d37c4f6d7b1d296d9702</anchor>
      <arglist>(index_t n_masses, index_t N_horiz=30, uint64_t seed=0, double steady_state_spring_length=0.1)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SpringMassParams</type>
      <name>domahidi_2012</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a9983a23525833f95bc7955ea6c719a13</anchor>
      <arglist>(index_t n_masses, index_t N_horiz, uint64_t seed=0)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static SpringMassParams</type>
      <name>active_state_constr</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a2b3c6215d1f45bcf7b522b952b98cac9</anchor>
      <arglist>(index_t n_masses=18, index_t N_horiz=256, uint64_t seed=0)</arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>friction</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>aa3bb54a4ca88ab2b1cf5a181eef31ce8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>k_spring</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>aed0f60da86572d85c4bc99f156216eb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>F_max</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a76e7d91c9e87d37d0955f9afad53f846</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_max</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a258e8b49d16185b306f31dec843c8a70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_min</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>ae8f483bc01bb19969aba0b83054e53a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_min_f</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>acba02f1a5a83c23dfe9a5484fb716c2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>p_max_f</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a192d6833a5f25b5f12530fe336c9e66e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>v_max</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a5f4c951467b3f93bce635b623802a704</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>v_max_f</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a6d633bc3b4eb7231f6e85b0c9aa2c833</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>width</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a357b32c5456d16dccde256b6399cdbe3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>N_horiz</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a7a8d1e0374f87744590361e0716fbb7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>T_horiz</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a89a70c9b03f36c55f702bc2e272d87ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>q_vel</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a0381978841501bc74680613c211f2b63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>q_pos</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>afa903242f8e5f4270a156a84c3d87702</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>q_vel_f</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a866961b0395fad85fa519113069a5bdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>q_pos_f</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a089bcd6d646a0341ef8590ca816e0b18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>real_t</type>
      <name>r_act</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a65eb165b4cff46cd6c59d9df05997cfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; real_t &gt;</type>
      <name>masses</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a66c4b295339d39d8a623b68cbd687fb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>index_t</type>
      <name>n_actuators</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a43d1d5ad7ca31fcb4242f20b642f2b22</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>enum fancyqlone::qpalm::problems::SpringMassParams::ActuatorPlacement</type>
      <name>actuator_placement</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>a9dc0a5da6779fd9a342b32ee7344ee25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uint64_t</type>
      <name>seed</name>
      <anchorfile>structSpringMassParams.html</anchorfile>
      <anchor>ab574c84dacb8d6f6ec661cb14b0a3743</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>TridiagSystem</name>
    <filename>solve-block-tridiagonal_8cpp.html</filename>
    <anchor>structTridiagSystem</anchor>
    <member kind="variable">
      <type>matrices</type>
      <name>M</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>abc697170b9533d791d25d633fb52b837</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrices</type>
      <name>K</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>a83a123410ddf401f3cab7e507d8eb50d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>matrices</type>
      <name>b</name>
      <anchorfile>solve-block-tridiagonal_8cpp.html</anchorfile>
      <anchor>aa5af71777abff45ccfd6f6a4c715f1d1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fancyqlone</name>
    <filename>namespacefancyqlone.html</filename>
    <namespace>fancyqlone::qpalm</namespace>
    <namespace>fancyqlone::detail</namespace>
    <namespace>fancyqlone::linalg</namespace>
    <namespace>fancyqlone::parallel</namespace>
    <class kind="struct">fancyqlone::EmptyCompletion</class>
    <class kind="class">fancyqlone::TreeBarrier</class>
    <class kind="struct">fancyqlone::LinearOCPSparseQP</class>
    <class kind="struct">fancyqlone::TricyqleParams</class>
    <class kind="struct">fancyqlone::CyqloneParams</class>
    <class kind="struct">fancyqlone::CyqloneStorage</class>
    <class kind="struct">fancyqlone::FanCyqloneStorage</class>
    <class kind="struct">fancyqlone::StageIndexInv</class>
    <class kind="struct">fancyqlone::TricyqleSolver</class>
    <class kind="struct">fancyqlone::CyqloneSolver</class>
    <class kind="struct">fancyqlone::TridiagonalSolver</class>
    <class kind="struct">fancyqlone::SolverStorage</class>
    <class kind="struct">fancyqlone::FanStorage_t</class>
    <class kind="struct">fancyqlone::FanCyqloneSolver</class>
    <class kind="class">fancyqlone::NeumaierSum</class>
    <class kind="struct">fancyqlone::OCPDim</class>
    <class kind="struct">fancyqlone::LinearOCPStorage</class>
    <class kind="struct">fancyqlone::FanOCPStorage</class>
    <class kind="struct">fancyqlone::SerialFanCyqloneSolver</class>
    <class kind="struct">fancyqlone::SparseMatrix</class>
    <class kind="struct">fancyqlone::SparseMatrixBuilder</class>
    <class kind="struct">fancyqlone::matio_traits</class>
    <class kind="struct">fancyqlone::matio_traits&lt; float &gt;</class>
    <class kind="struct">fancyqlone::matio_traits&lt; double &gt;</class>
    <class kind="struct">fancyqlone::matio_traits&lt; I &gt;</class>
    <class kind="struct">fancyqlone::PCRFactorTest</class>
    <class kind="struct">fancyqlone::SparseCSC</class>
    <class kind="struct">fancyqlone::SparseCOO</class>
    <member kind="typedef">
      <type>::_mat_t</type>
      <name>mat_t</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga60963e57104b35af5ebf325817e3fe48</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::unique_ptr&lt; mat_t, int(*)(mat_t *)&gt;</type>
      <name>MatFilePtr</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga77aa9d5b4d523080df8ff52209ca89db</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>batmat::DefaultTimings</type>
      <name>DefaultTimings</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>ac6f3d9ae1ac95657fbb5307ae5a70530</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::unique_ptr&lt; matvar_t, decltype(&amp;Mat_VarFree)&gt;</type>
      <name>MatVarPtr</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a99525f8b2bafaf74bd1399ada84bdac3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>index_t</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a3033535835e47fa15276d18699766ea1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>double</type>
      <name>real_t</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a643846854e9562c033bced3bec5b8d48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SolveMethod</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>ga02b7bc5e6f2bb033f2f89b03d51d6436</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-block-tridiag-solvers.html" anchor="gga02b7bc5e6f2bb033f2f89b03d51d6436a91fa024e7c3efdd56efd4588853cf488">StairPCG</enumvalue>
      <enumvalue file="group__topic-block-tridiag-solvers.html" anchor="gga02b7bc5e6f2bb033f2f89b03d51d6436a811f52a4a3648918ef143a0cb6a6e334">JacobiPCG</enumvalue>
      <enumvalue file="group__topic-block-tridiag-solvers.html" anchor="gga02b7bc5e6f2bb033f2f89b03d51d6436ac0ff1599838f84547b6668a463198617">PCR</enumvalue>
      <enumvalue file="group__topic-block-tridiag-solvers.html" anchor="gga02b7bc5e6f2bb033f2f89b03d51d6436a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>MatioOpenMode</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga78e7543166e64d103643d53a0fa09e33</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-util-matio.html" anchor="gga78e7543166e64d103643d53a0fa09e33a7a1a5f3e79fdc91edf2f5ead9d66abb4">Read</enumvalue>
      <enumvalue file="group__topic-util-matio.html" anchor="gga78e7543166e64d103643d53a0fa09e33a1129c0e4d43f2d121652a7302712cff6">Write</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>StorageOrder</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a98ef36a3bcaa63feb09e9a30189c18fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>StorageOrder</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a98ef36a3bcaa63feb09e9a30189c18fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>StorageOrder</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a98ef36a3bcaa63feb09e9a30189c18fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>StorageOrder</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a98ef36a3bcaa63feb09e9a30189c18fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>Symmetry</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a397fa707bcca52f40de82f40667e8382</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>atomic_notify_fence</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a10d36a9ec4647dafdf69761622b6659c</anchor>
      <arglist>() noexcept</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reference_to_gradient</name>
      <anchorfile>group__topic-ocp-formulations.html</anchorfile>
      <anchor>gaec2ffbb855f9e5dcfc01dcf321ce51cb</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp, std::span&lt; const real_t &gt; ref, std::span&lt; real_t &gt; qr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reference_to_gradient</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a5de3a2c9e52311f5f204ab358fe7e9d0</anchor>
      <arglist>(LinearOCPStorage &amp;ocp, std::span&lt; const real_t &gt; ref)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>enum_name</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>aec4fba8aed9bbefdf1735fcaf7e9d0e6</anchor>
      <arglist>(SolveMethod s)</arglist>
    </member>
    <member kind="function">
      <type>constexpr bool</type>
      <name>is_pow_2</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>af93f62caf86d8c86b7acd61a61ad3553</anchor>
      <arglist>(index_t n)</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>ceil_log2</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a84ce405d7f1c3371d77f9d8630481acc</anchor>
      <arglist>(index_t n)</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>get_level</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a6fd2280ecdb02bae7c6c1abad8597477</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>get_index_in_level</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>aad238f530432c7b1d8f88c7b3c5e6c0f</anchor>
      <arglist>(index_t i)</arglist>
    </member>
    <member kind="function">
      <type>MatFilePtr</type>
      <name>open_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga67fec1938cb44d6909f91584bcfbef9f</anchor>
      <arglist>(const std::filesystem::path &amp;filename, MatioOpenMode mode=MatioOpenMode::Read)</arglist>
    </member>
    <member kind="function">
      <type>MatFilePtr</type>
      <name>create_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga1e524da3db4f81ddb5dd6c2856c88502</anchor>
      <arglist>(const std::filesystem::path &amp;filename)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga235db8e974db22f3e8d4999cc1241290</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, float value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga1bce8c813758dc0ee0c51123eefd6d4c</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, double value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga542f7cc9199e691651d57a174aa33594</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, short value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga2ac9bf168fcccac6824f7b8778763245</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, int value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga48939416d19f9dd327178bbd804acd3c</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga5881d75c5a03b3164aeed167d97f76bb</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, long long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga69f73a0e5992ecc2f75e5d51ed123b5a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, unsigned short value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>gaae777ef5dd88755256300f62a2b13b87</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, unsigned int value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga0e78abb707d5bb79ff4372518e5dbb0e</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, unsigned long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga521a1cd6aa32db7307ab2012dbe7630e</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, unsigned long long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga9a8038d19161c792385831550f51d930</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, guanaqo::MatrixView&lt; const double, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga62f5dd78db8722e1f0e6d30ef89bda67</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, guanaqo::MatrixView&lt; const float, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga519092628d6a98809f002bb92eea8a4b</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, batmat::matrix::View&lt; const double, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga240cf9568cd4aea51407b96896d9b62d</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, batmat::matrix::View&lt; const float, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga011e2eba58eb8dc91e5f5ec6caed2479</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const float &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga45b17062fb35011a96f441288627e51e</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const double &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga6c8ac2c7fcd37fa428cedc3ddae1c4e2</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const unsigned short &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga12bdb39a1589821c798ac8a32f8f0e0a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const unsigned int &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga8d7930ee44dba2ef0e087c40ab8fb923</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const unsigned long &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga7f3f30db797283a4ee51ffafe255b21a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const unsigned long long &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga96ceb4c9787593db18b0d6aab5ff7287</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const short &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga8b7b93f4fe4cab45686b30ece43f783a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const int &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>gaf4b2434852e3878c5f5861dd6de10848</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const long &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>gadece8c937832409489f87c43e51b6834</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const long long &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga173c33213fca9d73dd78980979535903</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, const SparseMatrix &amp;matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga3a92335133126b546a25f3f379f8dfe1</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, const LinearOCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>gad32c54affae4cfeb7fc996ab3deab14a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, LinearOCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga1a6f1d1a9acd5ebcdbb8763378b87c73</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::vector&lt; float &gt; &amp;data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga46d71bd550f05e2b2db2f47041f7e978</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::vector&lt; double &gt; &amp;data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga55a7f52b546528d22f6ac869a61776ed</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; float &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga2f614289bce89916b1d82d64abdc11cd</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; double &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ocp_dump_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga24ad7736c10109c98fe49ab658f5c12a</anchor>
      <arglist>(const std::filesystem::path &amp;filename, const LinearOCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>LinearOCPStorage</type>
      <name>generate_random_ocp</name>
      <anchorfile>group__topic-ocp-formulations.html</anchorfile>
      <anchor>ga1c6c52a34e6c237829484a749903a430</anchor>
      <arglist>(OCPDim dim, uint_fast32_t seed=0)</arglist>
    </member>
    <member kind="function">
      <type>LinearOCPStorage</type>
      <name>generate_random_ocp_input_constr</name>
      <anchorfile>group__topic-ocp-formulations.html</anchorfile>
      <anchor>ga2541b94a0d444d5651c330a53343a7df</anchor>
      <arglist>(OCPDim dim, uint_fast32_t seed=0)</arglist>
    </member>
    <member kind="function">
      <type>MatVarPtr</type>
      <name>create_tensor_var</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a5fde68c0c2817bfadbb6a1ce000c3835</anchor>
      <arglist>(const char *name, std::span&lt; const T &gt; buffer, std::array&lt; index_t, N &gt; dims)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write_tensor</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a2e175274faba8303adc24dadf91139ad</anchor>
      <arglist>(mat_t *matfp, const char *name, std::span&lt; const T &gt; buffer, std::array&lt; index_t, N &gt; dims)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat_impl</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>ab3f6202cae7046e2563c6d0765803fb0</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, guanaqo::MatrixView&lt; const T, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>add_to_mat_impl</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>ac75560024fb3d6fb7677e16b2f28a40b</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, batmat::matrix::View&lt; const T, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>validate_mat_var</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a1b99e6d3bf3dff6f734dc5660e5c35ce</anchor>
      <arglist>(const matvar_t *var, const std::string &amp;name, int expected_rank)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>open_vector_var</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a1eea97a7bcdf3eb6d451edb91090f9d5</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname)</arglist>
    </member>
    <member kind="function">
      <type>constexpr index_t</type>
      <name>get_depth</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>aceb194b593c007f1550f5b58f3ad96c4</anchor>
      <arglist>(index_t n)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>λ_max_power</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>ab848c27db00dc422a1965aa3ce8dfa3c</anchor>
      <arglist>(const Mat &amp;M, const Mat &amp;K, int max_it, typename Mat::value_type tol)</arglist>
    </member>
    <member kind="function">
      <type>auto</type>
      <name>unpacked</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>aadaaca2e1b4ceca4062f2ab22d80a684</anchor>
      <arglist>(const M &amp;matrix)</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>simdify</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a83105b13bb65f22f974c2faffffd40fe</anchor>
      <arglist>(simdifiable auto &amp;&amp;a) -&gt; simdified_view_t&lt; decltype(a)&gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>simdify</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a83105b13bb65f22f974c2faffffd40fe</anchor>
      <arglist>(simdifiable auto &amp;&amp;a) -&gt; simdified_view_t&lt; decltype(a)&gt;</arglist>
    </member>
    <member kind="function">
      <type>constexpr auto</type>
      <name>simdify</name>
      <anchorfile>namespacefancyqlone.html</anchorfile>
      <anchor>a83105b13bb65f22f974c2faffffd40fe</anchor>
      <arglist>(simdifiable auto &amp;&amp;a) -&gt; simdified_view_t&lt; decltype(a)&gt;</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fancyqlone::detail</name>
    <filename>namespacefancyqlone_1_1detail.html</filename>
    <member kind="function">
      <type>void</type>
      <name>copy</name>
      <anchorfile>namespacefancyqlone_1_1detail.html</anchorfile>
      <anchor>a58c6d3a311e4e27a56607cb1467c2b07</anchor>
      <arglist>(guanaqo::MatrixView&lt; T1, I1, S1, O1 &gt; src, guanaqo::MatrixView&lt; T2, I2, S2, O2 &gt; dst)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scale</name>
      <anchorfile>namespacefancyqlone_1_1detail.html</anchorfile>
      <anchor>a03437b75df550c253b7d9e622c4158cb</anchor>
      <arglist>(T0 scalar, guanaqo::MatrixView&lt; T1, I1, S1, O1 &gt; src, guanaqo::MatrixView&lt; T2, I2, S2, O2 &gt; dst)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fancyqlone::linalg</name>
    <filename>namespacefancyqlone_1_1linalg.html</filename>
    <member kind="function">
      <type>void</type>
      <name>unpack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaa42da3bc15768d28dea6e9f9d10070ea</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga699631bdd8928031c01a6bdc9aea4aec</anchor>
      <arglist>(Structured&lt; VA, S &gt; A, Structured&lt; VB, S &gt; B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unpack_add</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga62982e090fc0815e6ba05adc13ca0f14</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaddcef15139ef3f45552b83b51431bd4b</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaaecce2aaac4780def856ed1b5a5474b0</anchor>
      <arglist>(Structured&lt; VA, S &gt; A, Structured&lt; VB, S &gt; B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>pack_add</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga1fd60de59ea38008c45e198b8bb8cadb</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fancyqlone::parallel</name>
    <filename>namespacefancyqlone_1_1parallel.html</filename>
    <class kind="struct">fancyqlone::parallel::Context</class>
    <class kind="struct">fancyqlone::parallel::FanContext</class>
    <class kind="struct">fancyqlone::parallel::SharedContext</class>
    <class kind="struct">fancyqlone::parallel::FanSharedContext</class>
    <class kind="struct">fancyqlone::parallel::arrival_token_typed_fan</class>
    <class kind="struct">fancyqlone::parallel::arrival_token_fan</class>
  </compound>
  <compound kind="namespace">
    <name>fancyqlone::qpalm</name>
    <filename>namespacefancyqlone_1_1qpalm.html</filename>
    <namespace>fancyqlone::qpalm::problems</namespace>
    <namespace>fancyqlone::qpalm::detail</namespace>
    <class kind="struct">fancyqlone::qpalm::CyqloneData</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackendSettings</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackendStats</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackend</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::CyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::FanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::CycloneBackendTraits&lt; fancyqlone::SerialFanCyqloneSolver&lt; VL, real_t, DefaultOrder &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::unique_CyQPALMBackend</class>
    <class kind="struct">fancyqlone::qpalm::DetailedStats</class>
    <class kind="struct">fancyqlone::qpalm::Breakpoint</class>
    <class kind="struct">fancyqlone::qpalm::ABSums</class>
    <class kind="struct">fancyqlone::qpalm::PartitionedBreakpoints</class>
    <class kind="struct">fancyqlone::qpalm::BreakpointsResult</class>
    <class kind="struct">fancyqlone::qpalm::compute_breakpoints_fn</class>
    <class kind="struct">fancyqlone::qpalm::get_partitioned_breakpoints_fn</class>
    <class kind="struct">fancyqlone::qpalm::get_breakpoints_fn</class>
    <class kind="struct">fancyqlone::qpalm::LineSearchSettings</class>
    <class kind="struct">fancyqlone::qpalm::LineSearch</class>
    <class kind="struct">fancyqlone::qpalm::SolverImplementation</class>
    <class kind="struct">fancyqlone::qpalm::Settings</class>
    <class kind="struct">fancyqlone::qpalm::SolverTimings</class>
    <class kind="struct">fancyqlone::qpalm::SolverStats</class>
    <class kind="class">fancyqlone::qpalm::Solver</class>
    <member kind="typedef">
      <type>real_t</type>
      <name>ABSum_t</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a49bd3110c376daeaa8abb3fc29b761cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>CyqloneSolver&lt; v, real_t, order, parallel::Context&lt; parallel::SharedContext &gt; &gt;</type>
      <name>DefaultInnerSolver</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>aa1ebbe5feb2e66562ad44d9002bab7ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>FanCyqloneSolver&lt; v, real_t, order, parallel::FanContext&lt; parallel::FanSharedContext &gt; &gt;</type>
      <name>FanInnerSolver</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a27779a7c1b02137d9aed6561bc79232a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>SerialFanCyqloneSolver&lt; v, real_t, order, parallel::Context&lt; parallel::SharedContext &gt; &gt;</type>
      <name>SerialFanInnerSolver</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a9428e937fd2cf61f1d9e1c1053e79e7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>WarmStartingStrategy</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>gac67dc98973eb37748e986ba97732b38c</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="ggac67dc98973eb37748e986ba97732b38ca8b7a61a6e9bd5b8977b7b3f02a425adc">Zeros</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="ggac67dc98973eb37748e986ba97732b38ca5fb63579fc981698f97d55bfecb213ea">Copy</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="ggac67dc98973eb37748e986ba97732b38ca825a3d98017bab11815ad2817201324c">Shift</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="ggac67dc98973eb37748e986ba97732b38cab882fa82c60e5b9a229e5ed6e52ad31a">ShiftNoInequality</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>FanWarmStartingStrategy</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ga90c820ba89c66a51ee3e57a7ebf796d2</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="gga90c820ba89c66a51ee3e57a7ebf796d2a8b7a61a6e9bd5b8977b7b3f02a425adc">Zeros</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="gga90c820ba89c66a51ee3e57a7ebf796d2a5fb63579fc981698f97d55bfecb213ea">Copy</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="gga90c820ba89c66a51ee3e57a7ebf796d2a825a3d98017bab11815ad2817201324c">Shift</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="gga90c820ba89c66a51ee3e57a7ebf796d2ab882fa82c60e5b9a229e5ed6e52ad31a">ShiftNoInequality</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>SolverStatus</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>ga24477fe148453ccedf7d5ad6d0ba0f78</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78ad8a942ef2b04672adfafef0ad817a407">Busy</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78ada5418b1eb4e80d05f2c1c7c4fa1b6ec">Converged</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78a9e8b9350c8f1716701ec1f9bbe76432e">MaxTime</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78abbf52264f7a6e91c48a242f95aeed3db">MaxIter</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78aff6e97b110349dae9c6e8be0ff7a85c3">NotFinite</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78ab644b4f0de4cf0c46acb4583602e168c">NoProgress</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78a12c37c4278b8c0db6c2f65052569cd80">Interrupted</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78ab0d4998a26f5b5742ad38c4af8817e32">Exception</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>StorageOrder</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a12561d95ffd5ca9cc074d7b3edceb429</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>unique_CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt;</type>
      <name>make_cyqpalm_backend</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ga04ffaf134708a2b3476e949e6dfa426e</anchor>
      <arglist>(const typename CycloneBackendTraits&lt; LinearSolver &gt;::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_cyqpalm_backend</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ga923329c8239f305d13cb14a91d838483</anchor>
      <arglist>(CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &amp;backend, const typename CycloneBackendTraits&lt; LinearSolver &gt;::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_cyqpalm_backend</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ga9b8823b057fe6a59e9d65db005d8c3ff</anchor>
      <arglist>(CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &amp;backend, const typename CycloneBackendTraits&lt; LinearSolver &gt;::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>sort</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a0e5621455d223744bb4cb2ff621cdf21</anchor>
      <arglist>(R &amp;&amp;range, F key)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>nth_element</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a4416f34ca15a7ca342298669a346af77</anchor>
      <arglist>(R &amp;&amp;range, I mid, F key)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static std::ranges::subrange&lt; std::ranges::iterator_t&lt; R &gt; &gt;</type>
      <name>partition_min</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a71954dbb7921433116705e923e036306</anchor>
      <arglist>(R &amp;&amp;range, F pred, C cmp)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static decltype(auto)</type>
      <name>partition</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a817e4099fa7003745265f06fa0e8f552</anchor>
      <arglist>(R &amp;&amp;range, F key)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static decltype(auto)</type>
      <name>partition</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a253d1e03560fadd7156b05f405f30622</anchor>
      <arglist>(I first, S last, F key)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static decltype(auto)</type>
      <name>min_element</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>aa056c09b3502ed82684674fbcc8281e1</anchor>
      <arglist>(R &amp;&amp;range, F key)</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>transform_reduce</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a1e5cde98e9bb08c358e0dbde2e26f24f</anchor>
      <arglist>(I first, I last, T init, BinOp binary_op, UnOp unary_op)</arglist>
    </member>
    <member kind="function">
      <type>ABSums</type>
      <name>partial_sum_negative</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a6f138c5f7d15cc41c0cecc4c2321e5e7</anchor>
      <arglist>(PartitionedBreakpoints breakpoints, real_t η=0, real_t β=0)</arglist>
    </member>
    <member kind="function">
      <type>std::span&lt; Breakpoint &gt;</type>
      <name>compute_breakpoints_default</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a31712886c80efac2ce71a559731db2c3</anchor>
      <arglist>(std::vector&lt; Breakpoint &gt; &amp;breakpoints, const Vec &amp;Σ, const Vec &amp;y, const Vec &amp;Ad, const Vec &amp;Ax, const Vec &amp;b_min, const Vec &amp;b_max)</arglist>
    </member>
    <member kind="function">
      <type>PartitionedBreakpoints</type>
      <name>partition_breakpoints_default</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a284200507c01e1f1c9823d99c318cf1b</anchor>
      <arglist>(std::span&lt; Breakpoint &gt; breakpoints)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>enum_name</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a26d4973d280fd9cde97918d0b0b1fe78</anchor>
      <arglist>(SolverStatus s)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ac78668c7efb8aa549ac3d3e7ce13810c</anchor>
      <arglist>(std::ostream &amp;os, SolverStatus s)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 1, StorageOrder::ColMajor, DefaultInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ae8c565fbca93f5e40e0c426c7975ad5a</anchor>
      <arglist>(const CyQPALMBackend&lt; 1, StorageOrder::ColMajor, DefaultInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ac6f465fad8dd8f57357f5d897f7978d8</anchor>
      <arglist>(CyQPALMBackend&lt; 1, StorageOrder::ColMajor, DefaultInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 1, StorageOrder::ColMajor, DefaultInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a66aece703a8d869eed4fde92f3bc09e7</anchor>
      <arglist>(CyQPALMBackend&lt; 1, StorageOrder::ColMajor, DefaultInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 1, StorageOrder::ColMajor, DefaultInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 4, StorageOrder::ColMajor, DefaultInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a55a4e67def5e01beaea2271c4f55fbcc</anchor>
      <arglist>(const CyQPALMBackend&lt; 4, StorageOrder::ColMajor, DefaultInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ad8dac8123ef4d4c18e0cb67b9a5e6bd6</anchor>
      <arglist>(CyQPALMBackend&lt; 4, StorageOrder::ColMajor, DefaultInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 4, StorageOrder::ColMajor, DefaultInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ab44d5bd8534ec63b05acd10977dc0928</anchor>
      <arglist>(CyQPALMBackend&lt; 4, StorageOrder::ColMajor, DefaultInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 4, StorageOrder::ColMajor, DefaultInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 8, StorageOrder::ColMajor, DefaultInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a981c1441f46473d19aed87f81689fc02</anchor>
      <arglist>(const CyQPALMBackend&lt; 8, StorageOrder::ColMajor, DefaultInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>abe6927ae4965c8b6c24f3f699788cdcd</anchor>
      <arglist>(CyQPALMBackend&lt; 8, StorageOrder::ColMajor, DefaultInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 8, StorageOrder::ColMajor, DefaultInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a08a0f11654165b7c9801676518571ef9</anchor>
      <arglist>(CyQPALMBackend&lt; 8, StorageOrder::ColMajor, DefaultInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 8, StorageOrder::ColMajor, DefaultInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 1, StorageOrder::ColMajor, FanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ab9112086e72eca21453b423ae8c2a66b</anchor>
      <arglist>(const CyQPALMBackend&lt; 1, StorageOrder::ColMajor, FanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a11ab78a582975ea70b503e6e9349d907</anchor>
      <arglist>(CyQPALMBackend&lt; 1, StorageOrder::ColMajor, FanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 1, StorageOrder::ColMajor, FanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ad654bc906af1db1fb3a6d0b0e25945e9</anchor>
      <arglist>(CyQPALMBackend&lt; 1, StorageOrder::ColMajor, FanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 1, StorageOrder::ColMajor, FanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 4, StorageOrder::ColMajor, FanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a0306349b78a982abb009e045d0012cf5</anchor>
      <arglist>(const CyQPALMBackend&lt; 4, StorageOrder::ColMajor, FanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a6f6fbb0b0e38f611b69051ad818c8f02</anchor>
      <arglist>(CyQPALMBackend&lt; 4, StorageOrder::ColMajor, FanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 4, StorageOrder::ColMajor, FanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>afcf80c489204cebc1cd09a6c3827624f</anchor>
      <arglist>(CyQPALMBackend&lt; 4, StorageOrder::ColMajor, FanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 4, StorageOrder::ColMajor, FanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 8, StorageOrder::ColMajor, FanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a9844fac65cfbf75551d6dc262741d9b0</anchor>
      <arglist>(const CyQPALMBackend&lt; 8, StorageOrder::ColMajor, FanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a933156eda2a07a6f5475c7d309bc5d11</anchor>
      <arglist>(CyQPALMBackend&lt; 8, StorageOrder::ColMajor, FanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 8, StorageOrder::ColMajor, FanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ad10e9c442eb06442f8dc8dfa64893a76</anchor>
      <arglist>(CyQPALMBackend&lt; 8, StorageOrder::ColMajor, FanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 8, StorageOrder::ColMajor, FanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 1, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a98408f45e677c32bcad07999c05ed8bd</anchor>
      <arglist>(const CyQPALMBackend&lt; 1, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ac2a4fff46354cd00910bb2b5feeb41c2</anchor>
      <arglist>(CyQPALMBackend&lt; 1, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 1, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 1, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a0f32f33e20fbb13f2273c8a5653c50c5</anchor>
      <arglist>(CyQPALMBackend&lt; 1, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 1, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 1, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 4, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a99fa8edac0425cb26c86803d043b9035</anchor>
      <arglist>(const CyQPALMBackend&lt; 4, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a6997955ebe0ed55bcdcaf83537ebc0e1</anchor>
      <arglist>(CyQPALMBackend&lt; 4, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 4, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 4, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a448e54f6554b5e65572426f0d29e6771</anchor>
      <arglist>(CyQPALMBackend&lt; 4, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 4, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 4, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 8, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a239e9713e387d7d43c863e2517ef0deb</anchor>
      <arglist>(const CyQPALMBackend&lt; 8, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a7f011c4b0f2d346cc8ed6ec6a9e4f4ca</anchor>
      <arglist>(CyQPALMBackend&lt; 8, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 8, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 8, StorageOrder::ColMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a5969103fd508334f653401b25511875b</anchor>
      <arglist>(CyQPALMBackend&lt; 8, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 8, StorageOrder::ColMajor, SerialFanInnerSolver&lt; 8, StorageOrder::ColMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 1, StorageOrder::RowMajor, DefaultInnerSolver&lt; 1, StorageOrder::RowMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 1, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a0a62631675a6269f207247760f65b2fc</anchor>
      <arglist>(const CyQPALMBackend&lt; 1, StorageOrder::RowMajor, DefaultInnerSolver&lt; 1, StorageOrder::RowMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 1, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>af748664021387ba684ecf88351f20007</anchor>
      <arglist>(CyQPALMBackend&lt; 1, StorageOrder::RowMajor, DefaultInnerSolver&lt; 1, StorageOrder::RowMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 1, StorageOrder::RowMajor, DefaultInnerSolver&lt; 1, StorageOrder::RowMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 1, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>aaa1c07be76b6df0935034afbe5f734f8</anchor>
      <arglist>(CyQPALMBackend&lt; 1, StorageOrder::RowMajor, DefaultInnerSolver&lt; 1, StorageOrder::RowMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 1, StorageOrder::RowMajor, DefaultInnerSolver&lt; 1, StorageOrder::RowMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 4, StorageOrder::RowMajor, DefaultInnerSolver&lt; 4, StorageOrder::RowMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 4, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a533b35626fdd48fb12e7348286b1b93c</anchor>
      <arglist>(const CyQPALMBackend&lt; 4, StorageOrder::RowMajor, DefaultInnerSolver&lt; 4, StorageOrder::RowMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 4, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>aa0dd7f7e0b1892c5f9d408fcb58fa7ec</anchor>
      <arglist>(CyQPALMBackend&lt; 4, StorageOrder::RowMajor, DefaultInnerSolver&lt; 4, StorageOrder::RowMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 4, StorageOrder::RowMajor, DefaultInnerSolver&lt; 4, StorageOrder::RowMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 4, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>ae350ab1a31a11d04711d6a2bf8e5e345</anchor>
      <arglist>(CyQPALMBackend&lt; 4, StorageOrder::RowMajor, DefaultInnerSolver&lt; 4, StorageOrder::RowMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 4, StorageOrder::RowMajor, DefaultInnerSolver&lt; 4, StorageOrder::RowMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template unique_CyQPALMBackend&lt; 8, StorageOrder::RowMajor, DefaultInnerSolver&lt; 8, StorageOrder::RowMajor &gt; &gt;</type>
      <name>make_cyqpalm_backend&lt; 8, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>aa8dc8a8cdd00d671de1d420c55c85299</anchor>
      <arglist>(const CyQPALMBackend&lt; 8, StorageOrder::RowMajor, DefaultInnerSolver&lt; 8, StorageOrder::RowMajor &gt; &gt;::traits::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 8, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>aec89b4fdbe5bf6db4ea9a91f8befe8e8</anchor>
      <arglist>(CyQPALMBackend&lt; 8, StorageOrder::RowMajor, DefaultInnerSolver&lt; 8, StorageOrder::RowMajor &gt; &gt; &amp;, const CyQPALMBackend&lt; 8, StorageOrder::RowMajor, DefaultInnerSolver&lt; 8, StorageOrder::RowMajor &gt; &gt;::traits::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>template void</type>
      <name>update_cyqpalm_backend&lt; 8, StorageOrder::RowMajor &gt;</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a4b8166ca2e5cfa40320e2c5526e44050</anchor>
      <arglist>(CyQPALMBackend&lt; 8, StorageOrder::RowMajor, DefaultInnerSolver&lt; 8, StorageOrder::RowMajor &gt; &gt; &amp;, const typename CyQPALMBackend&lt; 8, StorageOrder::RowMajor, DefaultInnerSolver&lt; 8, StorageOrder::RowMajor &gt; &gt;::traits::OCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="variable">
      <type>struct fancyqlone::qpalm::compute_breakpoints_fn</type>
      <name>compute_breakpoints</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a188d0d7d6c6ee33d437bc4fa5ae155f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct fancyqlone::qpalm::get_partitioned_breakpoints_fn</type>
      <name>get_partitioned_breakpoints</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a007773760e14275aa0e91d97ce19f7fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>struct fancyqlone::qpalm::get_breakpoints_fn</type>
      <name>get_breakpoints</name>
      <anchorfile>namespacefancyqlone_1_1qpalm.html</anchorfile>
      <anchor>a39b3b7bd65a62c6ecc606506542ca966</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fancyqlone::qpalm::detail</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1detail.html</filename>
    <class kind="struct">fancyqlone::qpalm::detail::backend_stats_type&lt; CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_type&lt; unique_CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_type</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_type&lt; std::unique_ptr&lt; T, D &gt; &gt;</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_type&lt; T * &gt;</class>
    <class kind="struct">fancyqlone::qpalm::detail::backend_stats_type</class>
    <member kind="typedef">
      <type>typename backend_type&lt; T &gt;::type</type>
      <name>backend_type_t</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1detail.html</anchorfile>
      <anchor>a49f3a418b141bc5e8f6b556923568b6a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>fancyqlone::qpalm::problems</name>
    <filename>namespacefancyqlone_1_1qpalm_1_1problems.html</filename>
    <class kind="struct">fancyqlone::qpalm::problems::CentroidalQuadrupedGaitPhase</class>
    <class kind="struct">fancyqlone::qpalm::problems::CentroidalQuadrupedParams</class>
    <class kind="struct">fancyqlone::qpalm::problems::CentroidalQuadrupedProblem</class>
    <class kind="struct">fancyqlone::qpalm::problems::FanCentroidalQuadrupedProblem</class>
    <class kind="struct">fancyqlone::qpalm::problems::PlatooningParams</class>
    <class kind="struct">fancyqlone::qpalm::problems::PlatooningProblem</class>
    <class kind="struct">fancyqlone::qpalm::problems::SpringMassParams</class>
    <class kind="struct">fancyqlone::qpalm::problems::SpringMassProblem</class>
    <class kind="struct">fancyqlone::qpalm::problems::FanSpringMassProblem</class>
    <member kind="typedef">
      <type>Eigen::MatrixX&lt; real_t &gt;</type>
      <name>eigen_mat</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a64074f24c2af831ca90b0cc3e8ecae19</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>CentroidalQuadrupedProblem</type>
      <name>centroidal_quadruped</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a55df8252720b2ca53506533388b9c4ed</anchor>
      <arglist>(CentroidalQuadrupedParams p)</arglist>
    </member>
    <member kind="function">
      <type>FanCentroidalQuadrupedProblem</type>
      <name>fan_centroidal_quadruped</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a21ab1286bab4a60e920b940a639020a4</anchor>
      <arglist>(CentroidalQuadrupedParams p, index_t num_branches, real_t mu_radius)</arglist>
    </member>
    <member kind="function">
      <type>LinearOCPStorage</type>
      <name>load_from_csv</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a5dcb9459cf8edbf58534c782b419cbf3</anchor>
      <arglist>(const fs::path &amp;folder, const std::string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>PlatooningProblem</type>
      <name>platooning</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a0e5975050cdbdc3702c00f519922a6dd</anchor>
      <arglist>(PlatooningParams p)</arglist>
    </member>
    <member kind="function">
      <type>SpringMassProblem</type>
      <name>spring_mass</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a28c6f6b2da0b1720ba707c5351e1f5f7</anchor>
      <arglist>(SpringMassParams p)</arglist>
    </member>
    <member kind="function">
      <type>FanSpringMassProblem</type>
      <name>fan_spring_mass</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>ad6df35818fd1a905713ce59651c93018</anchor>
      <arglist>(SpringMassParams p, index_t num_branches, real_t k_spring_diff=0.1)</arglist>
    </member>
    <member kind="function">
      <type>std::tuple&lt; eigen_mat, eigen_mat &gt;</type>
      <name>discretize_zoh</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a0cf7ee6db68a2209fb95a6f343461591</anchor>
      <arglist>(const Eigen::Ref&lt; const eigen_mat &gt; &amp;A, const Eigen::Ref&lt; const eigen_mat &gt; &amp;B, real_t Ts)</arglist>
    </member>
    <member kind="function">
      <type>std::tuple&lt; eigen_mat, eigen_mat, eigen_mat &gt;</type>
      <name>discretize_zoh</name>
      <anchorfile>namespacefancyqlone_1_1qpalm_1_1problems.html</anchorfile>
      <anchor>a9f4835c0a5aa54fbe52650937a54d6c7</anchor>
      <arglist>(const Eigen::Ref&lt; const eigen_mat &gt; &amp;A, const Eigen::Ref&lt; const eigen_mat &gt; &amp;B, const Eigen::Ref&lt; const eigen_mat &gt; &amp;b, real_t Ts)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>topic-lin-solvers</name>
    <title>Linear solvers</title>
    <filename>group__topic-lin-solvers.html</filename>
    <subgroup>topic-block-tridiag-solvers</subgroup>
    <subgroup>topic-ocp-solvers</subgroup>
    <file>cyqlone.hpp</file>
    <file>fancyqlone.hpp</file>
    <file>serial-fancyqlone.hpp</file>
  </compound>
  <compound kind="group">
    <name>topic-block-tridiag-solvers</name>
    <title>Block tridiagonal solvers</title>
    <filename>group__topic-block-tridiag-solvers.html</filename>
    <class kind="struct">fancyqlone::TricyqleParams</class>
    <class kind="struct">fancyqlone::TricyqleSolver</class>
    <member kind="enumeration">
      <type></type>
      <name>fancyqlone::SolveMethod</name>
      <anchorfile>group__topic-block-tridiag-solvers.html</anchorfile>
      <anchor>ga02b7bc5e6f2bb033f2f89b03d51d6436</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-block-tridiag-solvers.html" anchor="gga02b7bc5e6f2bb033f2f89b03d51d6436a91fa024e7c3efdd56efd4588853cf488">StairPCG</enumvalue>
      <enumvalue file="group__topic-block-tridiag-solvers.html" anchor="gga02b7bc5e6f2bb033f2f89b03d51d6436a811f52a4a3648918ef143a0cb6a6e334">JacobiPCG</enumvalue>
      <enumvalue file="group__topic-block-tridiag-solvers.html" anchor="gga02b7bc5e6f2bb033f2f89b03d51d6436ac0ff1599838f84547b6668a463198617">PCR</enumvalue>
      <enumvalue file="group__topic-block-tridiag-solvers.html" anchor="gga02b7bc5e6f2bb033f2f89b03d51d6436a6adf97f83acf6453d4a6a4b1070f3754">None</enumvalue>
    </member>
  </compound>
  <compound kind="group">
    <name>topic-ocp-solvers</name>
    <title>Optimal control solvers</title>
    <filename>group__topic-ocp-solvers.html</filename>
    <class kind="struct">fancyqlone::CyqloneParams</class>
    <class kind="struct">fancyqlone::CyqloneSolver</class>
    <class kind="struct">fancyqlone::SolverStorage</class>
    <class kind="struct">fancyqlone::SerialFanCyqloneSolver</class>
  </compound>
  <compound kind="group">
    <name>topic-optimization-solvers</name>
    <title>Optimization solvers</title>
    <filename>group__topic-optimization-solvers.html</filename>
    <subgroup>topic-optimization-solvers-ocp</subgroup>
    <class kind="struct">fancyqlone::qpalm::DetailedStats</class>
    <class kind="struct">fancyqlone::qpalm::Settings</class>
    <class kind="struct">fancyqlone::qpalm::SolverTimings</class>
    <class kind="struct">fancyqlone::qpalm::SolverStats</class>
    <class kind="class">fancyqlone::qpalm::Solver</class>
    <member kind="enumeration">
      <type></type>
      <name>fancyqlone::qpalm::SolverStatus</name>
      <anchorfile>group__topic-optimization-solvers.html</anchorfile>
      <anchor>ga24477fe148453ccedf7d5ad6d0ba0f78</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78ad8a942ef2b04672adfafef0ad817a407">Busy</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78ada5418b1eb4e80d05f2c1c7c4fa1b6ec">Converged</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78a9e8b9350c8f1716701ec1f9bbe76432e">MaxTime</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78abbf52264f7a6e91c48a242f95aeed3db">MaxIter</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78aff6e97b110349dae9c6e8be0ff7a85c3">NotFinite</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78ab644b4f0de4cf0c46acb4583602e168c">NoProgress</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78a12c37c4278b8c0db6c2f65052569cd80">Interrupted</enumvalue>
      <enumvalue file="group__topic-optimization-solvers.html" anchor="gga24477fe148453ccedf7d5ad6d0ba0f78ab0d4998a26f5b5742ad38c4af8817e32">Exception</enumvalue>
    </member>
  </compound>
  <compound kind="group">
    <name>topic-optimization-solvers-ocp</name>
    <title>Optimal control solvers</title>
    <filename>group__topic-optimization-solvers-ocp.html</filename>
    <class kind="struct">fancyqlone::qpalm::CyqloneData</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackendSettings</class>
    <class kind="struct">fancyqlone::qpalm::CyQPALMBackendStats</class>
    <class kind="struct">fancyqlone::qpalm::unique_CyQPALMBackend</class>
    <member kind="enumeration">
      <type></type>
      <name>fancyqlone::qpalm::WarmStartingStrategy</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>gac67dc98973eb37748e986ba97732b38c</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="ggac67dc98973eb37748e986ba97732b38ca8b7a61a6e9bd5b8977b7b3f02a425adc">Zeros</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="ggac67dc98973eb37748e986ba97732b38ca5fb63579fc981698f97d55bfecb213ea">Copy</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="ggac67dc98973eb37748e986ba97732b38ca825a3d98017bab11815ad2817201324c">Shift</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="ggac67dc98973eb37748e986ba97732b38cab882fa82c60e5b9a229e5ed6e52ad31a">ShiftNoInequality</enumvalue>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>fancyqlone::qpalm::FanWarmStartingStrategy</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ga90c820ba89c66a51ee3e57a7ebf796d2</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="gga90c820ba89c66a51ee3e57a7ebf796d2a8b7a61a6e9bd5b8977b7b3f02a425adc">Zeros</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="gga90c820ba89c66a51ee3e57a7ebf796d2a5fb63579fc981698f97d55bfecb213ea">Copy</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="gga90c820ba89c66a51ee3e57a7ebf796d2a825a3d98017bab11815ad2817201324c">Shift</enumvalue>
      <enumvalue file="group__topic-optimization-solvers-ocp.html" anchor="gga90c820ba89c66a51ee3e57a7ebf796d2ab882fa82c60e5b9a229e5ed6e52ad31a">ShiftNoInequality</enumvalue>
    </member>
    <member kind="function">
      <type>unique_CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt;</type>
      <name>fancyqlone::qpalm::make_cyqpalm_backend</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ga04ffaf134708a2b3476e949e6dfa426e</anchor>
      <arglist>(const typename CycloneBackendTraits&lt; LinearSolver &gt;::CStorage &amp;ocp, CyqloneData data, const CyQPALMBackendSettings &amp;settings)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::qpalm::update_cyqpalm_backend</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ga923329c8239f305d13cb14a91d838483</anchor>
      <arglist>(CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &amp;backend, const typename CycloneBackendTraits&lt; LinearSolver &gt;::CStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::qpalm::update_cyqpalm_backend</name>
      <anchorfile>group__topic-optimization-solvers-ocp.html</anchorfile>
      <anchor>ga9b8823b057fe6a59e9d65db005d8c3ff</anchor>
      <arglist>(CyQPALMBackend&lt; VL, DefaultOrder, LinearSolver &gt; &amp;backend, const typename CycloneBackendTraits&lt; LinearSolver &gt;::OCPStorage &amp;ocp)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>topic-ocp-formulations</name>
    <title>Optimal control problem formulations</title>
    <filename>group__topic-ocp-formulations.html</filename>
    <file>conversion.hpp</file>
    <file>cyqlone-storage.hpp</file>
    <file>ocp.hpp</file>
    <class kind="struct">fancyqlone::LinearOCPSparseQP</class>
    <class kind="struct">fancyqlone::CyqloneStorage</class>
    <class kind="struct">fancyqlone::OCPDim</class>
    <class kind="struct">fancyqlone::LinearOCPStorage</class>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::reference_to_gradient</name>
      <anchorfile>group__topic-ocp-formulations.html</anchorfile>
      <anchor>gaec2ffbb855f9e5dcfc01dcf321ce51cb</anchor>
      <arglist>(const LinearOCPStorage &amp;ocp, std::span&lt; const real_t &gt; ref, std::span&lt; real_t &gt; qr)</arglist>
    </member>
    <member kind="function">
      <type>LinearOCPStorage</type>
      <name>fancyqlone::generate_random_ocp</name>
      <anchorfile>group__topic-ocp-formulations.html</anchorfile>
      <anchor>ga1c6c52a34e6c237829484a749903a430</anchor>
      <arglist>(OCPDim dim, uint_fast32_t seed=0)</arglist>
    </member>
    <member kind="function">
      <type>LinearOCPStorage</type>
      <name>fancyqlone::generate_random_ocp_input_constr</name>
      <anchorfile>group__topic-ocp-formulations.html</anchorfile>
      <anchor>ga2541b94a0d444d5651c330a53343a7df</anchor>
      <arglist>(OCPDim dim, uint_fast32_t seed=0)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>topic-parallelization</name>
    <title>Parallelization</title>
    <filename>group__topic-parallelization.html</filename>
    <file>barrier.hpp</file>
    <file>parallel.hpp</file>
    <class kind="struct">fancyqlone::EmptyCompletion</class>
    <class kind="class">fancyqlone::TreeBarrier</class>
    <class kind="struct">fancyqlone::parallel::SharedContext</class>
    <class kind="struct">fancyqlone::parallel::FanSharedContext</class>
    <class kind="struct">fancyqlone::parallel::Context</class>
  </compound>
  <compound kind="group">
    <name>topic-linalg</name>
    <title>Linear algebra</title>
    <filename>group__topic-linalg.html</filename>
    <subgroup>topic-linalg-flops</subgroup>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::linalg::unpack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaa42da3bc15768d28dea6e9f9d10070ea</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::linalg::unpack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga699631bdd8928031c01a6bdc9aea4aec</anchor>
      <arglist>(Structured&lt; VA, S &gt; A, Structured&lt; VB, S &gt; B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::linalg::unpack_add</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga62982e090fc0815e6ba05adc13ca0f14</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::linalg::pack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaddcef15139ef3f45552b83b51431bd4b</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::linalg::pack</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>gaaecce2aaac4780def856ed1b5a5474b0</anchor>
      <arglist>(Structured&lt; VA, S &gt; A, Structured&lt; VB, S &gt; B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::linalg::pack_add</name>
      <anchorfile>group__topic-linalg.html</anchorfile>
      <anchor>ga1fd60de59ea38008c45e198b8bb8cadb</anchor>
      <arglist>(VA &amp;&amp;A, VB &amp;&amp;B, with_rotate_t&lt; Rot &gt;={})</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>topic-utilities</name>
    <title>Utilities</title>
    <filename>group__topic-utilities.html</filename>
    <subgroup>topic-util-matio</subgroup>
    <file>neumaier.hpp</file>
    <file>sparse.hpp</file>
    <class kind="class">fancyqlone::NeumaierSum</class>
    <class kind="struct">fancyqlone::SparseMatrix</class>
    <class kind="struct">fancyqlone::SparseMatrixBuilder</class>
  </compound>
  <compound kind="group">
    <name>topic-util-matio</name>
    <title>Exporting and loading .mat files</title>
    <filename>group__topic-util-matio.html</filename>
    <file>matio.hpp</file>
    <member kind="typedef">
      <type>::_mat_t</type>
      <name>fancyqlone::mat_t</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga60963e57104b35af5ebf325817e3fe48</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::unique_ptr&lt; mat_t, int(*)(mat_t *)&gt;</type>
      <name>fancyqlone::MatFilePtr</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga77aa9d5b4d523080df8ff52209ca89db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>fancyqlone::MatioOpenMode</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga78e7543166e64d103643d53a0fa09e33</anchor>
      <arglist></arglist>
      <enumvalue file="group__topic-util-matio.html" anchor="gga78e7543166e64d103643d53a0fa09e33a7a1a5f3e79fdc91edf2f5ead9d66abb4">Read</enumvalue>
      <enumvalue file="group__topic-util-matio.html" anchor="gga78e7543166e64d103643d53a0fa09e33a1129c0e4d43f2d121652a7302712cff6">Write</enumvalue>
    </member>
    <member kind="function">
      <type>MatFilePtr</type>
      <name>fancyqlone::open_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga67fec1938cb44d6909f91584bcfbef9f</anchor>
      <arglist>(const std::filesystem::path &amp;filename, MatioOpenMode mode=MatioOpenMode::Read)</arglist>
    </member>
    <member kind="function">
      <type>MatFilePtr</type>
      <name>fancyqlone::create_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga1e524da3db4f81ddb5dd6c2856c88502</anchor>
      <arglist>(const std::filesystem::path &amp;filename)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga235db8e974db22f3e8d4999cc1241290</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, float value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga1bce8c813758dc0ee0c51123eefd6d4c</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, double value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga542f7cc9199e691651d57a174aa33594</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, short value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga2ac9bf168fcccac6824f7b8778763245</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, int value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga48939416d19f9dd327178bbd804acd3c</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga5881d75c5a03b3164aeed167d97f76bb</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, long long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga69f73a0e5992ecc2f75e5d51ed123b5a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, unsigned short value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>gaae777ef5dd88755256300f62a2b13b87</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, unsigned int value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga0e78abb707d5bb79ff4372518e5dbb0e</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, unsigned long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga521a1cd6aa32db7307ab2012dbe7630e</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, unsigned long long value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga9a8038d19161c792385831550f51d930</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, guanaqo::MatrixView&lt; const double, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga62f5dd78db8722e1f0e6d30ef89bda67</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, guanaqo::MatrixView&lt; const float, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga519092628d6a98809f002bb92eea8a4b</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, batmat::matrix::View&lt; const double, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga240cf9568cd4aea51407b96896d9b62d</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, batmat::matrix::View&lt; const float, index_t &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga011e2eba58eb8dc91e5f5ec6caed2479</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const float &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga45b17062fb35011a96f441288627e51e</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const double &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga6c8ac2c7fcd37fa428cedc3ddae1c4e2</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const unsigned short &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga12bdb39a1589821c798ac8a32f8f0e0a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const unsigned int &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga8d7930ee44dba2ef0e087c40ab8fb923</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const unsigned long &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga7f3f30db797283a4ee51ffafe255b21a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const unsigned long long &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga96ceb4c9787593db18b0d6aab5ff7287</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const short &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga8b7b93f4fe4cab45686b30ece43f783a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const int &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>gaf4b2434852e3878c5f5861dd6de10848</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const long &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>gadece8c937832409489f87c43e51b6834</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; const long long &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga173c33213fca9d73dd78980979535903</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, const SparseMatrix &amp;matrix)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::add_to_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga3a92335133126b546a25f3f379f8dfe1</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, const LinearOCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>gad32c54affae4cfeb7fc996ab3deab14a</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, LinearOCPStorage &amp;ocp)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga1a6f1d1a9acd5ebcdbb8763378b87c73</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::vector&lt; float &gt; &amp;data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga46d71bd550f05e2b2db2f47041f7e978</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::vector&lt; double &gt; &amp;data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga55a7f52b546528d22f6ac869a61776ed</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; float &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::read_from_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga2f614289bce89916b1d82d64abdc11cd</anchor>
      <arglist>(mat_t *mat, const std::string &amp;varname, std::span&lt; double &gt; data)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fancyqlone::ocp_dump_mat</name>
      <anchorfile>group__topic-util-matio.html</anchorfile>
      <anchor>ga24ad7736c10109c98fe49ab658f5c12a</anchor>
      <arglist>(const std::filesystem::path &amp;filename, const LinearOCPStorage &amp;ocp)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>examples</name>
    <title>Examples</title>
    <filename>examples.html</filename>
    <docanchor file="examples.html" title="docs/source/doxygen/examples.md">md_docs_2source_2doxygen_2examples</docanchor>
  </compound>
  <compound kind="page">
    <name>md_benchmarks_2cyqpalm_2README</name>
    <title>CyQPALM benchmarks</title>
    <filename>md_benchmarks_2cyqpalm_2README.html</filename>
  </compound>
  <compound kind="page">
    <name>algorithms</name>
    <title>Algorithms</title>
    <filename>algorithms.html</filename>
    <docanchor file="algorithms.html" title="docs/source/doxygen/algorithms.md">md_docs_2source_2doxygen_2algorithms</docanchor>
    <docanchor file="algorithms.html" title="Algorithm 1: Factorization of a single modified Riccati block column">algorithm-1</docanchor>
    <docanchor file="algorithms.html" title="Algorithm 2: Cyqlone factorization">algorithm-2</docanchor>
    <docanchor file="algorithms.html" title="Algorithm 3: Factorization update of a single modified Riccati block column">algorithm-3</docanchor>
    <docanchor file="algorithms.html" title="Algorithm 4: Cyqlone factorization updates">algorithm-4</docanchor>
    <docanchor file="algorithms.html" title="Algorithm 5: CR: Solution of a symmetric block-tridiagonal system using cyclic reduction">algorithm-5</docanchor>
    <docanchor file="algorithms.html" title="Algorithm 6: PCR: Solution of a symmetric block-tridiagonal system using parallel cyclic reduction">algorithm-6</docanchor>
    <docanchor file="algorithms.html" title="Algorithm 7: Periodic PCR factorization of a block-tridiagonal matrix">algorithm-7</docanchor>
    <docanchor file="algorithms.html" title="Algorithm 8: Periodic PCR factorization updates by a block-bidiagonal matrix">algorithm-8</docanchor>
  </compound>
  <compound kind="dir">
    <name>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone/</path>
    <filename>dir_06bf5c636d5bad62a629ce1635aa266d.html</filename>
    <file>ineq-constr.tpp</file>
    <file>linalg.tpp</file>
    <file>linesearch.tpp</file>
    <file>solve.tpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/</path>
    <filename>dir_3daa426161d1662b718b724b36506c48.html</filename>
    <dir>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends/backend-fancyqlone</dir>
    <file>ocp-backend-fancyqlone.hpp</file>
    <file>ocp-backend-fancyqlone.tpp</file>
  </compound>
  <compound kind="dir">
    <name>benchmarks</name>
    <path>benchmarks/</path>
    <filename>dir_13a41d9ad64fb9ae396cb953294783cf.html</filename>
    <dir>benchmarks/cyqpalm</dir>
  </compound>
  <compound kind="dir">
    <name>src/example-problems/centroidal-quadruped</name>
    <path>src/example-problems/centroidal-quadruped/</path>
    <filename>dir_41e80d436864751956a0eed6b3991b97.html</filename>
    <file>centroidal-quadruped.cpp</file>
    <file>centroidal-quadruped.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/include/fancyqlone/cyqlone</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/</path>
    <filename>dir_578a611d3bcd387cca728ec8cb674af4.html</filename>
    <dir>src/fancyqlone/include/fancyqlone/cyqlone/implementation</dir>
    <file>cyqlone-params.hpp</file>
    <file>cyqlone-storage.hpp</file>
    <file>cyqlone.hpp</file>
    <file>tridiagonal-solver.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/src/cyqlone</name>
    <path>src/fancyqlone/src/cyqlone/</path>
    <filename>dir_4b0b1672edc8a4577d37605f9a54dda4.html</filename>
    <file>cyqlone-storage.cpp</file>
    <file>cyqlone.cpp</file>
  </compound>
  <compound kind="dir">
    <name>benchmarks/cyqpalm</name>
    <path>benchmarks/cyqpalm/</path>
    <filename>dir_a176c167fe9328c1c90f722060dd8e38.html</filename>
    <file>spring-mass.cpp</file>
  </compound>
  <compound kind="dir">
    <name>docs</name>
    <path>docs/</path>
    <filename>dir_49e56c817e5e54854c35e136979f97ca.html</filename>
    <dir>docs/source</dir>
  </compound>
  <compound kind="dir">
    <name>docs/source/doxygen</name>
    <path>docs/source/doxygen/</path>
    <filename>dir_0f66d13221df5a7c05ce5dcf2db3bc52.html</filename>
  </compound>
  <compound kind="dir">
    <name>src/example-problems</name>
    <path>src/example-problems/</path>
    <filename>dir_7de462e88404737134ea1126d9379241.html</filename>
    <dir>src/example-problems/centroidal-quadruped</dir>
    <dir>src/example-problems/include</dir>
    <dir>src/example-problems/src</dir>
  </compound>
  <compound kind="dir">
    <name>src/example-problems/include/fancyqlone/fancyqpalm/example-problems</name>
    <path>src/example-problems/include/fancyqlone/fancyqpalm/example-problems/</path>
    <filename>dir_516c0ff988de88ef6b69187d1e1a988a.html</filename>
    <file>csv.hpp</file>
    <file>platooning.hpp</file>
    <file>spring-mass.hpp</file>
    <file>zoh.hpp</file>
  </compound>
  <compound kind="dir">
    <name>examples</name>
    <path>examples/</path>
    <filename>dir_d28a4824dc47e487b107a5db32ef43c4.html</filename>
    <file>solve-block-tridiagonal.cpp</file>
  </compound>
  <compound kind="dir">
    <name>src/example-problems/include/fancyqlone</name>
    <path>src/example-problems/include/fancyqlone/</path>
    <filename>dir_8529a50ce48c006ea92f14346c4c0adb.html</filename>
    <dir>src/example-problems/include/fancyqlone/fancyqpalm</dir>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone</name>
    <path>src/fancyqlone/</path>
    <filename>dir_26072f99ed12771b3d14c916219456d2.html</filename>
    <dir>src/fancyqlone/include</dir>
    <dir>src/fancyqlone/src</dir>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/include/fancyqlone</name>
    <path>src/fancyqlone/include/fancyqlone/</path>
    <filename>dir_69c93eca2ce73f8839aab0c78a691b58.html</filename>
    <dir>src/fancyqlone/include/fancyqlone/cyqlone</dir>
    <dir>src/fancyqlone/include/fancyqlone/fancyqlone</dir>
    <dir>src/fancyqlone/include/fancyqlone/sequential-fancyqlone</dir>
    <file>barrier.hpp</file>
    <file>config.hpp</file>
    <file>conversion.hpp</file>
    <file>linalg.hpp</file>
    <file>matio.hpp</file>
    <file>neumaier.hpp</file>
    <file>ocp.hpp</file>
    <file>packing.hpp</file>
    <file>parallel.hpp</file>
    <file>random-ocp.hpp</file>
    <file>sparse.hpp</file>
    <file>timing.hpp</file>
    <file>tracing.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/include/fancyqlone/fancyqlone</name>
    <path>src/fancyqlone/include/fancyqlone/fancyqlone/</path>
    <filename>dir_0f922683799377da0756abe5aef98d91.html</filename>
    <dir>src/fancyqlone/include/fancyqlone/fancyqlone/implementation</dir>
    <file>fancyqlone.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/src/fancyqlone</name>
    <path>src/fancyqlone/src/fancyqlone/</path>
    <filename>dir_7377093b88dc72dd529436e1ffcbb7c9.html</filename>
    <file>fancyqlone.cpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqpalm/include/fancyqlone</name>
    <path>src/fancyqpalm/include/fancyqlone/</path>
    <filename>dir_d084f60815cfdf1dfcd08e8f9616e2eb.html</filename>
    <dir>src/fancyqpalm/include/fancyqlone/fancyqpalm</dir>
  </compound>
  <compound kind="dir">
    <name>src/example-problems/include/fancyqlone/fancyqpalm</name>
    <path>src/example-problems/include/fancyqlone/fancyqpalm/</path>
    <filename>dir_fbc82d66b563271039195a441a030cff.html</filename>
    <dir>src/example-problems/include/fancyqlone/fancyqpalm/example-problems</dir>
  </compound>
  <compound kind="dir">
    <name>src/fancyqpalm</name>
    <path>src/fancyqpalm/</path>
    <filename>dir_bd4a26a8667a3e0a7dd5327ab8878314.html</filename>
    <dir>src/fancyqpalm/include</dir>
    <dir>src/fancyqpalm/src</dir>
  </compound>
  <compound kind="dir">
    <name>src/fancyqpalm/include/fancyqlone/fancyqpalm</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/</path>
    <filename>dir_c3e3505100d7d08d3d6dea325ef2107f.html</filename>
    <dir>src/fancyqpalm/include/fancyqlone/fancyqpalm/backends</dir>
    <dir>src/fancyqpalm/include/fancyqlone/fancyqpalm/implementation</dir>
    <file>detailed-stats.hpp</file>
    <file>qpalm.hpp</file>
    <file>settings.hpp</file>
    <file>solver.hpp</file>
    <file>status.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/include/fancyqlone/cyqlone/implementation</name>
    <path>src/fancyqlone/include/fancyqlone/cyqlone/implementation/</path>
    <filename>dir_f9ffb315ae35022c7af17647d85926cd.html</filename>
    <file>cr.tpp</file>
    <file>data.tpp</file>
    <file>factor.tpp</file>
    <file>indexing.tpp</file>
    <file>mat-vec.tpp</file>
    <file>pcg.tpp</file>
    <file>pcr.tpp</file>
    <file>riccati.tpp</file>
    <file>schur.tpp</file>
    <file>sparse.tpp</file>
    <file>update.tpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/include/fancyqlone/fancyqlone/implementation</name>
    <path>src/fancyqlone/include/fancyqlone/fancyqlone/implementation/</path>
    <filename>dir_48567aea9121bf34c6c92bfd773d108e.html</filename>
    <file>fan-data.tpp</file>
    <file>fan-factor.tpp</file>
    <file>fan-mat-vec.tpp</file>
    <file>fan-update.tpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation</name>
    <path>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation/</path>
    <filename>dir_5245091977c81dde984ed67937983437.html</filename>
    <file>sfan-data.tpp</file>
    <file>sfan-factor.tpp</file>
    <file>sfan-mat-vec.tpp</file>
    <file>sfan-update.tpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqpalm/include/fancyqlone/fancyqpalm/implementation</name>
    <path>src/fancyqpalm/include/fancyqlone/fancyqpalm/implementation/</path>
    <filename>dir_de42a1381fa3e72a4caa5d47ecf60f7d.html</filename>
    <file>algorithms.hpp</file>
    <file>breakpoint.hpp</file>
    <file>breakpoint.tpp</file>
    <file>linesearch.tpp</file>
    <file>solver.tpp</file>
  </compound>
  <compound kind="dir">
    <name>src/example-problems/include</name>
    <path>src/example-problems/include/</path>
    <filename>dir_b0ad1b14a57645f86573ae64172f605e.html</filename>
    <dir>src/example-problems/include/fancyqlone</dir>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/include</name>
    <path>src/fancyqlone/include/</path>
    <filename>dir_ca4a4af1f17dfe7661916ac70bf0c58e.html</filename>
    <dir>src/fancyqlone/include/fancyqlone</dir>
  </compound>
  <compound kind="dir">
    <name>src/fancyqpalm/include</name>
    <path>src/fancyqpalm/include/</path>
    <filename>dir_3c11fa74d1c8131f5eb157894b69d059.html</filename>
    <dir>src/fancyqpalm/include/fancyqlone</dir>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/include/fancyqlone/sequential-fancyqlone</name>
    <path>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/</path>
    <filename>dir_fcc1f762b864cf9c2cf58b6210f4f1b4.html</filename>
    <dir>src/fancyqlone/include/fancyqlone/sequential-fancyqlone/implementation</dir>
    <file>serial-fancyqlone.hpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/src/sequential-fancyqlone</name>
    <path>src/fancyqlone/src/sequential-fancyqlone/</path>
    <filename>dir_d8883acabce15c9255dbdbde9961ce14.html</filename>
    <file>serial-fancyqlone.cpp</file>
  </compound>
  <compound kind="dir">
    <name>docs/source</name>
    <path>docs/source/</path>
    <filename>dir_1ab31cb45db5038bdda41b72d8600e0e.html</filename>
    <dir>docs/source/doxygen</dir>
  </compound>
  <compound kind="dir">
    <name>src</name>
    <path>src/</path>
    <filename>dir_68267d1309a1af8e8297ef4c3efbcdba.html</filename>
    <dir>src/example-problems</dir>
    <dir>src/fancyqlone</dir>
    <dir>src/fancyqpalm</dir>
  </compound>
  <compound kind="dir">
    <name>src/example-problems/src</name>
    <path>src/example-problems/src/</path>
    <filename>dir_b7c7187cfc7c2dae6fb436abbbfac846.html</filename>
    <file>csv.cpp</file>
    <file>platooning.cpp</file>
    <file>spring-mass.cpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqlone/src</name>
    <path>src/fancyqlone/src/</path>
    <filename>dir_432eca6c55fc1a3abf3fc50d2a7d3ee6.html</filename>
    <dir>src/fancyqlone/src/cyqlone</dir>
    <dir>src/fancyqlone/src/fancyqlone</dir>
    <dir>src/fancyqlone/src/sequential-fancyqlone</dir>
    <file>conversion.cpp</file>
    <file>matio.cpp</file>
    <file>ocp.cpp</file>
    <file>tracing.cpp</file>
  </compound>
  <compound kind="dir">
    <name>src/fancyqpalm/src</name>
    <path>src/fancyqpalm/src/</path>
    <filename>dir_6c100b72ce2d14aa9500f9c3d7abe405.html</filename>
    <file>breakpoint.cpp</file>
    <file>ocp-backend-cyqlone.cpp</file>
    <file>qpalm.cpp</file>
    <file>status.cpp</file>
  </compound>
  <compound kind="dir">
    <name>test</name>
    <path>test/</path>
    <filename>dir_13e138d54eb8818da29c3992edef070a.html</filename>
    <file>test-pcr.cpp</file>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>fancyqlone</title>
    <filename>index.html</filename>
    <docanchor file="index.html">md_README</docanchor>
  </compound>
</tagfile>
