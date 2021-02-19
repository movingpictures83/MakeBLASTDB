# MakeBLASTDB
# Language: C++
# Input: TXT
# Output: DB
# Tested with: PluMA 1.0, GCC 4.8.4
# Dependency: BLAST 2.2.25

PluMA plugin to build a database of sequences from an input
FASTA file using BLAST (Altschul et al, 1990).

The plugin accepts as input a TXT file of tab-delimited keyword-value pairs.  Keywords are:
fasta (name of the FASTA file)
dbtype (nucleotide or protein)

fasta will either be a single FASTA file or a directory
of FASTA files.

If the user supplies a single FASTA file, it will output a single file
for the database (the outputfile)

If the user supplies a directory for the inputfile, they must also supply
a directory for the outputfile.  In this case the plugin will produce a database
in the output directory for every input FASTA file in the input directory.
These files must end in ".fasta".
