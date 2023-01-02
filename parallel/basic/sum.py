import numpy as np
DATANUM = 128000000

arr = DATANUM - np.arange(DATANUM) + 0.1
np.set_printoptions(suppress=False)
print(np.sin(np.log(np.sqrt(arr))).sum())
