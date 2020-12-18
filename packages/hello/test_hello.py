def test_pillow(selenium):
    selenium.load_package("hello")
    selenium.run(
        r"""
import hello
hello.greet("coucou")
    """
    )
