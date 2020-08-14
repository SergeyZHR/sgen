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

N_deep = 10
N_star = 10
decS = -10	#>-85
decE = 80   #<85
clear = 1
Nmaps = 15
show_ans = True
show_N = False

SNstr=''

def make_chart(alpha0,delta0,N):
	tex =  r'''
	\documentclass[12pt,a4paper]{article}
	\usepackage[utf8x]{inputenc}
	\usepackage{ucs}
	\usepackage[russian]{babel}
	\usepackage[OT1]{fontenc}
	\usepackage{amsmath}
	\usepackage{amsfonts}
	\usepackage{amssymb}
	\usepackage{graphicx}
	\usepackage{wrapfig}
	\usepackage{color}
	\usepackage{wasysym}

	\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=1.5cm]{geometry}
	\begin{document}
		 \thispagestyle{empty}
		\begin{center}
			\large \sf 
			Автогенератор скайчартов для всех и вся -- теперь и на питоне{\tiny, v3.2}\\[-1pc]
			\rule{\textwidth}{0.5pt}
		\end{center}
			\begin{wrapfigure}{l}{0.1\textwidth}
				\centering
				\vspace{-4pc}
				\hspace*{0pc}
				\includegraphics[width = 0.2 \textwidth]{Logo2.jpg}
				\vspace{1pc}
			\end{wrapfigure}	
			
			{\vspace{1pc}
			\hspace{13pc} \Large \sc  Скайчарты! \par
			\vspace{1.5pc}
			\hspace{12pc} \large \sl ОНИ вас не бросят! \hspace{8 pt} 19.03.2020\\[1.5pc]
			 \rule{\textwidth}{0.5pt}}
			\vspace{-2pc}
			 		
			\begin{enumerate}
				\item{Обозначьте точку зенита символом <<$Z$>> и стороны света <<$N$, $E$, $S$, $W$>>.}
				\item{Обозначьте точку полюса мира символом <<$P$>> и проведите небесный мередиан.}
				\item{Проведите небесный экватор и обозначьте точку весеннего равноденствия символом<<$\vernal$>> или точку осеннего равноденствия <<$\libra$>>. }
				\item{Звездное время: \hrulefill}
				\item{Учитывая, что скайчарт приведен в стереографической проекции, определите широту места наблюдения: \hrulefill}
				\item{Проведите контуры всех созвездий и напишите сокращения их названий по Байеру.}

				\item{На карте найдите звёзды:\\
					$$STAR_TABLE$$
					}
				\item{На карте найдите объекты DeepSky:\\
				 $$M_LIST$$
				 }
			\end{enumerate}
			\vfill
			 \tiny{$$ANS$$$$N$$}
			\newpage
			\thispagestyle{empty}
			\begin{figure}
				\hspace*{ $$SHIFT$$\textwidth}				
				\includegraphics[width = 1.05\textwidth, angle = $$ANGLE$$]{$$MAP_NAME$$.pdf}
			\end{figure}
			
		
	\end{document}
	'''
	#filecp = codecs.open('stars.csv')#, encoding = 'cp1252')
	#N=1
	#alpha0=0
	#delta0=0

	Sdat = np.loadtxt('stars.csv',dtype=str,delimiter=',',encoding='UTF-8')
	Mdat = np.loadtxt('M.csv',delimiter=';')


	alphaS =15.*  Sdat[:,1].astype(float)
	deltaS = Sdat[:,2].astype(float)

	alphaM = Mdat[:,1]
	deltaM = Mdat[:,2]

	stars=SkyCoord(alphaS*u.degree, deltaS*u.degree)
	Ms=SkyCoord(alphaM*u.degree, deltaM*u.degree)

	center = SkyCoord(alpha0*u.degree, delta0*u.degree)

	sepArrS = center.separation(stars)
	Sdat = Sdat[np.where(sepArrS<85*u.degree)]

	sepArrM = center.separation(Ms)
	Mdat = Mdat[np.where(sepArrM<85*u.degree)]




	#print Sdat[:,0]

	map_name='Map_'+str(N)

	star_table=''

	endOfObj=''
	if N_star+N_deep<21:
		endOfObj=r'\\'

	if N_star<len(Sdat):
		Sdat = np.array(random.sample(list(Sdat), N_star) )
	
	for S in Sdat:
		#star_table+=S[0]+', '
		stemp=S[3].split(' ')
		star_table+=S[0] +'~--~$'+stemp[0]+'$~'+stemp[1]+', '+endOfObj

	star_table=star_table[:-2-len(endOfObj)]+'.'

	m_list=''

	if N_deep<len(Mdat):
		Mdat =  np.array(random.sample(list(Mdat), N_deep) ) 
		Mdat = sorted(Mdat,key=lambda x:x[0])

	for M in Mdat:
		m_list+='M'+str(int(M[0]))+', '+endOfObj
	m_list=m_list[:-2-len(endOfObj)]+'.'

	tex = tex.replace('$$MAP_NAME$$',map_name)
	tex = tex.replace('$$STAR_TABLE$$',star_table)
	tex = tex.replace('$$M_LIST$$',m_list)
	if show_ans:
		tex = tex.replace('$$ANS$$','{:.2f}; {:.2f}'.format(alpha0/15., delta0))
	else:
		tex = tex.replace('$$ANS$$','')

	if show_N:
		if delta0>0: hem='N'
		if delta0<0: hem='S'

		tex = tex.replace('$$N$$',hem)
	else:
		tex = tex.replace('$$N$$','')

	global SNstr
	if delta0>0: SNstr+='N'
	if delta0<0: SNstr+='S'


	angle = int(random.uniform(0,360))
	deltaAngle = np.radians(angle % 90)
	shift=-1*(1.05*np.sqrt(2)*np.cos(deltaAngle-np.radians(45))-1)/2.
	tex = tex.replace('$$SHIFT$$',str(shift))
	tex = tex.replace('$$ANGLE$$',str(angle))

	file = open('Chart'+str(N)+'.tex', 'w')
	file.write(tex)
	file.close()

	##pp3 conf
	pp3 = '''
	filename output Map_$$N$$.tex
	switch pdf_output on
	switch eps_output off

	set center_rectascension $$RA$$
	set center_declination $$DEC$$
	set grad_per_cm 10
	set box_width 18
	set box_height 18

	set star_scaling 0.5
	set faintest_star_disk_magnitude 5.5
	set minimal_star_radius 0.005

	switch constellation_lines off
	switch ecliptic off
	switch milky_way off
	switch grid off
	switch boundaries off
	switch nebulae off
	switch labels off
	switch colored_stars off
	color background 1 1 1
	color stars 0 0 0
	color horizon 0 0 0
	'''

	pp3=pp3.replace('$$N$$',str(N))
	pp3=pp3.replace('$$RA$$',str(alpha0/15.))
	pp3=pp3.replace('$$DEC$$',str(delta0))

	file = open('map'+str(N)+'.pp3', 'w')
	file.write(pp3)
	file.close()

	call(['./pp3-1.3.3_skychart/pp3', 'map'+str(N)+'.pp3'],stdout=DEVNULL,stderr = DEVNULL)
	call(['pdflatex', 'Chart'+str(N)+'.tex'],stdout=DEVNULL)#,stderr = DEVNULL )


