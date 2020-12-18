def test_pillow(selenium):
    selenium.load_package("testdlsym")
    selenium.run(
        r"""
from testdlsym import run
run()
    """
    )
