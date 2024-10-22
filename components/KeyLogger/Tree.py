
from collections import deque

class TreeNode:
  def __init__(self, name: str):
    self.name = name
    self.children: list[TreeNode] = []

  def add_child(self, child_node: 'TreeNode'):
    self.children.append(child_node)

  def __repr__(self):
    # return self.print_tree_by_children()[:-1]
    return self.print_tree_by_level()[:-1]
  
  def print_tree_by_children(self, level=0):
    # print(level, type(level))
    ret = "\t" * level + repr(self.name) + "\n"
    for child in self.children:
      ret += child.print_tree_by_children(level + 1)
    return ret



