# ACM Template

本项目基于 [Lodour/ACM-CheatSheet](https://github.com/Lodour/ACM-CheatSheet)，一方面作为自动生成Latex模板的部分，另一方面作为本蒟蒻屯自己模板的一个项目 QAQ  

本项目在原项目的基础上，改写`core.py`文件，引入`config.json`管理模板架构；修改`CheatSheet.sty`与`CheatSheet.tex`文件，调整封面风格。`config.json`中，每个对象均有三个属性  

- `section`: 显示的标题  
- `depth`: 深度，值为0, 1, 2，分别对应于`section`, `subsection`, `subsubsection`  
- `src`: 文件对应路径（若为`null`则代表该项为目录）  

其余内容基本与原项目相同  
