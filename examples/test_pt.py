import piece_table1
#import array1
#import gap_buffer
import pytest
def setup():
    sequence = piece_table1.Sequence("")
    return sequence

def test_1():
    s = setup()
    assert str(s) == ""
    s.insert(0,"xxxx")
    assert str(s) == "xxxx"
    s.erase(0,4)
    assert str(s) == ""

def test_2():
    s = setup()
    s.insert(0,"abcdefg")
    s.insert(7,"hijk")
    assert str(s) == "abcdefghijk"
    s.insert(0, "12345")
    assert str(s) == "12345abcdefghijk"

def test_3():
    s=setup()
    s.erase(0, 5)
    assert str(s) == ""
    s.insert(0,"1")
    s.erase(1,100)
    assert str(s) == "1"

def test_4():
    s= setup()
    s.insert(1,"asdfg")
    assert str(s) == ""
    s.insert(-1,"asdfg")
    assert str(s) == ""

def test_5():
    s = setup()
    s.insert(0,"xxxx")
    s.undo()
    s.redo()
    assert str(s) == "xxxx"
    s.insert(4,"abc")
    s.erase(0,1)
    s.undo()
    assert str(s) == "xxxxabc"
    s.redo()
    assert str(s) == "xxxabc"

def test_6():
    s = setup()
    s.insert(0,"xxxx")
    s.insert(2, "4")
    s.insert(0 , "5")
    s.undo()
    s.undo()
    assert str(s) == "xxxx"


    

