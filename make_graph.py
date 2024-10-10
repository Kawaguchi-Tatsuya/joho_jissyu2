import matplotlib.pyplot as plt
import numpy as np
 
# data set, omega and power
RPM = [ 155, 175, 200, 210,  250, 319,  380, 490, 550, 617]
Pout = [ 0.02, 0.11 , 0.36, 0.45, 0.51, 0.59, 0.66, 0.71, 0.58, 0.42 ]
 
# draw scatter plot
plt.scatter(RPM, Pout, marker='o', color = 'black', label='high')
    
# configure title, axis label and grid
plt.title('Output power of engine.')
plt.xlabel('Revolution (rpm)')
plt.ylabel('$P$ (W)')
    
# add axis tick
ax = plt.gca()             # get current axis
ax.tick_params(direction = 'in', length = 5) 
  
# set range of axis
plt.xlim(100, 700)
plt.ylim(0, 1.0)
 
# grid lines
plt.grid(True, color='black')
 
# save figure to file
plt.savefig('figure1.pdf')             # PDF file
plt.savefig('figure1.png', dpi=300)    # png image file
 
# Show image
plt.show()