if clear:
	rem = np.hstack([glob.glob('./*.pdf'), glob.glob('./*.tex'), glob.glob('./*.log'), glob.glob('./*.aux'), glob.glob('./*.eps'), glob.glob('./*.dvi'), glob.glob('./*.pp3'), glob.glob('./*.dat')])
	for f in rem:
		os.remove(f)


for i in range(Nmaps):
	
	ra = random.uniform(0,360)
	z = random.uniform(np.sin(np.radians(decS)),np.sin(np.radians(decE)))
	dec = np.degrees(np.arcsin(z))


	while (np.abs(dec)<6) :
		z = random.uniform(np.sin(np.radians(decS)),np.sin(np.radians(decE)))
		dec = np.degrees(np.arcsin(z))
	make_chart(ra,dec,i)
	print (i+1, 'chart done')
	print (ra,dec)
	 	
rem = np.hstack([glob.glob('./M*.tex'), glob.glob('./*.log'), glob.glob('./*.aux'), glob.glob('./*.eps'), glob.glob('./*.dvi'), glob.glob('./*.p3'), glob.glob('./*.dat')])
for f in rem:
	os.remove(f)

print(SNstr)

call('rm ./temp/*pdf', shell=True)
call('cp ./C*pdf ./temp', shell=True)
call('pdfjoin --outfile ./ALLcharts.pdf ./temp/*pdf', shell=True)