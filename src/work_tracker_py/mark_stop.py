

import os 
import time


timestr = time.strftime("%Y%m%d_%H%M%S")
fn = "mixed.txt"

f = open(fn, "a", encoding="utf-8")
f.write("    stop at: \t"+timestr+"\n")
# f.write("\n    --- prepare: et 1h \n        事务 once, direct\n        进展\n        研习代码\n        研习论文\n        研习书籍\n        生活\n")
f.close()

print("mark stop success")
