import sys, os
import xml.etree.ElementTree as ET
import csv

#------------- Change direction into ouput folder -------------#
path = os.getcwd()              # ..\\project\\framework
path = os.path.dirname(path)    # ..\\project
os.chdir(path + '\\output')         # ..\\project\\output

listXML = []    # List of xml file
listfile = os.listdir()

#--------------- List all XML file --------------#
for file in listfile:
	if '.xml' in file:
		listXML.append(file)
 
with open ('TestReport.csv', 'w') as csvfile:
    writer = csv.writer(csvfile, delimiter = '\t', \
    quotechar = '"', quoting = csv.QUOTE_MINIMAL)
    writer.writerow(['Test suite', 'Test Discription', \
    'No. of Tests', "Test's Result"])

#------------------ XML to CSV ------------------# 
for i in range(len(listXML)):
    xmlfile = listXML[i]
    tree = ET.parse(xmlfile)
    root = tree.getroot()
    
    '''-------- List all text from XML file --------'''
    name = root[0].text.split('\n')[1].lstrip()
    discrip = root[1].text.split('\n')[1].lstrip()
    num = root[2].text.split('\n')[1].lstrip()
    result = root[3].text.split('\n')[1].lstrip()
    
    '''---------- Write data to CSV file -----------'''
    with open ('TestReport.csv', 'a') as csvfile:
        writer = csv.writer(csvfile, delimiter = '\t', \
        quotechar = '"', quoting = csv.QUOTE_MINIMAL)
        writer.writerow([name, discrip, num, result])
