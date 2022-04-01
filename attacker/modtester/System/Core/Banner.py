from Colors import bcolors

def Banner(version,modulesNum):
	print ' _______ '
	print '< ModTester >'
	print ' ------- '
	print '           ________                    '
	print '|\   /|	      |      ________         '
	print '| \_/ | _  _| |	 __  __  |  __ __      '
	print '|     |/ \/ | | /_  /_   | /_  |_\    '
	print '|     |\_/\_/ | \__ _/   | \__ | \    '
	print '\n'
	print ' '*10 + '--=' + bcolors.OKBLUE + '[' + bcolors.ENDC + bcolors.BOLD + 'MODBUS' + bcolors.ENDC +' Pentesting Toolkit'
	print ' '*7 + '--+--=' + bcolors.OKBLUE + '[' + bcolors.ENDC + 'Version : ' + bcolors.OKGREEN + bcolors.BOLD + '1.0' + bcolors.ENDC + bcolors.ENDC
	print ' '*7 + '--+--=' + bcolors.OKBLUE + '[' + bcolors.ENDC + 'Modules : ' + bcolors.OKGREEN + bcolors.BOLD + str(modulesNum) + bcolors.ENDC + bcolors.ENDC	
	print ' '*7 + '--+--=' + bcolors.OKBLUE + '[' + bcolors.ENDC + 'Coder   : ' + bcolors.OKGREEN + bcolors.BOLD + 'Danel Lopez' + bcolors.ENDC + bcolors.ENDC	
	print ' '*10 + '--=' + bcolors.OKBLUE + '[' + bcolors.ENDC + 'github  : ' + bcolors.OKGREEN + bcolors.BOLD + 'www.github.com/dangoro94' + bcolors.ENDC + bcolors.ENDC	
	print ' '


