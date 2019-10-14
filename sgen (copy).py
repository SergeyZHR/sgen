#!/usr/bin/python
# -*- coding: UTF-8 -*-
import numpy as np
#import codecs
from astropy import units as u
from astropy.coordinates import SkyCoord
from subprocess import call
import random
import os
import glob
decS = -85	#>-85
decE = 85   #<85
clear = 1
Nmaps = 10
print(np.sin(np.radians(decS)),np.sin(np.radians(decE))) 

for i in range(Nmaps):
	
	ra = random.uniform(0,360)
	z = random.uniform(np.sin(np.radians(decS)),np.sin(np.radians(decE)))
	dec = np.degrees(np.arcsin(z))


	while (np.abs(dec)<6) :
		z = random.uniform(np.sin(np.radians(decS)),np.sin(np.radians(decE)))
		dec = np.degrees(np.arcsin(z))

	print(dec,i)
