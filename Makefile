build:
	python main.py
	xelatex -shell-escape CheatSheet.tex
	xelatex -shell-escape CheatSheet.tex
	rm -f content.tex *.log *.toc *.aux *.pyg
