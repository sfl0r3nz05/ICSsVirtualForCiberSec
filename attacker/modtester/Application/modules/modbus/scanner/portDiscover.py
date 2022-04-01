import os
import threading
import subprocess

from System.Core.Global import *
from System.Core.Colors import *
from System.Core.Modbus import *
from System.Lib import ipcalc

class Module:


	info = {
		'Name': 'Port scanner ',
		'Author': ['@Danel'],
		'Description': (" Port scan with Hping "),

        }
	options = {
		'RHOSTS'	:[''		,True	,'The target address range or CIDR identifier'],
		'PCOUNT'	:[1000		,False	,'The number of ports to scan'],
		'Output'	:[True		,False	,'The stdout save in output directory']
	}	
	output = ''

	def exploit(self):
			self.printLine('[+] Port scanning  started:',bcolors.OKGREEN)
			print "hping3 -S -8  1-%s %s" %(self.options['PCOUNT'][0],self.options['RHOSTS'][0])
	 		flood = os.system("/usr/sbin/hping3 -S -8 1-%s %s" %(self.options['PCOUNT'][0],self.options['RHOSTS'][0]))
			#subprocess.Popen(["./hping.sh"],stdin=subprocess.None)

			


	def printLine(self,str,color):
		self.output += str + '\n'
		if(str.find('[+]') != -1):
			print str.replace('[+]',color + '[+]' + bcolors.ENDC)
		elif(str.find('[-]') != -1):
			print str.replace('[-]',color + '[+]' + bcolors.ENDC)
		else:
			print str

	
