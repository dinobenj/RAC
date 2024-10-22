from Tree import TreeNode

root = TreeNode("Root")


child1 = TreeNode("Child 1")
child2 = TreeNode("Child 2")
child3 = TreeNode("Child 3")


root.add_child(child1)
root.add_child(child2)

child1.add_child(child3)

print(root)


