
import py_NP_nanobind_test as nbt

def test_inspect():
    print("[test_inspect")
    shape = (10,6,4)
    sz = functools.reduce(operator.mul,shape)
    a = np.arange(sz, dtype=np.float32).reshape(*shape)
    print("a\n",a)
    nbt.inspect(a)
    print("]test_inspect")


def test_Dog():
    print("[test_Dog")
    d = nbt.Dog("max")
    print(d)
    d.name = "maxine"
    print(d)
    print("]test_Dog")

def test_create():
    #s = nbt.create_2d(4,4)
    s = nbt.create_3d(4,4,4)
    print("repr(s):\n%s\n" % repr(s))

def test_example_numpy_array_view_of_NP():
    for i in range(6):
        s = nbt.example_numpy_array_view_of_NP(i)
        print("repr(s):\n%s\n" % repr(s))
    pass


if __name__ == "__main__":
    print("nbt\n",nbt)
    test_example_numpy_array_view_of_NP()

