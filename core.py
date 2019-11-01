# coding=utf-8
import logging
import re
import json
from pathlib import Path

import settings


class Generator(object):

    def __init__(self):
        self.content = []

    def populate(self):
        global data
        with open('./config.json', 'r') as f:
            data = json.load(f)
        
        for ele in data:
            name, depth, src = ele['section'], ele['depth'], ele['src']
            self.populate_section(name, depth)
            
            if ele['src'] is not None: # is File
                lang = ele['src'].split('.')
                lang = lang[len(lang) - 1]
                self.populate_file(name, lang, src, depth)

        return '\n'.join(self.content)

    def populate_section(self, caption, depth):
        """
        输出段落
        :param caption: 标题
        :param depth: 遍历深度
        :return: str
        """
        line = ''.join(['  ' * depth, '\\', 'sub' * depth, 'section{%s}' % caption])
        self.content.append(line)

    def populate_file(self, caption, suffix, path, depth):
        """
        输出文件
        :param caption: 标题
        :param suffix: 后缀名
        :param path: 相对路径
        :param depth: 遍历深度
        :return: list
        """
        if suffix.lower() in settings.INPUT_TYPE:
            line = ''.join(['  ' * depth, '\\input{%s}' % path])
            self.content.append(line)
        if suffix.lower() in settings.CODE_TYPE:
            line = ''.join(['  ' * depth, '\\inputminted{%s}{%s}' % (suffix, path)])
            self.content.append(line)
