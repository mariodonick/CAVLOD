#!/bin/bash
        
pdflatex projektarbeit
makeindex -s projektarbeit.ist -t projektarbeit.glg -o projektarbeit.gls projektarbeit.glo
makeindex -s projektarbeit.ist -t projektarbeit.alg -o projektarbeit.acr projektarbeit.acn
makeindex -s projektarbeit.ist -t projektarbeit.slg -o projektarbeit.syi projektarbeit.syg
pdflatex projektarbeit
