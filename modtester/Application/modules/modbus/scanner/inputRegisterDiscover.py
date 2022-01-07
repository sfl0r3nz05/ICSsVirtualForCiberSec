import os
import threading

from System.Core.Global import *
from System.Core.Colors import *
from System.Core.Modbus import *
from System.Lib import ipcalc




class Module:


	info = {
		'Name': 'Modbus Input Register Discover',
		'Author': ['@Danel'],
		'Description': (" Modbus Input Register Scanner"),

        }
	options = {
		'RHOSTS'	:[''		,True	,'The target address range or CIDR identifier'],
		'RPORT'		:[502		,False	,'The port number for modbus protocol'],
		'Threads'	:[1		,False	,'The number of concurrent threads'],
		'UID'		:[None		,True	,'Modbus Slave UID.'],
		'Output'	:[True		,False	,'The stdout save in output directory']
	}	

	output = ''

	def exploit(self):

		moduleName 	= self.info['Name']
		print bcolors.OKBLUE + '[+]' + bcolors.ENDC + ' Module ' + moduleName + ' Start'
		ips = list()
		for ip in ipcalc.Network(self.options['RHOSTS'][0]):
			ips.append(str(ip))
		while ips:
			for i in range(int(self.options['Threads'][0])):
				if(len(ips) > 0):
					thread 	= threading.Thread(target=self.do,args=(ips.pop(0),))
					thread.start()
					THREADS.append(thread)
				else:
					break
			for thread in THREADS:
				thread.join()
		if(self.options['Output'][0]):
			open(mainPath + '/Output/' + moduleName + '_' + self.options['RHOSTS'][0].replace('/','_') + '.txt','a').write('='*30 + '\n' + self.output + '\n\n')
		self.output 	= ''

	def printLine(self,str,color):
		self.output += str + '\n'
		if(str.find('[+]') != -1):
			print str.replace('[+]',color + '[+]' + bcolors.ENDC)
		elif(str.find('[-]') != -1):
			print str.replace('[-]',color + '[-]' + bcolors.ENDC)
		else:
			print str

	def do(self,ip):


		c = connectToTarget(ip,self.options['RPORT'][0])

		#Variables para recorre memoria y bloque de memoria a descubrir
		addressInt = 0
		MEM = [[],[]]
		top = addressInt + 10000

		if (c != None):


			while(addressInt <= top ):

				ans = c.sr1(ModbusADU(transId=getTransId(),unitId=int(self.options['UID'][0]))/ModbusPDU04_Read_Input_Registers(startAddr=addressInt,quantity=1),timeout=timeout, verbose=0)
				ans = ModbusADU_Answer(str(ans))
				#self.printLine('[+] Response is :',bcolors.OKGREEN)
				#ans.show()
				#print "Input Register : {} ".format(addressInt)

				try:
					#La respuesta es correcta
					if(ans.funcCode != 0x83):
						MEM[0].append(addressInt)
						MEM[1].append(ans.registerVal)
				except: 
					MEM[0].remove(addressInt)

				addressInt += 1

				sys.stdout.write("\rCorriendo : {}  % ".format(addressInt/100))
    			sys.stdout.flush()
    			print '\n'
		
					

			print '-------------------------------------------'
			print 'Input Registers en memoria: {}'.format(len(MEM[0]))
				
			try:

				for x in range(len(MEM[0])): 
					print MEM[0][x]," ==>" ,MEM[1][x]

			except: 
				pass		
