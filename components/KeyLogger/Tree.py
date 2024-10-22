
from collections import deque

class TreeNode:
  def __init__(self, name: str):
    self.name = name
    self.children: list[TreeNode] = []
    self.strength = 1

  def add_child(self, child_node: 'TreeNode'):
    self.children.append(child_node)

  def __repr__(self):
    return self.print_tree_by_children()[:-1]
    # return str(self.print_tree_by_level()[:-1])
    # return str(self.print_tree_by_level())
  
  def print_tree_by_children(self, level=0):
    # print(level, type(level))
    ret = "\t" * level + repr(self.name) + "\n"
    for child in self.children:
      ret += child.print_tree_by_children(level + 1)
    return ret

  # def print_tree_by_level(self, level=0):
  #   # [[[]]]
  #   # List of depths, depths are lists of groups of children of specific parent

  #   flock_of_children = {}

  #   flock_of_children[level] = []
  #   for child in self.children:
  #     flock_of_children[level].append(child.print_tree_by_level(level+1))
    
  #   return flock_of_children

