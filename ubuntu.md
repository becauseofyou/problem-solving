
# 改源
https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/
选择自己的ubutnu版本
>```sudo gedit /etc/apt/sources.list ```

test
>```sudo apt-get clean```

>```sudo apt-get update```

>```sudo apt-get upgrade```

# 修改主机名
> ```sudo vi /etc/hosts```

>```sudo vi /etc/hostname```
>右上角->关于这台计算机->直接修改

# 增加管理员权限用户
>```sudo su```

>```adduser oier```

>```sudo vi /etc/sudoers ```

>```sudo userdel -r lenovo  -f```

# 安装vim chrome ffmpeg git
>```sudo apt-get purge vim-common```

>```sudo apt-get update```

>```sudo apt-get upgrade```

>```sudo apt install chromium-browser vim emacs ffmpeg git ```

# 更新文件英文目录
>```export LANG=en_US```

>```xdg-user-dirs-gtk-update```

# 安装monaco字体
>```cd /usr/share/fonts/truetype/```

>```sudo mkdir ttf-monaco```

>```cd ttf-monaco/```

>```sudo wget http://codybonney.com/files/fonts/Monaco_Linux.ttf```

>```sudo mkfontdir```

>```cd ..```

>```fc-cache```

# 放置常用软件，不容易被误删除
>```sudo sudo mkdir /home/software```

# 直播软件
```下载之后解压到/home/live```

# vscode
>官网下载deb包
>```sudo dpkg  -i code_1.24.1-1528912196_amd64.•••••••••••deb ```

# sublime text

>```wget -qO - https://download.sublimetext.com/sublimehq-pub.gpg | sudo apt-key add -```

>```sudo apt-get install apt-transport-https```

>```echo "deb https://download.sublimetext.com/ apt/stable/" | sudo tee /etc/apt/sources.list.d/sublime-text.list```

>```sudo apt-get update```

>```sudo apt-get install sublime-text```

# 搜狗拼音
>官网下载ｄｅｂ包
>```sudo dpkg -i sogoupinyin_2.2.0.0108_amd64.deb ```

>```sudo apt install -f```

>```sudo dpkg -i sogoupinyin_2.2.0.0108_amd64.deb ```

# 安装topcoder
>安装java applet启动器
>```sudo apt install icedtea-netx```
>下载topcoder所需文件
>```git clone https://github.com/xjoi/topcoder.git```
>外网访问慢可到内网直接下载[内网链接](http://210.33.19.102:8000/index.php/s/ZRM4rLKBPXTWF66)
>将文件资源移动到/home/software/topcoder下面
>```sudo mv topcoder/* /home/software/topcoder/*```
>```sudo vim /usr/share/applications/topcoder.desktop ```
填入如下内容
```
[Desktop Entry]
Version=1.0
Name=TopCoder
Exec=javaws https://community.topcoder.com/contest/arena/ContestAppletProd.jnlp
Terminal=false
Icon=/home/software/topcoder/topcoder.jpeg
Type=Application
Categories=Development
```
然后就可以在应用里面找到topcoder了
接下来打开topcoder，按照topcoder目录下的instruction文本配置一下


# vim
>插件安装 ```git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim```
>```sudo gedit ~/.vimrc```
填入

```
set cin nu rnu ts=4 sw=4 sts=4 et noswapfile nobackup
set so=100
set backspace=eol,start,indent
syntax on
set incsearch
set hlsearch
set ignorecase
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
    Plugin 'gmarik/Vundle.vim'
    Plugin 'vim-airline/vim-airline'
call vundle#end()
filetype plugin indent on
let g:airline#extensions#tabline#enabled = 1
set autochdir
nmap <tab> :bn <enter>
map<f4> :!g++ -std=c++11 % -Wall -o %<.target<cr> 
map<c-c> :! <cr>
map<f5> :!./%<.target < in<cr>
colorscheme desert
set cursorline
hi CursorLine   cterm=NONE ctermbg=238 ctermfg=none
```
```vim ~/.vimrc ```
```:PluginInstall``` 自动安装插件

# 系统设置

外观：开启工作区 自动隐藏侧边栏

[科学上网](https://blog.csdn.net/mynameis121/article/details/70191057)
