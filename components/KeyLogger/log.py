from Tree import TreeNode

cluster_start = -1
in_cluster = True

trees: dict[chr, TreeNode] = {}
current_node = None

def cluster(char, time):
  f = open("Logs/testLog.txt", "a")
  global cluster_start
  # print(time-cluster_start)

  if time > 0.2:
    f.write("\n> ")
  print(char)
  if len(char) == 1:
    f.write(char)

  # if time < 0.2:
  #   if len(char) == 1:
  #     f.write(char)
  # else:
  #   print("NEW CLUSTER STARTS")
  #   f.write("\n> ")
  #   if len(char) == 1:
  #     f.write(char)
  #   cluster_start = time
  print(f"{char} at {time}")
  f.close()

# def add_char_to_tree(char):
#   global trees, in_cluster, current_node

#   print(trees.keys())
#   if char in trees.keys():
#     print("Tree exists. Checking children")
#     node = trees[char]

#     found = False
#     for child in node.children:
#       if char == child.name:
#         print("Found child. Increasing strength and breaking")
#         child.strength += 1
#         current_node = child
#         found = True
#         break
#     if not found:
#       print("Child does not exist. Creating child")
#       trees[char].add_child(TreeNode(char))

#   else:
#     print("Tree does not exist. Creating tree")
#     trees[char] = TreeNode(char)

def add_child_to_node(node: TreeNode, char: str):
  node.add_child(TreeNode(char))

def add_char_to_cluster(node: TreeNode, char: str):
  if char in node:
    
  else:
    add_child_to_node()

def add_char_to_tree(char: str, in_cluster: bool):
  global trees
  
  in_cluster = True # RIGHT NOW TESTING WITH ALWAYS BEING IN THE SAME CLUSTER
  if in_cluster:
    add_char_to_cluster(char)

def log(char, time):
  # cluster(char, time)
  # print(char, type(char))
  add_char_to_tree(char, time < 0.2)

def writeAll():
  print("WRITING!!")
  thing = []
  for tree in trees.values():
    # thing.append(tree.print_tree_by_children())
    print(tree)
    print(tree.children)
    break
  print(thing)

