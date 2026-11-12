import fancyqlone


def test_version():
    assert fancyqlone.__version__ == fancyqlone.__c_version__
    fancyqlone.build_time
