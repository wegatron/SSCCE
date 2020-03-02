import pandas as pd
import matplotlib.pyplot as plt

pdf_data = pd.read_csv('F:/workspace/gz_work/projects/scancontext/c++/result/multi_stairs/candidate_mr.csv', header=None)
pdf_data.hist(bins=20, cumulative=True, histtype='bar', normed=True)
plt.show()
