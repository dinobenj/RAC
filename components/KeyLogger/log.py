from Tree import TreeNode

cluster_start = -1
in_cluster = True

trees: dict[chr, TreeNode] = {}
current_node: TreeNode = None

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

def tree(char):
  global trees, current_node
  print(trees.keys())
  if char in trees.keys():
    print("Tree exists. Checking children")
    node = trees[char]

    found = 0
    for child in node.children:
      if char == child.name:
        print("Found child. Increasing strength and breaking")
        child.strength += 1
        current_node = child
        found = 1
        break
    if not found:
      print("Child does not exist. Creating child")
      node.add_child(TreeNode(char))

  else:
    print("Tree does not exist. Creating tree")
    trees[char] = TreeNode(char)

def log(char, time):
  # cluster(char, time)
  # print(char, type(char))
  tree(char)
  


