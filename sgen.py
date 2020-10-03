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
N_star = 12
decS = -40	#>-85
decE = 85   #<85
clear = 1
Nmaps = 10
show_ans = True
show_N = False
gen_ans = False
SNstr=''
star_list='stars.csv'
deep_list='deep.csv'

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
			Автогенератор скайчартов для всех и вся -- теперь и на питоне{\tiny, v3.3}\\[-1pc]
			\rule{\textwidth}{0.5pt}
		\end{center}
			\begin{wrapfigure}{l}{0.1\textwidth}
				\centering
				\vspace{-4pc}
				\hspace*{0pc}
				\includegraphics[width = 0.32 \textwidth]{LogoN.png}
				\vspace{1pc}
			\end{wrapfigure}	
			
			{\vspace{1pc}
			\hspace{15pc} \Large \sc  Скайчарт Коронный! \par
			\vspace{1.5pc}
			\hspace{14pc} \large \sl Когда вам ещё печатных принесут... \hspace{3 pt} 01.10.2020\\[1.5pc]
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
	#\includegraphics[width = 0.32 \textwidth]{Logo.jpg}		#+2pc
	#\includegraphics[width = 0.2 \textwidth]{Logo2.jpg}		

	texAns =  r'''
	\documentclass[12pt,a4paper]{article}
	\usepackage[utf8]{inputenc}
	\usepackage[russian]{babel}
	\usepackage[OT1]{fontenc}
	\usepackage{amsmath}
	\usepackage{amsfonts}
	\usepackage{amssymb}
	\usepackage{graphicx}
	\usepackage{float}
		\usepackage[left=1.5cm,right=1.5cm,top=1.5cm,bottom=0cm]{geometry}
	\begin{document}
	\center
	\bf
	Ответ на скайчарт $$NUMBER$$\\
	$\alpha=$$RA$$^h$, $\delta=$$DEC$$^\circ$
	\begin{figure}[H]
		\hspace*{ $$SHIFT$$\textwidth}				
		\includegraphics[width = 1.05\textwidth, angle = $$ANGLE$$]{$$MAP_NAME$$.pdf}
	\end{figure}
	\end{document}
	'''

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


	##pp3 conf
	pp3Ans = '''
	filename output MapAns_$$N$$.tex
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
	set faintest_star_with_label_magnitude -2.0

	switch constellation_lines on
	switch ecliptic on
	switch horizon on
	switch milky_way off
	switch grid on
	switch boundaries on
	switch nebulae off
	switch labels on
	switch colored_stars off
	color stars 0 0 0
	color nebulae 0 0 0
	color background 1 1 1
	color grid 0.5 0.5 0.5
	color ecliptic 0.3 0.3 0.3
	color labels 0.7 0.3 0.3
	color text_labels 0.3 0.7 0.3
	color constellation_lines 0.7 0.7 0.7
	color highlighted_boundaries 0.7 0.7 0.7
	color boundaries 0.7 0.7 0.7
	
	line_width boundaries 0.01
	line_width constellation_lines 0.01
	line_width grid 0.01

	switch pdf_output on
	switch eps_output off
	objects_and_labels

	'''


	#filecp = codecs.open('stars.csv')#, encoding = 'cp1252')
	#N=1
	#alpha0=0
	#delta0=0

	Sdat = np.loadtxt(star_list,dtype=str,delimiter=',',encoding='UTF-8')
	Mdat = np.loadtxt(deep_list,dtype=str,delimiter=';')
	Constdat = np.loadtxt('Const.csv',dtype=str,delimiter=';')


	alphaS =15.* Sdat[:,1].astype(float)
	deltaS = Sdat[:,2].astype(float)

	alphaM = Mdat[:,1].astype(float)
	deltaM = Mdat[:,2].astype(float)

	stars=SkyCoord(alphaS*u.degree, deltaS*u.degree)
	Ms=SkyCoord(alphaM*u.degree, deltaM*u.degree)

	center = SkyCoord(alpha0*u.degree, delta0*u.degree)

	sepArrS = center.separation(stars)
	Sdat = Sdat[np.where(sepArrS<85*u.degree)]

	sepArrM = center.separation(Ms)
	Mdat = Mdat[np.where(sepArrM<85*u.degree)]




	#print Sdat[:,0]

	map_name='Map_'+str(N)
	map_nameAns='MapAns_'+str(N)

	star_table=''

	endOfObj=''
	if N_star+N_deep<23:
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
		Mdat_idx = sorted(random.sample(range(len(Mdat)), N_deep) ) 
		Mdat = Mdat[Mdat_idx]

	for M in Mdat:
		m_list+=M[0]+', '+endOfObj
	m_list=m_list[:-2-len(endOfObj)]+'.'

	tex = tex.replace('$$MAP_NAME$$',map_name)
	tex = tex.replace('$$STAR_TABLE$$',star_table)
	tex = tex.replace('$$M_LIST$$',m_list)
	tex = tex.replace('$$NUMBER$$',str(N))

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

	texAns = texAns.replace('$$NUMBER$$',str(N))
	texAns = texAns.replace('$$SHIFT$$',str(shift))
	texAns = texAns.replace('$$ANGLE$$',str(angle))
	texAns = texAns.replace('$$MAP_NAME$$',map_nameAns)
	texAns = texAns.replace('$$RA$$','{:.2f}'.format(alpha0/15.))
	texAns = texAns.replace('$$DEC$$','{:.2f}'.format(delta0))


	file = open('Chart'+str(N)+'.tex', 'w')
	file.write(tex)
	file.close()

	if gen_ans:
		file = open('ChartAns'+str(N)+'.tex', 'w')
		file.write(texAns)
		file.close()

	pp3=pp3.replace('$$N$$',str(N))
	pp3=pp3.replace('$$RA$$',str(alpha0/15.))
	pp3=pp3.replace('$$DEC$$',str(delta0))

	pp3Ans=pp3Ans.replace('$$N$$',str(N))
	pp3Ans=pp3Ans.replace('$$RA$$',str(alpha0/15.))
	pp3Ans=pp3Ans.replace('$$DEC$$',str(delta0))

	if len(Mdat)!=10:
		print("LENDATTT!!!!!!!!!!!!!",len(Mdat))
	alphas_label=[]
	deltas_label=[]
	def nearest(ra,dec):
		if len(alphas_label)==0: return 180
		alphas_labelNP=np.array(alphas_label)
		deltas_labelNP=np.array(deltas_label)
		#minres = (np.sqrt((alphas_labelNP-ra)**2*np.cos(np.radians(deltas_labelNP))**2+(deltas_labelNP-dec)**2)).min()
		minres = (np.sqrt((alphas_labelNP-ra)**2*np.cos(np.radians(dec))**2+(deltas_labelNP-dec)**2)).min()
		#print(minres)
		if minres>3:
			return False
		else:
			return True
		#return minres

	for M in Mdat:
		towards = 'W_'
		if nearest(float(M[1]),float(M[2]) ):
			towards='E_'
		M_strX = 'text "\\\\psdots[dotstyle=+,dotangle=45,dotsize=5pt](0,0)" at '+str(float(M[1])/15)+' '+str(M[2])+' color 0.7 0.3 0.3 towards W_ ;\n'
		M_strN = 'text "\\\\small '+M[0]+' \\\\hskip0.3em" at '+str(float(M[1])/15)+' '+str(M[2])+' color 0.7 0.3 0.3 towards '+towards+' ;\n'

		alphas_label.append(float(M[1]))
		deltas_label.append(float(M[2]))
		pp3Ans+=M_strX
		pp3Ans+=M_strN


	for S in Sdat:
		stemp=S[3].split(' ')
		if stemp[0][0]=='\\':
			stemp[0]='\\'+stemp[0]

		towards = 'W_'
		if nearest(float(S[1])*15,float(M[2]) ):
			towards='E_'
		#star_str = 'text "$'+stemp[0]+'$ '+stemp[1]+'" at '+S[1]+' '+S[2]+' towards NE ;\n'
		star_strX = 'text "\\\\psdots[dotstyle=+,dotangle=45,dotsize=5pt](0,0)" at '+S[1]+' '+S[2]+' color 0.3 0.7 0.3 towards W_ ;\n'
		star_strN = 'text "\\\\small $'+stemp[0]+'$ '+stemp[1]+' \\\\hskip0.3em " at '+S[1]+' '+S[2]+' color 0.3 0.7 0.3 towards '+towards+' ;\n'
		alphas_label.append(float(S[1])*15)
		deltas_label.append(float(S[2]))
		pp3Ans+=star_strX
		pp3Ans+=star_strN		

	for const in Constdat:
		c_str = 'text "\\\\footnotesize '+const[1]+'" at '+const[2]+' '+const[3]+' color 0.7 0.8 0.8 towards S ;\n'
		pp3Ans+=c_str

	file = open('map'+str(N)+'.pp3', 'w')
	file.write(pp3)
	file.close()

	if gen_ans:
		file = open('mapAns'+str(N)+'.pp3', 'w')
		file.write(pp3Ans)
		file.close()


	call(['./pp3-1.3.3_skychart/pp3', 'map'+str(N)+'.pp3'],stdout=DEVNULL,stderr = DEVNULL)
	call(['pdflatex.exe', 'Chart'+str(N)+'.tex'],stdout=DEVNULL)#,stderr = DEVNULL )

	if gen_ans:
		call(['./pp3-1.3.3_skychart/pp3', 'mapAns'+str(N)+'.pp3'],stdout=DEVNULL,stderr = DEVNULL)
		call(['pdflatex.exe', 'ChartAns'+str(N)+'.tex'],stdout=DEVNULL)#,stderr = DEVNULL )


if clear:
	rem = np.hstack([glob.glob('./*.pdf'), glob.glob('./*.tex'), glob.glob('./*.log'), glob.glob('./*.aux'), glob.glob('./*.eps'), glob.glob('./*.dvi'), glob.glob('./*.pp3'), glob.glob('./*.dat')])
	for f in rem:
		os.remove(f)


for i in range(1,Nmaps+1):
	
	ra = random.uniform(0,360)
	z = random.uniform(np.sin(np.radians(decS)),np.sin(np.radians(decE)))
	dec = np.degrees(np.arcsin(z))


	while (np.abs(dec)<6) :
		z = random.uniform(np.sin(np.radians(decS)),np.sin(np.radians(decE)))
		dec = np.degrees(np.arcsin(z))

	make_chart(ra, dec,i)
	print (i, 'chart done')
	#print (ra,dec)
	 	
rem = np.hstack([glob.glob('./M*.tex'), glob.glob('./*.log'), glob.glob('./*.aux'), glob.glob('./*.eps'), glob.glob('./*.dvi'), glob.glob('./*.p3'), glob.glob('./*.dat')])
for f in rem:
	os.remove(f)

print(SNstr)

call('rm ./temp/*', shell=True)
#call('cp ./Chart*.tex ./temp_ans', shell=True)
call('cp ./Chart*.pdf ./temp', shell=True)
call('pdfjoin --outfile ./ALLcharts.pdf ./temp/*pdf', shell=True)