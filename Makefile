build:
	python main.py
	xelatex -shell-escape CheatSheet.tex
	xelatex -shell-escape CheatSheet.tex
	del /f content.tex *.log *.toc *.aux *.pyg
	rm -f content.tex *.log *.toc *.aux *.pyg
