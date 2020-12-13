import dendropy
import sys
import optparse


def process_input():
	inputFile = None
	parser = optparse.OptionParser()
	parser.add_option('-i', dest='inp',type='string', help='the name of the input file')
	parser.add_option('-o', dest='out', type='string', default='Data/newickNJ.txt', help='the name of the output file')
	parser.add_option('-a', dest='algo',type='string', default='NJ', help='name of the tree construction algorithm')
	(options, _) = parser.parse_args()

	if options.inp == None:
		print("No input file given.")
		sys.exit(1)
	else:
		inputFile = options.inp

	outputFile = options.out
	algorithm = options.algo

	return inputFile,outputFile,algorithm

def main():

	inputFile,outputFile,algorithm = process_input()
		
	pdm = dendropy.PhylogeneticDistanceMatrix.from_csv(src=open(inputFile), delimiter=",")
	tree = None

	if algorithm == "NJ":
		tree = pdm.nj_tree()
	elif algorithm == "UPGMA":
		tree = pdm.upgma_tree()
	else:
		print("No/Incorrect tree format given.")
		sys.exit(1)

	f = open(outputFile, "w")
	f.write(tree.as_string("newick"))
	print("Tree printed")


if __name__ == "__main__":
	main()
	
