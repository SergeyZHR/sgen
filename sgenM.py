#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import numpy as np
#import codecs
from astropy import units as u
from astropy.coordinates import SkyCoord
from subprocess import call, DEVNULL
import random
import os
import glob

Nmaps = 1
show_ans = True
gen_ans = False
deep_list='M.csv'

def make_chart(alpha0,delta0,M_Ns):
	tex =  r"""\documentclass[11pt,a4paper]{article}
		\usepackage[utf8]{inputenc}
		\usepackage[russian]{babel}
		\usepackage[OT1]{fontenc}
		\usepackage{amsmath}
		\usepackage{amsfonts}
		\usepackage{amssymb}
		\usepackage{graphicx}
		\usepackage[left=1.5cm,right=1.5cm,top=1cm,bottom=1cm]{geometry}
		\begin{document}
		"""
		tex_part = r"""
		\begin{figure}[h!]
		\begin{minipage}[h!]{0.45\linewidth}
		\center{\includegraphics[width=1\linewidth]{$$F1$$}}
		\end{minipage}
		\hfill
		\begin{minipage}[h!]{0.45\linewidth}
		\center{\includegraphics[width=1\linewidth]{$$F2$$}}
		\end{minipage}
		\end{figure}
		"""

	for i in range(len(M_Ns),2):
		f1name='40/MAP_'+str(M_NS[i])
		f2name='40/MAP_'+str(M_NS[i+1])
		now_tex_part = tex_part.replace('$$F1$$',f1name)
		now_tex_part = tex_part.replace('$$F2$$',f2name)
		tex+=now_tex_part

	tex+=r'\end{document}'

	# tex = tex.replace('$$MAP_NAME$$',map_name)
	# tex = tex.replace('$$STAR_TABLE$$',star_table)
	# tex = tex.replace('$$M_LIST$$',m_list)
	# tex = tex.replace('$$NUMBER$$',str(N))
	texfname = './M_Map'+str(N)+'.tex'
	file = open(texfname, 'w')
	file.write(tex)
	file.close()

	call(['pdflatex.exe', texfname],stdout=DEVNULL)#,stderr = DEVNULL )


Mdat = np.loadtxt(deep_list,dtype=str,delimiter=';')

for i in range(Nmaps):
	sequence = np.random.permutation(len(Mdat))
	MNS=Mdat[sequence,0]
	make_chart(MNS)
