

import functools, operator, numpy as np
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

def test_create_2d():
    print("[test_create_2d")
    s = nbt.create_2d(4,4)
    print("repr(s):\n%s\n" % repr(s))
    print("]test_create_2d")

def test_create_3d():
    print("[test_create_3d")
    s = nbt.create_3d(4,4,4)
    print("repr(s):\n%s\n" % repr(s))
    print("]test_create_3d")

def test_example_numpy_array_view_of_NP():
    print("[test_example_numpy_array_view_of_NP\n")
    for i in range(6):
        s = nbt.example_numpy_array_view_of_NP(i)
        print("repr(s):\n%s\n" % repr(s))
    pass
    print("]test_example_numpy_array_view_of_NP\n")


def make_array(shape=(2,6,4)):
    sz = functools.reduce(operator.mul,shape)
    a = np.arange(sz, dtype=np.float32).reshape(*shape)
    return a

def test_Processor_process():
    print("[test_Processor_process\n")
    a = make_array()
    print("a\n",a)

    pr = nbt.Processor()
    b = pr.process(a)
    print("b\n",b)
    print("]test_Processor_process\n")


def test_Processor_process_via_NP():
    print("[test_Processor_process_via_NP\n")
    a = make_array()
    print("a\n",a)
    pr = nbt.Processor()
    b = pr.process_via_NP(a)
    print("b\n",b)
    print("]test_Processor_process_via_NP\n")


def test_Processor_process_via_NP_with_meta():
    print("[test_Processor_process_via_NP_with_meta\n")
    a = make_array()
    print("a\n",a)
    pr = nbt.Processor()
    b, b_meta = pr.process_via_NP_with_meta(a)
    print("b\n",b)
    print("b_meta\n",b_meta)
    print("]test_Processor_process_via_NP_with_meta\n")



def main():
    print("nbt\n",nbt)
    test_inspect()
    test_Dog()
    test_create_2d()
    test_create_3d()
    test_example_numpy_array_view_of_NP()
    test_Processor_process()
    test_Processor_process_via_NP()
    test_Processor_process_via_NP_with_meta()


if __name__ == "__main__":
    #main()
    test_Processor_process_via_NP_with_meta()



