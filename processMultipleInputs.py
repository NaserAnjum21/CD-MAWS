import sys

taxa_to_seq = {}

def read_fasta_file(fileName):
    with open(fileName, 'r') as file:
        lines = (line.strip() for line in file)
        lines = (line for line in lines if line)
        cur_taxa = ""

        for line in lines:
            if line[0] == '>':
                cur_taxa = line
                if cur_taxa not in taxa_to_seq:
                    taxa_to_seq[cur_taxa] = ""
            else:
                taxa_to_seq[cur_taxa] += (line + '\n')


if __name__ == '__main__':

    fof_name = sys.argv[1]
    out_file_name = sys.argv[2]

    with open(fof_name) as file:
        file_locations = file.read().splitlines()

    for fasta_file in file_locations:
        read_fasta_file(fasta_file)

    with open(out_file_name, 'w') as file:
        for taxa, seq in taxa_to_seq.items():
            file.write(taxa + '\n')
            file.write(seq + '\n')

    
