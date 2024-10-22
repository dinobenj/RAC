
cluster_start = -1
in_cluster = True

def log(char, time):
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


